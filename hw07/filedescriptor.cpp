#include "filedescriptor.h"
#include <utility>

// TODO Implement the methods of the FileDescriptor class as given in the filedescriptor.h header.

namespace net {
	FileDescriptor::FileDescriptor() : fd_() {}
	
	FileDescriptor::FileDescriptor(int fd){
		fd_ = fd;
	}

	FileDescriptor::~FileDescriptor() {
    if (fd_.has_value() and this->fd_.value() != -1) {
        ::close(*fd_);
    	}
	}


	// Move assignment operator
FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) noexcept {
    if (this != &other) {
        // Close existing file descriptor (if present)
        if (fd_.has_value()) {
            ::close(*fd_);
        }
        // Move file descriptor from 'other' and reset it
        fd_ = std::exchange(other.fd_, {});
    }
    return *this;
}


// FileDescriptor& FileDescriptor::operator=(const FileDescriptor& other) {
//     if (this != &other) {
//         // Close existing file descriptor (if present)
//         if (fd_.has_value()) {
//             ::close(*fd_);
//         }
//         // Duplicate the file descriptor
//         fd_ = other.fd_;
//     }
//     return *this;
// }

// Move constructor
FileDescriptor::FileDescriptor(FileDescriptor&& other) noexcept : fd_(std::exchange(other.fd_, {})) {
     other.fd_ = -1;  // Reset the moved-from object
}
	int FileDescriptor::unwrap() const {
		return fd_.value_or(-1);
	}

// FileDescriptor::FileDescriptor(const FileDescriptor& other) : fd_(other.fd_) {
//     // Duplicate the file descriptor (you may want to use dup or dup2)
// }

	
// bool FileDescriptor::isValid() const { 
//  if (fd_.has_value() and this->fd_.value() != -1) {
//  	return true;
//  } else {
//  	return false;
//  }
// }

// Close the file descriptor
void FileDescriptor::close() {
    if (fd_.has_value() and fd_.value() != -1) {
        ::close(fd_.value());
        fd_ = -1;
    }
}

}