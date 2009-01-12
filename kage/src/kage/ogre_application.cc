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
#include "kage/ois_input_buffered.hh"

namespace kage {
namespace ogre {
namespace sys {


/*
 * Application
 */

Application::Application(const std::string &name,
                         const std::string &conf_path,
                         const std::string &plugins_cfg,
                         const std::string &ogre_cfg,
                         const std::string &resources_cfg,
                         const std::string &ogre_log_file_path)
    : kage::core::sys::Application(name)
    , conf_path(conf_path)
    , ogre_log_file_path(ogre_log_file_path)
    , root(NULL)
    , input_manager(NULL)
    , capture_input_task_name("OIS Capture Input")
{
    // Setup configuration files paths
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

Application::~Application(void)
{
    this->cleanup();
}

void Application::go(void)
{
    rInfo("Ogre Application starting...");
    try {
        if (this->setup())
            this->run();
    }
    catch ( ... ) {
        this->cleanup();
        throw;
    }
}

bool Application::setup(void)
{
    rInfo("Setting up Ogre Application");

    if (this->setup_root()) {
        rInfo("Ogre::Root ready");
    }
    else {
        rError("Failed to create Ogre::Root");
        return false;
    }

    if (this->setup_render_system()) {
        rInfo("Render system ready");
    }
    else {
        rError("Failed to setup Render system");
        return false;
    }

    if (this->setup_resources()) {
        rInfo("Resources ready");
    }
    else {
        rError("Failed to define resources");
        return false;
    }

    if (this->setup_render_window()) {
        rInfo("Render window ready");
    }
    else {
        rError("Failed to create render window");
        return false;
    }

    if (!this->setup_resource_group()) {
        rInfo("Resource group ready");
    }
    else {
        rError("Failed to initialise resource group");
        return false;
    }

    return true;
}

bool Application::cleanup(void)
{
    rInfo("Cleaning up Ogre Application");
    bool fail = false;

    if (this->cleanup_resource_group()) {
        rInfo("Cleaned up resource group");
    }
    else {
        rError("Failed to cleanup resource group");
        fail = true;
    }

    if (this->cleanup_render_window()) {
        rInfo("Cleaned up render window");
    }
    else {
        rError("Failed to cleanup render window");
        fail = true;
    }

    if (this->cleanup_resources()) {
        rInfo("Cleaned up resources");
    }
    else {
        rError("Failed to cleanup resources");
        fail = true;
    }

    if (this->cleanup_render_system()) {
        rInfo("Cleaned up render system");
    }
    else {
        rError("Failed to cleanup Render system");
        fail = true;
    }

    if (this->cleanup_root()) {
        rInfo("Cleaned up Ogre::Root");
    }
    else {
        rError("Failed to cleanup Ogre::Root");
        fail = true;
    }

    return !fail;
}

bool Application::setup_root(void)
{
    if (this->root)
        return false;
    this->root = new Ogre::Root(this->plugins_cfg, this->ogre_cfg,
            this->ogre_log_file_path);
    return (this->root != NULL);
}

bool Application::setup_render_system(void)
{
    if (!this->root->restoreConfig() && !this->root->showConfigDialog())
        return false;
    return true;
}

bool Application::setup_input_manager(void)
{
    std::size_t window_handler = 0;
    Ogre::RenderWindow *win = this->root->getAutoCreatedWindow();
    win->getCustomAttribute("WINDOW", &window_handler);
    if (!window_handler)
        return false;
    this->input_manager = new kage::ois::input::BufferedInputManager(
            window_handler);
    kage::core::input::CaptureInputTask task_ci(*this->input_manager);
    this->task_mgr.add_task(this->capture_input_task_name, task_ci);
    return true;
}

bool Application::setup_resources(void)
{
    std::string sec_name, type_name, arch_name;
    Ogre::ConfigFile cf;
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::ConfigFile::SettingsMultiMap *settings;
    Ogre::ResourceGroupManager *res_group_manager = \
            &Ogre::ResourceGroupManager::getSingleton();

    cf.load(this->resources_cfg);
    while (seci.hasMoreElements()) {
        sec_name = seci.peekNextKey();
        settings = seci.getNext();
        for (Ogre::ConfigFile::SettingsMultiMap::iterator i = settings->begin();
             i != settings->end(); ++i)
        {
            type_name = i->first;
            arch_name = i->second;
            res_group_manager->addResourceLocation(arch_name, type_name,
                                                   sec_name);
        }
    }
    // TODO: realize when to return false.
    return true;
}


bool Application::setup_render_window(void)
{
    return (this->root->initialise(true, this->name) != NULL);
}

bool Application::setup_resource_group(void)
{
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    // TODO: realize when to return false.
    return true;
}


bool Application::cleanup_root(void)
{
    if (this->root) {
        delete this->root;
        this->root = NULL;
    }
    return true;
}

bool Application::cleanup_render_system(void)
{
    return true;
}

bool Application::cleanup_input_manager(void)
{
    if (this->input_manager) {
        delete this->input_manager;
        this->input_manager = NULL;
        try {
            this->task_mgr.remove_task(this->capture_input_task_name);
        }
        catch ( ... ) {
            rError("...SOMETHING BAD HAPPENED!");
            return false;
        }
    }
    return true;

}

bool Application::cleanup_resources(void)
{
    return true;
}

bool Application::cleanup_render_window(void)
{
    return true;
}

bool Application::cleanup_resource_group(void)
{
    return true;
}


} // namespace sys
} // namespace ogre
} // namespace kage
