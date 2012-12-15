#include "buttonpass.h"
#include "../Control/servergo.h"

namespace Go
{
    ButtonPass::ButtonPass(ServerGo *server, irr::gui::IGUIEnvironment * gui, irr::core::rect<irr::s32> area,
                           const wchar_t * text, irr::gui::IGUIElement * parent) :
      irr::gui::IGUIButton(gui, parent, -1, area),
      m_server(server)
    {
        this->setText(text);
    }

    bool ButtonPass::OnEvent(const irr::SEvent &event)
    {
        if( event.EventType == irr::EET_GUI_EVENT
                && event.GUIEvent.EventType == irr::gui::EGBS_BUTTON_UP
                && event.GUIEvent.Caller == this)
            ;

    }
}
