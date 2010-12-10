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

#ifndef HUGO_ITEM_FACTORY_H
#define HUGO_ITEM_FACTORY_H

#include "Item.h"
#include "SearchBinTree.h"
#include "SortedList.h"
#include <iostream>

namespace rty
{
	//esta classe funciona um pouco diferente das factory padrao, apenas estou usando-a como um
	//modo "unificado" de criacao de items, pois cada vez que um item for criado ele deve ser adcionado
	//a 3 arvores e a uma lista.
	class ItemFactory
	{
	public:
		static SearchBinTree<int, Item> item_cod;
		static SearchBinTree<std::string, Item> item_desc;
		static SearchBinTree<double, Item> item_preco;
		static SortedList<Item> item_l;

		static Item createItem(int cod, const std::string desc, double preco, int t_prep, double custo);

		static std::ostream& printSortedByCod(std::ostream& stream);
		static std::ostream& printSortedByDescricao(std::ostream& stream, SearchBinTree<std::string, Item>::iterator& it = item_desc.begin());
		static std::ostream& printSortedByPrice(std::ostream& stream, SearchBinTree<double, Item>::iterator& it = item_preco.begin());
		static SearchBinTree<int, Item>::iterator searchByCode(int code);
		static bool removeItem(int code);
	};
}

#endif