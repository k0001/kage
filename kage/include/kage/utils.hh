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

#ifndef UTILS_HH_
#define UTILS_HH_

#include "kage/globals.hh"


namespace kage {
namespace utils {

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger(
        "kage.utils"));

/*
 * kage::utils::gettimeofdayf
 *
 * Returns the current localtime timestamp as float.
 */

float gettimeofdayf(void)
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return (static_cast<float>(tv.tv_sec) +
            static_cast<float>(tv.tv_usec) / 1000000.0);
}


} // namespace utils
} // namespace kage

#endif // UTILS_HH_

