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

#ifndef KAGE_SYS_INPUT_HH_
#define KAGE_SYS_INPUT_HH_

#include "kage/system.hh"

namespace kage {
namespace core {
namespace input {


/*
 * kage::core::input::InputSystem
 *
 * Interface for Input Systems that are part of a kage::core::sys::Application
 */

class InputSystem : public kage::core::sys::System
{
};


/*
 * kage::core::input::BufferedInputHandler
 *
 * Abstract base class for buffered input handlers.
 * XXX: We are relying on OIS here.
 */

class BufferedInputHandler
{
    public:
        virtual ~BufferedInputHandler(void) { }

        /* Keyboard event listeners */
        virtual bool key_pressed(const OIS::KeyEvent &arg);
        virtual bool key_released(const OIS::KeyEvent &arg);

        /* Mouse event listeners */
        virtual bool mouse_moved(const OIS::MouseEvent &arg);
        virtual bool mouse_pressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
        virtual bool mouse_released(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
};


/*
 * kage::core::input::BufferedInputSystem
 *
 * Interface for Buffered Input Systems that are part of a kage::core::sys::Application
 */

class BufferedInputSystem : public InputSystem
{
    public:
        bool update(void)
                { return this->capture(); }
        bool setup(kage::core::sys::Application &app)
                { return this->setup_keyboard() && this->setup_mouse(); }

        /* Set input handlers, return true on success */
        virtual bool set_keyboard_input_handler(BufferedInputHandler &handler) = 0;
        virtual bool set_mouse_input_handler(BufferedInputHandler &handler) = 0;

        /* Unset input handlers */
        virtual void unset_keyboard_input_handler(void) = 0;
        virtual void unset_mouse_input_handler(void) = 0;

    protected:
        /* Capture input. Must be called from update() */
        virtual bool capture(void) = 0;
        /* Setups Keyboard input. Returns true on success */
        virtual bool setup_keyboard(void) = 0;
        /* Setups Mouse input. Returns true on success */
        virtual bool setup_mouse(void) = 0;
};


} // namespace input
} // namespace core
} // namespace kage


#endif // KAGE_SYS_INPUT_HH_


