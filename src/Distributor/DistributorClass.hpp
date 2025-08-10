#include <iostream>
#include <vector>

const int BUFFER_SIZE = 100;

enum WorkerStatus
{
    EBusy,
    EIdle,
    EDead
};

struct Worker
{
    std::string type;
    int uuid;
    WorkerStatus status;
};

class Distributor
{
    public:
        Distributor();
        ~Distributor();
        void checkForNewWorker();
    
    private:
        std::vector<Worker> workersDetails;
        int registerFdRead_;
};