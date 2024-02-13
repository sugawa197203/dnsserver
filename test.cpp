#include <iostream>

class A
{
private:
	int a;

public:
	A()
	{
		a = 0;
		std::cout << "A constructor" << std::endl;
	}
	~A()
	{
		std::cout << "A destructor" << std::endl;
	}
	void call(std::string at)
	{
		std::cout << "call " << at << std::endl;
		a++;
		std::cout << "a = " << a << std::endl;
	}
};

A *Hoge()
{
	A a;
	a.call("Hoge");
	return &a;
}

int main()
{
	A *a = Hoge();
	a->call("main");
	return 0;
}