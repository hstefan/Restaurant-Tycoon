#include "src/htl/hlist.h"
#include <iostream>

int main()
{
	htl::list<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);

	for(htl::list<int>::const_iterator it = a.begin(); it != a.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	
	getchar();
	getchar();
}