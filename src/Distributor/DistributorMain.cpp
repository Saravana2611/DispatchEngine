#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

#include "DistributorMain.hpp"

static auto currentState = States::ECheckForNewWorker;

int  main()
{
    std::cout << "Distributor process starting" << std::endl;

    auto distributor = std::make_unique<Distributor>();

    while (true)
    {
        switch (currentState)
        {
            case States::ECheckForNewWorker:
                checkForNewWorker(distributor);
                break;
            case States::ECheckForNewRequest:
                checkForNewRequest(distributor);
                break;
            case States::ECheckForCompletedTask:
                checkForCompletedTask(distributor);
                break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "Distributor process ended" << std::endl;
    return 0;
}

void checkForNewWorker(const std::unique_ptr<Distributor>& distributor)
{
    std::cout << "Checking for new worker" << std::endl;

    distributor->checkForNewWorker();

    shiftToNextState(currentState, States::ECheckForNewRequest);
}

void checkForNewRequest(const std::unique_ptr<Distributor>& distributor)
{
    std::cout << "Checking for new request" << std::endl;
    shiftToNextState(currentState, States::ECheckForCompletedTask);
}

void checkForCompletedTask(const std::unique_ptr<Distributor>& distributor)
{
    std::cout << "Checking for Completed Tasks" << std::endl;
    shiftToNextState(currentState, States::ECheckForNewWorker);
}

void shiftToNextState(States& currentState, const States& nextState)
{
    currentState = nextState;
}