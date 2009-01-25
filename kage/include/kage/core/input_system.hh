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

#ifndef KAGE_CORE_INPUT_SYSTEM_HH_
#define KAGE_CORE_INPUT_SYSTEM_HH_

#include <kage/core/sys_system.hh>
#include <OIS/OIS.h>

namespace kage {
namespace core {
namespace input {

class BufferedInputSystem;

/* Signal types */
typedef boost::signal<void (const OIS::KeyEvent &arg)> KeyboardSignal;
typedef boost::signal<void (const OIS::MouseEvent &arg)> MouseSignal;


/*
 * kage::core::input::BufferedInputHandler
 *
 * Abstract base class for buffered input handlers.
 * XXX: We are relying on OIS here.
 */

class BufferedInputHandler
{
    friend class BufferedInputSystem;

    public:
        BufferedInputHandler(void);
        virtual ~BufferedInputHandler(void);

        /* kage::core::input::BufferedInputHandler keyboard interface */
        virtual bool key_pressed(const OIS::KeyEvent &arg)
                { this->key_pressed_signals[arg.key](arg); return true; }
        virtual bool key_released(const OIS::KeyEvent &arg)
                { this->key_released_signals[arg.key](arg); return true; }

        /* kage::core::input::BufferedInputHandler mouse interface */
        virtual bool mouse_pressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
                { this->mouse_pressed_signals[id](arg); return true; }
        bool mouse_released(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
                { this->mouse_released_signals[id](arg); return true; }
        virtual bool mouse_moved(const OIS::MouseEvent &arg)
                { (*this->mouse_moved_signal)(arg); return true; }

    protected:
        /* Signals placeholders */
        KeyboardSignal *key_pressed_signals;
        KeyboardSignal *key_released_signals;
        MouseSignal *mouse_pressed_signals;
        MouseSignal *mouse_released_signals;
        MouseSignal *mouse_moved_signal;
};



/*
 * kage::core::input::InputSystem
 *
 * Interface for Input Systems that are part of a kage::core::sys::Application
 */


class InputSystem : public kage::core::sys::System
{
    public:
        virtual ~InputSystem(void) { }
};


/*
 * kage::core::input::BufferedInputSystem
 *
 * Interface for Buffered Input Systems that are part of a kage::core::sys::Application
 */

class BufferedInputSystem : public InputSystem
{
    public:
        BufferedInputSystem(bool enable_keyboard=true, bool enable_mouse=true);
        virtual ~BufferedInputSystem(void) { }

        virtual bool update(void)
                { return this->capture(); }
        virtual bool setup(kage::core::sys::Application &app)
                { return this->setup_keyboard() && this->setup_mouse(); }

        /* Set input handlers, return true on success */
        virtual bool set_keyboard_input_handler(BufferedInputHandler &handler) = 0;
        virtual bool set_mouse_input_handler(BufferedInputHandler &handler) = 0;
        /* Unset input handlers */
        virtual void unset_keyboard_input_handler(void) = 0;
        virtual void unset_mouse_input_handler(void) = 0;

        /* Keyboard Signals Slot connectors */
        virtual boost::signals::connection on_key_pressed(OIS::KeyCode kc, KeyboardSignal::slot_type &slot)
                { return this->keyboard_handler->key_pressed_signals[kc].connect(slot); }
        virtual boost::signals::connection on_key_released(OIS::KeyCode kc, KeyboardSignal::slot_type &slot)
                { return this->keyboard_handler->key_released_signals[kc].connect(slot); }
        /* Mouse Signals Slot connectors */
        virtual boost::signals::connection on_mouse_pressed(OIS::MouseButtonID id, MouseSignal::slot_type &slot)
                { return this->mouse_handler->mouse_pressed_signals[id].connect(slot); }
        virtual boost::signals::connection on_mouse_released(OIS::MouseButtonID id, MouseSignal::slot_type &slot)
                { return this->mouse_handler->mouse_released_signals[id].connect(slot); }
        virtual boost::signals::connection on_mouse_moved(MouseSignal::slot_type &slot)
                { return this->mouse_handler->mouse_moved_signal->connect(slot); }

    protected:
        /* Capture input. Must be called from update() */
        virtual bool capture(void) = 0;
        /* Setups Keyboard input. Returns true on success */
        virtual bool setup_keyboard(void) = 0;
        /* Setups Mouse input. Returns true on success */
        virtual bool setup_mouse(void) = 0;
        /* Devices enabled? */
        bool keyboard_enabled;
        bool mouse_enabled;
        /* Current BufferedInputHandlers */
        BufferedInputHandler *keyboard_handler;
        BufferedInputHandler *mouse_handler;
};


} // namespace input
} // namespace core
} // namespace kage


#endif // KAGE_CORE_INPUT_SYSTEM_HH_
