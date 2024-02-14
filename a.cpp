#include <iostream>

#include "a.hpp"

int A::getA()
{
	return a;
}

void A::setA(int a)
{
	this->a = a;
}

A::A(int n)
{
	a = n;
	std::cout << "A constructor " << a << std::endl;
}

A::~A()
{
	std::cout << "A destructor " << a << std::endl;
}