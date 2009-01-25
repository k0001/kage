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

#ifndef KAGE_OIS_INPUT_SYSTEM_HH_
#define KAGE_OIS_INPUT_SYSTEM_HH_

#include <kage/core/input_system.hh>

namespace kage {
namespace ois {
namespace input {


/*
 * kage::ois::input::BufferedInputHandler
 *
 * Handles buffered input events through OIS.
 */

class OISBufferedInputHandler : public kage::core::input::BufferedInputHandler
                              , public OIS::KeyListener
                              , public OIS::MouseListener
{
    public:
        OISBufferedInputHandler(void)
                : kage::core::input::BufferedInputHandler() { }
        ~OISBufferedInputHandler(void) { };

        /* OIS::KeyListener interface */
        /* Definition proxies this OIS methods to the matching methods above */
        bool keyPressed(const OIS::KeyEvent &arg)
                { return this->key_pressed(arg); }
        bool keyReleased(const OIS::KeyEvent &arg)
                { return this->key_released(arg); }

        /* OIS::MouseListener interface
         * Definition proxies this OIS methods to the matching methods above */
        bool mouseMoved(const OIS::MouseEvent &arg)
                { return this->mouse_moved(arg); }
        bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
                { return this->mouse_pressed(arg, id); }
        bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
                { return this->mouse_released(arg, id); }
};


/*
 * kage::ois::input::OISBufferedInputSystem
 *
 * Interface for OIS Buffered Input Systems that are part of a kage::core::sys::Application
 */

class OISBufferedInputSystem : public kage::core::input::BufferedInputSystem
{
    public:
        OISBufferedInputSystem(bool enable_keyboard=true,
                               bool enable_mouse=true);
        ~OISBufferedInputSystem(void);

        /* Setup System. Returns true on success */
        bool setup(kage::core::sys::Application &app);

        /* Set input handlers, return true on success */
        bool set_keyboard_input_handler(kage::core::input::BufferedInputHandler &handler);
        bool set_mouse_input_handler(kage::core::input::BufferedInputHandler &handler);

        /* Unset input handlers */
        void unset_keyboard_input_handler(void);
        void unset_mouse_input_handler(void);

        /* App's pre_run slots */
        /* Attaches OIS input_manager to the window handle provided by this->app's sys_graphic */
        void ois_input_manager_setup(void);

    protected:
        /* Capture input. Must be called from update() */
        bool capture(void);
        /* Setups Keyboard input. Returns true on success */
        bool setup_keyboard(void);
        /* Setups Mouse input. Returns true on success */
        bool setup_mouse(void);
        /* Input manager */
        OIS::InputManager *ois_input_manager;
        /* Input devices */
        OIS::Keyboard *ois_keyboard;
        OIS::Mouse *ois_mouse;
        /* Current BufferedInputHandlers */
        kage::core::input::BufferedInputHandler *keyboard_handler;
        kage::core::input::BufferedInputHandler *mouse_handler;
};



} // namespace input
} // namespace ois
} // namespace kage


#endif // KAGE_OIS_INPUT_SYSTEM_HH_

