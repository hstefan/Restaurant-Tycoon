#include "src/SortedList.h"
#include <iostream>

int main()
{
	rty::SortedList<int> a;
	a.insert(5);
	a.insert(3);
	a.insert(4);
	a.insert(7);
	a.insert(1);
	a.insert(9);

	for(rty::SortedList<int>::iterator it = a.begin(); it != a.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	getchar();
	getchar();
}