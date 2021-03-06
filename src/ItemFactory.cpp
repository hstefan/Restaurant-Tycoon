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

#include "ItemFactory.h"

namespace rty
{
	SearchBinTree<int, Item> ItemFactory::item_cod;
	SearchBinTree<std::string, Item> ItemFactory::item_desc(false);
	SearchBinTree<double, Item> ItemFactory::item_preco(false);
	SortedList<Item> ItemFactory::item_l;

	Item ItemFactory::createItem(int cod, const std::string desc, double preco, int t_prep, double custo)
	{
		Item it = { cod, desc, preco, t_prep, custo };

		if(!item_cod.insert(it.codigo, it))
		{
			std::cout << "Ja existe um item com esse codigo, insercao cancelada" << std::endl;
			return it;
		}
			
		SearchBinTree<int, Item>::iterator iter = item_cod.search(it.codigo);

		if(iter.node != 0)
		{
			SearchBinTree<int, Item>::ValueType v = *iter;
			item_l.insert(v.second);
			if(!item_desc.insert(v.second.descricao, v.second))
			{
				std::cout << "Ja existe um item com essa descricao, insercao cancelada" << std::endl;
				item_cod.remove(v);
				return it;
			}

			else
			{
				if(! item_preco.insert(v.second.preco, v.second))
				{
					std::cout << "Ja existe um item com esse preco, insercao cancelada" << std::endl;
					item_cod.remove(v);
					item_desc.remove(v.second.descricao);
					return it;
				}
			}
		}
		return it;
	}

	std::ostream& ItemFactory::printSortedByCod(std::ostream& stream)
	{
		SortedList<Item>::iterator it = item_l.begin();
		while(it != item_l.end())
		{
			stream << *it << std::endl;
			it++;
		}
		return stream;
	}

	std::ostream& ItemFactory::printSortedByDescricao(std::ostream& stream, SearchBinTree<std::string, Item>::iterator& it)
	{
		if(it.node == 0)
			return stream;
		printSortedByDescricao(stream, it.left());
		stream << (*it).second << std::endl;
		printSortedByDescricao(stream, it.right());
		return stream;
	}

	std::ostream& ItemFactory::printSortedByPrice(std::ostream& stream, SearchBinTree<double, Item>::iterator& it)
	{
		if(it.node == 0)
			return stream;
		printSortedByPrice(stream, it.left());
		stream << (*it).second << std::endl;
		printSortedByPrice(stream, it.right());
		return stream;
	}

	SearchBinTree<int, Item>::iterator ItemFactory::searchByCode(int code)
	{
		return item_cod.search(code);
	}

	bool ItemFactory::removeItem(int code)
	{
		SearchBinTree<int, Item>::iterator it = item_cod.search(code);
		if(it.node == 0)
			return false;
	
		item_desc.remove((*it).second.descricao);
		item_preco.remove((*it).second.preco);
		for(SortedList<Item>::iterator itl = item_l.begin(); itl != item_l.end(); itl++)
		{
			if((*itl).codigo == code)
			{
				item_l.remove(itl);
				return true;
			}
		}
		return false;
	}

}