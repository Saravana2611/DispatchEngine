#include <iostream>
#include <unistd.h>
#include <chrono>

std::string generateUid()
{
    int pid = getpid();
    auto time = std::chrono::system_clock::now();
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(
        time.time_since_epoch()).count();

    return std::to_string(pid) + "_" + std::to_string(sec);
}