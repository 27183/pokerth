/***************************************************************************
 *   Copyright (C) 2007 by Lothar May                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef CLIENTPREFLOP_H
#define CLIENTPREFLOP_H

#include <preflopinterface.h>

class HandInterface;

class ClientPreflop : public PreflopInterface{
 
public:
	ClientPreflop(HandInterface*, int, int, int, int);
	~ClientPreflop();


	void setPlayersTurn(const int& theValue) { playersTurn = theValue; }
	int getPlayersTurn() const { return playersTurn; }
	
	void setHighestSet(const int& theValue) { highestSet = theValue; }
	int getHighestSet() const { return highestSet;}

	void setPreflopFirstRound(bool theValue) { preflopFirstRound = theValue; }
	bool setPreflopFirstRound() const { return preflopFirstRound; }

	void preflopRun();
	void nextPlayer2(); 



private:
	HandInterface *myHand;

	int myID;
	int actualQuantityPlayers;	
	int dealerPosition;
	int bigBlindPosition;

	int smallBlind;
	int highestSet;

	bool preflopFirstRound;
	int playersTurn;


};

#endif
