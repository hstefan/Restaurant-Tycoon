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