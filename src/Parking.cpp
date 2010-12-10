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

#include "Parking.h"
#include "htl/hlist.h"
#include <utility>

namespace rty
{
	Parking::Parking() 
	{
		reset();
	}

	void Parking::reset()
	{
		for(int i = 0; i < NUM_ROW; i++)
			for(int j = 0; j < NUM_SLOT + 1; j++)
				park_emp[i][j] = false;
		
	}

	bool Parking::isBusy(int row, int slot)
	{
		return park_emp[row][slot];
	}

	std::pair<int, std::pair<int,int> > Parking::parkCar()
	{
		for(int i = 0; i < NUM_ROW; i++) //tenta achar vagas no ultimo slot de cada linha (assim o tempo de remocao fica menor)
		{
			if(isBusy(i, NUM_SLOT - 1))
			{
				park_emp[i][NUM_SLOT - 1] = true;
				return std::pair<int, std::pair<int, int>>(i + 1, std::pair<int,int>(i, NUM_SLOT - 1)); //numero de linhas percorridas + 1 da entrada no slot
			}
		}

		for(int i = 0; i < NUM_ROW; i++)
		{
			if(theresAnEmptySlot(i))
			{
				int t_push = pushCars(i);
				park_emp[i][NUM_SLOT - 1] = true;
				return std::pair<int, std::pair<int, int>>(t_push + i + 1, std::pair<int,int>(i, NUM_SLOT - 1));
			}
		}

		return std::pair<int, std::pair<int, int>>(0, std::pair<int,int>(0, 0));
	}

	bool Parking::theresAnEmptySlot(int row)
	{
		for(int i = 0; i < NUM_SLOT; i++)
		{
			if(park_emp[row][i])
				return true;
		}
		return false;
	}

	int Parking::pushCars(int row)
	{
		int temp_push = 0;
		for(int i = 1; i < NUM_SLOT; i++)
		{
			park_emp[row][i] = false;
			park_emp[row][i - 1] = true;
			temp_push++;
		}
		return temp_push;
	}

	int Parking::removeCar(int row, int slot)
	{
		if(!theresABehind(row,slot))
		{
			park_emp[row][slot] = false;
			return row + slot;
		}

		int cars_moved = 0;

		for(int i = slot - 1; i > 0; i--)
		{
			cars_moved++;
			park_emp[row][i] = false;
		}

		int total = 0;
		while(cars_moved > 0)
		{
			total += parkCar();
			cars_moved--;
		}

		return cars_moved + total + row + slot;
	}

	bool Parking::theresABehind(int row, int slot)
	{
		return park_emp[row][slot - 1];
	}
}