#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex myMutex;
condition_variable var;

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
