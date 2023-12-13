#include "server.h"


namespace net {

Server::Server(uint16_t port) : serverSocket_() {
    serverSocket_.listen(port);
}

Connection Server::accept() const {
    return serverSocket_.accept();
}

} // namespace net
