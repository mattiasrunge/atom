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

#ifndef NET_TCPCLIENT_H
#define NET_TCPCLIENT_H

#include "Client.h"

#include "types.h"

namespace atom {
namespace net {

class TcpClient : public Client
{
public:
  typedef boost::shared_ptr<TcpClient> Pointer;
  
  TcpClient(boost::asio::io_service& io_service, SocketId id, SocketId server_id);
  TcpClient(boost::asio::io_service& io_service, TcpSocketPointer socket, SocketId id, SocketId server_id);
  virtual ~TcpClient();
  
  void Connect(std::string address, unsigned int port);
  void Send(common::Byteset data);
    
protected:
  void Read();
    
private:
  TcpSocketPointer socket_;
};

}; // namespace net
}; // namespace atom

#endif // NET_TCPCLIENT_H
