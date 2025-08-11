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
    std::cout << "Buffer = " << buffer << std::endl;
    if (not validateRegisterMsg(buffer))
    {
        std::cout << "Register Message Validation Failed" << std::endl;
        return;
    }

    std::string workerUid = getWorkerUid(buffer);
    registerWorker(workerUid);
}

bool Distributor::validateRegisterMsg(const std::string& buffer)
{
    std::string request = buffer.substr(0, buffer.find(" "));
    std::string uid = buffer.substr(buffer.find(" ") + 1, std::distance(buffer.begin(), buffer.end()));
    return (request == "REGISTER") and (uid.size() > 0);
}

std::string Distributor::getWorkerUid(const std::string& buffer)
{
    return buffer.substr(buffer.find(" ") + 1, std::distance(buffer.begin(), buffer.end()));
}

void Distributor::registerWorker(const std::string& workerUid)
{
    Worker worker;
    worker.uid = workerUid;
    worker.readFifo = "/tmp/DispatchEngine/WorkerComm/read_" + workerUid;
    worker.writeFifo = "/tmp/DispatchEngine/WorkerComm/work_" + workerUid;
    worker.status = EWorkerStatus::EIdle;
    workersDetails_[workerUid] = worker;

    idleQueue_.push(worker);
}

Distributor::~Distributor()
{
    unlink(registerFifo);
    close(registerFdRead_);
}