#include "preferences.h"

namespace Go
{
    Preferences::Preferences(irr::gui::IGUIEnvironment * env, irr::scene::ISceneManager *manager,
                             const irr::core::rect<irr::s32> & area, irr::gui::IGUIElement *parent,
                             bool createNewSceneManager) :
        m_server(NULL),
        m_area(area),
        m_parent(parent),
        m_env(env),
        m_manager( createNewSceneManager ? manager->createNewSceneManager() : manager)
        {
        }
}
