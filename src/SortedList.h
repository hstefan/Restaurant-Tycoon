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

#ifndef HUGO_SORTEDLIST_H
#define HUGO_SORTEDLIST_H

#include "htl/hlist.h"

namespace rty
{
	template <class T>
	class SortedList
	{
	public:
		typedef typename htl::list<T>::iterator iterator;
		typedef typename htl::list<T>::const_iterator const_iterator;

		SortedList();

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		void insert(const T& val);
		iterator remove(iterator it);

	private:
		htl::list<T> m_list;
	};

	template <class T>
	SortedList<T>::SortedList()
		: m_list()
	{}

	template <class T>
	typename SortedList<T>::iterator SortedList<T>::begin()
	{
		return m_list.begin();
	}

	template <class T>
	typename SortedList<T>::iterator SortedList<T>::end()
	{
		return m_list.end();
	}

	template <class T>
	typename SortedList<T>::const_iterator SortedList<T>::begin() const
	{
		return m_list.begin();
	}

	template <class T>
	typename SortedList<T>::const_iterator SortedList<T>::end() const
	{
		return m_list.begin();
	}
	
	template <class T>
	typename SortedList<T>::iterator SortedList<T>::remove(iterator it)
	{
		return m_list.erase(it);
	}

	template <class T>
	void SortedList<T>::insert(const T& val)
	{
		iterator it;
		for(it = begin(); it != end(); it++)
		{
			if(*it >= val)
				break;
		}
		m_list.insert(it, val);
	}
}

#endif