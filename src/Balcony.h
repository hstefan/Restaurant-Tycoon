/*
 *  Copyright (c) 2010
 *    Hugo Stefan Kaus Puhlmann <hugopuhlmann@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/

#ifndef RTY_BALCONY_H
#define RTY_BALCONY_H

#include "htl/hqueue.h"
#include "htl/hlist.h"
#include "Item.h"
#include <utility>

namespace rty
{
	class Table;
	
	class Balcony
	{
	public:
		Balcony();

		void leaveOrder(const Item& Item, Table* table);
		void leaveOrder(const htl::list<Item>& ords, Table* table);
		std::pair<Item, Table*> nextOrder();
		bool hasNext() const;
	private:
		htl::queue<std::pair<Item, Table*>> orders;
	};

	inline Balcony::Balcony()
		: orders()
	{}

	inline void Balcony::leaveOrder(const Item& order, Table* table)
	{
		orders.push(std::pair<Item, Table*>(order,table));
	}

	inline void Balcony::leaveOrder(const htl::list<Item>& ords, Table* table)
	{
		for(htl::list<Item>::const_iterator it = ords.begin(); it != ords.end(); it++)
			orders.push(std::pair<Item, Table*>(*it, table));
	}

	inline std::pair<Item, Table*> Balcony::nextOrder()
	{
		std::pair<Item, Table*> ord = orders.front();
		orders.pop();
		return ord;
	}

	inline bool Balcony::hasNext() const
	{
		return !orders.empty();
	}

}

#endif