#include "client.h"

namespace net {

Client::Client() : clientSocket_() {}

Connection Client::connect(const std::string& destination, uint16_t port) {
    return clientSocket_.connect(destination, port);
}

Connection Client::connect(uint16_t port) {
    return clientSocket_.connect(port);
}

} // namespace net
