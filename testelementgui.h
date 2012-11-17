#ifndef TESTELEMENTGUI_H
#define TESTELEMENTGUI_H

#include<irrlicht/irrlicht.h>
#include "elementgui.h"
#include "Go/preferences.h"

namespace Test
{
    /** @brief Test GUI Element, will be replace by ::Vue and Page */
    class TestElementGUI : public irr::IEventReceiver
    {
    public:
        /** @brief now e isn't used */
        TestElementGUI(ElementGUI * e);

        /** @brief handle event.
            @param const irr::SEvent &event : receiving event */
        bool OnEvent(const irr::SEvent &event);
    private :

        /** @brief Device */
        irr::IrrlichtDevice *device;

        /** @brief Graphic Driver */
        irr::video::IVideoDriver* driver;

        /** @brief sceneManager */
        irr::scene::ISceneManager *sceneManager;

        /** @brief gui */
        irr::gui::IGUIEnvironment * gui;
    };
}

#endif // TESTELEMENTGUI_H
