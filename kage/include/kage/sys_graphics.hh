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

#ifndef KAGE_SYS_GRAPHICS_HH_
#define KAGE_SYS_GRAPHICS_HH_

#include "kage/system.hh"

namespace kage {
namespace core {
namespace graphics {


/*
 * kage::core::graphics::GraphicSystem
 *
 * Interface for Graphic Systems that are part of a kage::core::sys::Application
 */

class GraphicSystem : public kage::core::sys::System
{
    public:
        /* Returns the window handle for the render window being used */
        virtual std::size_t get_window_handle(void) = 0;
};


} // namespace graphics
} // namespace core
} // namespace kage


#endif // KAGE_SYS_GRAPHICS_HH_


