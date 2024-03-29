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

#ifndef NET_CLIENT_H
#define NET_CLIENT_H

#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>

#include "common/Byteset.h"

#include "types.h"

namespace atom {
namespace net {

class Client
{
public:
  typedef boost::shared_ptr<Client>                                           Pointer;
  typedef boost::signals2::signal<void(SocketId, SocketId, ClientState)>      SignalOnNewState;
  typedef boost::signals2::signal<void(SocketId, SocketId, common::Byteset)>  SignalOnNewData;

  Client(boost::asio::io_service& io_service, SocketId id, SocketId server_id);
  virtual ~Client();

  void ConnectSlots(const SignalOnNewState::slot_type& slot_on_new_state, const SignalOnNewData::slot_type& slot_on_new_data);
  
  virtual void Connect(std::string address, unsigned int port_or_baud) = 0;
  void Disconnect();
  virtual void Stop();
  virtual void Send(common::Byteset data) = 0;

  SocketId GetServerId();
  SocketId GetId();
    
protected:
    common::Byteset           buffer_;
    boost::asio::io_service&  io_service_;
    SignalOnNewState          signal_on_new_state_;
    virtual void Read();
    void ReadHandler(const boost::system::error_code& error, size_t size);
    
    
    
private:
    SocketId        id_;
    SocketId        server_id_;
    SignalOnNewData signal_on_new_data_;
};

}; // namespace net
}; // namespace atom

#endif // NET_CLIENT_H
