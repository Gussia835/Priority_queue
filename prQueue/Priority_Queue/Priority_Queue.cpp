#include <iostream>
#include <cassert>
#include <chrono>
#include <queue>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>

#include "priority_queue.h"
#include "Queue_BinHeap.h"
#include "LengthComparator.h"

template<typename PriorityQueue>
void test_custom_queue(const std::vector<typename PriorityQueue::value_type>& data) {
    //
    // 1. Создание из массива
    //
    auto start = std::chrono::high_resolution_clock::now();
    PriorityQueue pq_custom(data);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
    std::cout << "[Custom] Create from array: " << duration.count() << " ms\n";

    //
    // 2. Добавление элементов
    //
    start = std::chrono::high_resolution_clock::now();
    for (auto val : data)
        pq_custom.push(val);

    duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
    std::cout << "[Custom] Push " << data.size() << " elements: " << duration.count() << " ms\n";

    //
    // 3. Извлечение элементов
    //
    start = std::chrono::high_resolution_clock::now();
    while (!pq_custom.empty())
        pq_custom.pop();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
    std::cout << "[Custom] Pop " << data.size() << " elements: " << duration.count() << " ms\n";

    //
    // 4. Слияние очередей
    //
    PriorityQueue pq1(data), pq2(data);
    start = std::chrono::high_resolution_clock::now();
    auto merged = pq1.Merge_PriorityQueue(pq2);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
    std::cout << "[Custom] Merge two queues: " << duration.count() << " ms\n";

    //
    // 5. Доступ к максимуму
    //
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < data.size(); ++i)
        (void)pq1.top();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
    std::cout << "[Custom] GetMax calls: " << duration.count() << " ms\n";
}

void test_std_queue(const std::vector<int>& data) {

    //
    // 1. Создание из массива
    //
    auto start = std::chrono::high_resolution_clock::now();
    std::priority_queue<int> pq_std(data.begin(), data.end());

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
    std::cout << "[STL] Create from array: " << duration.count() << " ms\n";

    //
    // 2. Добавление элементов (уже выполнено при создании)
    //
    std::cout << "[STL] Push " << data.size() << " elements: " << duration.count() << " ms\n";

    //
    // 3. Извлечение элементов
    //
    start = std::chrono::high_resolution_clock::now();
    while (!pq_std.empty())
        pq_std.pop();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
    std::cout << "[STL] Pop " << data.size() << " elements: " << duration.count() << " ms\n";

    //
    // 4. Слияние очередей 
    //
    std::priority_queue<int> pq1, pq2;

    for (int val : data)
        pq1.push(val);
    for (int val : data)
        pq2.push(val);

    start = std::chrono::high_resolution_clock::now();
    while (!pq2.empty()) {
        pq1.push(pq2.top());
        pq2.pop();
    }
    duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - start
    );
    std::cout << "[STL] Merge two queues: " << duration.count() << " ms\n";

    //
    // 5. Доступ к максимуму
    //
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < data.size(); ++i)
        (void)pq1.top();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - start
    );
    std::cout << "[STL] GetMax (top) calls: " << duration.count() << " ms\n";
}

//
//Работа с файлом
//

template<typename PQ>
void readFromFile(std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    PQ words;
    std::string word;

    while (ifs >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), [](char ch) { return ispunct(ch); }), word.end());

        if (!word.empty()) {
            words.push(word);

            if (words.size() > 20) {
                words.pop();
            }
        }
    }

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - start
    );

    // Выводим слова в порядке убывания длины
    std::cout << "20 longest words:" << std::endl;
    while (!words.empty()) {
        std::string w = words.top();
        std::cout << w << " (" << w.length() << ")" << std::endl;
        words.pop();
    }

    std::cout << "=================\ntime: " << duration.count() << "ms" << std::endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    std::cout << "Starting priority queue comparison test...\n" << std::endl;

    const size_t N = 100000;
    std::vector<int> data(N);
    for (int i = 0; i < N; ++i) data[i] = rand();

    std::cout << "=== Priority_queue (vector based) ===\n";
    test_custom_queue<Priority_queue<int>>(data);

    std::cout << "\n=== Queue_BinHeap (binary heap based) ===\n";
    test_custom_queue<Queue_BinHeap<int>>(data);

    std::cout << "\n=== std::priority_queue ===\n";
    test_std_queue(data);
    std::cout << std::endl;

    std::cout << "\n===Работа с файлом===\n";
    std::string filename = "war_and_peace.txt";

    std::cout << "\n=====Queue_Vector======\n";
    readFromFile<Priority_queue<std::string, std::vector<std::string>, LengthComparator>>(filename);

    std::cout << "\n=====Queue_BinHeap======\n";
    readFromFile<Queue_BinHeap<std::string, LengthComparator>>(filename);

    std::cout << "\n=======std::priority_queue=======\n";
    readFromFile<std::priority_queue<std::string, std::vector<std::string>, LengthComparator>>(filename);

    return 0;
}
