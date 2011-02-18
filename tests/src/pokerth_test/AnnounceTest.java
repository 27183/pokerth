/*  PokerTH automated tests.
	Copyright (C) 2010 Lothar May

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Affero General Public License as
	published by the Free Software Foundation, either version 3 of the
	License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Affero General Public License for more details.

	You should have received a copy of the GNU Affero General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

package pokerth_test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.net.Socket;

import org.junit.Test;

import pokerth_protocol.AnnounceMessage;
import pokerth_protocol.PokerTHMessage;
import pokerth_protocol.AnnounceMessage.AnnounceMessageSequenceType.ServerTypeEnumType;


public class AnnounceTest extends TestBase {

	protected void TestAnnounceMsg(AnnounceMessage announce, int numPlayersOnServer) {
		assertEquals(PROTOCOL_VERSION_MAJOR, announce.getValue().getProtocolVersion().getMajor().intValue());
		assertEquals(PROTOCOL_VERSION_MINOR, announce.getValue().getProtocolVersion().getMinor().intValue());
		assertEquals(ServerTypeEnumType.EnumType.serverTypeInternetAuth, announce.getValue().getServerType().getValue());
		assertEquals(numPlayersOnServer, announce.getValue().getNumPlayersOnServer().intValue());
	}

	@Test
	public void testAnnounce() throws Exception {

		PokerTHMessage msg = receiveMessage();
		assertTrue(msg.isAnnounceMessageSelected());
		TestAnnounceMsg(msg.getAnnounceMessage(), 0);

		// numPlayersOnServer should only be incremented after login.
		Socket s[] = new Socket[9];
		for (int i = 0; i < 9; i++) {
			s[i] = new Socket("localhost", 7234);
			msg = receiveMessage(s[i]);
			assertTrue(msg.isAnnounceMessageSelected());
			// Without login: Counter stays at 0.
			TestAnnounceMsg(msg.getAnnounceMessage(), 0);
		}

		Socket t[] = new Socket[9];
		for (int i = 0; i < 9; i++) {
			t[i] = new Socket("localhost", 7234);
			String username = "test" + (i+1);
			String password = username;
			userInit(t[i], username, password);

			sock.close();
			sock = new Socket("localhost", 7234);
			msg = receiveMessage();
			assertTrue(msg.isAnnounceMessageSelected());
			// After login: Counter is incremented.
			TestAnnounceMsg(msg.getAnnounceMessage(), i + 1);
		}

		for (int i = 0; i < 9; i++) {
			s[i].close();

			// Closing non-established sessions: counter stays the same.
			sock.close();
			sock = new Socket("localhost", 7234);
			msg = receiveMessage();
			assertTrue(msg.isAnnounceMessageSelected());
			// After login: Counter is incremented.
			TestAnnounceMsg(msg.getAnnounceMessage(), 9);
		}

		for (int i = 0; i < 9; i++) {
			t[i].close();
			Thread.sleep(1000);

			// Closing established sessions: counter is decremented.
			sock.close();
			sock = new Socket("localhost", 7234);
			msg = receiveMessage();
			assertTrue(msg.isAnnounceMessageSelected());
			// After login: Counter is incremented.
			TestAnnounceMsg(msg.getAnnounceMessage(), 8 - i);
		}
	}
}
