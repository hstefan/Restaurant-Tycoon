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