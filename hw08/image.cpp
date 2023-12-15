#include "image.h"

Image::Image(FileContent &&content, resolution_t res)
    : File{std::move(content)}, resolution{res} {}

// TODO implement get_type function

size_t Image::get_raw_size() const {
  // TODO calculate raw size
  return 0;
}

auto Image::get_resolution() const -> resolution_t { return this->resolution; }

// TODO implement content update function
