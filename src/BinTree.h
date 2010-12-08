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

#ifndef RTY_BINTREE
#define RTY_BINTREE

namespace rty
{
	//pair of values
	template <class T, class V>
	struct pair
	{
		T v1;
		V v2;

		pair(T a, V b)
			: v1(a), v2(b)
		{}

		void operator pair(T a, V b)
		{
			v1 = a;
			v2 = b;
		}
	};

	template <class Key, class Ty>
	class BinTreeIterator
	{
	public:
		virtual BinTreeIterator toRoot()
		{ return BinTereIterator(); }
		virtual BinTreeIterator toLeft() = 0;
		virtual BinTreeIterator toRight() = 0;
		virtual bool hasLeft() = 0;
		virtual bool hasRight() = 0;

		virtual const Key& operator*() const = 0;
		virtual Key& operator*() = 0;
		virtual BinTreeIterator& operator=(const BinTreeIterator&);
	};

	template <class Key, class Ty>
	class BinTree
	{
	public:
		typedef typename KeyType				Key;
		typedef typename Type					Value;
		typedef BinTreeIterator<Key, Ty>		iterator;
		typedef BinTreeIterator<Key, Ty>		const_iterator;
		
		typedef pair<Key, Ty>					ValueType;
		
		virtual bool insert(const ValueType&) = 0;
		virtual bool insert(const KeyType&, const Value&) = 0;

		virtual bool remove(const Key&) = 0;
		virtual bool remove(const ValueType&) = 0;
		
		virtual iterator search(Key&) = 0;
		virtual iterator search(ValueType&) = 0;
		virtual const_iterator search(Key&) const = 0;
		virtual const_iterator search(ValueType&) const = 0;
		virtual iterator operator[](const Key&) = 0;
		virtual const_iterator operator[](const Key&) const = 0;

		virtual bool empty() const = 0;
		virtual iterator root() = 0;
		virtual const_iterator root() const = 0;
	};

} // namespace rty 

#endif