#ifndef RTY_TABLE_H
#define RTY_TABLE_H

#include "Chair.h"
#include "Client.h"

namespace rty
{
	class Table
	{
	public:
		static const unsigned int N_CHAIRS 2;
	private:
		friend class TableGroup;
		Chair[N_CHAIRS] chairs;
	};
}

#endif