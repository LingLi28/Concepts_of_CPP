#include "filesystem.h"

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <iostream>

Filesystem::Filesystem() {}

bool Filesystem::register_file(const std::string &name,
                               std::shared_ptr<File> file) {

  if (name.empty() || file == nullptr) {
        return false;
    }

  // Check if the file is not already registered in another filesystem
  if (file->filesystem.lock() != nullptr && file->filesystem.lock() != shared_from_this()) {
      return false;
  }

  // Check if the name already exists
  auto it = files.find(name);
  if (it != files.end()) {
      return false;
  }

  // TODO: Do sanity checks first! Is that actually a good name, is the pointer set,
  //       does a file with that name already exists? Anything else to check here?

  // Creater a shared pointer to the this object
  
  auto thisptr = this->shared_from_this();

  // TODO: Check if the file already has a filesystem, if so, it may only be
  //       the same as this one, not another one!

  file->filesystem = std::move(thisptr);
  // file->filesystem = shared_from_this();
  file->name = name;

  // TODO: Now actually store it in the filesystem
  files[name] = file;
  // std::cout << name << " created" << std::endl;

  // for (auto & item : files){
  //   std::cout << item.first << std::endl;
  // }

  return true;
  
}

bool Filesystem::remove_file(std::string_view name) {
  // TODO: Remove file from the filesystem, return true if successful, false otherwhise.
  //       false may indicate multple different reasons for failure, which is not impotant
  if (name.empty()) {
        return false;
    }

    auto it = files.find(std::string(name));
    if (it != files.end()) {
        files.erase(it);
        return true;
    }

    return false;
}

bool Filesystem::rename_file(std::string_view source, std::string_view dest) {
  // TODO: Check filesystem for the source and dest files, if it's possible to rename
  //       the source file, then update the filesystem
  if (source.empty() || dest.empty() || source == dest || this == nullptr) {
        return false;
    }

    auto itSource = files.find(std::string(source));
    auto itDest = files.find(std::string(dest));

    if (itSource != files.end() && itDest == files.end()) {
        std::shared_ptr<File> sourceFile = itSource->second;
        sourceFile->name = std::string(dest); 
        files[std::string(dest)] = sourceFile;
        files.erase(itSource);
        return true;
    }
    std::cout << "problem" << std::endl;

    return false;
}

std::shared_ptr<File> Filesystem::get_file(std::string_view name) const {
  // TODO: Check the filesystem for the given file, return it if you found it,
  //       else just return nothing
  auto it = files.find(std::string(name));
  if (it != files.end()) {
      return it->second;
  }
  return nullptr;
}

size_t Filesystem::get_file_count() const {
  // TODO: how many files have you got?
  return files.size();
}

size_t Filesystem::in_use() const {
  // TODO: sum up all real file sizes
  size_t totalSize = 0;
    for (const auto& pair : files) {
        totalSize += pair.second->get_size();
    }
    return totalSize;
}

// convenience function so you can see what files are stored
std::string Filesystem::file_overview(bool sort_by_size) {
  std::ostringstream output;
  // this function is not tested, but it may help you when debugging.

  output << "files in filesystem: " << std::endl;

  for (auto & entry : files) {
      // TODO: fix printing name, type and size
      output << entry.first  << std::endl;
      std::cout << "get_name" << entry.second->get_name()  << std::endl;
  }
  return std::move(output).str();
}

std::vector<std::shared_ptr<File>>
Filesystem::files_in_size_range(size_t max, size_t min) const {
  // TODO: find the matching files and return them
  std::vector<std::shared_ptr<File>> result;

    for (const auto& pair : files) {
        size_t fileSize = pair.second->get_size();
        if (fileSize >= min && fileSize <= max) {
            result.push_back(pair.second);
        }
    }

    return result;
}
