#include <iostream>
#include <bit>

struct AB
{
	short a = 0xaaaa;
	int b = 0xbbbbbbbb;
};

struct C : AB
{
	int c = 0xcccccccc;
};

class DEF : C
{
	int d = 0xdddddddd;
	int e = 0xeeeeeeee;
	int f = 0xffffffff;
};

void printString(std::string *s)
{
	std::cout << *s << std::endl;
}

std::string *hoge(std::string s)
{
	std::string ss = s;
	printString(&ss);
	return &ss;
}

int main()
{
	std::cout << __cplusplus << std::endl;
	DEF def;
	void *ptr = &def;
	for (int i = 0; i < sizeof(DEF); i++)
	{
		printf("%02X ", ((unsigned char *)ptr)[i]);
	}

	puts("");
	std::string local = "hoge";
	std::string *p = hoge(local);
	using namespace std;
	cout << p << endl;
	printString(p);
	return 0;
}