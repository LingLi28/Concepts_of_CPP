#include "monitor.h"

#include <thread>



FileMonitor::FileMonitor(const std::string &targetpath,
                         std::chrono::milliseconds interval,
                         const std::string &logfilename)
    : targetPath_(targetpath)
    , logger{logfilename}
    , interval{interval}
{
    for (const auto& entry : std::filesystem::directory_iterator(targetpath)){
        if (std::filesystem::is_regular_file(entry.path()) || std::filesystem::is_directory(entry.path()))
{
    const auto & filePath = entry.path();
    std::filesystem::file_time_type lastModified = std::filesystem::last_write_time(filePath);
    fileMap[filePath] = lastModified;
    std::cout << filePath << "\n";
}    }
    // TODO: Initialize a mapping for all files in the target path
}

void FileMonitor::checkForChanges() {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(targetPath_))
{
    if (std::filesystem::is_regular_file(entry.path()) || std::filesystem::is_directory(entry.path())) {
    const auto & filePath = entry.path();
    const auto lastModified = std::filesystem::last_write_time(entry.path());
    auto it = fileMap.find(filePath);

    if(it == fileMap.end()){
        fileMap[filePath] = lastModified;
        logger.log(filePath, status::added);
        std::cout<< "New file:" << filePath<< std::endl;

    } else if(lastModified > it->second) {
        it->second = lastModified;
        logger.log(filePath, status::changed);
        std::cout<< "Modified file: " << filePath << std::endl;
        }
    }
}

    auto it = fileMap.begin();
    while (it != fileMap.end()) {
        if (!std::filesystem::exists(it->first)) {
            logger.log(it->first, status::removed);
            std::cout << "Deleted file: " << it->first << std::endl;
            it = fileMap.erase(it);
        } else {
            ++it;
        }
    }
}

// Monitor the targetpath for changes and pass information to the logger in case of differences
void FileMonitor::start(std::chrono::seconds timeout) {
    // TODO: Monitor the system for the given amount of time.
    // Every given interval, check for modifications to the files and log it
    auto startTime = std::chrono::system_clock::now();
    auto endTime = startTime + timeout;
    while(std::chrono::system_clock::now() < endTime) {
        checkForChanges();
        std::this_thread::sleep_for(interval);
    }


}
