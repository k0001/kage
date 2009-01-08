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

#include "kage/state.hh"

namespace kage {
namespace core {
namespace sys {


StateMachine::StateMachine(void)
    : running(false)
{
}

StateMachine::~StateMachine(void)
{
    this->shutdown();
}

bool StateMachine::is_running(void) const
{
    return this->running;
}

void StateMachine::quit(void)
{
    this->running = false;
}

void StateMachine::change_state(State &state)
{
    // cleanup the current state
    if (!this->states.empty()) {
        this->states.top()->shutdown();
        this->states.pop();
    }
    // store and attach the new state to this
    this->states.push(&state);
    this->states.top()->attach_to(*this);
}


void StateMachine::push_state(State &state)
{
    // pause current state
    if (!this->states.empty())
        this->states.top()->pause();
    // store and attach the new state to this
    this->states.push(&state);
    this->states.top()->attach_to(*this);
}

void StateMachine::pop_state(void)
{
    // cleanup the current state
    if (!this->states.empty()) {
        this->states.top()->shutdown();
        this->states.pop();
    }
    // resume previous state (if any)
    if (!this->states.empty())
        this->states.top()->resume();
    else
        this->running = false;
}

void StateMachine::go(void)
{
    init();
    loop();
    shutdown();
}

void StateMachine::loop(void)
{
    while (this->running)
        this->running = this->run();
}

bool StateMachine::run(void)
{
    return this->states.top()->run();
}


} // namespace sys
} // namespace core
} // namespace kage

