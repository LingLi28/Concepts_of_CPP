#include "file.h"

#include "filesystem.h"

size_t File::get_size() const { return this->content.get_size(); }

bool File::rename(std::string_view new_name) {

  
    
  if (!new_name.empty() && !name.empty() && static_cast<std::string>(new_name) != name){

    if (auto fs = filesystem.lock()) {
        // Call the rename function on the associated Filesystem
        if (fs->rename_file(name, new_name)) {
            name = std::string(new_name);  // Update the file name
            return true;
        }
    }

  }
  // TODO: Check that a filesystem actually exists, then rename it in the filesystem
  return false;
}

const std::string &File::get_name() const { return this->name; }

const FileContent &File::get_content() const { return this->content; }

// TODO file constructor


File::File(FileContent&& fileContent, std::string_view fileName)
    : content(std::move(fileContent)), name(fileName) {}
