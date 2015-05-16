#include<stdio.h>

typedef int (*func)(int a, int b);
int add(int a, int b){return a + b; }
int sub(int a, int b){return a - b; }
int result(int a, int b, func result){return result(a, b);}





int main()
{
	printf("%d\n",result(5, 6, sub));
	int (*ptr)(int a, int b);
	ptr = add;
	printf("%d\n",ptr(5,6));

	getchar();
}