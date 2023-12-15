#include "audio.h"

Audio::Audio(FileContent &&content, unsigned duration)
    : File{std::move(content)}, duration{duration} {}

// TODO implement get_type function

size_t Audio::get_raw_size() const {
  return 0;  // TODO calculate raw size
}

unsigned Audio::get_duration() { return this->duration; }

// TODO implement content update function
