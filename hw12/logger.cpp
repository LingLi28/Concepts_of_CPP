#include "logger.h"

#include <ctime>
#include <chrono>
#include <iostream>


Logger::Logger(const std::string &filename){
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::filesystem::path path_cur = std::filesystem::current_path();
    std::filesystem::path path_file = path_cur/filename;

    if(std::filesystem::exists(path_file)) {
        // Backup the existing file
        std::cout << "log file exits, backup and log a new one.\n";
        std::filesystem::path backupFilePath = path_file;
        backupFilePath += "_old";

        //Remove any existing backupfile
        std::filesystem::remove(backupFilePath);

        //Rename the current file to the backup file
        std::filesystem::rename(path_file, backupFilePath);
    }

    file = std::ofstream(filename);

    file << "Commencing logging for directory: "
         << "TODO: insert current path here.."
         << std::endl
         << "Current time is: "
         << std::ctime(&time)
         << std::endl;
}

void Logger::log(const std::string &path, status what) {
    if (not file.is_open()) {
        throw std::runtime_error("File could not be opened!");
    }

    switch (what) {
    case status::added :
        file << "+ File was added:    " << path << std::endl;
        break;
    case status::changed :
        file << "! File was modified: " << path << std::endl;
        break;
    case status::removed :
        file << "~ File was deleted:  " << path << std::endl;
        break;
    default:
        file << "? Error! Unknown file status detected for: " << path << std::endl;
        break;
    }
}
