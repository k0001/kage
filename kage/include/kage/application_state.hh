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

#ifndef APPLICATION_STATE_HH_
#define APPLICATION_STATE_HH_

namespace kage {
namespace core {
namespace sys {

class Application;

class ApplicationState
{
    public:
        ApplicationState(void);
        virtual ~ApplicationState(void);

        /* ApplicationState startup: app is the Application this
         * ApplicationState is being attached to. */
        virtual void init(Application *app);
        /* ApplicationState cleanup: called before removal. */
        virtual void shutdown(void);
        /* ApplicationState execution is paused */
        virtual void pause(void);
        /* ApplicationState excecution is resumed */
        virtual void resume(void);
        /* method called on every frame/loop */
        virtual bool run(void);
        /* check current excecution status */
        bool is_running(void);

    private:
        Application *app;
        bool running;

        /* this ApplicationState can call quit when it needs to remove itself */
        void quit(void);

};


} // namespace sys
} // namespace core
} // namespace kage

#endif // APPLICATION_STATE_HH_
