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
			std::cout << "1 - Adcionar grupo" << std::endl;
			std::cin >> op;
			switch(op)
			{
			case 0:
				quit = true;
				break;
			case 1:
				groupArrival();
				break;
			}
		}
	}

	void UserInterface::groupArrival()
	{
		std::cout << "Numero de pessoas do grupo: ";
		int p;
		std::cin >> p;

	}
 
}