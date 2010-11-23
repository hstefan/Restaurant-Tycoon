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

#ifndef HUGO_H_LIST__
#define HUGO_H_LIST__

#include "hallocator.h"
#include "hlist_node.h"
#include "hiterator.h"

namespace htl 
{
	namespace detail 
	{
		template <class T>
		class list_iterator 
		{
		public:
			typedef T*					pointer;
			typedef T&					reference_type;
			typedef T					value_type;
			typedef unsigned int		diff_type;
			list_iterator(hlist_node<T>* i);
			list_iterator(const list_iterator<T>& it);
			list_iterator();

			list_iterator& operator=(const list_iterator<T>& it);
			list_iterator& operator++();
			list_iterator operator++(int);
			list_iterator& operator--();
			list_iterator& operator--(int);
			bool operator==(const list_iterator<T>& it);
			bool operator!=(const list_iterator<T>& it);
			reference_type operator*();

		private:
			template <class S, class U>
			friend class list;

			template <class I>
			friend class const_list_iterator;

			hlist_node<T>* ptr;
		};

		template <class T>
		list_iterator<T>& list_iterator<T>::operator=(const list_iterator<T>& it)
		{
			ptr = it.ptr;
			return *this;
		}

		template <class T>
		list_iterator<T>& list_iterator<T>::operator++()
		{
			ptr = ptr->next;
			return *this;
		}

		template <class T>
		list_iterator<T> list_iterator<T>::operator++(int)
		{
			list_iterator i = *this;
			ptr = ptr->next;
			return i;
		}

		template <class T>
		list_iterator<T>& list_iterator<T>::operator--()
		{   
			ptr = ptr->prev;
			return *this;
		}

		template <class T>
		list_iterator<T>& list_iterator<T>::operator--(int)
		{
			list_iterator i = *this;
			ptr = ptr->prev;
			return i;
		}

		template <class T>
		bool list_iterator<T>::operator==(const list_iterator<T>& it)
		{ return ptr == it.ptr; }
		
		template <class T>
		bool list_iterator<T>::operator!=(const list_iterator<T>& it)
		{ return ptr != it.ptr; }
		
		template <class T>
		typename list_iterator<T>::reference_type list_iterator<T>::operator*()
		{ return ptr->value;}
		
		template <class T>
		list_iterator<T>::list_iterator(hlist_node<T>* i)
		{ ptr = i; }

		template <class T>
		list_iterator<T>::list_iterator(const list_iterator<T>& it) 
		{ ptr = it.ptr; }
		
		template <class T>
		list_iterator<T>::list_iterator() 
		{ ptr = 0; }	

		template <class T>
		class const_list_iterator 
		{
		public:
			typedef T*							pointer;
			typedef const T&					reference_type;
			typedef T							value_type;
			typedef unsigned int				diff_type;

			const_list_iterator(hlist_node<T>* i);
			const_list_iterator(const list_iterator<T>& it);
			const_list_iterator(const const_list_iterator<T>& cit);
			const_list_iterator();

			const_list_iterator& operator=(const const_list_iterator<T>& it);
			const_list_iterator& operator++();
			const_list_iterator operator++(int)
			const_list_iterator& operator--();
			const_list_iterator& operator--(int);
			bool operator==(const const_list_iterator<T>& it);
			bool operator!=(const const_list_iterator<T>& it);
			const_reference operator*();

		private:
			template <class S, class U>
			friend class list;

			hlist_node<T>* ptr;
		};
		template <class T>
		const_list_iterator<T>& const_list_iterator<T>::operator=(const const_list_iterator<T>& it)
		{
			ptr = it.ptr;
			return *this;
		}

		template <class T>
		const_list_iterator<T>& const_list_iterator<T>::operator++()
		{
			ptr = ptr->next;
			return *this;
		}

		template <class T>
		const_list_iterator<T> const_list_iterator<T>::operator++(int)
		{
			list_iterator i = *this;
			ptr = ptr->next;
			return i;
		}

