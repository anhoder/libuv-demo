#include "echo_server.h"

uv_loop_t* g_loop;
uv_tcp_t g_server;

int main(int argc, char* argv[]) {

    printf("libuv_version: %d.%d.%d, %s\n", UV_VERSION_MAJOR, UV_VERSION_MINOR, UV_VERSION_PATCH, UV_VERSION_SUFFIX);

    g_loop = uv_default_loop();

    struct sockaddr_in addr; // tcp绑定的地址
    uv_ip4_addr("0.0.0.0", PORT, &addr);

    uv_tcp_init(g_loop, &g_server); // init server
    uv_tcp_bind(&g_server, (const struct sockaddr*) &addr, 0); // bind address to server

    int result = uv_listen((uv_stream_t*)&g_server, DEFAULT_BACKLOG, new_conn_callback);
    if (result) {
        fprintf(stderr, "listen err: %s\n", uv_strerror(result));
        return 1;
    }

    printf("The echo server have been started\n");
    return uv_run(g_loop, UV_RUN_DEFAULT);
}

// 新建连接回调
void new_conn_callback(uv_stream_t* server, int status) {
    assert(server == (uv_stream_t*)&g_server);
    if (status < 0) {
        fprintf(stderr, "new connection err: %s\n", uv_strerror(status));

        return;
    }

    uv_tcp_t* client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(g_loop, client);

    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        printf("New client connected\n");
        uv_read_start((uv_stream_t*) client, alloc_callback, read_callback);
    } else {
        uv_close((uv_handle_t *) client, close_callback);
    }
}

// tcp数据放到buf上的回调
void alloc_callback(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
    *buf = uv_buf_init(malloc(suggested_size), suggested_size);
}

static const char* write_prefix = "You write: ";

// 读取tcp数据后的回调
void read_callback(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {
    if (nread > 0) {
        size_t prefix_len = strlen(write_prefix);
        char* write_content = (char*)malloc(sizeof(char) * (prefix_len + nread + 1));
        strcpy(write_content, write_prefix);
        strcat(write_content, buf->base);

        uv_buf_t* write_buf = (uv_buf_t*)malloc(sizeof(uv_buf_t));
        *write_buf = uv_buf_init(write_content, prefix_len + nread);

        uv_write_t* write = (uv_write_t*) malloc(sizeof(uv_write_t));
        uv_write(write, stream, write_buf, 1, write_callback);

        free(write_content); // 释放内存
    }

    // 释放alloc_callback中的内存
    if (buf->base) {
        free(buf->base);
    }
}

// 写数据后的回调
void write_callback(uv_write_t* req, int status) {
    if (status != 0) {
        fprintf(stderr, "write err: %s\n", uv_strerror(status));
    }

    // 释放read_callback中 write
    if (req->data) {
        free(req->data);
    }
    free(req);
}

// 关闭连接时的回调
void close_callback(uv_handle_t* handle) {
    printf("closed\n");
    free(handle);
}

