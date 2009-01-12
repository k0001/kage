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

#include "kage/task.hh"
#include "kage/utils.hh"

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger(
        "kage.core.sys.task"));


namespace kage {
namespace core {
namespace sys {


/*
 * kage::core::sys::TaskManager
 */
Task::Task(void)
{
}

Task::~Task(void)
{
}


/*
 * kage::core::sys::TaskManager
 */

TaskManager::TaskManager(void)
{
}

TaskManager::~TaskManager(void)
{
    /* Destroy all allocated TaskInfos in this->tasks and this->task_add_queue.
     * we skip this->task_rem_queue since it's just a subset of this->tasks */
    for (std::deque<TaskInfo*>::iterator dit = this->task_add_queue.begin()
            ; dit != this->task_add_queue.end()
            ; ++dit)
        delete *dit;
    for (std::vector<TaskInfo*>::const_iterator vit = this->tasks.begin()
            ; vit != this->tasks.end()
            ; ++vit)
        delete *vit;
}

unsigned int TaskManager::add_task(std::string name, Task &task)
{
    // O(2n)
    std::vector<TaskInfo*>::const_iterator vit;
    for (vit = this->tasks.begin(); vit != this->tasks.end(); ++vit)
        if ((*vit)->name == name)
            throw "Task already exists -- TODO: THROW REAL EXCEPTION";
    std::deque<TaskInfo*>::const_iterator dit;
    for (dit = this->task_add_queue.begin(); dit != this->task_add_queue.end()
            ; ++dit)
        if ((*dit)->name == name)
            // task already added, no need to add name again
            return (*dit)->id;
    TaskInfo ti = this->create_TaskInfo(name, task);
    this->task_add_queue.push_back(&ti);
    LOG4CXX_DEBUG(logger, "Queued task for addition: " << name);
    return ti.id;
}

void TaskManager::remove_task(unsigned int id)
{
    // O(2n)
    std::vector<TaskInfo*>::const_iterator vit;
    for (vit = this->tasks.begin()
            ; ((*vit)->id != id) && (vit != this->tasks.end())
            ; ++vit)
        ;
    if (vit == this->tasks.end())
        throw "Task does not exist -- TODO: THROW REAL EXCEPTION";
    std::deque<TaskInfo*>::const_iterator dit;
    for (dit = this->task_rem_queue.begin(); dit != this->task_rem_queue.end()
            ; ++dit)
        if ((*dit)->id == id)
            // task already removed, no need to remove it again
            return;
    this->task_rem_queue.push_back(*dit);
    LOG4CXX_DEBUG(logger, "Queued task for removal: " << (*dit)->name);
}

void TaskManager::remove_task(std::string name)
{
    // O(2n)
    std::vector<TaskInfo*>::const_iterator vit;
    for (vit = this->tasks.begin()
            ; ((*vit)->name != name) && (vit != this->tasks.end())
            ; ++vit)
        ;
    if (vit == this->tasks.end())
        throw "Task does not exist -- TODO: THROW REAL EXCEPTION";
    std::deque<TaskInfo*>::const_iterator dit;
    for (dit = this->task_rem_queue.begin(); dit != this->task_rem_queue.end()
            ; ++dit)
        if ((*dit)->name == name)
            // task already removed, no need to remove it again
            return;
    this->task_rem_queue.push_back(*dit);
    LOG4CXX_DEBUG(logger, "Queued task for removal: " << name);
}

void TaskManager::remove_task(Task &task)
{
    // O(n^2)
    std::vector<TaskInfo*>::const_iterator vit;
    std::deque<TaskInfo*>::const_iterator dit;
    bool found = false;
    for (vit = this->tasks.begin(); vit != this->tasks.end(); ++vit) {
        if ((*vit)->task == &task) {
            found = true;
            for (dit = this->task_rem_queue.begin()
                    ; (*vit != *dit) && (dit != this->task_rem_queue.end())
                    ; ++dit)
            if (dit == this->task_rem_queue.end()) {
                this->task_rem_queue.push_back(*vit);
                LOG4CXX_DEBUG(logger, "Queued task for removal: " << (*dit)->name);
            }
        }
    }
    if (!found)
        throw "Task does not exist -- TODO: THROW REAL EXCEPTION";
}

void TaskManager::run(void)
{
    while (true) {
        this->pre_run_once();
        this->run_once();
        this->post_run_once();
    }
}

void TaskManager::run_once(void)
{
    std::vector<TaskInfo*>::iterator vit;
    for (vit = this->tasks.begin(); vit != this->tasks.end(); ++vit) {
        TaskInfo *ti = *vit;
        this->task_info_pre_run_tick(*ti);
        float time_start = kage::utils::gettimeofdayf();
        ti->task->run(*ti);
        this->task_info_post_run_tick(*ti, time_start);
    }
}

inline void TaskManager::pre_run_once(void)
{
}

inline void TaskManager::post_run_once(void)
{
    this->rem_queued_tasks();
    this->add_queued_tasks();
}

void TaskManager::rem_queued_tasks(void)
{
    // 0(2^n)
    while (!this->task_rem_queue.empty()) {
        TaskInfo *ti = this->task_rem_queue.front();
        std::vector<TaskInfo*>::iterator it;
        // we are sure ti is here. so don't worry about bounds.
        for (it = this->tasks.begin(); *it != ti ; ++it)
            ;
        this->tasks.erase(it);
        this->task_rem_queue.pop_front();
        LOG4CXX_DEBUG(logger, "Removed task " << ti->name);
        this->destroy_TaskInfo(*ti);
    }
}

void TaskManager::add_queued_tasks(void)
{
    while (!this->task_add_queue.empty()) {
        TaskInfo *ti = this->task_add_queue.front();
        this->tasks.push_back(ti);
        this->task_add_queue.pop_front();
        LOG4CXX_DEBUG(logger, "Added task " << ti->name);
    }
}

TaskInfo& TaskManager::create_TaskInfo(std::string name, Task &task)
{
    static unsigned int last_id = 0;

    TaskInfo *ti = new TaskInfo();
    ti->id = ++last_id;
    ti->name = name;
    ti->task = &task;
    ti->scheduled_since = kage::utils::gettimeofdayf();
    ti->last_run = 0.0;
    ti->active_time = 0.0;
    ti->frame = 0;
    LOG4CXX_DEBUG(logger, "Created TaskInfo " << ti->id << " for Task " << name);
    return *ti;
}

inline void TaskManager::destroy_TaskInfo(TaskInfo &ti)
{
    LOG4CXX_DEBUG(logger, "Removing TaskInfo " << ti.id << " for Task " << ti.name);
    delete &ti;
}

inline void TaskManager::task_info_pre_run_tick(TaskInfo &ti)
{
}

inline void TaskManager::task_info_post_run_tick(TaskInfo &ti, float time_start)
{
    ++ti.frame;
    ti.last_run = time_start;
    ti.active_time += time_start;
}


} // namespace sys
} // namespace core
} // namespace kage
