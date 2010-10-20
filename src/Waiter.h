/*
* Copyright (c) <2010> <Hugo S. K. Puhlmann>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*/

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