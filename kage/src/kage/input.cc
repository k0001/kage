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

#include "kage/input.hh"

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger(
        "kage.core.input"));


namespace kage {
namespace core {
namespace input {


/*
 * kage::core::input::InputManager
 */

InputManager::InputManager(void)
{
}

InputManager::~InputManager(void)
{
}


/*
 * kage::core::input::CaptureInputTask
 */

CaptureInputTask::CaptureInputTask(void)
    : input_manager(NULL)
{
}

CaptureInputTask::CaptureInputTask(InputManager &input_manager)
    : input_manager(&input_manager)
{
}

CaptureInputTask::~CaptureInputTask(void)
{
}

void CaptureInputTask::set_input_manager(InputManager &input_manager)
{
    this->input_manager = &input_manager;
}

kage::core::sys::Task::ExitCode CaptureInputTask::run(
        const kage::core::sys::TaskInfo &ti)
{
    this->input_manager->capture();
    return this->TASK_CONTINUE;
}


} // namespace input
} // namespace core
} // namespace kage

