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

#ifndef INPUT_HH_
#define INPUT_HH_

#include "kage/globals.hh"
#include "kage/task.hh"

namespace kage {
namespace core {
namespace input {


/*
 * kage::core::input::InputManager
 *
 * Abstract base class for input system managers.
 */

class InputManager
{
    public:
        InputManager(void);
        virtual ~InputManager(void) = 0;

        /* setups keyboard input, returns true on success */
        virtual bool setup_keyboard(void) = 0;
        /* setups mouse input, returns true on success */
        virtual bool setup_mouse(void) = 0;

        /* capture device statuses */
        virtual void capture(void) = 0;
};


/*
 * kage::core::input::CaptureInputTask
 *
 * Task for capturing input.
 */

class CaptureInputTask : public kage::core::sys::Task
{
    public:
        CaptureInputTask(void);
        /* Creates a new CaptureInputTask who will capture input using ``input_manager`` */
        CaptureInputTask(InputManager &input_manager);
        ~CaptureInputTask(void);

        kage::core::sys::Task::ExitCode run(const kage::core::sys::TaskInfo &ti);

        void set_input_manager(InputManager &input_manager);

    protected:
        /* The InputManager responsible for capturing input */
        InputManager* input_manager;
};


} // namespace input
} // namespace core
} // namespace kage

#endif // INPUT_HH_
