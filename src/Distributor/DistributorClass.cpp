#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "DistributorClass.hpp"

const char* registerFifo = "/tmp/WorkerRegister";

Distributor::Distributor()
{
    std::cout << "calling constructor for Distributor" << std::endl;
    
    // Create Register fifo
    mkfifo(registerFifo, 0666);
    registerFdRead_ = open(registerFifo, O_RDONLY | O_NONBLOCK);

    std::cout << "Constructor Done" << std::endl;
}

void Distributor::checkForNewWorker()
{
    std::cout << "calling checkForNewWorker" << std::endl;

    char buffer[BUFFER_SIZE];
    auto noOfBytesRead = read(registerFdRead_, buffer, sizeof(buffer));
    
    if (noOfBytesRead > 0)
    {
        std::cout << buffer << std::endl;
    }
    else
    {
        std::cout << "buffer is empty" << std::endl;
    }
}

Distributor::~Distributor()
{
    unlink(registerFifo);
    close(registerFdRead_);
}