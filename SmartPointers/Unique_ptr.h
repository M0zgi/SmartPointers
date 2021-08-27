#pragma once
#include<iostream>
#include<Windows.h>
#include<string>

using namespace std;

template<class T>
class Uniqueptr
{
public:
	Uniqueptr() {};

	//создаёт новый unique_ptr
	explicit Uniqueptr(T* ptr) : ptr(ptr) {}

	//конструктор копирования
	Uniqueptr(const Uniqueptr& obj) = delete;

	//конструктор перемещения
	// для его реализации нужно написать методы reset и release
	
	//оператор присваивания
	Uniqueptr& operator = (const Uniqueptr<T>& obj) = delete;

	Uniqueptr& operator = (Uniqueptr<T>&& obj) noexcept 
	{
		reset(obj.release());
		return *this;
	}

	Uniqueptr(Uniqueptr&& obj) noexcept
		: ptr(obj.release()) {}

	T* release() {
		T* tmp = ptr;
		ptr = nullptr;
		return tmp;
	}

	void reset(T* p) {
		delete ptr;
		ptr = p;
	}	

	//возвращает хранимый указатель
	T* get() const noexcept;

	T& operator*() const noexcept { return *get(); }

	T* operator->() const noexcept { return get(); }

	void Destroy();

	//разрушает объект, которым владеет, если больше нет shared_ptr ссылающихся на него
	~Uniqueptr();


private:

	T* ptr = nullptr;
};

template<class T>
inline T* Uniqueptr<T>::get() const noexcept
{
	return ptr ? ptr : NULL;
}

template<class T>
inline void Uniqueptr<T>::Destroy()
{
	if (!ptr)
		return;

	delete ptr;		

	cout << "Delete Uniqueptr ptr" << endl;
	
}

template<class T>
inline Uniqueptr<T>::~Uniqueptr()
{
	Destroy();
}
