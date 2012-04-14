/*
 * 
 *  Copyright (C) 2012  Mattias Runge
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

#ifndef LOG_H
#define LOG_H

#include <exception>
#include <string>
#include <stdio.h>
#include <stdint.h>

namespace atom {
namespace log {

typedef enum
{
  LOG_LEVEL_NONE      = 0x000000,
  LOG_LEVEL_ERROR     = 0x000001,
  LOG_LEVEL_EXCEPTION = 0x000002,
  LOG_LEVEL_WARNING   = 0x000004,
  LOG_LEVEL_INFO      = 0x000008,
  LOG_LEVEL_DEBUG     = 0x000010,
  LOG_LEVEL_ALL       = 0xFFFFFF
} Level;

void SetLogLevel(Level level);

void Info(std::string module, char* format, ...);
void Info(std::string module, std::string message);

void Debug(std::string module, char* format, ...);
void Debug(std::string module, std::string message);

void Error(std::string module, char* format, ...);
void Error(std::string module, std::string message);

void Warning(std::string module, char* format, ...);
void Warning(std::string module, std::string message);
  
void Exception(std::string module, std::exception& exception);
  
}; // namespace log
}; // namespace atom

#endif // LOG_H
