#include "src/htl/hqueue.h"
#include <iostream>

int main()
{
	htl::queue<int> i;
	i.push(1), i.push(2), i.push(3);
	while(!i.empty())
	{
		std::cout << i.front() << std::endl;
		i.pop();
	}
	getchar();
	getchar();
}