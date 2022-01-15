cmake_minimum_required(VERSION 3.21)
project(libuv_test C)

set(CMAKE_C_STANDARD 99)

include(CMakePackageConfigHelpers)
include(CMakeDependentOption)
include(CheckCCompilerFlag)
include(GNUInstallDirs)
include(CTest)

set(uv_dir "libuv")

set(uv_sources
        ${uv_dir}/src/fs-poll.c
        ${uv_dir}/src/idna.c
        ${uv_dir}/src/inet.c
        ${uv_dir}/src/random.c
        ${uv_dir}/src/strscpy.c
        ${uv_dir}/src/threadpool.c
        ${uv_dir}/src/timer.c
        ${uv_dir}/src/uv-common.c
        ${uv_dir}/src/uv-data-getter-setters.c
        ${uv_dir}/src/version.c
        ${uv_dir}/src/unix/async.c
        ${uv_dir}/src/unix/core.c
        ${uv_dir}/src/unix/dl.c
        ${uv_dir}/src/unix/fs.c
        ${uv_dir}/src/unix/getaddrinfo.c
        ${uv_dir}/src/unix/getnameinfo.c
        ${uv_dir}/src/unix/loop-watcher.c
        ${uv_dir}/src/unix/loop.c
        ${uv_dir}/src/unix/pipe.c
        ${uv_dir}/src/unix/poll.c
        ${uv_dir}/src/unix/process.c
        ${uv_dir}/src/unix/random-devurandom.c
        ${uv_dir}/src/unix/signal.c
        ${uv_dir}/src/unix/stream.c
        ${uv_dir}/src/unix/tcp.c
        ${uv_dir}/src/unix/thread.c
        ${uv_dir}/src/unix/tty.c
        ${uv_dir}/src/unix/udp.c
        ${uv_dir}/src/unix/proctitle.c
        ${uv_dir}/src/unix/bsd-ifaddrs.c
        ${uv_dir}/src/unix/kqueue.c
        ${uv_dir}/src/unix/random-getentropy.c
        ${uv_dir}/src/unix/darwin-proctitle.c
        ${uv_dir}/src/unix/darwin.c
        ${uv_dir}/src/unix/fsevents.c)

include_directories(${uv_dir}/include ${uv_dir}/src)
add_library(libuv OBJECT ${uv_sources})

add_executable(libuv_test
#        first.c
        echo_server.c
        echo_server.h)
target_link_libraries(libuv_test libuv)