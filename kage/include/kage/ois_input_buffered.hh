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

#ifndef OIS_INPUT_BUFFERED_HH_
#define OIS_INPUT_BUFFERED_HH_

#include "kage/globals.hh"
#include "kage/input_buffered.hh"

namespace kage {
namespace ois {
namespace input {


class BufferedInputManager : public kage::core::input::BufferedInputManager
{
    public:
        BufferedInputManager(std::size_t window_handle);

        void setup_keyboard(void);
        void setup_mouse(void);
};


} // namespace input
} // namespace ois
} // namespace kage

#endif // OIS_INPUT_BUFFERED_HH_
