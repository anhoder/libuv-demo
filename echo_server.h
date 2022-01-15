//
// Created by anhoder on 2022/1/15.
//

#ifndef LIBUV_TEST_ECHO_SERVER_H
#define LIBUV_TEST_ECHO_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include <assert.h>

#define PORT 32000
#define DEFAULT_BACKLOG 511

void new_conn_callback(uv_stream_t* server, int status);
void alloc_callback(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
void read_callback(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf);
void write_callback(uv_write_t* req, int status);
void close_callback(uv_handle_t* handle);

#endif //LIBUV_TEST_ECHO_SERVER_H

