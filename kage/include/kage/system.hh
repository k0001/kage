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

#ifndef KAGE_SYSTEM_HH_
#define KAGE_SYSTEM_HH_

#include "kage/application.hh"

namespace kage {
namespace core {
namespace sys {

/*
 * kage::core::sys::System
 *
 * Interface for Systems that are part of a kage::core::sys::Application
 */

class System
{
    public:
        virtual ~System(void) = 0;

        /* Setup System. Returns true on succes */
        virtual bool setup(kage::core::sys::Application &app) = 0;
};


} // namespace sys
} // namespace core
} // namespace kage

#endif // KAGE_SYSTEM_HH_

