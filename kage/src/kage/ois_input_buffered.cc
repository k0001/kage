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

/*
 * BufferedInputHandler
 */

bool BufferedInputHandler::keyPressed(const OIS::KeyEvent &arg)
{
    return true;
}

bool BufferedInputHandler::keyReleased(const OIS::KeyEvent &arg)
{
    return true;
}


bool BufferedInputHandler::mouseMoved(const OIS::MouseEvent &arg)
{
    return true;
}

bool BufferedInputHandler::mousePresed(const OIS::MouseEvent &arg,
                                       OIS::MouseButtonID id)
{
    return true;
}

bool BufferedInputHandler::mouseReleased(const OIS::MouseEvent &arg,
                                         OIS::MouseButtonID id)
{
    return true;
}



/*
 * BufferedInputManager
 */

BufferedInputManager::BufferedInputManager(std::size_t window_handle)
    : input_manager(NULL), keyboard(NULL), mouse(NULL), keyboard_handler(NULL),
      mouse_handler(NULL)
{
    this->input_manager = OIS::InputManager::createInputSystem(window_handle);
}

BufferedInputManager::~BufferedInputManager(void)
{
    if (this->keyboard) {
        this->input_manager->destroyInputObject(this->keyboard);
        this->keyboard = NULL;
    }
    if (this->mouse) {
        this->input_manager->destroyInputObject(this->mouse);
        this->mouse = NULL;
    }
    OIS::InputManager::destroyInputSystem(this->input_manager);
    this->input_manager = NULL;
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

bool BufferedInputManager::set_keyboard_input_handler(BufferedInputHandler &handler)
{
    if (!this->keyboard)
        return false;
    this->keyboard->setEventCallback(&handler);
    return true;
}

bool BufferedInputManager::set_mouse_input_handler(BufferedInputHandler &handler)
{
    if (!this->mouse)
        return false;
    this->mouse->setEventCallback(&handler);
    return true;
}

void BufferedInputManager::unset_keyboard_input_handler(void)
{
    this->keyboard_handler = NULL;
}

void BufferedInputManager::unset_mouse_input_handler(void)
{
    this->mouse_handler = NULL;
}

} // namespace input
} // namespace ois
} // namespace kage
