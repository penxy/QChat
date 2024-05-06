#include "Server.h"

int main(int argc, char *argv[]) {
    Server *server = new Server();
    server->Run();
    delete server;
    return 0;
}