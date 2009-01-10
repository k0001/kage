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

#ifndef STATE_HH_
#define STATE_HH_

#include "kage/globals.hh"

namespace kage {
namespace core {
namespace sys {


class StateMachine;

class State
{
    public:
        State(void);
        virtual ~State(void);

        /* initialize this state attached to a StateMachine */
        virtual void setup(StateMachine &sm) = 0;
        /* State cleanup: called before removal. */
        virtual void shutdown(void) = 0;
        /* State execution is paused */
        virtual void pause(void) = 0;
        /* State excecution is resumed */
        virtual void resume(void) = 0;
        /* method called on every frame/loop */
        virtual bool run(void) = 0;

        /* check current excecution status */
        bool is_running(void) const;

    private:
        /* this ApplicationState can call quit when it needs to remove itself */
        virtual void quit(void);

        /* the StateMachine this State is attached to */
        StateMachine *sm;
        /* is the state runnnig? */
        bool running;
};


class StateMachine
{
    public:
        StateMachine(void);
        virtual ~StateMachine(void);

        /* Entry point for the StateMachine flow: responsible for running
         * init, loop and shutdown */
        void go(void);

    protected:
        /* called when the StateMachine flow starts */
        virtual void setup(void) = 0;
        /* called after the engine has been started, here goes the main loop */
        virtual void loop(void);
        /* called when the StateMachine flow is over */
        virtual void shutdown(void) = 0;

        /* called on each iteration of loop. flow should stop if return false */
        virtual bool run(void);

        /* change the current state to a new one */
        virtual void change_state(State &state);
        /* pushes a new states onto the stack */
        virtual void push_state(State &state);
        /* removes last state */
        virtual void pop_state(void);

        /* is the StateMachine running? */
        virtual bool is_running(void) const;
        /* should be called when you need to end the StateMachine */
        virtual void quit(void);

        /* Application name */
        std::string name;
        /* The stack of States */
        std::stack<State*> states;
        /* The mainloop flag */
        bool running;
};


} // namespace sys
} // namespace core
} // namespace kage

#endif // STATE_HH_
