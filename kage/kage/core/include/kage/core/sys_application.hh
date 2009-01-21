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

#ifndef KAGE_CORE_SYS_APPLICATION_HH_
#define KAGE_CORE_SYS_APPLICATION_HH_

#include "kage/core/globals.hh"
#include "kage/core/sys_fsm.hh"
#include "kage/core/sys_task.hh"
#include "kage/core/graphics_system.hh"
#include "kage/core/input_system.hh"

namespace kage {
namespace core {
namespace sys {


/*
 * kage::core::sys::Application
 *
 * Controls the workflow of an application.
 */

class Application
{
    public:
        Application(const std::string &name="Kage Application");
        virtual ~Application(void) { }

        /* Starts the Application workflow */
        virtual void run(void);

        /* Systems setup*/
        bool set_graphic_system(kage::core::graphics::GraphicSystem &sys);
        bool set_input_system(kage::core::input::InputSystem &sys);

        /* Systems placeholders */
        kage::core::graphics::GraphicSystem *sys_graphic;
        kage::core::input::InputSystem *sys_input;

        std::string get_name(void) const { return this->name; }
    protected:
        /* Prepare Systems for exceution by calling their after_setup method and adding their
         * update method to the TaskManager. Returns true on success */
        bool prepare_systems(void);

        /* Application name */
        std::string name;
        /* Task Manager */
        TaskManager task_mgr;
        /* Game Screens FSM */
        FiniteStateMachine game_screens;
        /* Systems update task */
        SystemsUpdateTask systems_update_task;
};


} // namespace sys
} // namespace core
} // namespace kage

#endif // KAGE_CORE_SYS_APPLICATION_HH_
