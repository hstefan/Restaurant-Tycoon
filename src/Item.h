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

#ifndef RTY_ITEM_H
#define RTY_ITEM_H

#include <string>
#include <iostream>

namespace rty
{
	struct Item
	{
		int codigo;
		std::string descricao;
		double preco;
		int tempo_p;
		double custo;

		bool operator<(const Item& it)
		{
			return codigo < it.codigo;
		}

		bool operator<=(const Item& it)
		{
			return codigo <= it.codigo;
		}

		bool operator>=(const Item& it)
		{
			return codigo >= it.codigo;
		}

		friend std::ostream& operator<< (std::ostream &out, Item& it)
		{
			out << "Codigo: " << it.codigo << std::endl;
			out << "Descricao: " << it.descricao << std::endl;
			out << "Preco: " << it.preco << std::endl;
			out << "Tempo de preparo: " << it.tempo_p << "s" << std::endl;
			return out;
		}
	};
}

/*std::ostream& rty::Item::operator<< (std::ostream &out, rty::Item& it)
{
		
}*/

#endif