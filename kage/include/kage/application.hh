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
#include "kage/application_state.hh"

namespace kage {
namespace core {
namespace sys {


class Application
{
    public:
        Application(void);
        virtual ~Application(void);

        /* Entry point for the whole application flow: responsible for running
         * init, run and shutdown */
        void go(void);

    protected:
        /* called when the application starts */
        virtual void init(void) = 0;
        // called after the engine has been started, here goes the main loop
        virtual void run(void);
        // called when the game engine is over
        virtual void shutdown(void) = 0;

        // change the last state to a new one
        virtual void change_state(ApplicationState *state);
        // pushes a new states onto the stack
        virtual void push_state(ApplicationState *state);
        // removes last state
        virtual void pop_state(void);

        // is the application running?
        virtual bool is_running(void) const;
        // should be called when you need to end the game
        virtual void quit(void);
        /* The stack of Application States */
        std::stack<ApplicationState*> states;
        /* The mainloop flag */
        bool running;
};



} // namespace sys
} // namespace core
} // namespace kage

#endif // APPLICATION_HH_
