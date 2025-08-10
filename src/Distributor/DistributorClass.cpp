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

    std::string buffer(BUFFER_SIZE, '\0');
    auto noOfBytesRead = read(registerFdRead_, &buffer[0], buffer.size());
    
    if (noOfBytesRead <= 0)
    {
        std::cout << "Buffer is empty" << std::endl;
        return;    
    }

    buffer.resize(noOfBytesRead);
    std::cout << "Buffer = " << Buffer;
    if (not validateRegisterMsg(buffer))
    {
        std::cout << "Register Message Validation Failed" << std::endl;
        return;
    }

}

bool Distributor::validateRegisterMsg(std::string buffer)
{
    std::string request = buffer.substr(0, buffer.find(" "));
    return request == "REGISTER";
}

Distributor::~Distributor()
{
    unlink(registerFifo);
    close(registerFdRead_);
}