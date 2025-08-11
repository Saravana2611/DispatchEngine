#include <iostream>
#include <vector>
#include <map>
#include <queue>

const int BUFFER_SIZE = 100;

enum EWorkerStatus
{
    EBusy,
    EIdle,
    EDead
};

struct Worker
{
    std::string uid;
    std::string readFifo, writeFifo;
    EWorkerStatus status;
};

class Distributor
{
    public:
        Distributor();
        ~Distributor();
        void checkForNewWorker();
    
    private:
        bool validateRegisterMsg(const std::string& buffer);
        std::string getWorkerUid(const std::string& buffer);
        void registerWorker(const std::string& workerUid);
        
        int registerFdRead_;
        std::map<std::string, Worker> workersDetails_;
        std::queue<Worker> idleQueue_;
};