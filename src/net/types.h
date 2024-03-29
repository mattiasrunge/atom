/*
 *
 *    Copyright (C) 2010  Mattias Runge
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License along
 *    with this program; if not, write to the Free Software Foundation, Inc.,
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef NET_TYPES_H
#define NET_TYPES_H

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

namespace atom {
namespace net {

typedef enum
{
  CLIENT_STATE_CONNECTED        = 0x00,
  CLIENT_STATE_DISCONNECTED     = 0x01,
  CLIENT_STATE_ACCEPTED         = 0x02
} ClientState;

typedef enum
{
  TRANSPORT_PROTOCOL_TCP        = 0x00,
  TRANSPORT_PROTOCOL_UDP        = 0x01,
  TRANSPORT_PROTOCOL_SERIAL     = 0x02
} TransportProtocol;

typedef enum
{
  APPLICATION_PROTOCOL_UNKNOWN  = 0x00,
  APPLICATION_PROTOCOL_HTTP     = 0x01,
  APPLICATION_PROTOCOL_FTP      = 0x02
} ApplicationProtocol;

typedef unsigned int                                    SocketId;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> TcpSocketPointer;

}; // namespace net
}; // namespace atom

#endif // NET_TYPES_H
