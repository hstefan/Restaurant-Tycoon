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


#ifndef RTY_CHEF_H
#define RTY_CHEF_H

#include "Balcony.h"
#include "Chronometer.h"

namespace rty
{
	class Chef
	{
	public:
		inline void routine();

		inline Chef(Balcony& in_balc, Balcony& out_balc);
		inline void prepareNext();
		inline bool depositReadyOrder();
		inline bool busy();
		inline bool orderReady();
	private:
		Balcony* in_balc;
		Balcony* out_balc;
		Chronometer& cntr;
		time_t order_arrival;
		Order cur_ord;
	};

	Chef::Chef(Balcony& in_balc, Balcony& out_balc)
		: in_balc(&in_balc), out_balc(&out_balc), cntr(Chronometer::getInstance()), order_arrival(), cur_ord()
	{}

	void Chef::prepareNext()
	{
		if(in_balc != 0)
		{
			if(!busy() && in_balc->hasNext())
			{
				cur_ord = in_balc->nextOrder();
				order_arrival = cntr.getCurrent();
			}
		}
	}

	bool Chef::depositReadyOrder()
	{
		if(orderReady())
		{
			out_balc->leaveOrder(cur_ord);
			return true;
		}

		return false;
	}

	bool Chef::busy()
	{
		return orderReady() || in_balc == 0;
	}
	
	bool Chef::orderReady()
	{
		return cntr.getCurrent() - order_arrival > cur_ord.preparingTime();
	}

	void Chef::routine()
	{
		if(!busy())
		{
			depositReadyOrder();
			prepareNext();
		}
	}
}

#endif