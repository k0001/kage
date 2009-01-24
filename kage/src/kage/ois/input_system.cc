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

#include <kage/ois/input_system.hh>
#include <kage/core/sys_application.hh>

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger(
        "kage.ois.input.system"));


namespace kage {
namespace ois {
namespace input {

/*
 * kage::ois::input::OISBufferedInputSystem
 */

OISBufferedInputSystem::OISBufferedInputSystem(bool enable_keyboard,
                                               bool enable_mouse)
    : ois_input_manager(NULL)
    , ois_keyboard(NULL)
    , ois_mouse(NULL)
    , keyboard_handler(NULL)
    , mouse_handler(NULL)
    , keyboard_enabled(enable_keyboard)
    , mouse_enabled(enable_mouse)
{
}

OISBufferedInputSystem::~OISBufferedInputSystem(void)
{
    if (this->ois_keyboard) {
        this->ois_input_manager->destroyInputObject(this->ois_keyboard);
        this->ois_keyboard = NULL;
    }
    if (this->ois_mouse) {
        this->ois_input_manager->destroyInputObject(this->ois_mouse);
        this->ois_mouse = NULL;
    }
    OIS::InputManager::destroyInputSystem(this->ois_input_manager);
    this->ois_input_manager = NULL;
}

bool OISBufferedInputSystem::setup(kage::core::sys::Application &app)
{
    if (!kage::core::input::InputSystem::setup(app))
        return false;
    this->app->pre_run.connect(boost::bind(&OISBufferedInputSystem::ois_input_manager_setup, this));
    return true;
}

void OISBufferedInputSystem::ois_input_manager_setup(void)
{
    std::size_t window_handle = this->app->sys_graphic->get_window_handle();
    this->ois_input_manager = OIS::InputManager::createInputSystem(window_handle);
    if (this->keyboard_enabled)
        if (!this->setup_keyboard())
            throw "Couldnt' setup OIS keyboard";
    if (this->mouse_enabled)
        if (!this->setup_mouse())
            throw "Couldnt' setup OIS mouse";
}

bool OISBufferedInputSystem::set_keyboard_input_handler(
        kage::core::input::BufferedInputHandler &handler)
{
    if (!this->ois_keyboard)
        return false;
    // downcast here since we can't change the signature of this method.
    OISBufferedInputHandler &ois_bih(static_cast<OISBufferedInputHandler&>(handler));
    this->ois_keyboard->setEventCallback(&ois_bih);
    return true;
}

bool OISBufferedInputSystem::set_mouse_input_handler(
        kage::core::input::BufferedInputHandler &handler)
{
    if (!this->ois_mouse)
        return false;
    // downcast here since we can't change the signature of this method.
    OISBufferedInputHandler &ois_bih(static_cast<OISBufferedInputHandler&>(handler));
    this->ois_mouse->setEventCallback(&ois_bih);
    return true;
}

void OISBufferedInputSystem::unset_keyboard_input_handler(void)
{
    this->keyboard_handler = NULL;
}

void OISBufferedInputSystem::unset_mouse_input_handler(void)
{
    this->mouse_handler = NULL;
}

bool OISBufferedInputSystem::capture(void)
{
    if (this->ois_keyboard)
        this->ois_keyboard->capture();
    if (this->ois_mouse)
        this->ois_mouse->capture();
    return true;
}

bool OISBufferedInputSystem::setup_keyboard(void)
{
    try {
       this->ois_keyboard = static_cast<OIS::Keyboard*>(this->ois_input_manager->
                createInputObject(OIS::OISKeyboard, true));
    }
    catch (const OIS::Exception &e) {
       return false;
    }
    return true;
}

bool OISBufferedInputSystem::setup_mouse(void)
{
    try {
       this->ois_mouse = static_cast<OIS::Mouse*>(this->ois_input_manager->
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


