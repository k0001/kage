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


class BufferedInputHandler : public OIS::KeyListener, public OIS::MouseListener
{
    public:
        BufferedInputHandler(void);
        virtual ~BufferedInputHandler(void);

        /* OIS::KeyListener interface */
        virtual bool keyPressed(const OIS::KeyEvent &arg);
        virtual bool keyReleased(const OIS::KeyEvent &arg);

        /* OIS::MouseListener interface */
        virtual bool mouseMoved(const OIS::MouseEvent &arg);
        virtual bool mousePresed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
        virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
};


class BufferedInputManager : public kage::core::input::BufferedInputManager
{
    public:
        BufferedInputManager(std::size_t window_handle);
        ~BufferedInputManager(void);

        /* setups keyboard input, returns true on success */
        bool setup_keyboard(void);
        /* setups mouse input, returns true on success */
        bool setup_mouse(void);

        /* set input handlers, return true on success */
        bool set_keyboard_input_handler(BufferedInputHandler &handler);
        bool set_mouse_input_handler(BufferedInputHandler &handler);

        /* unset input handlers */
        void unset_keyboard_input_handler();
        void unset_mouse_input_handler();

    protected:
        /* input manager */
        OIS::InputManager *input_manager;

        /* input devices */
        OIS::Keyboard *keyboard;
        OIS::Mouse *mouse;

        /* input handlers */
        BufferedInputHandler *keyboard_handler;
        BufferedInputHandler *mouse_handler;
};


} // namespace input
} // namespace ois
} // namespace kage

#endif // OIS_INPUT_BUFFERED_HH_
