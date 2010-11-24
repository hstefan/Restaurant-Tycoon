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

#ifndef RTY_BILLMANAGER_H
#define RTY_BILLMANAGER_H

#include "htl/hlist.h"
#include "TableGroup.h"
#include "Order.h"

namespace rty
{
	namespace detail
	{
		struct Bill
		{
			TableGroup* table;
			htl::list<Order> orders;
			bool left;

			Bill()
				: table(0), orders(), left(false)
			{}
		};
	}

	class BillManager
	{
	private:
		static BillManager _instance;

		BillManager();
	protected:
		friend class Waiter;

		static BillManager& getInstance()
		{
			return _instance;
		}
		Bill* getBill(const TableGroup& table);
		bool notifyLeft(const TableGroup& table);
	};
}

#endif