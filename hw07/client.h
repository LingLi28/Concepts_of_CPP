#pragma once

#include "socket.h"
#include "connection.h"
#include <string>

namespace net {

class Client {
public:
    Client();
    ~Client() = default;

    Connection connect(const std::string& destination, uint16_t port);
    Connection connect(uint16_t port);
    
private:
    Socket clientSocket_;
};

} // namespace net


/**
 * TCP socket client. Can connect to a server given a destination IP address and a port.
 *
 * TODO:
 * - A client must be default constructible
 * - A client must have a function `connect` which connects on a given port on the localhost  
 * - A client must have a function `connect` which connects to a given destination address and port
 */

