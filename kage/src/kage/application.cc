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

#include "kage/application.hh"

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger(
        "kage.core.sys.application"));


namespace kage {
namespace core {
namespace sys {

/*
 * Appplication
 */

Application::Application(const std::string &name)
    : name(name)
    , sys_graphic(NULL)
{
}

void Application::run(void)
{
    this->task_mgr.run();
}

bool Application::set_graphic_system(kage::core::graphics::GraphicSystem &sys)
{
    if (!sys.setup(*this)) {
        LOG_ERROR("Graphic System setup failed");
        return false;
    }
    this->sys_graphic = &sys;
    LOG_INFO("Graphic System initialized");
    return true;
}

bool Application::set_input_system(kage::core::input::InputSystem &sys)
{
    if (!sys.setup(*this)) {
        LOG_ERROR("Input System setup failed");
        return false;
    }
    this->sys_input = &sys;
    LOG_INFO("Input System initialized");
    return true;
}


} // namespace sys
} // namespace core
} // namespace kage
