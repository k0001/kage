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

namespace kage {
namespace core {
namespace sys {

Application::Application(const std::string &name)
    : name(name),
      running(false)
{
}

Application::~Application(void)
{
}

bool Application::is_running(void) const
{
    return this->running;
}

void Application::quit(void)
{
    this->running = false;
}

void Application::change_state(ApplicationState *state)
{
    // cleanup the current state
    if (!this->states.empty()) {
        this->states.top()->shutdown();
        this->states.pop();
    }
    // store and init the new state
    this->states.push(state);
    this->states.top()->init(this);
}


void Application::push_state(ApplicationState *state)
{
    // pause current state
    if (!this->states.empty())
        this->states.top()->pause();
    // store and init the new state
    this->states.push(state);
    this->states.top()->init(this);
}

void Application::pop_state(void)
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

void Application::go(void)
{
    init();
    run();
    shutdown();
}

void Application::run(void)
{
    while (this->is_running())
        this->states.top()->run();
}


} // namespace sys
} // namespace core
} // namespace kage
