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

#include "UserInterface.h"
#include <string>
#include "ItemFactory.h"

namespace rty
{
	void UserInterface::start()
	{
		int l, c;
		std::cout << "Neste restaurante, as mesas serao dispostas em forma matricial" << std::endl;
		std::cout << "Numero de colunas: ";
		std::cin >> c;
		std::cout << "Numero de linhas: ";
		std::cin >> l;

		bool quit = false;
		char op;
		while (!quit)
		{
			std::cout << "0 - Sair" << std::endl;
			std::cout << "1 - Gerenciar items de menu" << std::endl;
			std::cin >> op;
			switch(op)
			{
			case 0:
				quit = true;
				break;
			case 1:
				menuItems();
				break;
			}
		}
	}

	void UserInterface::menuItems()
	{
		bool quit = false;
		char op;
		while (!quit)
		{
			std::cout << "0 - Voltar" << std::endl;
			std::cout << "1 - Inserir" << std::endl;
			std::cout << "2 - Remover" << std::endl;
			std::cout << "3 - Listar" << std::endl;
			std::cin >> op;
			switch(op)
			{
			case 0:
				quit = true;
				break;
			case 1:
				insertItem();
				break;
			case 2:
				removeItem();
				break;
			case 3:
				listaItem();
				break;
			default:
				break;
			}
		}
		start();
	}

	void UserInterface::insertItem()
	{
		int cod;
		std::string desc;
		double preco;
		int tp;

		std::cout << "Codigo: ";
		std::cin >> cod;
		std::cout << "Descricao: ";
		std::cin.sync();
		std::getline(std::cin, desc);
		std::cin.sync();
		std::cout << "Preco: ";
		std::cin >> preco;
		std::cout << "Tempo de preparacao (m): ";
		std::cin >> tp;

		ItemFactory::createItem(cod, desc, preco, tp);
		menuItems();
	}

	void UserInterface::removeItem()
	{
		int cod;
		std::cout << "Codigo do item a ser removido: ";
		std::cin >> cod;
		ItemFactory::removeItem(cod);
		menuItems();
	}

	void UserInterface::listaItem()
	{
		int op;
		std::cout << "0 - Por codigo" << std::endl;
		std::cout << "1 - Por descricao" << std::endl;
		std::cout << "2 - Por preco" << std::endl;
		lab:
		std::cin >> op;
		switch(op)
		{
		case 0:
			ItemFactory::printSortedByCod(std::cout);
			break;
		case 1:
			ItemFactory::printSortedByDescricao(std::cout);
			break;
		case 2:
			ItemFactory::printSortedByPrice(std::cout);
			break;
		default:
			goto lab;
		}
	}
 
}