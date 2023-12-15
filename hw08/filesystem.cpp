#include "filesystem.h"

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>

Filesystem::Filesystem() {}

bool Filesystem::register_file(const std::string &name,
                               std::shared_ptr<File> file) {
  // TODO: Do sanity checks first! Is that actually a good name, is the pointer set,
  //       does a file with that name already exists? Anything else to check here?

  // Creater a shared pointer to the this object
  auto thisptr = this->shared_from_this();

  // TODO: Check if the file already has a filesystem, if so, it may only be
  //       the same as this one, not another one!

  file->filesystem = std::move(thisptr);

  // TODO: Now actually store it in the filesystem
  return false;
}

bool Filesystem::remove_file(std::string_view name) {
  // TODO: Remove file from the filesystem, return true if successful, false otherwhise.
  //       false may indicate multple different reasons for failure, which is not impotant
  return false;
}

bool Filesystem::rename_file(std::string_view source, std::string_view dest) {
  // TODO: Check filesystem for the source and dest files, if it's possible to rename
  //       the source file, then update the filesystem
}

std::shared_ptr<File> Filesystem::get_file(std::string_view name) const {
  // TODO: Check the filesystem for the given file, return it if you found it,
  //       else just return nothing
  return nullptr;
}

size_t Filesystem::get_file_count() const {
  // TODO: how many files have you got?
  return 0;
}

size_t Filesystem::in_use() const {
  // TODO: sum up all real file sizes
  return 0;
}

// convenience function so you can see what files are stored
std::string Filesystem::file_overview(bool sort_by_size) {
  std::ostringstream output;
  // this function is not tested, but it may help you when debugging.

  output << "files in filesystem: " << std::endl;

  // for (auto&& entry : this->files) {
  //     // TODO: fix printing name, type and size
  //     output << entry.get_name << std::endl;
  // }
  return std::move(output).str();
}

std::vector<std::shared_ptr<File>>
Filesystem::files_in_size_range(size_t max, size_t min) const {
  // TODO: find the matching files and return them
  return {};
}
