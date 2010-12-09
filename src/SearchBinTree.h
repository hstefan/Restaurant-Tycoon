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

#include <utility>

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

			TreeNode(const T& val, TreeNode* l = 0, TreeNode* r = 0)
				: tleft(l), val(new T(val)), tright(r)
			{}
		};

		template <class Key, class Ty>
		class SearchBinTreeIter
		{
		public:
			typedef std::pair<Key, Ty> ValueType;
			TreeNode<ValueType>* node;
			
			SearchBinTreeIter()
				: node(0)
			{}

			SearchBinTreeIter(TreeNode<ValueType>* v)
				: node(v)
			{}

			SearchBinTreeIter left() const
			{
				return SearchBinTreeIter<Key, Ty>(node->tleft);
			}

			SearchBinTreeIter right() const
			{
				return SearchBinTreeIter<Key, Ty>(node->tright);
			}

			SearchBinTreeIter toRoot() {
				return SearchBinTreeIter<Key, Ty>(*this);
			}

			SearchBinTreeIter toLeft()
			{
				node = node->tleft;
				return SearchBinTreeIter<Key, Ty>(*this);
			}

			SearchBinTreeIter toRight()
			{
				node = node->tright;
				return SearchBinTreeIter<Key, Ty>(*this);
			}

			const ValueType& operator*() const
			{
				return *node->val;
			}

			ValueType& operator*()
			{
				return *node->val;
			}

			SearchBinTreeIter operator=(const SearchBinTreeIter& t)
			{
				TreeNode<ValueType>* n = new TreeNode<ValueType>(t.val, &t.tleft, &&t.tright);
				node = n;
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
	class SearchBinTree
	{
	public:
		typedef std::pair<Key, Ty>						ValueType;
		typedef typename Key							KeyType;
		typedef typename Ty								Value;
		typedef detail::SearchBinTreeIter<Key, Ty>		iterator;
		typedef detail::SearchBinTreeIter<Key, Ty>		const_iterator;
		typedef detail::TreeNode<ValueType>				node;

		SearchBinTree()
			: root(0), sz(0)
		{}

		bool insert(const ValueType& x) 
		{
			return _insert(root, x).second;
		}

		bool insert(const KeyType& k, const Value& v)
		{
			return insert(ValueType(k, v));
		}

		bool remove(const KeyType& k)
		{
			return _remove(root, k).second;
		}

		bool remove(const ValueType& v) 
		{
			return _remove(root, v.first).second;
		}
		
		iterator search(const Key& k)
		{
			return iterator(_search(root,k).first);
		}

		iterator search(const ValueType& v)
		{
			return search(v.first);
		}

		/*const_iterator search(const Key&) const 
		{
			return const_iterator(_search(root,k).first);
		}

		const_iterator search(const ValueType&) const
		{
			return search(v.first);
		}*/

		iterator operator[](const Key& k)
		{
			return iterator(_search(root,k).first);
		}

		/*const_iterator operator[](const Key& k) const
		{
			return const_iterator(_search(root,k).first);
		}*/

		bool empty() const
		{
			return root == 0;
		}

		iterator begin() 
		{
			return iterator(root);
		}

		const_iterator begin() const
		{
			return const_iterator(root);
		}
	
	protected:
		std::pair<node*,bool> _insert(node* t, ValueType v)
		{
			if(t == 0)
			{
				t = new node(v);
				if(root == 0)
					root = t;
				sz++;
				return std::pair<node*,bool>(t, true);
			}
			if(v.first == t->val->first)
				return std::pair<node*,bool>(t, false);
			else if (v.first > t->val->first)
				t->tright = _insert(t->tright, v).first;
			else
				t->tleft = _insert(t->tleft, v).first;
			return std::pair<node*,bool>(t, false);
		}

		std::pair<node*,bool> _remove(node* t, const KeyType v)
		{
			if(t == 0)
				return std::pair<node*,bool>(t, false); 
			else if (v > t->val->first)
				t->tright = _remove(t->tright, v).first;
			else if (v < t->val->first)
				t->tleft = _remove(t->tleft, v).first;
			else 
			{
				if(t->tleft == 0 && t->tright == 0)
				{
					delete t;
					t = 0;
				}
				else if(t->tleft == 0)
				{
					node* n = t;
					if(n == root)
						root = t->tright;
					t = t->tright;
					delete n;
				}
				else if(t->tright == 0)
				{
					node* n = t;
					if(n == root)
						root = t->tleft;
					t = t->tleft;
					delete n;
				}
				else
				{
					node* f = t->tleft;
					while(f->tleft != 0)
						f = f->tleft;

					if(t == root)
						root = f;
					
					std::swap(t->val, f->val);
					t->tleft = _remove(t->tleft, v).first;
				}
				sz--;
				if(sz == 0)
					root = 0;
			}
			return std::pair<node*,bool>(t, true);
		}

		std::pair<node*,bool> _search(node* t, const KeyType k)
		{
			if(t == 0)
				return std::pair<node*,bool>(t, false);
			else if (t->val->first == k)
				return std::pair<node*,bool>(t, true);
			else if (k > t->val->first)
				return _search(t->tright, k);
			else 
				return _search(t->tleft, k);

		}

	private:
		detail::TreeNode<ValueType>* root;
		int sz;
	};


} // namespace rty

#endif