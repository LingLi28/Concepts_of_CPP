#pragma once

#include "file.h"

/**
 * Represents audio files.
 */
class Audio : public File {
public:
  Audio(FileContent &&content = {}, unsigned duration = 0);

  // TODO: Implement inherited member functions
  std::string_view get_type() const override;
  size_t get_raw_size() const override;
  /**
   * Get the duration of this audio file.
   */
  unsigned get_duration();

  void update(FileContent &&new_content, unsigned new_duration);
private:
  unsigned duration;
};
