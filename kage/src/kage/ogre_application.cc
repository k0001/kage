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

#include "kage/ogre_application.hh"


namespace kage {
namespace ogre {
namespace sys {


Application::Application(const std::string &name,
                         const std::string &conf_path,
                         const std::string &plugins_cfg,
                         const std::string &ogre_cfg,
                         const std::string &resources_cfg,
                         const std::string &log_file_path)
    : kage::core::sys::Application(name),
      conf_path(conf_path),
      log_file_path(log_file_path)
{
    /* Setup configuration files paths */
    if (this->conf_path.length())
        this->conf_path += '/';

    if (plugins_cfg[0] == '/')
        this->plugins_cfg = plugins_cfg;
    else
        this->plugins_cfg = this->conf_path + plugins_cfg;

    if (ogre_cfg[0] == '/')
        this->ogre_cfg = ogre_cfg;
    else
        this->ogre_cfg = this->conf_path + ogre_cfg;

    if (resources_cfg[0] == '/')
        this->resources_cfg = resources_cfg;
    else
        this->resources_cfg = this->conf_path + resources_cfg;
}

void Application::create_root(void)
{
    this->root = Ogre::Root(this->plugins_cfg, this->ogre_cfg,
            this->log_file_path);
}

void Application::setup_render_system(void)
{
    if (!this->root.restoreConfig() && !this->root.showConfigDialog())
        throw Ogre::Exception(52, "User canceled the config dialog!",
                "kage::ogre::sys::Application::setup_render_system()");
}


} // namespace sys
} // namespace ogre
} // namespace kage
