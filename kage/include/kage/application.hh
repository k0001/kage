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
#include "kage/state.hh"

namespace kage {
namespace core {
namespace sys {


/*
 * kage::code::sys::ApplicationState
 *
 * An state within an Application.
 */

class ApplicationState : public kage::core::sys::State
{
    public:
        ApplicationState(void);
        virtual ~ApplicationState(void);
};


/*
 * kage::core::sys::Application
 *
 * Controls the workflow of an application.
 */

class Application : public kage::core::sys::StateMachine
{
    public:
        Application(const std::string &name="Kage Application");
        virtual ~Application(void);

    protected:
        /* Application name */
        std::string name;
};


} // namespace sys
} // namespace core
} // namespace kage

#endif // APPLICATION_HH_
