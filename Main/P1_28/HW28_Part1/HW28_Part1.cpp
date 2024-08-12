#include <iostream>
#include <vector>
#include <thread>
#include <numeric> 
#include <chrono>  
#include <functional>
#include <algorithm>

double measure_time(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}
long long sum_single_thread(const std::vector<int>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 0LL);
}
long long sum_multi_thread(const std::vector<int>& vec, int num_threads) {
    std::vector<std::thread> threads;
    std::vector<long long> results(num_threads, 0);
    int block_size = vec.size() / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread([&, i]() {
            int start = i * block_size;
            int end = (i == num_threads - 1) ? vec.size() : (i + 1) * block_size;
            results[i] = std::accumulate(vec.begin() + start, vec.begin() + end, 0LL);
            }));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return std::accumulate(results.begin(), results.end(), 0LL);
}
int main() {
    std::vector<int> sizes = { 10000, 100000, 1000000, 10000000, 100000000 };
    int max_threads = std::thread::hardware_concurrency();

    for (int size : sizes) {
        std::vector<int> vec(size);
        std::iota(vec.begin(), vec.end(), 1); 

        std::cout << "Vector size: " << size << std::endl;

        double time_single = measure_time([&]() { sum_single_thread(vec); });
        std::cout << "1 Thread: Time = " << time_single << " seconds" << std::endl;

        double time_2_threads = measure_time([&]() { sum_multi_thread(vec, 2); });
        std::cout << "2 Threads: Time = " << time_2_threads << " seconds, Boost = " << time_single / time_2_threads << std::endl;

        double time_hw_threads = measure_time([&]() { sum_multi_thread(vec, max_threads); });
        std::cout << max_threads << " Threads: Time = " << time_hw_threads << " seconds, Boost = " << time_single / time_hw_threads << std::endl;

        double time_2x_hw_threads = measure_time([&]() { sum_multi_thread(vec, max_threads * 2); });
        std::cout << 2 * max_threads << " Threads: Time = " << time_2x_hw_threads << " seconds, Boost = " << time_single / time_2x_hw_threads << std::endl;

        std::cout << std::endl;
    }

    return 0;
}
