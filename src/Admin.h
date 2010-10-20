#ifndef RTY_ADMIN_H
#define RTY_ADMIN_H

namespace rty
{
	class Admin
	{
	public:
		void consultMovimentation();
		void insertItem();
		void removeItem();
		void listItems(unsigned int);
		void seachItemByCode(unsigned int);
	};
}

#endif