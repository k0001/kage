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

namespace kage {
namespace ogre {
namespace sys {

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

protected:
    /* Creates Ogre Application Root */
    virtual void create_root(void);
    /* Loads resources */
    virtual void define_resources(void);
    virtual void setup_render_system(void);
    virtual void create_render_window(void);

    /* filesystem path where to find relative *.cfg files */
    std::string conf_path;

    /* config files */
    std::string plugins_cfg;
    std::string ogre_cfg;
    std::string resources_cfg;

    /* Ogre important stuff */
    Ogre::Root root;
    Ogre::RenderWindow *win;
    std::string log_file_path;
};

} // namespace sys
} // namespace ogre
} // namespace kage

#endif // OGRE_APPLICATION_HH_
