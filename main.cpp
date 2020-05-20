#include <stdio.h>
#include "String.h"

int main()
{
	String str = "123457987";
	printf("%s", str.getCstr());
	return 0;
}