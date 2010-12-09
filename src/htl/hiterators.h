
/*
 *  Copyright (c) 2010 
 * 	Hugo Stefan Kaus Puhlmann <hugopuhlmann@gmail.com>
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
*/

#ifndef HUGO_H_ITERATORS_H__
#define HUGO_H_ITERATORS_H__

namespace htl
{

	template <class T>
	class randomAcessIterator 
	{
	public:
		typedef T*				pointer;
		typedef T&				reference;
		typedef	T				value_type;
		typedef unsigned int	diff_type;
		
		randomAcessIterator(pointer x) : ptr(x) {}
		randomAcessIterator(const randomAcessIterator<T>& x) : ptr(x.ptr) {}
		
		randomAcessIterator& operator++() 
		{
			++ptr;
			return *this;
		}
		randomAcessIterator& operator++(int)
		{
			ptr++;
			return *this;
		}

		randomAcessIterator& operator--()
		{
			--ptr;
			return *this;
		}
		randomAcessIterator& operator--(int)
		{
			ptr--;
			return *this;
		}
		bool operator==(const randomAcessIterator<T>& x)
		{
			return x.ptr == this->ptr;
		}
		bool operator!=(const randomAcessIterator<T>& x)
		{
			return x.ptr != this->ptr;
		}
		reference operator*()
		{
			return *ptr;
		}
		reference operator[](int i)
		{
			return ptr[i];
		}
		reference operator=(const randomAcessIterator<T>& x)
		{
			ptr = x.pr;
			return *this;
		}
		diff_type operator-(const randomAcessIterator<T> x)
		{
			return (ptr - x.ptr)/sizeof(pointer);
		}

	private:
		pointer ptr;
	};

	template <class T, class C>
	class bidirectionalIterator
		{
		public:
			typedef C				container;
			typedef T*				pointer;
			typedef T&				reference;
			typedef T				value_type;
			typedef unsigned int	diff_type;
			bidirectionalIterator(C* x = 0);
			bidirectionalIterator(const bidirectionalIterator<T, C>& it);
			
			bidirectionalIterator& operator=(const bidirectionalIterator<T, C>& it)
			{
				ptr = it.ptr;
				return *this;
			}
			bidirectionalIterator& operator++()
			{
				ptr = ptr->next;
				return *this;
			}
			bidirectionalIterator& operator++(int)
			{
				ptr = ptr->next;
				return *this;
			}
			bidirectionalIterator& operator--()
			{   
				ptr = ptr->prev;
				return *this;
			}
			bidirectionalIterator& operator--(int)
			{
				ptr = ptr->prev;
				return *this;
			}
			bidirectionalIterator& operator==(const bidirectionalIterator<T,C>& it)
			{ return ptr == it; }
			bidirectionalIterator& operator!=(const bidirectionalIterator<T,C>& it)
			{ return ptr != it; }
			reference operator*()
			{ return ptr->value;}

		private:
			C* ptr;
		};
}

#endif