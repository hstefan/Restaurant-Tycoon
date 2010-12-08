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
		BinTreeIterator(const Key&, const Ty&);
		BinTreeIterator();

		virtual BinTreeIterator toRoot()
		{ return BinTereIterator(); }
		virtual BinTreeIterator toLeft() = 0;
		virtual BinTreeIterator toRight() = 0;

		virtual const key& operator*() const = 0;
		virtual key& operator*() = 0;
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