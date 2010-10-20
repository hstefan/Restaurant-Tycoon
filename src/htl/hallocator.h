
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

#ifndef HUGO_ALLOCATOR_H__
#define HUGO_ALLOCATOR_H__

#include <new>

namespace htl
{
	template <class T> class allocator;
	template <> class allocator<void>
	{
	public:
		typedef void*           pointer;
		typedef const void*     const_pointer;
		typedef void            value_type;
		template <class U> struct rebind { typedef allocator<U> other; };
	};

	template <class T>
	class allocator
	{
	public:
		typedef size_t               size_type;
		typedef size_t               difference_type;
		typedef T*                   pointer;
		typedef const T*             const_pointer;
		typedef T&                   reference;
		typedef const T&             const_reference;
		typedef const T              value_type;
		template <class U>  struct rebind {typedef allocator<U> other;};

		allocator() throw();
		allocator(const allocator&) throw();
		template <class U> allocator(const allocator<U>&) throw();
		~allocator() throw();

		pointer adress(reference x) const;
		const_pointer adress(const_reference x) const;
		pointer allocate(
			size_type, typename allocator<void>::const_pointer hint = 0);
		void deallocate(pointer p, size_type n = 0);
		size_type max_size() const throw();

		void construct(pointer p, const T& val);
		void destroy(pointer p);
	private:
		T value;
	};

	template <class T>
	allocator<T>::allocator() throw()
	{}

	template <class T>
	allocator<T>::allocator(const allocator<T>&) throw()
	{}

	template <class T>
	template <class U>
	allocator<T>::allocator(const allocator<U>&) throw()
	{}

	template <class T>
	allocator<T>::~allocator() throw()
	{}

	template <class T>
	typename allocator<T>::pointer allocator<T>::adress(reference x) const 
	{
		return &value;
	}

	template <class T>
	typename allocator<T>::const_pointer allocator<T>::adress(const_reference x) const
	{
		return &value;
	}

	template <class T>
	typename allocator<T>::pointer allocator<T>::allocate(size_type x, allocator<void>::const_pointer hint = 0)
	{
		return (T*) new unsigned char[x * sizeof(T*)];
	}

	template <class T>
	void allocator<T>::deallocate(pointer p, size_type n = 0)
	{
		delete[] p;
	}

	template <class T>
	size_t allocator<T>::max_size() const
	{
		size_type count = (size_type)(-1) / sizeof(T);
		return (0 < count ? count : 1);
	}

	template <class T>
	void allocator<T>::construct(pointer p, const T& val)
	{
		new ((void*) p) T(val);
	}

	template <class T>
	void allocator<T>::destroy(pointer p)
	{
		((T*)p)->~T();
	}
}
#endif