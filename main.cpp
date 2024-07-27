#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <thread>
#include <mutex>

std::recursive_mutex mtx;

std::vector<int> store(100, -1);

int factorial(const int& num) {
    if (num == 0) {
        return 1;
    }
    if (num == 1) {
        return 1;
    }
    if (-1 != store[num]) {
        return store[num];
    }
    mtx.lock();
    int res = store[num] = num * factorial(num - 1);
    mtx.unlock();
    return res;
}

void factorialWrapper(const int& num, std::ostringstream& stream) {
    auto start = std::chrono::high_resolution_clock::now();
    
    stream << "fibo (" << num << ") = " << factorial(num) << std::endl;
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    
    stream << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
}

int main() {
    store[1] = 1;

    int num1 = 12;
    int num2 = 10;

    std::ostringstream os1;
    std::ostringstream os2;

    std::thread t1(factorialWrapper, std::ref(num1), std::ref(os1));
    std::thread t2(factorialWrapper, std::ref(num2), std::ref(os2));

    t1.join();
    t2.join();

    std::cout << os1.str() << std::endl;
    std::cout << os2.str() << std::endl;

    return 0;
}