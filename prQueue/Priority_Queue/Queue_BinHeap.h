#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <initializer_list>
#include <algorithm>

template <typename T, typename Comparator = std::less<T>>
class Queue_BinHeap {
private:
    std::vector<T> data;
    Comparator comp;

    void UpHeapify(int i) {
        while (i > 0 && comp(data[(i - 1) / 2], data[i])) {
            std::swap(data[i], data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void DownHeapify(int i) {
        int size = data.size();
        while (2 * i + 1 < size) { // пока есть хот€ бы один дочерний элемент
            int maxChild = 2 * i + 1; // левый дочерний
            if (maxChild + 1 < size && comp(data[maxChild], data[maxChild + 1])) {
                maxChild++; // выбираем больший дочерний
            }

            if (comp(data[i], data[maxChild])) {
                std::swap(data[i], data[maxChild]);
                i = maxChild; // перемещаемс€ вниз
            }
            else {
                break; // куча уже соблюдена
            }
        }
    }

    void Heapify() {
        for (int i = (data.size() / 2) - 1; i >= 0; --i) {
            DownHeapify(i);
        }
    }

public:
    using value_type = T;

    Queue_BinHeap() = default;

    Queue_BinHeap(std::initializer_list<value_type> il) : data(il) {
        Heapify();
    }

    Queue_BinHeap(const std::vector<T>& elems) : data(elems) {
        Heapify();
    }

    void push(const T& val) {
        data.push_back(val);
        UpHeapify(data.size() - 1);
    }

    value_type pop() {
        if (data.empty()) {
            throw std::out_of_range("ќчередь пуста!");
        }

        value_type fst = data[0];
        data[0] = data.back();
        data.pop_back();
        DownHeapify(0);
        return fst;
    }

    value_type top() const {
        if (data.empty()) {
            throw std::out_of_range("ќчередь пуста!");
        }
        return data[0];
    }

    Queue_BinHeap<value_type> Merge_PriorityQueue(Queue_BinHeap<value_type>& other) {
        data.insert(data.end(), other.data.begin(), other.data.end());
        Heapify(); 
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Queue_BinHeap<value_type>& pr) {
        for (const value_type& x : pr.data) {
            os << x << " ";
        }
        os << std::endl;
        return os;
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }
};
