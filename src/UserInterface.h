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

#include "htl/hvector.h"
#include "htl/hqueue.h"

#include "Chronometer.h"
#include "Balcony.h"
#include "Chef.h" 

#include "RestaurantRegistry.h" 

namespace rty
{
	class TableMatrix;

	class UserInterface
	{
	public:
		UserInterface()
			: client_queue(), groups(), balc(), out_balc(), chef(&balc, &out_balc), reg()
		{}

		void start();

	private:
		void mainMenu();

		void menuItems();
		void insertItem();
		void removeItem();
		void listaItem();
		void menuRelatory();

		void addClients();
		void toQueue(int n);
		void showQueue();
		void leaveQueue();

		void callNextOnQueue();

		void leaveRestaurant();
		void makeOrder();
		void checkReadyOrders();

		void printCost();
		void printGain();
		void listOrders();
		void listClients();
		void listActive();

		group_data* getTableGroup(int no);
		
		TableMatrix* tm;

		htl::list<group_data> client_queue;
		htl::list<group_data> groups;
		Balcony balc;
		Balcony out_balc;
		Chef chef;

		RestaurantRegistry reg;
	};
}

#endif