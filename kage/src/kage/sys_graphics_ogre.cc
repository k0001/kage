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

#include "kage/sys_graphics_ogre.hh"

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger(
        "kage.ogre.graphics.system"));


namespace kage {
namespace ogre {
namespace graphics {


OgreGraphicSystem::OgreGraphicSystem(const std::string &conf_path,
                                     const std::string &plugins_cfg,
                                     const std::string &ogre_cfg,
                                     const std::string &resources_cfg,
                                     const std::string &log_file_path)
    : conf_path(conf_path)
    , ogre_log_file_path(ogre_log_file_path)
    , root(NULL)
    , app(NULL)
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

    // TODO: stat() file paths to check existence/permissions
}

OgreGraphicSystem::~OgreGraphicSystem(void)
{
    this->cleanup();
}


bool OgreGraphicSystem::setup(kage::core::sys::Application &app)
{
    LOG_INFO("Setting up Ogre Application");

    if (this->setup_root()) {
        LOG_INFO("Ogre::Root ready");
    }
    else {
        LOG_ERROR("Failed to create Ogre::Root");
        return false;
    }

    if (this->setup_render_system()) {
        LOG_INFO("Render system ready");
    }
    else {
        LOG_ERROR("Failed to setup Render system");
        return false;
    }

    if (this->setup_resources()) {
        LOG_INFO("Resources ready");
    }
    else {
        LOG_ERROR("Failed to define resources");
        return false;
    }

    if (this->setup_render_window()) {
        LOG_INFO("Render window ready");
    }
    else {
        LOG_ERROR("Failed to create render window");
        return false;
    }

    if (this->setup_resource_group()) {
        LOG_INFO("Resource group ready");
    }
    else {
        LOG_ERROR("Failed to initialise resource group");
        return false;
    }

    this->app = &app;
    return true;
}

bool OgreGraphicSystem::setup_root(void)
{
    if (this->root)
        return false;

    /* TODO: try/catch here */
    this->root = new Ogre::Root(this->plugins_cfg, this->ogre_cfg,
                                this->ogre_log_file_path);
    return true;
}

bool OgreGraphicSystem::setup_render_system(void)
{
    // if (this->root->restoreConfig() && !this->root->showConfigDialog())
    if (!this->root->showConfigDialog())
        return false;
    return true;
}

bool OgreGraphicSystem::setup_resources(void)
{
    std::string sec_name, type_name, arch_name;
    Ogre::ConfigFile cf;
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::ConfigFile::SettingsMultiMap *settings;
    Ogre::ResourceGroupManager *res_group_manager = \
            &Ogre::ResourceGroupManager::getSingleton();

    try {
        cf.load(this->resources_cfg);
    }
    catch (Ogre::Exception &e) {
        if (e.getNumber() == 6) {
            LOG_ERROR("File not found: " << this->resources_cfg);
            return false;
        }
    }

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

bool OgreGraphicSystem::setup_render_window(void)
{
    return this->root->initialise(true, this->app->get_name()) != NULL;
}

bool OgreGraphicSystem::setup_resource_group(void)
{
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    // TODO: realize when to return false.
    return true;
}

bool OgreGraphicSystem::cleanup(void)
{
    LOG_INFO("Cleaning up Ogre Application");
    bool fail = false;

    if (this->cleanup_resource_group()) {
        LOG_INFO("Cleaned up resource group");
    }
    else {
        LOG_ERROR("Failed to cleanup resource group");
        fail = true;
    }

    if (this->cleanup_render_window()) {
        LOG_INFO("Cleaned up render window");
    }
    else {
        LOG_ERROR("Failed to cleanup render window");
        fail = true;
    }

    if (this->cleanup_resources()) {
        LOG_INFO("Cleaned up resources");
    }
    else {
        LOG_ERROR("Failed to cleanup resources");
        fail = true;
    }

    if (this->cleanup_render_system()) {
        LOG_INFO("Cleaned up render system");
    }
    else {
        LOG_ERROR("Failed to cleanup Render system");
        fail = true;
    }

    if (this->cleanup_root()) {
        LOG_INFO("Cleaned up Ogre::Root");
    }
    else {
        LOG_ERROR("Failed to cleanup Ogre::Root");
        fail = true;
    }

    return !fail;
}

bool OgreGraphicSystem::cleanup_root(void)
{
    if (this->root) {
        delete this->root;
        this->root = NULL;
    }
    return true;
}

bool OgreGraphicSystem::cleanup_render_system(void)
{
    return true;
}

bool OgreGraphicSystem::cleanup_resources(void)
{
    return true;
}

bool OgreGraphicSystem::cleanup_render_window(void)
{
    return true;
}

bool OgreGraphicSystem::cleanup_resource_group(void)
{
    return true;
}


} // namespace graphics
} // namespace ogre
} // namespace kage