		template <class T>
		const_list_iterator<T>& const_list_iterator<T>::operator--()
		{   
			ptr = ptr->prev;
			return *this;
		}

		template <class T>
		const_list_iterator<T>& const_list_iterator<T>::operator--(int)
		{
			list_iterator i = *this;
			ptr = ptr->prev;
			return i;
		}

		template <class T>
		bool const_list_iterator<T>::operator==(const const_list_iterator<T>& it)
		{ return ptr == it.ptr; }
		
		template <class T>
		bool const_list_iterator<T>::operator!=(const const_list_iterator<T>& it)
		{ return ptr != it.ptr; }
		
		template <class T>
		typename const_list_iterator<T>::reference_type const_list_iterator<T>::operator*()
		{ return ptr->value; }
		
		template <class T>
		const_list_iterator<T>::const_list_iterator(hlist_node<T>* i)
		{ ptr = i; }

		template <class T>
		const_list_iterator<T>::const_list_iterator(const list_iterator<T>& it) 
		{ ptr = it.ptr; }
		
		template <class T>
		const_list_iterator<T>::const_list_iterator(const const_list_iterator<T>& it) 
		{ ptr = it.ptr; }	
		
		template <class T>
		const_list_iterator<T>::const_list_iterator() 
		{ ptr = 0; }	

		template <class T>
		struct list_iters
		{
			list_iterator<T> begin;
			list_iterator<T> end;
			const_list_iterator<T> const_begin;
			const_list_iterator<T> const_end;
			
			reverse_iterator<list_iterator<T>> rbegin;
			reverse_iterator<list_iterator<T>> rend;
			reverse_iterator< const_list_iterator<T> > const_rbegin;
			reverse_iterator< const_list_iterator<T> > const_rend;

			list_iters()
				: begin(0), end(0), const_begin(0), const_end(0), rbegin(begin), rend(end),
				const_rbegin(const_begin), const_rend(const_end)
			{}
		};
	} //namespace detail 

	template <class T, class Allocator = allocator<T> >
	class list 
	{
	public:
		// types:
		typedef typename Allocator::reference								reference;
		typedef typename Allocator::const_reference							const_reference;		
		typedef typename detail::list_iterator<T>							iterator; 
		typedef typename detail::const_list_iterator<T>						const_iterator;
		typedef unsigned int												size_type;
		typedef unsigned int												difference_type;
		typedef T															value_type;
		typedef Allocator													allocator_type;
		typedef typename Allocator::pointer									pointer;
		typedef typename Allocator::const_pointer							const_pointer;
		typedef	reverse_iterator<iterator>									reverse_iterator;
		typedef	reverse_iterator<const_iterator>							const_reverse_iterator;

		//construct/copy/destroy:
		explicit list(const Allocator& = Allocator());

		explicit list(size_type n, const T& value = T(),
		const Allocator& = Allocator());
		
		template <class InputIterator>
		list(InputIterator first, InputIterator last,
			const Allocator& = Allocator());

		list(const list<T,Allocator>& x );
		~list();

		list<T,Allocator>& operator=(const list<T,Allocator>& x);

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last);

		void assign(size_type n, const T& t);
		allocator_type get_allocator() const;
		
		// iterators:
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;
		
