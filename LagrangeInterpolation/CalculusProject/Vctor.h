#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Vctor // ������ "���� ������" ��� ���������� Set �� ��� ����
{

public:
	Vctor();
	Vctor(const Vctor<T>&);
	bool BinarySearch(int l, int r, T x);
	void SelectionSortNotDecreasing();
	friend void swap(T& a, T& b);
	void Add(T el);// ��� ���������� ������ �������� ����� ��������� ������
	void Del(T num);// ��� �������� �������� ������ ����� ������
	int GetSize() { return size; }
	void Show();
	T& operator[ ] (int i);
	T* operator()() { return vec; }
	Vctor<T>& operator =(Vctor&);
	T* vec; // ������, B ������� ����� ��������� �������� �������
	unsigned int size; // ��� ������
private:

	int vectorMinIndexCurrent(unsigned int);

	int vectorMaxIndexCurrent(unsigned int i);

};


// ���� ������� �������
//---------------------------------------------------------------------



template <typename T> // ����� ������������ � �������� 
int Vctor<T> ::vectorMinIndexCurrent(unsigned int i)
{
	int imin = i;
	for (i; i < size; i++)
	{
		if (vec[i] < vec[imin])
			imin = i;
	}
	return imin;
}

template <typename T>
Vctor<T>::Vctor(const Vctor& a) : size(a.size)
{
	vec = new int[size];
	for (int i = 0; i < size; i++)
	{
		vec[i] = a.vec[i];
	}
}

template <typename T> // ����� ������������� � ��������
int Vctor<T> ::vectorMaxIndexCurrent(unsigned int i)
{
	int imax = i;
	for (i; i < size; i++)
	{
		if (vec[i] > vec[imax])
			imax = i;
	}
	return imax;
}

template <typename T> // ���������� �� �����������
void Vctor<T> ::SelectionSortNotDecreasing()
{
	for (unsigned int i = 0; i < size; i++)
	{
		int imax = vectorMinIndexCurrent(i);
		swap(vec[i], vec[imax]);
	}
}

template <typename T> // �������� �����
bool Vctor<T> ::BinarySearch(int l, int r, T x)
{
	SelectionSortNotDecreasing();
	if (r >= l) {
		int mid = l + (r - l) / 2;

		// ���� �������� 
		if (vec[mid] == x)
			return 1;

		// ���� ������ �������� - �� �����
		if (vec[mid] > x)
			return BinarySearch(l, mid - 1, x);

		// ����� ������
		return BinarySearch(mid + 1, r, x);
	}

	// We reach here when element is not 
	// present in array 
	return 0;
}

template <typename T> // ��� ������������� ����
void swap(T& a, T& b)
{
	T t;
	t = a;
	a = b;
	b = t;
	delete t;
}

template<typename T> // ����������� ��� ����������
Vctor<T> ::Vctor()
{
	vec = new T[0];
	size = 0;
}

template<typename T> // ���������� ��������
void Vctor<T> ::Add(T el) // ��� ���������� ������ �������� ����� ��������� ������
{
	size++;
	T* temp = new T[size];// ����� ������ ������� +1
	for (int i = 0; i < size - 1; i++)// �������� ��� �������� ������� � �����
	{
		temp[i] = vec[i];
	}
	temp[size - 1] = el;// � ��������� ��������� �������
	delete[]vec;
	vec = temp;
	// ��������� O(n) - ���������, �� ����� ���� ��� �� ��������
}

template<typename T> // �������� ��������
void Vctor<T>::Del(T num)// ��� �������� �������� ������ ����� ������
{
	size--;
	int i = 0;
	/*if (num >= size)
	{
		return;
	}*/
	T* temp = new T[size];// ����� ������ ������� -1
	for (; vec[i] != num; i++)// �������� ��, ��� �� ���������� ��������
	{
		temp[i] = vec[i];
	}
	for (i++; i < size + 1; i++)//� ����� ����
	{
		temp[i - 1] = vec[i];
	}

	delete[]vec;
	vec = temp;



	// ��������� O(n) - ���������, �� ����� ���� ��� �� ��������
}

template<typename T> // ����� � ������� 
void Vctor<T>::Show()
{
	for (int i = 0; i < size; i++)
	{
		cout << vec[i] << " ";
	}
}

template<typename T> // ���������� []
T& Vctor<T> :: operator[ ] (int i)
{
	if (i < 0 or i >= size)
	{
		cout << "WRONG!\n";
		exit(1);
	}
	return vec[i];

}

template<typename T>
Vctor<T>& Vctor<T>:: operator=(Vctor& a) {
	//this ->size = a.size;
	this->size = a.size;
	this->vec = new T[size];
	for (int i = 0; i < size; i++)
	{
		this->vec[i] = a.vec[i];
	}
	return *this;
}
//-------------------------------------------------------------------
