// socket.cpp
#include "socket.h"
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>
#include <unistd.h>
#include <iostream>

namespace net {

bool is_listening(int fd) {
    int optval;
    socklen_t optlen = sizeof(optval);

    if (getsockopt(fd, SOL_SOCKET, SO_ACCEPTCONN, &optval, &optlen) == -1) {
        // Error handling: You may want to throw an exception or handle it differently.
        return false;
    }

    return optval != 0;
}

Socket::Socket()  {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        throw std::runtime_error("Failed to create socket");
    }
    fd_ = FileDescriptor(sockfd);
    int optval = -1;
    if (setsockopt(fd_.unwrap(), SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        std::cerr << 'failed to set SO_REUSEADDR' << std::endl;
        close(fd_.unwrap());
    }
}


void Socket::listen(uint16_t port) const {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (::bind(fd_.unwrap(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
        // Error handling: You may want to throw an exception or handle it differently.
        throw std::runtime_error("Failed to bind socket");
    }

    if (::listen(fd_.unwrap(), 4096) == -1) {
        // Error handling: You may want to throw an exception or handle it differently.
        throw std::runtime_error("Failed to listen on socket");
    }
}

Connection Socket::accept() const {
    if (!is_listening(fd_.unwrap())) {
        // Error handling: You may want to throw an exception or handle it differently.
        throw std::runtime_error("Socket is not listening");
    }

    int client_fd = ::accept(fd_.unwrap(), nullptr, nullptr);
    if (client_fd == -1) {
        // Error handling: You may want to throw an exception or handle it differently.
        throw std::runtime_error("Failed to accept connection");
    }

    return Connection(FileDescriptor(client_fd));
}

Connection Socket::connect(const std::string destination, uint16_t port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (destination == "localhost") {
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    } else {
        addr.sin_addr.s_addr = inet_addr(destination.c_str());
    }

    if (addr.sin_addr.s_addr == INADDR_NONE) {
        struct hostent* host = gethostbyname(destination.c_str());
        if (host == nullptr) {
            throw std::runtime_error("Host resolution failed");
        }
        addr.sin_addr = *reinterpret_cast<in_addr*>(host->h_addr);

    }

    if (::connect(fd_.unwrap(), (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        // Error handling: You may want to throw an exception or handle it differently.
        throw std::runtime_error("Failed to connect to destination");
    }

    return Connection(std::move(fd_));
}

Connection Socket::connect(uint16_t port) {
    return connect("localhost", port);
}

int Socket::fd() const {
    return fd_.unwrap();
}

} // namespace net
