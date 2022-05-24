#include <compiler.h>
#include <rpc/server.h>
#include <rpc/this_session.h>
#include <rpc/this_server.h>
#include <functional>

int main() {
    Compiler compiler;
    rpc::server server(8080);


    server.bind("compile", [&compiler](Payload payload){ return compiler.compile(payload);});

    // A session represents a client connection
    // Exiting completes all ongoing reads and writes first
//    server.bind("exit", []() {
//        rpc::this_session().post_exit(); // post exit to the queue
//    });

    // Gracefully stops all sessions on the server
//    server.bind("stop_server", []() {
//        rpc::this_server().stop();
//    });

    server.run();
    return 0;
}