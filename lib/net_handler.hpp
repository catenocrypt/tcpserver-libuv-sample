#pragma once

#include "uv_socket.hpp"

#include <memory>
#include <string>
#include <thread>

namespace sample
{
    class BaseApp; // forward

    class NetHandler: public IUvSocket
    {
    public:
        NetHandler(BaseApp* app_in);
        int start();
        // return actual listen port
        int startWithListen(int port_in, int tryNextPorts_in);
        int stop();
        void onConnect(uv_connect_t* req, int status) { }
        void onRead(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) { }
        void onWrite(uv_write_t* req, int status) { }
        void onNewConnection(uv_stream_t* server, int status);
        void onClose(uv_handle_t* handle) { }
        static std::string getRemoteAddress(const uv_tcp_t* socket_in);

    private:
        int startUvLoop();
        int stopUvLoop();
        int doBindAndListen(int port_in);
        int doListen(int port_in, int tryNextPorts_in);
        int doBgThread();
        static void on_new_connection(uv_stream_t* server, int status);
        static void on_close(uv_handle_t* handle);
        static void on_walk(uv_handle_t* handle, void* arg);

    private:
        BaseApp* myApp;
        uv_async_t* myUvAsync;
        std::thread myBgThread;
        bool myBgThreadStop;
    };
}