#include "elementgui.h"

#include <iostream>

ElementGUI::ElementGUI(irr::gui::IGUIElement * parent,
                       const irr::core::rect<irr::s32> & area,
                       irr::gui::IGUIEnvironment * env)
    : irr::gui::IGUIElement( irr::gui::EGUIET_ELEMENT, env , (parent? parent: env->getRootGUIElement()), -1, area)
{
}
