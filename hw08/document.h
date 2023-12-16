#pragma once

#include "file.h"

/**
 * Derived class for text documents.
 */
class Document : public File {
public:
  Document(FileContent &&content = {});
  // TODO: Implement inherited member functions
  std::string_view get_type() const override;
  size_t get_raw_size() const override;

  /**
   * Return the number of non-whitespace characters in the file content.
   */
  unsigned get_character_count() const;

  void update(FileContent &&new_content);
};
