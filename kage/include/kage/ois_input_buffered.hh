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


/*
 * kage::ois::input::BufferedInputHandler
 *
 * Handles buffered input events through OIS.
 */

class BufferedInputHandler : public kage::core::input::BufferedInputHandler,
                             public OIS::KeyListener, public OIS::MouseListener
{
    public:
        BufferedInputHandler(void);
        virtual ~BufferedInputHandler(void);

        /* kage::core::input::BufferedInputHandler keyboard interface */
        virtual bool key_pressed(const OIS::KeyEvent &arg);
        virtual bool key_released(const OIS::KeyEvent &arg);

        /* kage::core::input::BufferedInputHandler mouse interface */
        virtual bool mouse_moved(const OIS::MouseEvent &arg);
        virtual bool mouse_pressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
        virtual bool mouse_released(const OIS::MouseEvent &arg, OIS::MouseButtonID id);


        /* OIS::KeyListener interface */
        /* Definition proxies this OIS methods to the matching methods above */
        bool keyPressed(const OIS::KeyEvent &arg);
        bool keyReleased(const OIS::KeyEvent &arg);

        /* OIS::MouseListener interface */
        /* Definition proxies this OIS methods to the matching methods above */
        bool mouseMoved(const OIS::MouseEvent &arg);
        bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
};


/*
 * kage::ois::input::BufferedInputManager
 *
 * Manages buffered input through OIS.
 */

class BufferedInputManager : public kage::core::input::BufferedInputManager
{
    public:
        /* initializes input manager so that grabs input from window_handle */
        BufferedInputManager(std::size_t window_handle);
        virtual ~BufferedInputManager(void);

        /* setup keyboard input, returns true on success */
        virtual bool setup_keyboard(void);
        virtual bool setup_mouse(void);

        /* set input handlers, return true on success */
        virtual bool set_keyboard_input_handler(kage::core::input::BufferedInputHandler &handler);
        virtual bool set_mouse_input_handler(kage::core::input::BufferedInputHandler &handler);

        /* unset input handlers */
        virtual void unset_keyboard_input_handler(void);
        virtual void unset_mouse_input_handler(void);

        /* capture device statuses */
        virtual void capture(void);

    protected:
        /* input manager */
        OIS::InputManager *ois_input_manager;

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
