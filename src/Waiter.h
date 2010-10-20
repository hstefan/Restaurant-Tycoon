#ifndef RTY_WAITER_H
#define RTY_WAITER_H

#include "Client.h"
#include "TableGroup.h"

namespace rty
{
	class Waiter
	{
	public:
		void allocateTableGroup(const Client&);
		void askForPreparaton();
		void deliverBill(const TableGroup&);
		void deliverRequest(const TableGroup&);
		void getRequest(const TableGroup&);
	};
}

#endif