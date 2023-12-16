#include "video.h"

Video::Video(FileContent &&content, resolution_t resolution, double duration)
    : File{std::move(content)}, resolution{resolution}, duration{duration} {}

// TODO implement get_type function
std::string_view Video::get_type() const {
  return "VID";
}

size_t Video::get_raw_size() const {
    // Assuming 8-bit RGB video at 30 FPS
    return static_cast<size_t>(3 * resolution[0] * resolution[1] * int(30 * duration));
}

auto Video::get_resolution() const -> resolution_t { return this->resolution; }

double Video::get_duration() const { return this->duration; }

// TODO implement content update function

void Video::update(FileContent &&new_content, resolution_t new_resolution, double new_duration) {
    // Update content, resolution, and duration
    content = std::move(new_content);
    resolution = new_resolution;
    duration = new_duration;
}
