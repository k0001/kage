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

#include "kage/logging.hh"

namespace kage {
namespace core {
namespace logging {


void rlog_stdio_setup(LoggingLevel log_level, FILE &out_file, FILE &err_file)
{
    int log_flags = rlog::StdioNode::OutputColor | \
                    rlog::StdioNode::OutputContext | \
                    rlog::StdioNode::OutputChannel;
    static rlog::StdioNode err_log(fileno(&err_file), log_flags);
    static rlog::StdioNode out_log(fileno(&out_file), log_flags);
    if (log_level == LOGLEVEL_DEBUG)
        out_log.subscribeTo(RLOG_CHANNEL("debug"));
    if (log_level >= LOGLEVEL_INFO)
        out_log.subscribeTo(RLOG_CHANNEL("info"));
    if (log_level >= LOGLEVEL_WARNING)
        out_log.subscribeTo(RLOG_CHANNEL("warning"));
    if (log_level >= LOGLEVEL_ERROR)
        err_log.subscribeTo(RLOG_CHANNEL("error"));
}


} // namespace logging
} // namespace core
} // namespace kage

