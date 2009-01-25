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

#include <kage/core/input_system.hh>

namespace kage {
namespace core {
namespace input {


/*
 * kage::core::input::BufferedInputHandler
 */

BufferedInputHandler::BufferedInputHandler(void)
    : key_pressed_signals(NULL)
    , key_released_signals(NULL)
    , mouse_pressed_signals(NULL)
    , mouse_released_signals(NULL)
    , mouse_moved_signal(NULL)
{
    // TODO: OIS can handle 256 different keys, but actually it handles less than that,
    // so we are allocating more KeyboardSignals than needed. Someday I'll fix this.
    this->key_pressed_signals = new KeyboardSignal[256];
    this->key_released_signals = new KeyboardSignal[256];
    // OIS handles 8 different mouse buttons.
    this->mouse_pressed_signals = new MouseSignal[8];
    this->mouse_released_signals = new MouseSignal[8];
    this->mouse_moved_signal = new MouseSignal;
}

BufferedInputHandler::~BufferedInputHandler(void)
{
    if (this->key_pressed_signals)
        delete[] this->key_pressed_signals;
    if (this->key_released_signals)
        delete[] this->key_released_signals;
    if (this->mouse_pressed_signals)
        delete[] this->mouse_pressed_signals;
    if (this->mouse_released_signals)
        delete[] this->mouse_released_signals;
    if (this->mouse_moved_signal)
        delete this->mouse_moved_signal;
}


/*
 * kage::core::input::BufferedInputSystem
 */

BufferedInputSystem::BufferedInputSystem(bool enable_keyboard, bool enable_mouse)
    : keyboard_enabled(enable_keyboard)
    , mouse_enabled(enable_mouse)
    , keyboard_handler(NULL)
    , mouse_handler(NULL)
{
}


} // namespace input
} // namespace core
} // namespace kage

