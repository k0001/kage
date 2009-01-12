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
{
}

Application::~Application()
{
}

void Application::run(void)
{
    LOG4CXX_INFO(logger, "Application's Task manager started running");
    this->task_mgr.run();

}


} // namespace sys
} // namespace core
} // namespace kage
