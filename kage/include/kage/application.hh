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

#ifndef APPLICATION_HH_
#define APPLICATION_HH_

#include "kage/globals.hh"
#include "kage/fsm.hh"
#include "kage/task.hh"
#include "kage/sys_graphics.hh"
#include "kage/sys_input.hh"

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

        std::string get_name(void) const { return this->name; }
    protected:
        /* Application name */
        std::string name;
        /* Task Manager */
        TaskManager task_mgr;
        /* Game Screens FSM */
        FiniteStateMachine game_screens;
        /* Systems placeholders */
        kage::core::graphics::GraphicSystem *sys_graphic;
        kage::core::input::InputSystem *sys_input;
};


} // namespace sys
} // namespace core
} // namespace kage

#endif // APPLICATION_HH_
