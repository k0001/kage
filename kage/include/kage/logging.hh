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

#ifndef LOGGING_HH_
#define LOGGING_HH_

#ifndef RLOG_COMPONENT
    #define RLOG_COMPONENT "libkage"
#endif

#include "rlog/rlog.h"
#include "rlog/RLogChannel.h"
#include "rlog/StdioNode.h"

namespace kage {
namespace core {
namespace logging {

/* Logging level */
enum LoggingLevel {
    LOGLEVEL_ERROR,
    LOGLEVEL_WARNING,
    LOGLEVEL_INFO,
    LOGLEVEL_DEBUG
};

/* Setups logging to out_stream and err_stream */
void rlog_stdio_setup(LoggingLevel log_level=LOGLEVEL_WARNING,
        FILE &out_file=*stdout, FILE &err_file=*stderr);


} // namespace logging
} // namespace core
} // namespace kage


#endif // LOGGING_HH_
