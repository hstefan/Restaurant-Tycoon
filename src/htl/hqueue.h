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

#ifndef HUGO_H_QUEUE_H
#define HUGO_H_QUEUE_H

#include "hlist.h"

namespace htl
{
	template < class T, class Container = htl::list<T> >
	class queue
	{
	public:
		explicit queue(const Container& ctnr = Container());

		typedef typename Container::size_type size_type;
		typedef typename Container::value_type value_type;

		bool empty() const;
		size_type size() const;

		value_type& front();
		const value_type& front() const;
		value_type& back();
		const value_type& back() const;

		void push(const T& x);
		void pop();

	private:
		Container ctnr;
	};

	template <class T, class Container>
	queue<T, Container>::queue(const Container& ctnr = Container())
		: ctnr(ctnr)
	{}

	template <class T, class Container>
	bool queue<T, Container>::empty() const
	{
		return ctnr.empty();
	}
	
	template <class T, class Container>
	typename queue<T,Container>::size_type queue<T,Container>::size() const
	{
		return ctnr.size();
	}

	template <class T, class Container>
	typename queue<T, Container>::value_type& queue<T, Container>::front()
	{
		return ctnr.front();
	}

	template <class T, class Container>
	typename const queue<T, Container>::value_type& queue<T, Container>::front() const
	{
		return ctnr.front();
	}

	template <class T, class Container>
	typename queue<T, Container>::value_type& queue<T, Container>::back()
	{
		return ctnr.back();
	}

	template <class T, class Container>
	typename const queue<T, Container>::value_type& queue<T, Container>::back() const
	{
		return ctnr.back();
	}

	template <class T, class Container>
	void queue<T, Container>::push(const T& x)
	{
		ctnr.push_back(x);
	}

	template <class T, class Container>
	void queue<T, Container>::pop()
	{
		ctnr.pop_front();
	}
}

#endif