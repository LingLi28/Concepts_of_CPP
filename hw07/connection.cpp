// connection.cpp
#include "connection.h"
#include <cstring>
#include <iostream>
#include <vector>

namespace net {

Connection::Connection(FileDescriptor&& fd) : fd_(std::move(fd)) {}

ssize_t send(int fd, std::span<const char> data) {
    return ::send(fd, data.data(), data.size(), 0);
}

ssize_t receive(int fd, std::span<char> buf) {
    return ::recv(fd, buf.data(), buf.size(), 0);
}

void Connection::send(std::string_view data) const {
    net::send(fd_.unwrap(), std::span<const char>(data.data(), data.size()));

}

void Connection::send(std::istream& data) const {
    std::vector<char> buffer(1024);
    while (data.read(buffer.data(), static_cast<long>(buffer.size()))) {
        net::send(fd_.unwrap(), std::span<const char>(buffer.data(), data.gcount()));
    }
    if (data.gcount() > 0) {
        net::send(fd_.unwrap(), std::span<const char>(buffer.data(), data.gcount()));
    }
}

ssize_t Connection::receive(std::ostream& stream) const {
    std::vector<char> buffer(128);
    ssize_t bytesRead = net::receive(fd_.unwrap(), buffer);
    if (bytesRead > 0) {
        stream.write(buffer.data(), bytesRead);
    }
    return bytesRead;
}

ssize_t Connection::receive_all(std::ostream& stream) const {
    

    ssize_t totalBytesRead = 0;
    ssize_t bytesRead;
    
    do {
        bytesRead = receive(stream);
        totalBytesRead += bytesRead;
    } while (bytesRead > 0);

    return totalBytesRead;
}

int Connection::fd() const {
    return fd_.unwrap();
}

} // namespace net
