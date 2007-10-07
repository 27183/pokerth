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
/* Thread safe server session manager. */

#ifndef _SESSIONMANAGER_H_
#define _SESSIONMANAGER_H_

#include <net/sessiondata.h>
#include <playerdata.h>
#include <core/thread.h>

#include <boost/function.hpp>
#include <map>
#include <string>

class SenderThread;
class NetPacket;

struct SessionWrapper
{
	SessionWrapper() {}
	SessionWrapper(boost::shared_ptr<SessionData> s, boost::shared_ptr<PlayerData> p)
		: sessionData(s), playerData(p) {}
	boost::shared_ptr<SessionData>	sessionData;
	boost::shared_ptr<PlayerData>	playerData;
};

class SessionManager
{
public:
	SessionManager();
	virtual ~SessionManager();

	bool HasSessions() const;

	void AddSession(boost::shared_ptr<SessionData> sessionData); // new Sessions without player data
	void AddSession(SessionWrapper session);
	void SetSessionPlayerData(SOCKET session, boost::shared_ptr<PlayerData> playerData);
	void RemoveSession(SOCKET session);

	SessionWrapper Select(unsigned timeoutMsec);
	SessionWrapper GetSessionByPlayerName(const std::string playerName) const;
	SessionWrapper GetSessionByUniquePlayerId(unsigned uniqueId) const;

	PlayerDataList GetPlayerDataList() const;
	PlayerIdList GetPlayerIdList() const;
	bool IsPlayerConnected(const std::string &playerName) const;
	bool IsPlayerConnected(unsigned uniqueId) const;

	void ForEach(boost::function<void (SessionWrapper)> func);
	unsigned CountReadySessions() const;

	void Clear();
	unsigned GetRawSessionCount();

	void SendToAllSessions(SenderThread &sender, boost::shared_ptr<NetPacket> packet, SessionData::State state);
	void SendToAllButOneSessions(SenderThread &sender, boost::shared_ptr<NetPacket> packet, SOCKET except, SessionData::State state);

protected:

	typedef std::map<SOCKET, SessionWrapper> SessionMap;

private:

	SessionMap m_sessionMap;
	mutable boost::mutex m_sessionMapMutex;
};

#endif
