
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <memory>
#include <list>

#define size 1024 * 1024

class A
{
public:
	int a;
};

class B
{
public:
	int b;
};

std::unique_ptr<A> hoge()
{
	std::unique_ptr<A> a = std::make_unique<A>();
	a->a = 10;
	printf("%p\n", a.get());
	return a;
}

int main()
{
	std::unique_ptr<A> a = hoge();
	printf("%p\n", a.get());
	return 0;
}