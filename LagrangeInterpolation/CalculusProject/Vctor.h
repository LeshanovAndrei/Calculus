#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Vctor // Опишем "свой вектор" для реализации Set на его базе
{

public:
	Vctor();
	Vctor(const Vctor<T>&);
	bool BinarySearch(int l, int r, T x);
	void SelectionSortNotDecreasing();
	friend void swap(T& a, T& b);
	void Add(T el);// Для добавления нового элемента будем расширять вектор
	void Del(T num);// Для удаления элемента вектор будем сужать
	int GetSize() { return size; }
	void Show();
	T& operator[ ] (int i);
	T* operator()() { return vec; }
	Vctor<T>& operator =(Vctor&);
	T* vec; // Массив, B котором будут храниться элементы вектора
	unsigned int size; // Его размер
private:

	int vectorMinIndexCurrent(unsigned int);

	int vectorMaxIndexCurrent(unsigned int i);

};


// БЛОК МЕТОДОВ ВЕКТОРА
//---------------------------------------------------------------------



template <typename T> // Поиск минимального с текущего 
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

template <typename T> // Поиск максимального с текущего
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

template <typename T> // Сортировка по возрастанию
void Vctor<T> ::SelectionSortNotDecreasing()
{
	for (unsigned int i = 0; i < size; i++)
	{
		int imax = vectorMinIndexCurrent(i);
		swap(vec[i], vec[imax]);
	}
}

template <typename T> // Двоичный поиск
bool Vctor<T> ::BinarySearch(int l, int r, T x)
{
	SelectionSortNotDecreasing();
	if (r >= l) {
		int mid = l + (r - l) / 2;

		// Если середина 
		if (vec[mid] == x)
			return 1;

		// Если меньше середины - то слева
		if (vec[mid] > x)
			return BinarySearch(l, mid - 1, x);

		// Иначе справа
		return BinarySearch(mid + 1, r, x);
	}

	// We reach here when element is not 
	// present in array 
	return 0;
}

template <typename T> // мой дружественный свап
void swap(T& a, T& b)
{
	T t;
	t = a;
	a = b;
	b = t;
	delete t;
}

template<typename T> // Конструктор без параметров
Vctor<T> ::Vctor()
{
	vec = new T[0];
	size = 0;
}

template<typename T> // Добавление элемента
void Vctor<T> ::Add(T el) // Для добавления нового элемента будем расширять вектор
{
	size++;
	T* temp = new T[size];// Новый массив размера +1
	for (int i = 0; i < size - 1; i++)// Копируем все элементы старого в новый
	{
		temp[i] = vec[i];
	}
	temp[size - 1] = el;// И добавляем требуемый элемент
	delete[]vec;
	vec = temp;
	// Сложность O(n) - многовато, но лучше пока что не придумал
}

template<typename T> // Удаление элемента
void Vctor<T>::Del(T num)// Для удаления элемента вектор будем сужать
{
	size--;
	int i = 0;
	/*if (num >= size)
	{
		return;
	}*/
	T* temp = new T[size];// Новый массив размера -1
	for (; vec[i] != num; i++)// Копируем всё, что до удаляемого элемента
	{
		temp[i] = vec[i];
	}
	for (i++; i < size + 1; i++)//и после него
	{
		temp[i - 1] = vec[i];
	}

	delete[]vec;
	vec = temp;



	// Сложность O(n) - многовато, но лучше пока что не придумал
}

template<typename T> // Вывод в консоль 
void Vctor<T>::Show()
{
	for (int i = 0; i < size; i++)
	{
		cout << vec[i] << " ";
	}
}

template<typename T> // перегрузка []
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
