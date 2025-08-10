#include <iostream>
#include <memory>

#include "WorkerMain.hpp"

static auto currentState = States::ECheckForTask;
int main()
{
    auto worker = std::make_unique<Worker>();

    worker->registerAsWorker();
    return 0;
}