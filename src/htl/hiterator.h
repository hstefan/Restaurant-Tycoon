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

#ifndef HUGO_H_ITERATOR_H__
#define HUGO_H_ITERATOR_H__

namespace htl
{	
	template <class Iter>
	class reverse_iterator
	{
	public:
		typedef typename Iter::reference reference_type;

		reverse_iterator(const reverse_iterator& rit);
		reverse_iterator(const Iter& it);

		reverse_iterator& operator=(const reverse_iterator<Iter>& rit);
		reverse_iterator& operator++();
		reverse_iterator& operator++(int);
		reverse_iterator& operator--();
		reverse_iterator& operator--(int);
		bool operator==(const reverse_iterator<Iter>& rit);
		bool operator!=(const reverse_iterator<Iter>& rit);
		reference_type operator*();

	private:
		Iter _iterator;
	};

	template <class Iter>
	reverse_iterator<Iter>::reverse_iterator(const reverse_iterator<Iter>& rit)
		: _iterator(rit._iterator)
	{}

	template <class Iter>
	reverse_iterator<Iter>::reverse_iterator(const Iter& it)
		: _iterator(it)
	{}

	template <class Iter>
	reverse_iterator<Iter>& reverse_iterator<Iter>::operator=(const reverse_iterator<Iter>& rit)
	{
		_iterator = rit._iterator;
	}

	template <class Iter>
	reverse_iterator<Iter>& reverse_iterator<Iter>::operator++()
	{
		_iterator++;
		return *this;
	}

	template <class Iter>
	reverse_iterator<Iter>& reverse_iterator<Iter>::operator++(int)
	{
		reverse_iterator it = *this;
		_iterator++;
		return *it;
	}	

	template <class Iter>
	reverse_iterator<Iter>& reverse_iterator<Iter>::operator--()
	{
		_iterator--;
		return *this;
	}

	template <class Iter>
	reverse_iterator<Iter>& reverse_iterator<Iter>::operator--(int)
	{
		reverse_iterator it = *this;
		_iterator--;
		return *it;
	}
	
	template <class Iter>
	bool reverse_iterator<Iter>::operator==(const reverse_iterator<Iter>& rit)
	{ return _iterator == rit._iterator;}
	
	template <class Iter>
	bool reverse_iterator<Iter>::operator!=(const reverse_iterator<Iter>& rit)
	{ return _iterator != rit._iterator;}

	template <class Iter>
	typename reverse_iterator<Iter>::reference_type reverse_iterator<Iter>::operator*()
	{ return *_iterator; }
}

#endif
