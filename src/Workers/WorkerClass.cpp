#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#include "WorkerClass.hpp"
#include "Utility.hpp"

const char* registerFifo = "/tmp/WorkerRegister";

Worker::Worker()
{
    std::cout<< "Worker constructor called" << std::endl;
}

void Worker::registerAsWorker()
{
    uid_ = generateUid();

    std::cout << "Registering as Worker with uid: " << uid_ << std::endl;

    // Create Register fifo
    mkfifo(registerFifo, 0666);
    int registerFdWrite = open(registerFifo, O_WRONLY);
    
    char buffer[BUFFER_SIZE];
    std::string msg = "REGISTER " + uid_;
    strncpy(buffer, msg.c_str(), BUFFER_SIZE);
    write(registerFdWrite, buffer, BUFFER_SIZE);

    close(registerFdWrite);
}