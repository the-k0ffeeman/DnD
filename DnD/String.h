#pragma once
#include<iostream>
#include<cassert>

using namespace std;

class String
{
	char* str = nullptr;
	int size = 0;

	int lenStr(const char* str) const
	{
		int i = 0;
		if (str != nullptr)
		{
			while (str[i] != '\0')
			{
				i++;
			}
		}

		return i;
	}

	//void myStrcpy(char* str, const String& obj) const
	//{
	//	for (int i = 0; i <= size; i++)
	//	{
	//		str[i] = obj.str[i];
	//	}
	//}

public:
	String();
	String(int l);
	String(const char* line);
	String(const String& obj);

	String& operator=(const String& obj);

	String operator+(const String& obj) const;
	String operator*(int times) const;
	String& operator+=(const String& obj);
	String& operator*=(int times);

	char& operator[](int index);
	void operator()(const char* line);
	void operator()(const String& obj);

	bool operator==(const String& obj) const;
	bool operator!=(const String& obj) const;
	bool operator<(const String& obj) const;
	bool operator>(const String& obj) const;
	bool operator<=(const String& obj) const;
	bool operator>=(const String& obj) const;

	String operator+(int value) const;
	String& operator+=(int value);

	friend String operator+(int value, const String& s);

	friend ostream& operator<<(ostream& out, const String& s);
	friend istream& operator>>(istream& in, String& s);

	operator char* () const;
	operator int() const;

	~String();

	void clear();
	void clear(int l);

	void input();
	void input(const char* line);

	const char* getStr() const;
	int getLen() const;

	void print() const;

	void reverse();
};

String::String() : String(80) {}
String::String(int l)
{
	clear(l);
}
String::String(const char* line)
{
	input(line);
}
String::String(const String& obj)
{
	size = obj.size;
	str = new char[size + 1];
	strcpy(str, obj.str);
}

String& String::operator=(const String& obj)
{
	if (this == &obj)
	{
		return *this;
	}

	delete[] str;

	size = obj.size;
	str = new char[size + 1];
	strcpy(str, obj.str);

	return *this;
}

String String::operator+(const String& obj) const
{
	char* temp = new char[size + obj.size + 1];
	strcpy(temp, str);
	strcpy(temp + size, obj.str);

	String st(temp);
	delete[] temp;
	return st;
}
String String::operator*(int times) const
{
	if (times > 0)
	{
		char* temp = new char[size * times + 1];

		for (int i = 0; i < times; i++)
		{
			strcpy(temp + size * i, str);
		}

		String st(temp);
		delete[] temp;
		return st;
	}
	return "";
}
String& String::operator+=(const String& obj)
{
	*this = *this + obj;
	return *this;
}
String& String::operator*=(int times)
{
	*this = *this * times;
	return *this;
}

char& String::operator[](int index)
{
	assert(index >= 0 && index < size);
	return str[index];
}
void String::operator()(const char* line)
{
	input(line);
}
void String::operator()(const String& obj)
{
	size = obj.size;
	delete[] str;
	str = new char[size + 1];
	strcpy(str, obj.str);
}

bool String::operator==(const String& obj) const
{
	return strcmp(str, obj.str) == 0;
}
bool String::operator!=(const String& obj) const
{
	return !(*this == obj);
}
bool String::operator<(const String& obj) const
{
	if (strcmp(str, obj.str) < 0)
	{
		return true;
	}
	return false;
}
bool String::operator>(const String& obj) const
{
	return !(*this < obj || *this == obj);
}
bool String::operator<=(const String& obj) const
{
	return (*this < obj || *this == obj);
}
bool String::operator>=(const String& obj) const
{
	return (*this > obj || *this == obj);
}

String String::operator+(int value) const
{
	char digits[12];
	int count = 0;

	do
	{
		digits[count++] = '0' + value % 10;
		value /= 10;
	} while (value > 0);

	char text[12];
	for (int i = 0; i < count; ++i)
		text[i] = digits[count - 1 - i];
	text[count] = '\0';

	return *this + String(text);
}

String& String::operator+=(int value)
{
	*this = *this + value;
	return *this;
}

String operator+(int value, const String& s)
{
	return ' ';
}

ostream& operator<<(ostream& out, const String& s)
{
	out << s.str;
	return out;
}
istream& operator>>(istream& in, String& s)
{
	char word[80];
	in >> word;
	if (in)
	{
		s.input(word);
	}
	return in;
}

String::operator char* () const
{
	return str;
}
String::operator int() const
{
	return atoi(str);
}

String::~String()
{
	delete[] str;
}

void String::clear(int l)
{
	size = l;
	delete[] str;
	str = new char[size + 1];
	str[0] = '\0';
}
void String::clear()
{
	clear(80);
}

void String::input()
{
	//cout << "Input line: ";
	char buffer[256];

	cin.getline(buffer, 256);
	if (lenStr(buffer) > size)
	{
		input(buffer);
	}
	else
	{
		strcpy(str, buffer);
	}
}
void String::input(const char* line)
{
	size = lenStr(line);
	delete[] str;
	str = new char[size + 1];
	strcpy(str, line);
}

int String::getLen() const
{
	return size;
}

const char* String::getStr() const
{
	return str;
}

void String::print() const
{
	cout << str << endl;
}

void String::reverse()
{
	for (int i = 0; i < size / 2; i++)
	{
		char c = str[size - 1 - i];
		str[size - 1 - i] = str[i];
		str[i] = c;
	}
}