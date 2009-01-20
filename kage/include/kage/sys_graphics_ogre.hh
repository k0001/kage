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

#ifndef KAGE_SYS_GRAPHICS_OGRE_HH_
#define KAGE_SYS_GRAPHICS_OGRE_HH_

#include "kage/sys_graphics.hh"
#include "kage/globals.hh"


namespace kage {
namespace ogre {
namespace graphics {


/*
 * kage::core::graphics::OgreGraphicSystem
 *
 * Interface for Graphic Systems that are part of a kage::core::sys::Application
 */

class OgreGraphicSystem : public kage::core::graphics::GraphicSystem
{
    public:
        OgreGraphicSystem(const std::string &conf_path="",
                          const std::string &plugins_cfg="plugins.cfg",
                          const std::string &ogre_cfg="ogre.cfg",
                          const std::string &resources_cfg="resources.cfg",
                          const std::string &ogre_log_file_path="ogre.log");
        ~OgreGraphicSystem(void);

        /* Setup Ogre Graphic System. Returns true on succes */
        bool setup(kage::core::sys::Application &app);

        bool after_setup(void) { }

        /* Update Ogre Graphic System status. Called once per frame. Returns true on success */
        bool update(void);

        /* Returns the window handle for the RenderWindow being used */
        std::size_t get_window_handle(void);

    protected:
        /* Setup subroutines. Return true on success. */
        bool setup_root(void);
        bool setup_render_system(void);
        bool setup_resources(void);
        bool setup_render_window(void);
        bool setup_resource_group(void);

        /* Ogre Graphics System cleanup routine. Returns true on success */
        bool cleanup(void);
        /* Cleanup subroutines. Return true on success. */
        bool cleanup_root(void);
        bool cleanup_render_system(void);
        bool cleanup_resources(void);
        bool cleanup_render_window(void);
        bool cleanup_resource_group(void);

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

        /* Application pointer */
        kage::core::sys::Application *app;
};


} // namespace graphics
} // namespace ogre
} // namespace kage


#endif // KAGE_SYS_GRAPHICS_OGRE__

