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

		tm = new TableMatrix(l,c);
		mainMenu();
	}

	void UserInterface::mainMenu()
	{
		bool quit = false;
		int op;
		while (!quit)
		{
			std::cout << "0 - Sair" << std::endl;
			std::cout << "1 - Gerenciar items de menu" << std::endl;
			std::cout << "2 - Adcionar clientes" << std::endl;
			std::cout << "3 - Ver fila" << std::endl;
			std::cout << "4 - Sair da fila" << std::endl;
			std::cin >> op;
			switch(op)
			{
			case 0:
				quit = true;
				break;
			case 1:
				menuItems();
				break;
			case 2:
				addClients();
				break;
			case 3:
				showQueue();
				break;
			case 4:
				leaveQueue();
				break;
			}
		}
	}

	void UserInterface::menuItems()
	{
		bool quit = false;
		int op;
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
		mainMenu();
	}

	void UserInterface::insertItem()
	{
		int cod;
		std::string desc;
		double preco, custo;
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
		std::cout << "Custo: ";
		std::cin >> custo;

		ItemFactory::createItem(cod, desc, preco, tp, custo);
	}

	void UserInterface::removeItem()
	{
		int cod;
		std::cout << "Codigo do item a ser removido: ";
		std::cin >> cod;
		ItemFactory::removeItem(cod);
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

	void UserInterface::addClients()
	{
		unsigned int ng;
		std::cout << "Digite o numero de pessoas: ";
		std::cin >> ng;
		htl::vector<Table*> mesas = tm->getTableGroup(ng);
		if(mesas.empty())
		{
			std::cout << "Desculpe, nao ha mesas disponiveis. Acompanhe-me ate a fila." << std::endl;
			toQueue(ng);
		}
		else
		{
			std::cout << "A(s) mesa(s) ";
			for(htl::vector<Table*>::iterator it = mesas.begin(); it != mesas.end(); it++)
				std::cout << (*it)->num << " ";
			std::cout << "foram especialmente escolhidas para voce!" << std::endl;
			std::cout << "Aproveite a estadia!" << std::endl;
		}
	}

	void UserInterface::toQueue(int n)
	{
		std::cout << "Recepcionista: Quem ficara responsavel pela espera de mesa? " << std::endl;
		std::cout << "Voce: ";
		std::string nome;
		std::cin.sync();
		std::getline(std::cin, nome);
		client_queue.push_back(std::pair<std::string,int>(nome,n));
		std::cout << "Recepcionista: Ok! Pronto! Voce esta na " << client_queue.size() << "a posicao na fila" << std::endl;
	}	
 
	void UserInterface::showQueue()
	{
		for(htl::list<std::pair<std::string,int>>::iterator it = client_queue.begin(); it != client_queue.end(); it++)
		{
			std::cout << "Responsavel: " << (*it).first << std::endl;
			std::cout << "Tamanho do grupo: " << (*it).second << std::endl;
		}
	}

	void UserInterface::leaveQueue()
	{
		std::cout << "Qual a posicao do elemento que deseja sair?" << std::endl;
		int a;
		std::cin >> a;
		for(htl::list<std::pair<std::string,int>>::iterator it = client_queue.begin(); it != client_queue.end(); it++)
		{
			if(--a == 0)
			{
				client_queue.erase(it);
				break;
			}
		}
		std::cout << "Volte sempre!" << std::endl;
	}
}