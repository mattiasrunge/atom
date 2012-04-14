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

#include "log.h"

#include <iostream>
#include <stdarg.h>
#include <string.h>

#include <boost/date_time.hpp>
#include <boost/thread/mutex.hpp>

namespace atom {
namespace log {

static boost::mutex mutex_;
static Level level_ = LOG_LEVEL_ALL;

void SetLogLevel(Level level)
{
  level_ = level;
}

void Print(Level level, std::string module, std::string message)
{
  std::string               level_string;
  boost::posix_time::ptime  date_and_time(boost::posix_time::second_clock::local_time());
  
  
  /* Check log level */
  if (0 == (level & level_))
  {
    return;
  }
  
  
  /* Convert log level to string */
  if (0 != (level & LOG_LEVEL_ERROR))
  {
    level_string = "ERROR";
  }
  else if (0 != (level & LOG_LEVEL_INFO))
  {
    level_string = "INFO";
  }
  else if (0 != (level & LOG_LEVEL_DEBUG))
  {
    level_string = "DEBUG";
  }
  else if (0 != (level & LOG_LEVEL_EXCEPTION))
  {
    level_string = "EXCEPTION";
  }
  else if (0 != (level & LOG_LEVEL_WARNING))
  {
    level_string = "WARNING";
  }
  else
  {
    level_string = "UNKNOWN";
  }
  
  
  /* Adjust lengths of sub strings */
  level_string.insert(level_string.end(), 9 - level_string.size(), ' ');
  module.insert(module.end(), 25 - module.size(), ' ');
  
  
  /* Print message */
  mutex_.lock();

  std::cout << date_and_time << " " << level_string << " " << module << " " << message << std::endl;
  std::cout.imbue(std::locale::classic());
  
  mutex_.unlock();
}

void Info(std::string module, char* format, ...)
{
  char    buffer[1024];
  va_list parameters;
  
  
  /* Initialize variables */
  memset(&buffer[0], 0, sizeof(buffer));
  
  
  /* Construct message */
  va_start(parameters, format);
  vsnprintf(&buffer[0], sizeof(buffer), format, parameters);
  va_end(parameters);
  
  Print(LOG_LEVEL_INFO, module, &buffer[0]);
}

void Info(std::string module, std::string message)
{
  Print(LOG_LEVEL_INFO, module, message);
}

void Debug(std::string module, char* format, ...)
{
  char    buffer[1024];
  va_list parameters;
  
  
  /* Initialize variables */
  memset(&buffer[0], 0, sizeof(buffer));
  
  
  /* Construct message */
  va_start(parameters, format);
  vsnprintf(&buffer[0], sizeof(buffer), format, parameters);
  va_end(parameters);
  
  Print(LOG_LEVEL_DEBUG, module, &buffer[0]);
}

void Debug(std::string module, std::string message)
{
  Print(LOG_LEVEL_DEBUG, module, message);
}

void Error(std::string module, char* format, ...)
{
  char    buffer[1024];
  va_list parameters;
  
  
  /* Initialize variables */
  memset(&buffer[0], 0, sizeof(buffer));
  
  
  /* Construct message */
  va_start(parameters, format);
  vsnprintf(&buffer[0], sizeof(buffer), format, parameters);
  va_end(parameters);
  
  Print(LOG_LEVEL_ERROR, module, &buffer[0]);
}

void Error(std::string module, std::string message)
{
  Print(LOG_LEVEL_ERROR, module, message);
}

void Warning(std::string module, char* format, ...)
{
  char    buffer[1024];
  va_list parameters;
  
  
  /* Initialize variables */
  memset(&buffer[0], 0, sizeof(buffer));
  
  
  /* Construct message */
  va_start(parameters, format);
  vsnprintf(&buffer[0], sizeof(buffer), format, parameters);
  va_end(parameters);
  
  Print(LOG_LEVEL_WARNING, module, &buffer[0]);
}

void Warning(std::string module, std::string message)
{
  Print(LOG_LEVEL_WARNING, module, message);
}

void Exception(std::string module, std::exception& exception)
{
  Print(LOG_LEVEL_EXCEPTION, module, exception.what());
}


}; // namespace log
}; // namespace atom
