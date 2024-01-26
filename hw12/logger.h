#pragma once

#include <fstream>
#include <string>

enum class status {
    added,
    changed,
    removed,
};

class Logger {
public:
    /*
     * Create a new logger, that writes to the given file name.
     *
     * The file should start with:
     * ```
     * Commencing logging for directory: <current_dir>
     * Current time is: <time>
     * ```
     *
     * If the file already exists, back the current file up (by appending _old to the filename).
     * If a backup file already exists, it will be overwritten (Note for Windows users:
     * remove the backup file, Linux and MacOs should handle overwriting just fine)
     */
    Logger(const std::string& filename = "log.txt");

    void log(const std::string& path, status what);

private:
    std::ofstream file;
};
