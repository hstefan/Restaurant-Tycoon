#include "src\htl\hvector.h"
#include <iostream>

int main()
{
	htl::vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	for(htl::vector<int>::iterator it = a.begin(); it != a.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	getchar();
	getchar();
}