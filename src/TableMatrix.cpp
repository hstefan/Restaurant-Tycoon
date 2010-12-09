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

#include "TableMatrix.h"

namespace rty
{
	TableMatrix::TableMatrix(int l, int c)
		: rows(l), cols(c)
	{
		mat = new Table*[l];
		for(int i = 0; i < l; i++)
			mat[i] = new Table[c];
		ngrupos = 0;
		int table_num = 0;
		for(int i = 0; i < l; i++)
		{
			for(int j = 0; j < c; j++)
				mat[i][j].num = table_num++;
		}
	}

	htl::vector<Table*> TableMatrix::getTableGroup(unsigned int s)
	{
		htl::vector<Table*> vec;
		vec.reserve(s + s%Table::MAX_OCCUPANTS / Table::MAX_OCCUPANTS);
		
		if(s == 0)
			return vec;
		
		if(s <= 2)
		{
			for(int i = 0; i < rows; i++)
			{
				for(int j = 0; j < cols; j++)
				{
					if(mat[i][j].free == mat[i][j].MAX_OCCUPANTS)
					{
						vec.push_back(&mat[i][j]);
						break;
					}
				}
				if(!vec.empty())
					break;
			}
		}

		if(s > 2)
		{
			for(int i = 0; i < rows; i++)
			{
				for(int j = 0; j < cols; j++)
				{
					vec = findAround(i, j, s);
					if(!vec.empty())
						break;
				}
				if(!vec.empty())
					break;
			}
		}

		for(htl::vector<Table*>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			(*it)->free -= (*it)->MAX_OCCUPANTS - s%2;
			s -= (*it)->MAX_OCCUPANTS - s%2;
		}

		return vec;
	}

	htl::vector<Table*>	TableMatrix::findAround(int row, int column, int n)
	{
		htl::vector<Table*> tab;
		for (int i = 0; i + row < rows; ++i)
		{
			if(mat[i + row][column].free == Table::MAX_OCCUPANTS)
			{
				tab.push_back(&mat[i + row][column]);
				if(int(tab.size()) >= n/Table::MAX_OCCUPANTS)
				{
					return tab;
				}
			}
		}

		for (int i = -1; i + row > 0; --i)
		{
			if(mat[i + row][column].free == Table::MAX_OCCUPANTS)
			{
				tab.push_back(&mat[i + row][column]);
				if(int(tab.size()) >= n/Table::MAX_OCCUPANTS)
					return tab;
			}
			else 
				break;
		}

		for (int i = 0; i + column < column; ++i)
		{
			if(mat[row][column + i].free == Table::MAX_OCCUPANTS)
			{
				tab.push_back(&mat[i + row][column]);
				if(int(tab.size()) >= n/Table::MAX_OCCUPANTS)
					return tab;
				
			}
			else 
				break;
		}

		for (int i = -1; i + column > 0; i--)
		{
			if(mat[row][column + i].free == Table::MAX_OCCUPANTS)
			{
				tab.push_back(&mat[i + row][column]);
				if(int(tab.size()) >= n/Table::MAX_OCCUPANTS)
					return tab;
			}
			else 
				break;
		}
		
		tab.clear();
		return tab;
	}
}