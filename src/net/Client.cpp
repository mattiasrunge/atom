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

#include "Client.h"

#include <iostream>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

namespace atom {
namespace net {

Client::Client(boost::asio::io_service& io_service, SocketId id, SocketId server_id) : buffer_(2048)
{
    this->server_id_ = server_id;
    this->id_ = id;
}

Client::~Client()
{
    this->Stop();
}

void Client::ConnectSlots(const SignalOnNewState::slot_type& slot_on_new_state, const SignalOnNewData::slot_type& slot_on_new_data)
{
    this->signal_on_new_state_.connect(slot_on_new_state);
    this->signal_on_new_data_.connect(slot_on_new_data);
}

SocketId Client::GetId()
{
    return this->id_;
}

SocketId Client::GetServerId()
{
    return this->server_id_;
}

void Client::Read()
{
    this->buffer_.Clear();
}

void Client::ReadHandler(const boost::system::error_code& error, size_t size)
{
    if (error)
    {
        this->Disconnect();
    }
    else if (size == 0)
    {
        this->Disconnect();
    }
    else
    {
        this->buffer_.SetSize(size);
        
        this->signal_on_new_data_(this->id_, this->server_id_, this->buffer_);
        
        this->Read();
    }
}

void Client::Stop()
{
}

void Client::Disconnect()
{
  if (this->id_ != 0)
  {
    SocketId id = this->id_;
      
    this->Stop();
        
    this->id_ = 0;
        
    this->signal_on_new_state_(id, this->server_id_, CLIENT_STATE_DISCONNECTED);
  }
}
    
}; // namespace net
}; // namespace atom
