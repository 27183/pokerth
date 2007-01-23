/***************************************************************************
 *   Copyright (C) 2006 by FThauer FHammer   *
 *   f.thauer@web.de   *
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
#include "newgamedialogimpl.h"
#include "configfile.h"

newGameDialogImpl::newGameDialogImpl(QWidget *parent, const char *name)
      : QDialog(parent, name)
{

    setupUi(this);

	//Formulare Füllen
	ConfigFile myConfig;	

	//Game Settings

	spinBox_quantityPlayers->setValue(myConfig.readConfigInt("NumberOfPlayers", 5));
	spinBox_startCash->setValue(myConfig.readConfigInt("StartCash", 2000));
	spinBox_smallBlind->setValue(myConfig.readConfigInt("SmallBlind", 10));
	spinBox_gameSpeed->setValue(myConfig.readConfigInt("GameSpeed", 4));
	spinBox_handsBeforeRaiseSmallBlind->setValue(myConfig.readConfigInt("HandsBeforeRaiseSmallBlind", 9));

}

