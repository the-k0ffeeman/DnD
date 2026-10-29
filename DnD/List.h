#pragma once
#include<initializer_list>
#include<iostream>
#include<cassert>

#include"Func.h"
#include"Node.h"

using namespace std;

template<class T>
class List
{
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;
	size_t   size = 0;

	Node<T>* getNode(size_t index) const;

public:
	List();
	List(initializer_list<T> list);
	List(const List<T>& obj);
	List<T>& operator=(const List<T>& obj);
	~List();

	void push_front(const T& value);
	void push_back(const T& value);
	void insert(const T& value, size_t index);

	void pop_front();
	void pop_back();
	void remove(size_t index);
	void erase(const T& value);
	void erase_if(bool(*predicate)(const T&));

	T& front() const;
	T& back() const;
	T& operator[](int index) const;
	T at(size_t index) const;

	size_t getSize() const;
	void print() const;
	void print(int x, int y) const;
	void print_reverse() const;
	void clear();

	size_t firstIndex(const T& value);
	size_t lastIndex(const T& value);

	List splice(size_t index1, size_t index2);

	List<T> operator+(const List<T>& list) const;
	void operator+=(const List<T>& list);

	template<class U>
	friend ostream& operator<<(ostream& out, const List<U>& l);
};

template<class T>
Node<T>* List<T>::getNode(size_t index) const
{
	assert(index < size);

	Node<T>* pos = nullptr;
	if (index < size / 2)
	{
		pos = first;
		for (size_t i = 0; i < index; i++)
		{
			pos = pos->next;
		}
	}
	else
	{
		pos = last;
		for (size_t i = 0; i < size - index - 1; i++)
		{
			pos = pos->prev;
		}
	}

	return pos;
}

template<class T>
List<T>::List() {}

template<class T>
List<T>::List(initializer_list<T> list)
{
	for (T elem : list)
	{
		push_back(elem);
	}
}

template<class T>
List<T>::List(const List<T>& obj)
{
	if (obj.first == nullptr)
	{
		return;
	}

	Node<T>* lower = obj.first;
	for (size_t i = 0; i < obj.size; i++)
	{
		push_back(lower->value);
		lower = lower->next;
	}
}

template<class T>
List<T>& List<T>::operator=(const List<T>& obj)
{
	if (this == &obj)
	{
		return *this;
	}

	clear();

	Node<T>* lower = obj.first;
	for (size_t i = 0; i < obj.size; i++)
	{
		push_back(lower->value);
		lower = lower->next;
	}

	return *this;
}

template<class T>
List<T>::~List()
{
	clear();
}

template<class T>
void List<T>::push_front(const T& value)
{
	if (size == 0)
	{
		first = last = new Node<T>(value);
	}
	else
	{
		Node<T>* newNode = new Node<T>(value);
		newNode->next = first;
		first->prev = newNode;
		first = newNode;
	}
	size++;
}

template<class T>
void List<T>::push_back(const T& value)
{
	if (size == 0)
	{
		first = last = new Node<T>(value);
	}
	else
	{
		last->next = new Node<T>(value);
		last->next->prev = last;
		last = last->next;
	}
	size++;
}

template<class T>
void List<T>::insert(const T& value, size_t index)
{
	if (index > size)
	{
		return;
	}

	if (index == 0)
	{
		push_front(value);
	}
	else if (index == size)
	{
		push_back(value);
	}
	else
	{
		Node<T>* pos = getNode(index - 1);
		Node<T>* newNode = new Node<T>(value);
		newNode->next = pos->next;
		pos->next->prev = newNode;
		pos->next = newNode;
		newNode->prev = pos;
		size++;
	}
}


template<class T>
void List<T>::pop_front()
{
	if (size == 0)
	{
		return;
	}

	Node<T>* temp = first;
	first = first->next;
	delete temp;
	size--;
	if (first != nullptr)
	{
		first->prev = nullptr;
	}
}

template<class T>
void List<T>::pop_back()
{
	if (size == 0)
	{
		return;
	}

	if (size == 1)
	{
		delete first;
		first = last = nullptr;
	}
	else
	{
		last = last->prev;
		delete last->next;
		last->next = nullptr;
	}
	size--;
}

