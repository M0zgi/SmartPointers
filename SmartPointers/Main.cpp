#include"Shared_ptr.h"
#include"Unique_ptr.h"

class People
{
public:
	People() { this->name = "NoName"; this->age = 0;}
	People(string name, int age) : name(name), age(age) {}
	
	//конструктор копирования
	People(const People& obj) 
	{ 
	this->name = obj.name; 
	this->age = obj.age;
	};

	//оператор присваивания
	People& operator = (const People& obj)
	{
		this->name = obj.name;
		this->age = obj.age;
	};

	void print() const
	{
		cout << "ФИО: " << name << endl << "Возраст: " << age;
	}

	friend ostream& operator << (ostream& out, const People& obj);

private:

	string name;
	int age;
};


int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	
	cout << "class Sharedptr" << endl;

	Sharedptr<People> ptr1 (new People ("Иван Петрович", 10));
	cout << endl;

	cout << "ptr1->print(): \n";
	ptr1->print();

	cout << endl;

	cout << "Счетчик ptr1.use_count(): " << ptr1.use_count();

	cout << endl;

	cout << "(*ptr1).print():\n";
	cout << *ptr1;
	cout << endl;

	cout << "\n--------------------------------------------\n";
	Sharedptr<People> ptr2(ptr1);

	cout << "ptr2->print(): \n";
	ptr2->print();
	cout << endl;
	cout << "Счетчик ptr1.use_count(): " << ptr1.use_count();
	cout << "\n--------------------------------------------\n";


	Sharedptr<People> ptr3(new People("Сергей Иванов", 10));
	cout << "Sharedptr<People> ptr3(new People(p2))\n";
	cout << "*ptr1 = *ptr3\n";
	ptr1 = ptr3;

	cout << "(*ptr1).print():\n";

	(*ptr1).print();
	cout << "\n--------------------------------------------\n";
	cout << endl;
	cout << "Счетчик ptr1.use_count(): " << ptr1.use_count() << endl;
	cout << "Счетчик ptr2.use_count(): " << ptr2.use_count() << endl;
	cout << "Счетчик ptr3.use_count(): " << ptr3.use_count()  << endl;

	cout << "\n--------------------------------------------\n";
	cout << "\n--------------------------------------------\n";


	cout << "class Uniqueptr" << endl;

	Uniqueptr<People> uptr1(new People("Сергей Иванов Uniqueptr", 20));

	cout << *uptr1;
	cout << endl;
	uptr1->print();
	cout << endl;
	cout << uptr1.get();

	// конструктор копирования удален
	// Uniqueptr<People> uptr2(uptr1);

	Uniqueptr<People> uptr2;

	uptr2 = move(uptr1);
	cout << endl;
	cout << uptr2.get();

	cout << endl;
	system("pause");
}


ostream& operator<<(ostream& out, const People& obj)
{
	out << "ФИО: " << obj.name << endl << "Возраст: " << obj.age;
		out << endl;

	return out;
}