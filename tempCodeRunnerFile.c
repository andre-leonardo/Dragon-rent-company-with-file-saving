#include <stdio.h>
#include <string.h>

void halve(int n)
{
	int a;
	a = n;
	while(a>1)
	{
		a = a/2;
		n = n+a;
		printf("%d", a);
	}
	printf("%d", n);
}

int main()
{
	halve(25);
}