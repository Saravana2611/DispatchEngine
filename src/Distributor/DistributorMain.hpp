#include "DistributorClass.hpp"

enum States
{
    ECheckForNewWorker,
    ECheckForNewRequest,
    ECheckForCompletedTask  
};

int main();
void checkForNewWorker(const std::unique_ptr<Distributor>& distributor);
void checkForNewRequest(const std::unique_ptr<Distributor>& distributor);
void checkForCompletedTask(const std::unique_ptr<Distributor>& distributor);
void shiftToNextState(States& currentState, const States& nextState);