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

#ifndef HUGO_REGISTRY_H
#define HUGO_REGISTRY_H

#include "htl/hlist.h"
#include "UserInterface.h"

namespace rty
{
	class RestaurantRegistry
	{
	public:
		typedef UserInterface::group_data group_data;

		struct gp_time
		{
			group_data gd;
			time_t left_at;
		};

		struct ord_group
		{
			group_data gp;
			htl::list<Item> ord;
		};
		
		void registryGroup(const group_data& gp)
		{
			group_active.push_back(gp);
		}

		void notifyGroupLeft(const group_data& gp)
		{
			int no_table = gp.tables.front()->num;
			for(htl::list<group_data>::iterator it = group_active.begin(); it != group_active.end(); it++)
			{
				for(htl::vector<Table*>::iterator iv = (*it).tables.begin(); iv != (*it).tables.end(); it++)
				{
					if((*iv)->num == no_table)
					{
						group_active.erase(it);
						gp_time g = {(*it), Chronometer::getInstance().getCurrent()};
						groups_left.push_back(g);
						no_table = -1;
						break;
					}
				}
				if(no_table == -1)
					break;
			}
		}
		
		void registryOrder(const group_data& gp, const htl::list<Item>& order)
		{
			ord_group o = { gp , order };
			orders.push_back(o);
		}

		

	private:
		htl::list<gp_time> groups_left;
		htl::list<group_data> group_active;
		htl::list<ord_group> orders; 
	};
}

#endif