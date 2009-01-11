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

#include "kage/fsm.hh"

namespace kage {
namespace core {
namespace sys {


/*
 * kage::core::sys::FiniteStateMachine
 */

FiniteStateMachine::FiniteStateMachine(void)
{
}

FiniteStateMachine::~FiniteStateMachine(void)
{
}

void FiniteStateMachine::register_state(const std::string &id, State &state)
{
    if (this->states.count(id))
        throw "State identifier already exists -- TODO: REAL EXCEPTION";
    this->states[id] = &state;
}

void FiniteStateMachine::unregister_state(const std::string &id)
{
    if (id == this->current_state_id)
        throw "Can't unregister current state -- TODO: REAL EXCEPTION";
    if (!this->states.count(id))
        throw "State idenfifier not registered -- TODO: REAL EXCEPTION";
    this->states.erase(id);
}

void FiniteStateMachine::unregister_state(State &state)
{
    std::map<const std::string, State*>::iterator it;
    for (it = this->states.begin(); it != this->states.end(); ++it) {
        if (it->second == &state) {
            if (it->first == this->current_state_id) {
                throw "Can't unregister current state -- TODO: REAL EXCEPTION";
            }
            else {
                this->states.erase(it);
            }
        }
    }
    throw "State not registered -- TODO: REAL EXCEPTION";
}

void FiniteStateMachine::request(const std::string &id)
{
    if (id == this->current_state_id)
        // we already are where we want to be
        return;
    if (!this->states.count(id))
        throw "State idenfifier not registered -- TODO: REAL EXCEPTION";
    this->set_state(id);
}

void FiniteStateMachine::request(State &state)
{
    std::map<const std::string, State*>::iterator it;
    for (it = this->states.begin(); it != this->states.end(); ++it) {
        if (it->second == &state) {
            if (it->first == this->current_state_id) {
                // we already are where we want to be
                return;
            }
            else {
                this->set_state(it->first);
            }
        }
    }
    throw "State not registered -- TODO: REAL EXCEPTION";
}

const std::string& FiniteStateMachine::get_current_state_id(void) const
{
    return this->current_state_id;
}

void FiniteStateMachine::set_state(const std::string &id)
{
    // set transitional ids
    this->old_state_id = this->current_state_id;
    this->current_state_id = "";
    this->new_state_id = id;

    // states transition
    this->states[this->old_state_id]->exit();
    this->states[this->new_state_id]->enter();

    // set stable ids
    this->current_state_id = this->new_state_id;
    this->new_state_id = "";
}


} // namespace sys
} // namespace core
} // namespace kage

