#include "src/SortedList.h"
#include "src/SearchBinTree.h"
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

	rty::SearchBinTree<int, double> i;
	i.insert(1, 2.3);
	i.insert(2, 4.3);
	i.search(1);
	i.remove(1);
	i.remove(2);
	i.remove(3);
	getchar();
	getchar();
}