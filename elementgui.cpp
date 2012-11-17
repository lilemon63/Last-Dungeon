#include "elementgui.h"

ElementGUI::ElementGUI(irr::gui::IGUIElement * parent,
                       const irr::core::rect<irr::s32> & area,
                       irr::gui::IGUIEnvironment * env)
    : irr::gui::IGUIElement( irr::gui::EGUIET_ELEMENT, env , parent, -1, area)
{
}
