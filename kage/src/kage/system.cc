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

#include "kage/system.hh"

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger(
        "kage.core.sys.system"));

namespace kage {
namespace core {
namespace sys {


Task::ExitCode SystemsUpdateTask::run(const TaskInfo &ti)
{
    std::vector<System*>::iterator it;
    for (it=this->systems.begin(); it != this->systems.end(); ++it) {
        if (!(*it)->update()) {
            LOG_ERROR("Failed to update system. Finishing Systems Update Task now");
            return this->TASK_DONE;
        }
    }
    return this->TASK_CONTINUE;
}

void SystemsUpdateTask::register_system(System &sys)
{
    this->systems.push_back(&sys);
}


} // namespace sys
} // namespace core
} // namespace kage


