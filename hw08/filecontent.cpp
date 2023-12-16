// TODO implement constructors

// TODO implement member functions

#include "filecontent.h"

FileContent::FileContent(const std::string& content)
    : content(std::make_shared<std::string>(content)) {}

FileContent::FileContent(std::string&& content)
    : content(std::make_shared<std::string>(std::move(content))) {}

FileContent::FileContent(const char* content)
    : content(std::make_shared<std::string>(content)) {}

size_t FileContent::get_size() const {
    if (content) {
        return content->size();
    }
    return 0;
}

std::shared_ptr<const std::string> FileContent::get() const {
    return content;
}

