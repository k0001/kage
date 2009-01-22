/*
 * This file is part of Kage.
 * Copyright (C) 2008, Renzo Carbonara <gnuk0001 AT gmail DOT com>
 *
 * Kage is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * Kage is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Kage.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KAGE_CORE_UTILS_LOGGING_HH_
#define KAGE_CORE_UTILS_LOGGING_HH_

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>

/*
 * log4cxx macros wrappers.
 *
 * They log to a predefined log4cxx::LoggerPtr you should name 'logger'.
 */

#define LOG_DEBUG(message)              LOG4CXX_DEBUG(logger, message)
#define LOG_TRACE(message)              LOG4CXX_TRACE(logger, message)
#define LOG_INFO(message)               LOG4CXX_INFO(logger, message)
#define LOG_WARN(message)               LOG4CXX_WARN(logger, message)
#define LOG_ERROR(message)              LOG4CXX_ERROR(logger, message)
#define LOG_FATAL(message)              LOG4CXX_FATAL(logger, message)
#define LOG_ASSERT(condition, message)  LOG4CXX_ASSERT(logger, condition, message)


namespace kage {
namespace core {
namespace logging {


/* Setups logging to out_stream and err_stream */
void setup_logging(void);


} // namespace logging
} // namespace core
} // namespace kage


#endif // KAGE_CORE_UTILS_LOGGING_HH_
