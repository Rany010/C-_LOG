#include <iostream>
#include <thread>
#include <vector>
#include "mdlog.h"

void logMessage(int threadId) {
    for (int i = 0; i < 1000; i++) {
        MDINFO("main", "Hello from thread " + std::to_string(threadId));
    }
}

int main() 
{
    const int numThreads = 50;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(logMessage, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}