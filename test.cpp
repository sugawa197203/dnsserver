#include <iostream>
#include <byteswap.h>

int main()
{
	char a[4] = {'\x00', '\x01', '\x00', '\x01'};
	unsigned short b = *(unsigned short *)a;
	unsigned short c = *(unsigned short *)(a + 1);
	unsigned short d = *(unsigned short *)(a + 2);
	unsigned short e = *(unsigned short *)(a + 3);

	printf("%04x\n", b);
	printf("%04x\n", c);
	printf("%04x\n", d);
	printf("%04x\n", e);

	b = bswap_16(b);
	c = bswap_16(c);
	d = bswap_16(d);
	e = bswap_16(e);

	printf("%04x\n", b);
	printf("%04x\n", c);
	printf("%04x\n", d);
	printf("%04x\n", e);
}