template<class T>
void List<T>::remove(size_t index)
{
	if (index >= size)
	{
		return;
	}

	if (index == 0)
	{
		pop_front();
	}
	else if (index == size - 1)
	{
		pop_back();
	}
	else
	{
		Node<T>* pos = getNode(index - 1);
		Node<T>* temp = pos->next;
		pos->next = temp->next;
		temp->next->prev = pos;
		delete temp;
		size--;
	}
}

template<class T>
void List<T>::erase(const T& value)
{
	size_t i = 0;
	Node<T>* temp = first;
	while (temp)
	{
		Node<T>* next = temp->next;
		if (temp->value == value)
		{
			remove(i);
		}
		else
		{
			i++;
		}
		temp = next;
	}
}

template<class T>
void List<T>::erase_if(bool(*predicate)(const T&))
{
	size_t i = 0;
	Node<T>* temp = first;
	while (temp)
	{
		Node<T>* next = temp->next;
		if (predicate(temp->value))
		{
			remove(i);
		}
		else
		{
			i++;
		}
		temp = next;
	}
}


template<class T>
T& List<T>::front() const
{
	return first->value;
}

template<class T>
T& List<T>::back() const
{
	return last->value;
}

template<class T>
T& List<T>::operator[](int index) const
{
	assert(abs(index) < size);
	if (index < 0)
	{
		return getNode(size - (-index))->value;
	}

	return getNode(index)->value;
}

template<class T>
T List<T>::at(size_t index) const
{
	assert(index < size);
	return getNode(index)->value;
}


template<class T>
size_t List<T>::getSize() const
{
	return size;
}

template<class T>
void List<T>::print() const
{
	Node<T>* temp = first;
	while (temp)
	{
		cout << temp->value;// << " ";
		temp = temp->next;
	}
	cout << endl;
}
template<class T>
void List<T>::print(int x, int y) const
{
	Node<T>* temp = first;
	while (temp)
	{
		SetCursor(x, y++);
		cout << temp->value;// << " ";
		temp = temp->next;
	}
	cout << endl;
}

template<class T>
void List<T>::print_reverse() const
{
	Node<T>* temp = last;
	while (temp)
	{
		cout << temp->value << " ";
		temp = temp->prev;
	}
	cout << endl;
}

template<class T>
void List<T>::clear()
{
	Node<T>* temp = first;
	while (temp)
	{
		first = first->next;
		delete temp;
		temp = first;
	}
	size = 0;
	last = nullptr;
}


template<class T>
size_t List<T>::firstIndex(const T& value)
{
	size_t i = 0;
	Node<T>* temp = first;
	while (temp)
	{
		if (temp->value == value)
		{
			return i;
		}
		temp = temp->next;
		i++;
	}

	return size; //error
}

template<class T>
size_t List<T>::lastIndex(const T& value)
{
	size_t i = 0, find = size;
	Node<T>* temp = last;
	while (temp)
	{
		if (temp->value == value)
		{
			return size - i - 1;
		}
		temp = temp->prev;
		i++;
	}

	return size;
}

template<class T>
List<T> List<T>::splice(size_t index1, size_t index2)
{
	List<T> list;
	Node<T>* start = getNode(index1);
	Node<T>* end = getNode(index2 + 1);
	while (start != end)
	{
		list.push_back(start->value);
		start = start->next;
	}

	return list;
}


template<class T>
List<T> List<T>::operator+(const List<T>& list) const
{
	List<T> l = *this;
	Node<T>* temp = list.first;
	for (size_t i = 0; i < list.size; i++)
	{
		l.push_back(temp->value);
		temp = temp->next;
	}

	return l;
}

template<class T>
void List<T>::operator+=(const List<T>& list)
{
	Node<T>* temp = list.first;
	for (size_t i = 0; i < list.size; i++)
	{
		push_back(temp->value);
		temp = temp->next;
	}
}

template<class T>
ostream& operator<<(ostream& out, const List<T>& l)
{
	Node<T>* temp = l.first;
	while (temp)
	{
		out << *temp->value;
		temp = temp->next;
	}
	return out;
}