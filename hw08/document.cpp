#include "document.h"


Document::Document(FileContent &&content) : File{std::move(content)} {}

// TODO implement get_type function
std::string_view Document::get_type() const {
    return "DOC";
}

size_t Document::get_raw_size() const {
  // TODO get the document size
  return content.get_size();
}

unsigned Document::get_character_count() const {
  // TODO count non whitespace characters

  const std::string& contentStr = *content.get();
  size_t count = 0;

  for (char c : contentStr) {
      if (c != ' ' && c != '\n' && c != '\t') {
          count++;
      }
  }

  return count;
  
}

// TODO implement content update function
void Document::update(FileContent &&new_content) {
  content = std::move(new_content);
}
