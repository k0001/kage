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

#ifndef TASK_HH_
#define TASK_HH_

#include "kage/globals.hh"

namespace kage {
namespace core {
namespace sys {

class TaskManager;
class Task;


/*
 * kage::core::sys::TaskInfo
 *
 * Task information handled to every Task on each run.
 */

struct TaskInfo
{
    // Task id assigned by the TaskManager
    std::size_t id;
    // Task name
    std::string desc;
    // The Task itself
    boost::shared_ptr<Task> task;
    // When did the Task was scheduled for excecution
    time_t scheduled_since;
    // How much time the Task has been actually active (i.e, not idle)
    time_t active_time;
    // How many frames since the Task started running
    std::size_t frame;
};


/*
 * kage::core::sys::Task
 *
 * kage::core::sys::TaskManager's Task interface.
 */

class Task {
    public:
        /* ExitCode enumerates exit values for Task::run, specifying what
         * should happen with the Task before the next execution happens. */
        enum ExitCode {
            TASK_DONE,       // Stop running the Task
            TASK_CONTINUE    // Continue running the Task
        };

        Task(void);
        virtual ~Task(void);

        /* Actual Task code */
        virtual ExitCode run(const TaskInfo &ti) = 0;
};


/*
 * kage::core::sys::TaskManager
 *
 * Manages a collection of Tasks to be executed.
 */

class TaskManager {
    public:
        TaskManager(void);
        ~TaskManager(void);

        /* Adds a ``task` to be executed on the next iteration of this TaskManager.
         * An unique identifier for the Task within this TaskManager is returned. */
        std::size_t add_task(Task &task, const std::string &desc="");
        /* Removes all the registered tasks identified by ``id`` after the current run ends. */
        void remove_task(std::size_t id);

        /* TaskManager's main loop. Serially excecute all available tasks in the same order they where added */
        void run(void);

    protected:
        /* Called on each iteration of run(), responsible for running all tasks. */
        void run_once(void);

        /* Pre run_once hook. Returns true if there are still tasks to be executed on a next iteration */
        bool pre_run_once(void);
        /* Post run_once hook */
        void post_run_once(void);

        /* Removal of queued Tasks, called on current run iteration's post_run_once() -- before addition of queued tasks */
        void rem_queued_tasks(void);
        /* Addition of queued Tasks, called on current run iteration's post_run_once() -- after removal of queued tasks */
        void add_queued_tasks(void);

        /* TaskInfo factory */
        TaskInfo& create_TaskInfo(Task &task, const std::string &desc);
        /* TaskInfo destroyer */
        void destroy_TaskInfo(TaskInfo &ti);
        /* Updates ``ti`` before running the associated task.
         * Returns a the currennt timestamp meaning "when the ``ti`` started running" */
        time_t task_info_pre_run_tick(TaskInfo &ti);
        /* Updates ``ti`` after running the associated task.
         * ``time_start`` tells the "time when ``ti`` started running" as returned by task_info_pre_run_tick(ti) */
        void task_info_post_run_tick(TaskInfo &ti, time_t time_start);

        /* Tasks ids queued for removal */
        std::deque<std::size_t> task_rem_queue;
        /* Tasks queued for addition */
        std::deque<TaskInfo*> task_add_queue;
        /* Here we hold the TaskInfo for each Task scheduled for execution */
        std::vector<TaskInfo*> tasks;

        /* Last id assigned to a TaskInfo */
        std::size_t last_task_info_id;

};


} // namespace sys
} // namespace core
} // namespace kage

#endif // TASK_HH_

