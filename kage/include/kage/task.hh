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
    unsigned int id;
    // Task name
    std::string name;
    // The Task itself
    Task *task;
    // When did the Task was scheduled for excecution
    float scheduled_since;
    // When did the task started running for the last time
    float last_run;
    // How much time the Task has been actually active (i.e, not idle)
    float active_time;
    // How many frames since the Task started running
    unsigned int frame;
};


/*
 * kage::core::sys::Task
 *
 * kage::core::sys::TaskManager's Task interface.
 */

class Task {
    public:
        /* Continuation enumerates exit values for Task::run, specifying what
         * should happen with the Task before the next execution happens. */
        enum Continuation {
            DONE,       // Stop running the Task
            CONTINUE,   // Continue running the Task
        };

        Task(void);
        virtual ~Task(void) = 0;

        /* Actual Task code */
        virtual Continuation run(const TaskInfo &ti) = 0;
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

        /* Adds a ``task` to be executed on the next run, identified by ``name`` within this TaskManager.
         * An unique identifier for the Task within this TaskManager is returned.
         * Notice the ``name`` must be unique, however you can add the same ``task`` under different names.
         * How many times you add a pair with the same ``name`` per run is irrelevant, since it will be added just once per run
         *
         * XXX: Takes O(2n) to run to preserve addition order. Is it needed? */
        unsigned int add_task(std::string name, Task &task);
        /* Removes all tasks identified by ``id`` after the current run ends.
         * How many times you remove a task with the same ``id`` per run is irrelevant, since it will be removed just once per run.
         *
         * XXX: Takes O(2n) to run to preserve addition order. Is it needed? */
        void remove_task(unsigned int id);
        /* Removes all tasks identified by ``name`` after the current run ends.
         * How many times you remove a task with the same ``name`` per run is irrelevant, since it will be removed just once per run.
         *
         * XXX: Takes O(2n) to run to preserve addition order. Is it needed? */
        void remove_task(std::string name);
        /* Removes every occurrence of ``task`` previously added after the current run ends.
         * How many times you remove the same ``task`` per run is irrelevant, since it will be removed just once per run.
         *
         * XXX: Takes O(n^2) to run to preserve addition order. Is it needed? */
        void remove_task(Task &task);

        /* TaskManager's main loop. Serially excecute all available tasks in the same order they where added */
        void run(void);

    protected:
        /* Called on each iteration of run(), responsible for running all tasks */
        void run_once(void);

        /* Pre and Post hooks for run_once */
        void pre_run_once(void);
        void post_run_once(void);

        /* Removal of queued Tasks, called on current run iteration's post_run_once() -- before addition of queued tasks */
        void rem_queued_tasks(void);
        /* Addition of queued Tasks, called on current run iteration's post_run_once() -- after removal of queued tasks */
        void add_queued_tasks(void);

        /* TaskInfo factory */
        TaskInfo& create_TaskInfo(std::string name, Task &task);
        /* TaskInfo destroyer */
        void destroy_TaskInfo(TaskInfo &ti);
        /* Updates ``ti`` before running the associated task */
        void task_info_pre_run_tick(TaskInfo &ti);
        /* Updates ``ti`` after running the associated task, ``time_start`` tells the time when ``ti`` started running */
        void task_info_post_run_tick(TaskInfo &ti, float time_start);

        /* Tasks queued for removal */
        std::deque<TaskInfo*> task_rem_queue;
        /* Tasks queued for addition */
        std::deque<TaskInfo*> task_add_queue;

        /* Here we hold the TaskInfo for each Task scheduled for execution */
        std::vector<TaskInfo*> tasks;
};


} // namespace sys
} // namespace core
} // namespace kage

#endif // TASK_HH_

