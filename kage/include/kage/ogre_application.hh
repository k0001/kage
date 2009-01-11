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

#ifndef OGRE_APPLICATION_HH_
#define OGRE_APPLICATION_HH_

#include "kage/globals.hh"
#include "kage/application.hh"
#include "kage/input.hh"

namespace kage {
namespace ogre {
namespace sys {


/*
 * kage::ogre::sys::Application
 *
 * Controls the workflow of an Ogre powered application.
 */

class Application : public kage::core::sys::Application
{
    public:
        Application(const std::string &name="Kage Ogre Application",
                    const std::string &conf_path="",
                    const std::string &plugins_cfg="plugins.cfg",
                    const std::string &ogre_cfg="ogre.cfg",
                    const std::string &resources_cfg="resources.cfg",
                    const std::string &log_file_path="ogre.log");
        virtual ~Application(void);
        /* App entry point: setup, run and cleanup */
        virtual void go(void);

    protected:
        /* Application setup.
         * Calls each of the setup routines defined below. Returns true on succes */
        virtual bool setup(void);
        /* Application setup routines. Returns true on success. */
        virtual bool setup_root(void);
        virtual bool setup_render_system(void);
        virtual bool setup_input_manager(void);
        virtual bool setup_resources(void);
        virtual bool setup_render_window(void);
        virtual bool setup_resource_group(void);

        /* Application cleanup.
         * Calls each of the cleanup routines defined below. Returns true on succes */
        virtual bool cleanup(void);
        /* Application cleanup routines. Returns true on success. */
        virtual bool cleanup_root(void);
        virtual bool cleanup_render_system(void);
        virtual bool cleanup_input_manager(void);
        virtual bool cleanup_resources(void);
        virtual bool cleanup_render_window(void);
        virtual bool cleanup_resource_group(void);

        /* filesystem path where to find relative *.cfg files */
        std::string conf_path;

        /* config files */
        std::string plugins_cfg;
        std::string ogre_cfg;
        std::string resources_cfg;

        /* log files */
        std::string ogre_log_file_path;

        /* Ogre important stuff */
        Ogre::Root *root;

        /* Input manager */
        kage::core::input::InputManager *input_manager;
};


} // namespace sys
} // namespace ogre
} // namespace kage

#endif // OGRE_APPLICATION_HH_
