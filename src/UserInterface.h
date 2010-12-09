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

#ifndef RTY_USER_INTERFACE_H
#define RTY_USER_INTERFACE_H

#include <iostream>
#include "TableMatrix.h"
#include "htl/hqueue.h"
#include "Chronometer.h" 

namespace rty
{
	class UserInterface
	{
	public:
		UserInterface()
		{}
		void start();
	private:
		void mainMenu();

		void menuItems();
		void insertItem();
		void removeItem();
		void listaItem();

		void addClients();
		void toQueue(int n);
		void showQueue();
		void leaveQueue();

		void callNextOnQueue();

		void leaveRestaurant();
		
		TableMatrix* tm;

		struct group_data
		{
			htl::vector<Table*> tables;
			int sz;
			time_t arrival;
			time_t gottable;
			htl::list<Item> orders;

			group_data(int s, time_t arr, time_t gtb, htl::vector<Table*> tab = htl::vector<Table*>())
				: tables(tab), sz(s), arrival(arr), gottable(gtb), orders()
			{}

			group_data& operator=(const group_data& g)
			{
				tables = g.tables;
				sz = g.sz;
				arrival = g.arrival;
				gottable = g.gottable;
				orders = g.orders;
				return *this;
			}

			group_data()
			{}
		};

		htl::list<group_data> client_queue;
		htl::list<group_data> groups;
	};
}


#endif