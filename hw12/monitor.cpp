#include "monitor.h"

#include <thread>



FileMonitor::FileMonitor(const std::string &targetpath,
                         std::chrono::milliseconds interval,
                         const std::string &logfilename)
    : logger{logfilename}
    , interval{interval}
{
    // TODO: Initialize a mapping for all files in the target path
}

// Monitor the targetpath for changes and pass information to the logger in case of differences
void FileMonitor::start(std::chrono::seconds timeout) {
    // TODO: Monitor the system for the given amount of time.
    // Every given interval, check for modifications to the files and log it
}
