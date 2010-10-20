#ifndef RTY_CHAIR_H
#define RTY_CHAIR_H

#include "Client.h"

namespace rty
{
	class Chair
	{
	public:
		Chair();
		void setOccupant(Client* occupant);
		void occupantLeft();
		bool isBusy();
	private:
		Client* occupant;
	};
}

#endif