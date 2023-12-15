#include "document.h"


Document::Document(FileContent &&content) : File{std::move(content)} {}

// TODO implement get_type function

size_t Document::get_raw_size() const {
  // TODO get the document size
  return 0;
}

unsigned Document::get_character_count() const {
  // TODO count non whitespace characters
  return 0;
}

// TODO implement content update function
