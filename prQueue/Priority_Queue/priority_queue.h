#pragma once
#pragma once
#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <initializer_list>
#include <algorithm>

template <typename T, typename Container = std::vector<T>, typename Comparator = std::less<typename Container::value_type>>
class Priority_queue
{
private:
	Container data;
	Comparator comp;

public:
	using value_type = T;
	//
	//Конструктор
	//
	Priority_queue() = default;

	Priority_queue(std::initializer_list<value_type> il)
	{
		for (int x : il)
		{
			data.push_back(x);
		}
		std::sort(data.begin(), data.end(), comp);
	}



	//
	//Создание очереди из массива элементов (выполнить сортировку);
	//
	Priority_queue(Container cont) : data(cont)
	{
		std::sort(data.begin(), data.end(), comp);
	}


	//
	//Добавление элемента
	//
	void push(const T& val)
	{
		auto it = std::lower_bound(data.begin(), data.end(), val, comp);
		data.insert(it, val);
	}
	//
	//Удаление
	//
	void pop()
	{
		if (data.empty())
		{
			throw new std::out_of_range("Очередь пуста!");
		}

		data.pop_back();
	}

	//
	//получение максимального элемента
	//
	value_type top()
	{
		if (data.empty())
		{
			throw new std::out_of_range("Очередь пуста!");
		}

		return data.back();

	}
	//
	//Слияние двух очередей с приоритетом
	//
	Priority_queue<value_type> Merge_PriorityQueue(Priority_queue<value_type>& other)
	{
		data.insert(data.end(), other.data.begin(), other.data.end());
		std::sort(data.begin(), data.end(), comp);
		return *this;
	}
	//
	//Операция вывода в поток 
	// 	
	friend std::ostream& operator<<(std::ostream& os, Priority_queue pr)
	{
		for (value_type& x : pr.data)
		{
			os << x << " ";
		}
		os << std::endl;
		return os;
	}

	size_t size()
	{
		return data.size();
	}

	bool empty()
	{
		return data.empty();
	}


};