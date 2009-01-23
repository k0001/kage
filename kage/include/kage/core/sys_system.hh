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

#ifndef KAGE_CORE_SYS_SYSTEM_HH_
#define KAGE_CORE_SYS_SYSTEM_HH_

#include <kage/core/sys_task.hh>

namespace kage {
namespace core {
namespace sys {

class Application;

/*
 * kage::core::sys::System
 *
 * Interface for Systems that are part of a kage::core::sys::Application
 */

class System
{
    public:
        virtual ~System(void) { }

        /* Setup System. Returns true on success */
        virtual bool setup(Application &app) = 0;

        /* Called after all Systems for an Application have been setup. Returns true if is ok to
         * proceed qwith Application execution */
        virtual bool after_setup(void)
                { return true; }

        /* Update system status. Called once per frame. Returns true on success */
        virtual bool update(void) = 0;
};


class SystemsUpdateTask : public Task
{
    public:
        ~SystemsUpdateTask(void) { }

        /* Actual Task code, dispatch calls to every system's update method */
        Task::ExitCode run(const TaskInfo &ti);

        /* Register a system for updating */
        void register_system(System &sys);

    protected:
        /* Systems registered with this Task */
        std::vector<System*> systems;
};


} // namespace sys
} // namespace core
} // namespace kage

#endif // KAGE_CORE_SYS_SYSTEM_HH_

