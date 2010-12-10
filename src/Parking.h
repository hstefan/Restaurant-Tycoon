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

#ifndef RTY_PARKING_H
#define RTY_PARKING_H

namespace rty
{
	/*O tempo necessario para retirar um carro e dado em funcao do numero de 'casas' que o carro precisa percorrer para sair*/
	class Parking
	{
	public:
		const static int NUM_ROW = 20;
		const static int NUM_SLOT = 3;
		
		Parking();

		int parkCar();
		int removeCar(int row, int slot);
	
	protected:
		bool isBusy(int row, int slot);
		void reset();
		bool theresAnEmptySlot(int row);
		int pushCars(int row);
		bool theresABehind(int row, int slot);

	private:
		bool park_emp[NUM_ROW][NUM_SLOT + 1];
	};
}

#endif