#include "testelementgui.h"
#include "Go/Control/servergo.h"
#include<iostream>


namespace Test
{
    TestElementGUI::TestElementGUI(ElementGUI *e)
        : device(irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(800,600), 32, false, true, true, 0) ),
          driver(device->getVideoDriver() ),
          sceneManager(device->getSceneManager() ),
          gui( device->getGUIEnvironment() )
    {

        Go::Preferences pref( gui,
                              sceneManager,
                              irr::core::rect<irr::s32>(0,0,800,600),
                              gui->getRootGUIElement() );


        pref.setShortcut(irr::KEY_KEY_8, Go::CAMERA_UP);
        pref.setShortcut(irr::KEY_KEY_5, Go::CAMERA_INIT_POSITION);
        pref.setShortcut(irr::KEY_KEY_2, Go::CAMERA_DOWN);
        pref.setShortcut(irr::KEY_KEY_4, Go::CAMERA_LEFT);
        pref.setShortcut(irr::KEY_KEY_6, Go::CAMERA_RIGHT);
        pref.setShortcut(irr::KEY_ADD, Go::CAMERA_FRONT);
        pref.setShortcut(irr::KEY_SUBTRACT, Go::CAMERA_BACK);
        pref.setShortcut(irr::KEY_KEY_7, Go::CAMERA_LOOK_UP);
        pref.setShortcut(irr::KEY_KEY_9, Go::CAMERA_LOOK_RIGHT);
        pref.setShortcut(irr::KEY_KEY_3, Go::CAMERA_LOOK_DOWN);
        pref.setShortcut(irr::KEY_KEY_1, Go::CAMERA_LOOK_LEFT);
        pref.setShortcut(irr::KEY_DIVIDE, Go::CAMERA_LOOK_FRONT);
        pref.setShortcut(irr::KEY_MULTIPLY, Go::CAMERA_LOOK_BACK);
        Go::ServerGo s("test.map", pref);

        gui->addButton(irr::core::rect<irr::s32>(800-100,50,800,80), NULL, -1, L"Passer");
        gui->addButton(irr::core::rect<irr::s32>(800-100,80,800,110), NULL, -1, L"Abandonner");
        gui->addStaticText(L"Equipe 1 : 0 points", irr::core::rect<irr::s32>(800-100,130,800,150));
        gui->addStaticText(L"Neckara", irr::core::rect<irr::s32>(800-80,150,800,180));
        gui->addStaticText(L"Equipe 2 : 0 points", irr::core::rect<irr::s32>(800-100,190,800,210));
        gui->addStaticText(L"NeckaraBis", irr::core::rect<irr::s32>(800-80,210,800,230));

        int i = 0;
        /* gestionnaire d'event */
        device->setEventReceiver(this);
        while (device->run())
        {
            driver->beginScene(true,true,irr::video::SColor(255,100,255,255));    // fond blanc
            //sceneManager->drawAll();                    // calcule le rendu
            gui->drawAll();
            driver->endScene();
            if(++i == 20)
            {
                irr::core::stringw titre;
                titre += driver->getFPS();
                device->setWindowCaption(titre.c_str ());//for know the frame rate
                i = 0;
            }
        }

        device->drop();
    }

    bool TestElementGUI::OnEvent(const irr::SEvent &)
    {
        return false;
    }
}
