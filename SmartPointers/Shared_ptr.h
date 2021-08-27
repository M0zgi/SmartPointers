#pragma once
#include<iostream>
#include<Windows.h>
#include<string>

using namespace std;



template<class T>
class Sharedptr
{
public:
	Sharedptr() {};

	//создаёт новый shared_ptr
	explicit Sharedptr(T* ptr) : ptr(ptr), count(new int(1)) {}

	//конструктор копирования
	Sharedptr(const Sharedptr& obj);
	
	//конструктор перемещения
	Sharedptr(Sharedptr&& obj);

	//оператор присваивания
	 Sharedptr& operator = (const Sharedptr<T>& obj);

	//возвращает хранимый указатель
	T* get() const noexcept;

	T& operator*() const noexcept { return *get(); }

	T* operator->() const noexcept { return get(); }

	//возвращает количество объектов shared_ptr, ссылающихся на один и тот же управляемый объект
	int use_count() const noexcept;
	
	void Destroy();

	//разрушает объект, которым владеет, если больше нет shared_ptr ссылающихся на него
	~Sharedptr();

	
private:

	T* ptr = nullptr;
	int* count = nullptr;

	/*template<class U>
	struct ControlBlock
	{
		int count;
		U object;
	};

	ControlBlock<T>* cptr = nullptr;

	template<class U, class... Args>
	friend Sharedptr<U> make_shared(Args&&... args);

	struct make_shared_t;

	template<class... Args>
	Sharedptr(make_shared_t, ControlBlock<T>* storage_ptr): cptr(storage_ptr)
	{
	}*/
	

	// int count - нельзя использовать, так как не будет общего счетчика у всех. 
	// У каждого указателя будет свой отдельный счетчик, при создании нового
	// указателя нужно будет у всех указателей увеличивать свой отдельный счетчик, так же как и при вызове деструктора.
	// А как понять каким указателям менять этот счетчик ???
	

	// static count нельзя использовать, так как будет общий счетчик у всех объектов класса.
	// даже если они будут смотреть в разные ячейки памяти, ссылаясь на разные объекты.

	// Нужно использовать указатель на счетчик, тогда в конструкторе копирования мы будем копировать
	// адрес памяти в указатель на счетчик	
};

template<class T>
inline Sharedptr<T>::Sharedptr(const Sharedptr& obj)
{
	this->ptr = obj.ptr;
	this->count = obj.count;

	if (count) 
	{
		++*count;
	}
}

template<class T>
inline Sharedptr<T>::Sharedptr(Sharedptr&& obj)
{
	this->ptr = obj.ptr;
	this->count = obj.count;

	obj.ptr = nullptr;
	obj.count = nullptr;
}



template<class T>
inline Sharedptr<T>& Sharedptr<T>::operator=(const Sharedptr<T>& obj)
{
	
	if (this == &obj)
	{
		return *this;
	}
	
	if (this != &obj)
	{
		Destroy();
	}

	this->ptr = obj.ptr;
	this->count = obj.count;

	if (count)
	{
		++* count;
	}

	return *this;
}

template<class T>
inline T* Sharedptr<T>::get() const noexcept
{
	return count ? ptr : NULL;
}

template<class T>
inline int Sharedptr<T>::use_count() const noexcept
{
	return count ? *count : NULL;
}

template<class T>
inline void Sharedptr<T>::Destroy()
{
	if (!count)
		return;

	--*count;

	if (!*count)
	{
		delete ptr;
		delete count;

		cout << "Delete Sharedptr ptr" << endl;
		cout << "Delete Sharedptr count" << endl;
	}
}

template<class T>
inline Sharedptr<T>::~Sharedptr()
{
	Destroy();
}