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

#ifndef INPUT_BUFFERED_HH_
#define INPUT_BUFFERED_HH_

#include "kage/globals.hh"

namespace kage {
namespace core {
namespace input {


/*
 * kage::core::input::BufferedInputHandler
 *
 * Abstract base class for buffered input handlers.
 */

class BufferedInputHandler
{
    public:
        BufferedInputHandler(void);
        virtual ~BufferedInputHandler(void);

        /* Keyboard event listeners interface */
        virtual bool key_pressed(void) = 0;
        virtual bool key_released(void) = 0;

        /* Mouse event listeners interface */
        virtual bool mouse_moved(void) = 0;
        virtual bool mouse_presed(void) = 0;
        virtual bool mouse_released(void) = 0;
};


/*
 * kage::core::input::BufferedInputManager
 *
 * Abstract base class for buffered input managers.
 */

class BufferedInputManager
{
    public:
        BufferedInputManager(void);
        virtual ~BufferedInputManager(void);

        /* setups keyboard input, returns true on success */
        virtual bool setup_keyboard(void) = 0;
        /* setups mouse input, returns true on success */
        virtual bool setup_mouse(void) = 0;

        /* set input handlers, return true on success */
        virtual bool set_keyboard_input_handler(BufferedInputHandler &handler) = 0;
        virtual bool set_mouse_input_handler(BufferedInputHandler &handler) = 0;

        /* unset input handlers */
        virtual void unset_keyboard_input_handler(void) = 0;
        virtual void unset_mouse_input_handler(void) = 0;

        /* capture device statuses */
        virtual void capture(void) = 0;

    protected:
        /* input handlers */
        BufferedInputHandler *keyboard_handler;
        BufferedInputHandler *mouse_handler;
};


} // namespace input
} // namespace core
} // namespace kage

#endif // INPUT_BUFFERED_HH_
