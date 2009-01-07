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

#include "kage/ois_input_buffered.hh"

namespace kage {
namespace ois {
namespace input {


BufferedInputManager::BufferedInputManager(std::size_t window_handle)
{
    this->input_manager = OIS::InputManager::createInputSystem(window_handle);
}

BufferedInputManager::~BufferedInputManager(void)
{
    if (this->keyboard)
        this->input_manager->destroyInputObject(this->keyboard);
    if (this->mouse)
        this->input_manager->destroyInputObject(this->mouse);
    OIS::InputManager::destroyInputSystem(this->input_manager);
}

bool BufferedInputManager::setup_keyboard(void)
{
    try {
       this->keyboard = static_cast<OIS::Keyboard*>(this->input_manager->
                createInputObject(OIS::OISKeyboard, true));
    }
    catch (const OIS::Exception &e) {
       return false;
    }
    return true;
}

bool BufferedInputManager::setup_mouse(void)
{
    try {
       this->mouse = static_cast<OIS::Mouse*>(this->input_manager->
                createInputObject(OIS::OISMouse, true));
    }
    catch (const OIS::Exception &e) {
       return false;
    }
    return true;
}


} // namespace input
} // namespace ois
} // namespace kage
