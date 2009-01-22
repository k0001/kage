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

#ifndef KAGE_CORE_SYS_FSM_HH_
#define KAGE_CORE_SYS_FSM_HH_

#include "kage/core/globals.hh"

namespace kage {
namespace core {
namespace sys {


/*
 * kage::core::sys::State
 *
 * kage::core::sys::FiniteStateMachine's states interface.
 */

class State
{
    public:
        virtual ~State(void);

        /* Entering to state transition */
        virtual void enter(void) = 0;
        /* Exiting from state transition */
        virtual void exit(void) = 0;
};


/*
 * kage::core::sys::FiniteStateMachine
 *
 * A Finite State Machine implemetation.
 */

class FiniteStateMachine
{
    public:
        FiniteStateMachine(void);
        ~FiniteStateMachine(void);

        /* Registers the given ``state``, identified by ``id`` within this FiniteStateMachine */
        void register_state(const std::string &id, State &state);
        /* Unregisters a previously registered state identified by ``id`` */
        void unregister_state(const std::string &id);
        /* Unregisters a previously registered ``state`` */
        void unregister_state(State &state);

        /* Request state change to the previously registered state identified by ``id`` */
        void request(const std::string &id);
        /* Request state change to the previously registered ``state`` */
        void request(State &state);

        /* Get the current State identifier. If none, then "" is returned */
        const std::string& get_current_state_id(void) const;

    protected:
        /* Sets a new current state */
        void set_state(const std::string &id);

        /* Here we hold the registered states */
        std::map<const std::string, State*> states;
        /* Current state identifier */
        std::string current_state_id;
        /* Old state (the previous current) identifier */
        std::string old_state_id;
        /* New state (the next current) identifier */
        std::string new_state_id;
};


} // namespace sys
} // namespace core
} // namespace kage

#endif // KAGE_CORE_SYS_FSM_HH_
