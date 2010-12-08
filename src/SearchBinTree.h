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

#ifndef RTY_SEARCH_BINTREE
#define RTY_SEARCH_BINTREE

#include "BinTree.h"

namespace rty
{
	namespace detail
	{
		template<class T>
		struct TreeNode
		{
			TreeNode* tleft;
			T* val;
			TreeNode* tright;

			TreeNode(const T& val, TreeNode* l = 0; TreeNode* r)
				: tleft(l), val(new T(val)), tright(r)
			{}
		};

		template <class Key, class Ty>
		class SearchBinTreeIter : public BinTreeIterator<Key, Ty>
		{
		private:
			TreeNode<ValueType>* node;

		public:

			SearchBinTreeIter()
				: node(0)
			{}

			SearchBinTreeIter(TreeNode<ValueType>* v)
				: node(v)
			{}

			BinTreeIterator toRoot();

			BinTreeIterator toLeft()
			{
				node = node->tleft;
				return *this;
			}

			BinTreeIterator toRight()
			{
				node = node->tright;
				return *this;
			}

			const ValueType& operator*() const
			{
				return node->val;
			}

			ValueType& operator*()
			{
				return node->val;
			}

			BinTreeIterator<Key,Ty>& operator=(const BinTreeIterator& t)
			{
				TreeNode<ValueType>* n = new BinTreeIterator<Key, Ty>();
				n->tleft = &t.tleft;
				n->tleft = &t.tright;
				return *this;
			}

			bool hasLeft()
			{
				return node->tleft == 0;
			}

			bool hasRight()
			{
				return node->tright == 0;
			}
		};
	}

	template <class Key, class Ty>
	class SearchBinTree : public BinTree<Key, Ty>
	{
	public:
		bool insert(const ValueType&) = 0;
		bool insert(const KeyType&, const Value&) = 0;

		bool remove(const Key&) = 0;
		bool remove(const ValueType&) = 0;
		
		iterator search(Key&) = 0;
		iterator search(ValueType&) = 0;
		const_iterator search(Key&) const = 0;
		const_iterator search(ValueType&) const = 0;
		iterator operator[](const Key&) = 0;
		const_iterator operator[](const Key&) const = 0;

		bool empty() const = 0;
		iterator root() = 0;
		const_iterator root() const = 0;
	};


} // namespace rty

#endif