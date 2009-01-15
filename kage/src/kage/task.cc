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
    LOG4CXX_DEBUG(logger, "Task at [" << this << "] deleted");
}


/*
 * kage::core::sys::TaskManager
 */

TaskManager::TaskManager(void)
    : last_task_info_id(0)
{
}

TaskManager::~TaskManager(void)
{
    // O(2 * (ntasks + nadded))
    /* Destroy all allocated TaskInfos in this->tasks and this->task_add_queue.
     * we skip this->task_rem_queue since it's just a subset of this->tasks */
    std::deque<TaskInfo*>::iterator dit;
    for (dit = this->task_add_queue.begin(); dit != this->task_add_queue.end(); ++dit)
        delete *dit;
    std::vector<TaskInfo*>::iterator vit;
    for (vit = this->tasks.begin(); vit != this->tasks.end(); ++vit)
        delete *vit;
}

std::size_t TaskManager::add_task(Task &task, const std::string &desc)
{
    // O(1)
    TaskInfo *ti = &this->create_TaskInfo(task, desc);
    this->task_add_queue.push_back(ti);
    LOG_DEBUG("Task id " << ti->id << " queued for addition");
    return ti->id;
}

void TaskManager::remove_task(std::size_t id)
{
    // O(nremoved)
    /* We better spend time doing this check here since doing it in
     * rem_queued_tasks() would take O(nremoved * ntasks) */
    std::deque<std::size_t>::iterator dit;
    for (dit = this->task_rem_queue.begin(); dit != this->task_rem_queue.end(); ++dit)
        if (*dit == id) {
            LOG_DEBUG("Task id " << id << " already queued for removal, skipping");
            return;
        }
    this->task_rem_queue.push_back(id);
    LOG_DEBUG("Queued Task id " << id << " for removal");
}

void TaskManager::run(void)
{
    std::size_t num_frames = 0;
    bool more_tasks = true;
    time_t started_at = time(NULL);

    LOG_INFO("TaskManager started working");
    while (more_tasks) {
        more_tasks = this->pre_run_once();
        this->run_once();
        this->post_run_once();
        ++num_frames;
    }
    LOG_INFO("TaskManager work done after "
            << time(NULL) - started_at << " seconds and "
            << num_frames << " frames.");
}

void TaskManager::run_once(void)
{
    // O(ntasks)
    TaskInfo *ti;
    time_t time_start;
    std::vector<TaskInfo*>::iterator vit;
    Task::ExitCode tec;

    for (vit = this->tasks.begin(); vit != this->tasks.end(); ++vit) {
        ti = *vit;
        time_start = this->task_info_pre_run_tick(*ti);
        tec = ti->task->run(*ti);
        this->task_info_post_run_tick(*ti, time_start);
        if (tec == Task::TASK_DONE) {
            LOG_DEBUG("Task id " << ti->id << " done");
            this->remove_task(ti->id);
        }
    }
}

inline bool TaskManager::pre_run_once(void)
{
    this->add_queued_tasks();
    return !this->tasks.empty();
}

inline void TaskManager::post_run_once(void)
{
    this->rem_queued_tasks();
}

void TaskManager::rem_queued_tasks(void)
{
    // 0(nremoved * ntasks)
    std::size_t id;
    std::vector<TaskInfo*>::iterator it;
    while (!this->task_rem_queue.empty()) {
        id = this->task_rem_queue.front();
        this->task_rem_queue.pop_front();
        for (it = this->tasks.begin(); (*it)->id != id; ++it)
            continue;
        this->destroy_TaskInfo(**it);
        this->tasks.erase(it);
        LOG_DEBUG("Removed Task id: " << id);
    }
}

void TaskManager::add_queued_tasks(void)
{
    // O(nadded)
    TaskInfo *ti;
    while (!this->task_add_queue.empty()) {
        ti = this->task_add_queue.front();
        this->tasks.push_back(ti);
        this->task_add_queue.pop_front();
        LOG_DEBUG("Added Task id: " << ti->id);
    }
}

TaskInfo& TaskManager::create_TaskInfo(Task &task, const std::string &desc)
{
    TaskInfo *ti = new TaskInfo();
    ti->id = ++this->last_task_info_id;
    ti->task.reset(&task);
    ti->desc = desc;
    ti->scheduled_since = time(NULL);
    ti->active_time = 0;
    ti->frame = 0;
    return *ti;
}

inline void TaskManager::destroy_TaskInfo(TaskInfo &ti)
{
    delete &ti;
}

inline time_t TaskManager::task_info_pre_run_tick(TaskInfo &ti)
{
    return time(NULL);
}

inline void TaskManager::task_info_post_run_tick(TaskInfo &ti, time_t time_start)
{
    ++ti.frame;
    ti.active_time += time_start;
}


} // namespace sys
} // namespace core
} // namespace kage
