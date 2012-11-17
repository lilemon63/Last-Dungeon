#ifndef ELEMENTGUI_H
#define ELEMENTGUI_H

#include<irrlicht/irrlicht.h>

/** @brief All personnal elementGUI must herit (public) by ElementGUI.<br/>
  He construct the irr::gui::IGUIElement with no Id (id = -1).<br/>
  He put the position of the elementGUI, its dimensions, its parent and the environment (gui)
            */
class ElementGUI : public irr::gui::IGUIElement
{
public:
    /** @brief Construct an ElementGUI
        @param irr::gui::IGUIElement * parent : parent of the elementGUI.<br/>
        The elementGUI will be put relative to the parent.<br/>
        The parent will be receive the event before its children.
        @param const irr::core::rect<irr::s32> & area : Set the elementGUI's coordonate.<br/>
        Firts the coordonate of the corner at the top left of the elementGUI relative to his parent.<br/>
        And then the widht and the length of the elementGUI.
        @param irr::gui::IGUIEnvironment * env : gui where we put the elementGUI.<br/>
        You should have one only gui.*/
    ElementGUI(irr::gui::IGUIElement * parent,
               const irr::core::rect<irr::s32> & area,
               irr::gui::IGUIEnvironment * env);

    virtual ~ElementGUI(){}
};

#endif // ELEMENTGUI_H
