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
#include "TableMatrix.h"

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
			std::cout << "5 - Ir embora" << std::endl;
			std::cout << "6 - Fazer pedido" << std::endl;
			std::cout << "7 - Ver pedidos prontos" << std::endl;
			std::cout << "8 - Ver relatorio" << std::endl;
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
			case 5:
				leaveRestaurant();
				break;
			case 6:
				makeOrder();
				break;
			case 7:
				checkReadyOrders();
				break;
			case 8:
				menuRelatory();
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

		if(!client_queue.empty())
		{
			std::cout << "Infelizmente, ja existe uma fila de espera, portanto acompanhe-me ate a fila." << std::endl;
			toQueue(ng);
			return;
		}
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
			std::cout << "Aproveite a estadia!" << std::endl << std::endl;
			group_data g(group_data(ng, Chronometer::getInstance().getCurrent(), Chronometer::getInstance().getCurrent(), mesas));
			groups.push_back(g);
			reg.registryGroup(g);
		}
	}

	void UserInterface::toQueue(int n)
	{
		client_queue.push_back(group_data(n, Chronometer::getInstance().getCurrent(), Chronometer::getInstance().getCurrent()) );
		std::cout << "Voce foi encaminhado para a " << client_queue.size() << "a posicao" << std::endl << std::endl; 
	}	
 
	void UserInterface::showQueue()
	{
		int i = 1;
		for(htl::list<group_data>::iterator it = client_queue.begin(); it != client_queue.end(); it++)
		{
			std::cout << i << " - " << (*it).sz << " pessoas"  << " esperando ha: " << (Chronometer::getInstance().getCurrent() - (*it).arrival)/60 << " minutos"  << std::endl;
		}
	}

	void UserInterface::leaveQueue()
	{
		std::cout << "Qual a posicao do elemento que deseja sair?" << std::endl;
		int a;
		std::cin >> a;
		for(htl::list<group_data>::iterator it = client_queue.begin(); it != client_queue.end(); it++)
		{
			if(--a == 0)
			{
				client_queue.erase(it);
				break;
			}
		}
		std::cout << "Volte sempre!" << std::endl;
	}

	void UserInterface::leaveRestaurant()
	{
		int no;
		std::cout << "Digite o numero de uma das mesas pertencentes ao grupo que esta indo embora: ";
		std::cin >> no;
		bool done = false;
		for(htl::list<group_data>::iterator it = groups.begin(); it != groups.end(); it++)
		{
			for(htl::vector<Table*>::iterator iv = (*it).tables.begin(); iv != (*it).tables.end(); iv++)
			{
				if((*iv)->num == no)
				{
					for(htl::vector<Table*>::iterator iw = (*it).tables.begin(); iw != (*it).tables.end(); iw++)
						(*iw)->free = (*iw)->MAX_OCCUPANTS;

					double total = 0;

					for(htl::list<Item>::iterator ik = (*it).orders.begin(); ik != (*it).orders.end(); ik++)
						total += (*ik).preco;

					reg.notifyGroupLeft(*it);
					groups.erase(it);
					std::cout << "*Foi paga uma conta de " << total << " dinheiros*" << std::endl; 
					done = true;
					callNextOnQueue();
					break;
				}
			}
			if(done)
				break;
		}
	}

	void UserInterface::callNextOnQueue()
	{
		if(!client_queue.empty())
		{
			htl::vector<Table*> tab;
			group_data* f;
			while(true)
			{
				tab = tm->getTableGroup(client_queue.front().sz);
				if(!tab.empty())
				{
					std::cout << "O proximo da fila pode passar, foram liberadas mesas que suprem sua necessidade!" << std::endl;
					f = &client_queue.front();
					group_data g(f->sz, f->arrival, Chronometer::getInstance().getCurrent(), tab);
					groups.push_back(g);
					client_queue.pop_front();
				}
				else
					break;
			}
		}
	}

	void UserInterface::makeOrder()
	{
		int no = 0;
		std::cout << "Digite o numero de uma do grupo" << std::endl;
		std::cin >> no;

		group_data* g  = getTableGroup(no);
		
		if(g == 0)
		{
			std::cout << "Nao ha nenhum grupo com pessoas nessa mesa." << std::endl;
			return;
		}

		std::cout << "Digite os codigos dos items que deseja armazenar, para parar, digite -1" << std::endl;
		int code = 0;
		while(1)
		{
			std::cin >> code;
			if(code == -1)
				break;
			else
			{
				SearchBinTree<int, Item>::iterator it = ItemFactory::searchByCode(code);
				if(it.node == 0)
					std::cout << "Item nao encontrado." << std::endl;
				else
				{
					g->orders.push_back((*it).second);
					balc.leaveOrder((*it).second, g->tables.front());
				}
			}
		}

		reg.registryOrder(*g, g->orders);
	}

	group_data* UserInterface::getTableGroup(int no)
	{
		for(htl::list<group_data>::iterator it = groups.begin(); it != groups.end(); it++)
		{
			for(htl::vector<Table*>::iterator iw = (*it).tables.begin(); iw != (*it).tables.end(); iw++)
			{
				if((*iw)->num == no)
					return &(*it);
			}
		}
		return 0;
	}

	void UserInterface::checkReadyOrders()
	{
		chef.routine();
		std::pair<Item, Table*> o;
		while(out_balc.hasNext())
		{
			o = out_balc.nextOrder();
			std::cout << "O item de codigo " << o.first.codigo << "da mesa " << o.second->num << "esta pronto!" << std::endl; 
		}
	}

	void UserInterface::menuRelatory()
	{
		bool quit = false;
		int op;
		while(!quit)
		{
			std::cout << "0 - Voltar" << std::endl;
			std::cout << "1 - Ver custo total" << std::endl;
			std::cout << "2 - Ver lucro total" << std::endl;
			std::cout << "3 - Listar pedidos feitos" << std::endl;
			std::cout << "4 - Listar clientes (somente aqueles que ja foram embora)" << std::endl;
			std::cout << "5 - Listar clientes ativos" << std::endl;
			std::cin >> op;
			switch(op)
			{
			case 0:
				quit = true;
				break;
			case 1:
				printCost();
				break;
			case 2:
				printGain();
				break;
			case 3:
				listOrders();
				break;
			case 4:
				listClients();
				break;
			case 5:
				listActive();
				break;
			}
		}
	}

	void UserInterface::printCost()
	{
		htl::list<RestaurantRegistry::ord_group>& o = reg.getOrders();
		double total = 0;
		for(htl::list<RestaurantRegistry::ord_group>::iterator it = o.begin(); it != o.end(); it++)
		{
			for(htl::list<Item>::iterator iw = (*it).ord.begin(); iw != (*it).ord.end(); iw++)
				total += (*iw).custo;
		}
		std::cout << std::endl << "O custo total foi de " << total << " dinheiros" << std::endl;
	}

	void UserInterface::printGain()
	{
		std::cout << std::endl;
		htl::list<RestaurantRegistry::ord_group>& o = reg.getOrders();
		double custo = 0;
		double total = 0;
		for(htl::list<RestaurantRegistry::ord_group>::iterator it = o.begin(); it != o.end(); it++)
		{
			for(htl::list<Item>::iterator iw = (*it).ord.begin(); iw != (*it).ord.end(); iw++)
			{
				custo += (*iw).custo;
				total += (*iw).preco;
			}
		}

		std::cout << "O lucro foi de " << total - custo << std::endl;
		std::cout << std::endl;
	}

	void UserInterface::listOrders()
	{
		std::cout << std::endl;
		htl::list<RestaurantRegistry::ord_group>& o = reg.getOrders();
		for(htl::list<RestaurantRegistry::ord_group>::iterator it = o.begin(); it != o.end(); it++)
		{
			for(htl::list<Item>::iterator iw = (*it).ord.begin(); iw != (*it).ord.end(); iw++)
			{
				std::cout << (*iw).codigo << "\t" << (*iw).descricao << std::endl;		
			}
		}	
		std::cout << std::endl;
	}

	void UserInterface::listClients()
	{
		std::cout << std::endl;
		htl::list<RestaurantRegistry::gp_time>& g = reg.getGroupLeft();
		std::cout << "Numero de pessoas, hora de chegada, hora que conseguiu mesa, hora que foi embora" << std::endl;
		
		struct tm* arr, *gta, *lef;
		for(htl::list<RestaurantRegistry::gp_time>::iterator it = g.begin(); it != g.end(); it++)
		{
			arr = localtime(&(*it).gd.arrival);
			gta = localtime(&(*it).gd.gottable);
			lef = localtime(&(*it).left_at);

			std::cout << (*it).gd.sz << "\t" << asctime(arr) << "\t" << asctime(gta) << "\t" << asctime(lef) << std::endl;
		}
		std::cout << std::endl;
	}

	void UserInterface::listActive()
	{
		std::cout << std::endl;

	}
}