#pragma once
#include<iostream>
#include<cassert>

using namespace std;

template<class T>
class Array
{
	T* arr = nullptr;
	int size = 0;
	int filled = 0;

	int growth = 1;

public:

	Array();
	explicit Array(int s);
	Array(const Array& obj);
	~Array();

	Array& operator=(const Array& obj);
	Array<T> operator+(const Array& obj) const;
	Array<T>& operator+=(const Array& obj);
	T& operator[](int index);
	void create(int s);

	int getSize() const;
	void setSize(int s, int grow = 1);
	int getUpperBound() const;
	bool IsEmpty() const;
	void freeExtra();
	void clear(); // RemoveAll
	T get(int index) const;
	void set(int index, const T& value);
	void append(const Array& obj);
	T* getData() const;
	void add(T value);
	void insert(const T& value, int index);
	void remove(int index);

	void show() const;
	void sort();
	void reverse();
	bool contains(const T& value) const;

	void fill(const T& value) const;
	void setRand();
	int countValue(const T& value) const;
	int findValue(const T& value) const;
};

template<class T>
Array<T>::Array() : arr(nullptr), size(0) {}

template<class T>
Array<T>::Array(int s)
{
	create(s);
}

template<class T>
Array<T>::Array(const Array& obj)
{
	size = obj.size;
	filled = obj.filled;
	growth = obj.growth;
	arr = new T[size];
	for (int i = 0; i < filled; i++)
	{
		arr[i] = obj.arr[i];
	}
}

template<class T>
Array<T>::~Array()
{
	delete[] arr;
}


template<class T>
Array<T>& Array<T>::operator=(const Array& obj)
{
	if (this == &obj)
	{
		return *this;
	}

	delete[] arr;

	size = obj.size;
	filled = obj.filled;
	growth = obj.growth;
	arr = new T[size];
	for (int i = 0; i < filled; i++)
	{
		arr[i] = obj.arr[i];
	}

	return *this;
}

template<class T>
Array<T> Array<T>::operator+(const Array& obj) const
{
	Array<T> result(*this);
	result.append(obj);
	return result;
}

template<class T>
Array<T>& Array<T>::operator+=(const Array& obj)
{
	append(obj);
	return *this;
}

template<class T>
T& Array<T>::operator[](int index)
{
	assert(index >= 0 && index < filled);
	return arr[index];
}

template<class T>
void Array<T>::create(int s)
{
	if (s <= 0)
	{
		return;
	}
	size = s;
	arr = new T[size];
}


template<class T>
int Array<T>::getSize() const
{
	return size;
}

template<class T>
void Array<T>::setSize(int s, int grow)
{
	if (s < 0)
	{
		return;
	}

	int newFilled = (filled < s) ? filled : s;
	size = s + grow;
	T* temp = new T[size];
	for (int i = 0; i < newFilled; i++)
	{
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;
	filled = newFilled;
	growth = grow;
}

template<class T>
int Array<T>::getUpperBound() const
{
	return filled - 1;
}

template<class T>
bool Array<T>::IsEmpty() const
{
	return filled == 0;
}

template<class T>
void Array<T>::freeExtra()
{
	if (filled < size)
	{
		setSize(filled, 0);
	}
}

template<class T>
void Array<T>::clear()
{
	delete[] arr;
	arr = nullptr;
	size = 0;
	filled = 0;
}

template<class T>
T Array<T>::get(int index) const
{
	if (index < 0 || index >= filled)
	{
		return 0;
	}
	return arr[index];
}

template<class T>
void Array<T>::set(int index, const T& value)
{
	if (index < 0 || index >= filled)
	{
		return;
	}
	arr[index] = value;
}

template<class T>
void Array<T>::append(const Array& obj)
{
	int newSize = size + obj.size;
	T* temp = new T[newSize];

	for (int i = 0; i < filled; ++i)
	{
		temp[i] = arr[i];
	}
	for (int i = 0; i < obj.filled; ++i)
	{
		temp[filled + i] = obj.arr[i];
	}

	delete[] arr;
	arr = temp;
	size = newSize;
	filled += obj.filled;
}

template<class T>
T* Array<T>::getData() const
{
	return arr;
}

template<class T>
void Array<T>::add(T value)
{
	if (filled == size)
	{
		setSize(size, growth);
	}
	arr[filled++] = value;
}

template<class T>
void Array<T>::insert(const T& value, int index)
{
	if (index < 0 || index > filled)
	{
		return;
	}

	T temp = value;
	if (filled == size)
	{
		setSize(size);
	}
	for (int i = filled; i > index; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[index] = temp;
	filled++;
}

template<class T>
void Array<T>::remove(int index)
{
	if (index < 0 || index >= filled)
	{
		return;
	}
	T* temp = new T[size];
	for (int i = 0; i < index; i++)
	{
		temp[i] = arr[i];
	}
	for (int i = index; i < filled - 1; i++)
	{
		temp[i] = arr[i + 1];
	}
	delete[] arr;
	filled--;
	arr = temp;
}

template<class T>
void Array<T>::show() const
{
	if (arr != nullptr)
	{
		for (int i = 0; i < filled; i++)
		{
			cout << arr[i] << " ";
		}
	}
	cout << endl;
}

template<class T>
void Array<T>::sort()
{
	for (int j = 0; j < filled - 1; j++)
	{
		for (int i = 0; i < filled - 1 - j; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
			}
		}
	}
}

template<class T>
void Array<T>::reverse()
{
	for (int i = 0; i < filled / 2; i++)
	{
		swap(arr[i], arr[filled - 1 - i]);
	}
}

template<class T>
bool Array<T>::contains(const T& value) const
{
	for (int i = 0; i < filled; i++)
	{
		if (arr[i] == value)
		{
			return true;
		}
	}
	return false;
}

// ---

template<class T>
void Array<T>::fill(const T& value) const
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = value;
	}
}

template<class T>
void Array<T>::setRand()
{
	cout << "no implemention for " << typeid(T).name() << endl;
}
template<>
void Array<int>::setRand()
{
	int minValue = 0, maxValue = 9;
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % (maxValue - minValue + 1) + minValue;
	}
	filled = size;
}

template<class T>
int Array<T>::countValue(const T& value) const
{
	int countValue = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] == value)
		{
			countValue++;
		}
	}

	return countValue;
}

template<class T>
int Array<T>::findValue(const T& value) const
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == value)
		{
			return i;
		}
	}

	return -1;
}