		//capacity:
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		void resize(size_type sz, T c = T());
		// element access:
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		//modifiers:
		void push_front(const T& x);
		void pop_front();
		void push_back(const T& x);
		void pop_back();
		iterator insert(iterator position, const T& x);
		void insert(iterator position, size_type n, const T& x);
		
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator position, iterator last);
		void swap(list<T,Allocator>&);
		void clear();
		//list operations:
		void splice(iterator position, list<T,Allocator>& x);
		void splice(iterator position, list<T,Allocator>& x, iterator i);
		void splice(iterator position, list<T,Allocator>& x, iterator first,
		iterator last);
		void remove(const T& value);
		
		template <class Predicate> 
		void remove_if(Predicate pred);
		
		void unique();
		template <class BinaryPredicate>
		void unique(BinaryPredicate binary_pred);
		void merge(list<T,Allocator>& x);
		
		template <class Compare> 	
		void merge(list<T,Allocator>& x, Compare comp);
		
		void sort();
		
		template <class Compare> 	
		void sort(Compare comp);
		void reverse();
	
	protected:
		void _init_iterators();
	private:

		detail::hlist_node<T>* first;
		detail::hlist_node<T>* last;
		detail::list_iters<T> m_iterators;
		size_type m_size;
		Allocator alloc;


		template <typename U>
		friend class detail::list_iterator;
	};
	
	template <class T, class Allocator>
	list<T,Allocator>::list(const Allocator& x)
		: first(0),  last(0), m_iterators(), m_size(0), alloc(x)
	{
		first = new h_list_node(T(), 0, 0);
		last = new h_list_node(T(), first, 0);
		first->prev = last;
		
		_init_iterators();
	}

	template <class T, class Allocator>
	void list<T,Allocator>::_init_iterators()
	{
		m_iterators.begin = list_iterator<T>(first);
		m_iterators.end = list_iterator<T>(end);
		m_iterators.const_begin = const_list_iterator<T>(first);
		m_iterators.const_end = const_list_iterator<T>(end);

		m_iterators.rbegin = reverse_iterator<list_iterator<T>>(end);
		m_iterators.rend = reverse_iterator<list_iterator<T>>(begin()--);
		m_iterators.const_rbegin = const_reverse_iterator<List_iterator<T>>(end);
		m_iterators.const_rend = const_reverse_iterator<List_iterator<T>>(begin--);	
	}

	template <class T, class Allocator>
	list<T, Allocator>::list(size_type n, const T& value, 
		const Allocator& x) 
		: first(0), last(0), m_iterators(), m_size(0), alloc(x)
	{
		first = new h_list_node(T(), 0, 0);
		last = new h_list_node(T(), first, 0);
		first->prev = last;
		_init_iterators();
		while(n >= 0)
		{
			push_back(value);
			n--;
		}
	}

	template <class T, class Allocator>
	template <class InputIterator>
	list<T, Allocator>::list(InputIterator first, InputIterator last,
		const Allocator& x)
		: first(0), last(0), m_iterators(), m_size(0), alloc(x)
	{
		first = new h_list_node(T(), 0, 0);
		last = new h_list_node(T(), first, 0);
		first->prev = last;
		_init_iterators();
		while(first != last)
		{
			push_back(*first);
			first++;
		}
		push_back(*last);
	}

	template <class T, class Allocator>
	list<T, Allocator>::list(const list<T, Allocator>& x)
		: first(0), last(0), m_iterators(), m_size(0), alloc(x.get_allocator())
	{
		first = new h_list_node(T(), 0, 0);
		last = new h_list_node(T(), first, 0);
		first->prev = last;
		_init_iterators();
		
		iterator it = x.begin();
		while(it != x.last())
		{
			push_back(it);
			it++;
		}
		push_back(*it);
	}

	template <class T, class Allocator>
	list<T, Allocator>::~list()
	{
		erase(begin(), end());
	}

	template <class T, class Allocator>
	list<T,Allocator>& list<T, Allocator>::operator=(const list<T,Allocator>& x)
	{
		clear();
		for(iterator it = x.begin(); it != x.last(); it++)
			push_back(*it);
	}

	template <class T, class Allocator>
	template <class InputIterator>
	void list<T, Allocator>::assign(InputIterator first, InputIterator last)
	{
		clear();
		while(first != last)
		{
			push_back(*first);
			first++;
		}
	}
	template <class T, class Allocator>
	void list<T, Allocator>::assign(size_type n, const T& t)
	{
		for(size_type i = 0; i < n; i++)
			push_back(t);
	}

	template <class T, class Allocator>
	typename list<T, Allocator>::allocator_type list<T, Allocator>::get_allocator() const
	{ return alloc; }

	template <class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::begin() 
	{ return m_iterators.begin; }	

	template <class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::end() 
	{ return m_iterators.end; }

	template <class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::end() 
	{ return m_iterators.end; }

	template <class T, class Allocator>
	typename list<T, Allocator>::const_iterator list<T, Allocator>::begin() const 
	{ return m_iterators.const_begin; }

	template <class T, class Allocator>
	typename list<T, Allocator>::const_iterator list<T, Allocator>::end() const
	{ return m_iterators.const_end; }

	template <class T, class Allocator>
	typename list<T, Allocator>::reverse_iterator list<T, Allocator>::rbegin()
	{ return m_iterators.rbegin; }

	template <class T, class Allocator>
	typename list<T, Allocator>::reverse_iterator list<T, Allocator>::rend()
	{ return m_iterators.rend; }

	template <class T, class Allocator>
	typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::begin() const
	{ return m_iterators.const_rbegin; }
	
	template <class T, class Allocator>
	typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::rend() const
	{ return m_iterators.const_rend; }

	template <class T, class Allocator>
	bool list<T, Allocator>::empty() const
	{ return m_size == 0; }

	template <class T, class Allocator>
	typename list<T, Allocator>::size_type list<T, Allocator>::size() const
	{ return size; }

	template <class T, class Allocator>
	typename list<T, Allocator>::size_type list<T, Allocator>::max_size() const
	{ return alloc.max_size(); }

	template <class T, class Allocator>
	typename list<T, Allocator>::reference list<T, Allocator>::front()
	{ return first->value; }

	template <class T, class Allocator>
	typename list<T, Allocator>::const_reference list<T, Allocator>::front() const
	{ return first->value; }

	template <class T, class Allocator>
	typename list<T, Allocator>::reference list<T, Allocator>::back()
	{ return last->value; }

	template <class T, class Allocator>
	typename list<T, Allocator>::const_reference list<T, Allocator>::back() const
	{ return last->value; }

	template <class T, class Allocator>
	void list<T, Allocator>::push_front(const T& x) 
	{
		insert(m_iterators->begin, x);
	}

	template <class T, class Allocator>
	void list<T, Allocator>::pop_front() 
	{
		erase(m_iterators->begin);	
	}

	template <class T, class Allocator>
	void list<T, Allocator>::push_back(const T& x)
	{
		insert(m_iterators->end, x);
	}

	template <class T, class Allocator>
	void list<T, Allocator>::pop_back()
	{
		erase(m_iterators->end);
	}

	template <class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::erase(iterator position)
	{
		if(position.ptr == first || position.ptr == last )
			//TODO handle this exception : can't erase the 'base' nodes 
			return iterator(position.ptr->next);
		else
		{
			if(position.ptr->prev != 0)
				position.ptr->prev->next = position.ptr->next;
			if(position.ptr->next != 0)
				position.ptr->next->prev = position.ptr->prev;
			iterator it(position.ptr->next);
			delete position.ptr;
			return it;
		}
	}

	template <class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::erase(iterator position, iterator last)
	{
		iterator it;
		while(position != last)
			it = erase(position++);
		return it;
	}

	template <class T, class Allocator>
	typename list<T,Allocator>::iterator list<T, Allocator>::insert(iterator position, const T& x)
	{
		detail::hlist_node<T>* node = new detail::hlist_node<T>(x, position.ptr->prev, position.ptr);
		position.ptr->prev->next = node; //considering that the user will not pass an null iterator
		m_size++;
		return iterator(node);
	}

	template <class T, class Allocator>
	void list<T, Allocator>::insert(iterator position, size_type n, const T& x)
	{
		while(n != 0)
		{
			insert(position++, x);
			n--;
		}
	}

	template <class T, class Allocator>
	template <class InputIterator>
	void list<T, Allocator>::insert(iterator position, InputIterator first, InputIterator last)
	{
		while(first != last)
			insert(position++, *first++);
	}

	template <class T, class Allocator>
	void list<T, Allocator>::swap(list<T, Allocator>& x)
	{
		detail::hlist_node<T>* f = x.first;
		detail::hlist_node<T>* l = x.last;
		size_type size = x.size();
		Allocator al = x.get_allocator();

		x.first = this->first;
		x.last = this->last;
		x.m_size = this->m_size;
		x.alloc = this->alloc;

		first = f;
		last = l;
		m_size = size;
		alloc = al;
	}

	template <class T, class Allocator>
	void list<T, Allocator>::clear()
	{ erase(begin(), last()); }

	template <class T, class Allocator>
	void list<T, Allocator>::splice(iterator position, list<T, Allocator>& x)
	{
		splice(position, x, x.begin(), x.end());	
	}

	template <class T, class Allocator>
	void list<T, Allocator>::splice(iterator position, list<T, Allocator>& x, iterator i)
	{
			insert(position, *i);
			x.erase(i);
	}

	template <class T, class Allocator>
	void list<T, Allocator>::splice(iterator position, list<T, Allocator>& x, iterator first, 
					iterator last)
	{
		while(first != last)
		{
			insert(position++, *first);
			x.erase(first++);
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::remove(const T& value)
	{
		iterator it = begin();
		while(it != end())
		{
			if(*it == value)
				erase(it);
			it++;
		}
	}
	
	template <class T, class Allocator>
	template <class Predicate>
	void list<T, Allocator>::remove_if(Predicate pred)
	{
		iterator it = begin();
		while(it != end())
		{
			if(pred(*it))
				erase(it);
			it++;
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::unique()
	{
		iterator it = begin();
		value_type val;
		while(it != end())
		{
			if(*it != val)
				val = *it;
			it++;
			if(val == *it)
				it = erase(it);
		}
	}

	template <class T, class Allocator>
	template <class BinaryPredicate>
	void list<T, Allocator>::unique(BinaryPredicate binary_pred)
	{
		iterator it = begin();
		value_type val;
		while(it != end())
		{
			if(binary_pred(*it, val))
				it = erase(it);
			else
				val = *it;
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::merge(list<T, Allocator>&  x)
	{
		x.sort();
		sort();
		iterator it_x = x.begin();
		iterator it_y = this->begin();
		
		while(it_x != x.end())
		{
			if(*it_y <= *it_x)
			{
				insert(it_y, *it_x);
				it_x = x.erase(it_x);
			}
			else if(it_y != end())
				it_y++;
			else
			{
				while(it_x != x.end())
				{
					push_back(*it_x);
					it_x++;
				}
			}
		}
	}

	template <class T, class Allocator>
	template <class Compare>
	void list<T, Allocator>::merge(list<T, Allocator>& x, Compare comp)
	{
		x.sort();
		sort();
		iterator it_x = x.begin();
		iterator it_y = this->begin();
		
		while(it_x != x.end())
		{
			if(comp(*it_y,*it_x))
			{
				insert(it_y, *it_x);
				it_x = x.erase(it_x);
			}
			else if(it_y != end())
				it_y++;
			else
			{
				while(it_x != x.end())
				{
					push_back(*it_x);
					it_x = x.erase(it_x);
				}
			}
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::sort() //temporary bubble sort... but it'll be upgraded soon
	{
		iterator it_a = begin();
		iterator it_b = begin();
		while(it_a != end())
		{
			while(it_b != end())
			{
				if(*it_a > *it_b)
				{
					insert(it_b, *it_a);
					it_b = erase(it_a);
				}
				else
					it_b++;
			}
			it_b = begin();
		}
	}

	template <class T, class Allocator>
	template <class Compare>
	void list<T, Allocator>::sort(Compare comp)
	{
		iterator it_a = begin();
		iterator it_b = begin();
		while(it_a != end())
		{
			while(it_b != end())
			{
				if(comp(*it_a, *it_b))
				{
					insert(it_b, *it_a);
					it_b = erase(it_a);
				}
				else
					it_b++;
			}
			it_b = begin();
		}
	}

	template <class T, class Allocator>
	void list<T, Allocator>::reverse()
	{
		size_type sz = m_size;
		iterator it = begin();
		while(sz > 0)
		{
			push_back(*it++);
			erase(begin());
			sz--;
		}
	}
}

#endif
