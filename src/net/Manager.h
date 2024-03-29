/*
 *
 *  Copyright (C) 2010  Mattias Runge
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef NET_MANAGER_H
#define NET_MANAGER_H

#include <string>
#include <map>

#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>

#include "common/IoService.h"

#include "types.h"
#include "Client.h"
#include "TcpClient.h"
#include "UdpClient.h"
#include "SerialClient.h"
#include "TcpServer.h"


namespace atom {
namespace net {

class Manager : public common::IoService
{
public:
  typedef boost::shared_ptr<Manager>                                Pointer;
  typedef boost::signals2::signal<void(SocketId, ClientState)>      SignalOnNewState;
  typedef boost::signals2::signal<void(SocketId, SocketId)>         SignalOnNewClient;
  typedef boost::signals2::signal<void(SocketId, common::Byteset)>  SignalOnNewData;

  virtual ~Manager();

  static Pointer Instance();
  static void Create();
  static void Delete();
  
  void ConnectSlots(const SignalOnNewState::slot_type& slot_on_new_state, const SignalOnNewClient::slot_type& slot_on_new_client, const SignalOnNewData::slot_type& slot_on_new_data);
  
  SocketId StartServer(TransportProtocol protocol, unsigned int port);
  SocketId Connect(TransportProtocol protocol, std::string address, unsigned int port_or_baud);
  
  void StopServer(SocketId server_id);
  void Disconnect(SocketId client_id);
  
  void SendToAll(SocketId server_id, common::Byteset data);
  void SendTo(SocketId client_id, common::Byteset data);

private:
  typedef std::map<SocketId, Client::Pointer>     ClientList;
  typedef std::map<SocketId, TcpServer::Pointer>  ServerList;

  static Pointer instance_;
  
  ClientList        clients_;
  ServerList        servers_;
  SignalOnNewState  signal_on_new_state_;
  SignalOnNewClient signal_on_new_client_;
  SignalOnNewData   signal_on_new_data_;
  
  Manager();
  
  void SlotOnNewState(SocketId client_id, SocketId server_id, ClientState client_state);
  void SlotOnNewData(SocketId client_id, SocketId server_id, common::Byteset data);
  void SlotOnNewClient(SocketId server_id, TcpSocketPointer socket);
  
  void StopServerHandler(SocketId server_id);
  void DisconnectHandler(SocketId client_id);
  
  void SendToAllHandler(SocketId server_id, common::Byteset data);
  void SendToHandler(SocketId client_id, common::Byteset data);
  
  SocketId GetFreeSocketId();
};

}; // namespace net
}; // namespace atom

#endif // NET_MANAGER_H
