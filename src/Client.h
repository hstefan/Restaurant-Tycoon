#ifndef RT_CLIENT_H
#define RT_CLEINT_H

#include "TableGroup.h"

namespace rty
{
	class Client
	{
	public:
		void askForATable();
		void askForPark();
		void askForUnpark();
		void leaveQueue();
		void leaveRestaurant();
		void orderItems();
		void payBill();
	protected:
		TableGroup* table;
	};
}

#endif