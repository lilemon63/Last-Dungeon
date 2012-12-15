#include "testelementgui.h"
#include "Go/Control/servergo.h"
#include "Go/Vue/buttonpass.h"
#include "Network/server.h"
#include<iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>


namespace Test
{
    TestElementGUI::TestElementGUI(ElementGUI *e)
        : device(irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(800,600), 32, false, true, true, 0) ),
          driver(device->getVideoDriver() ),
          sceneManager(device->getSceneManager() ),
          gui( device->getGUIEnvironment() )
    {
        boost::mutex paralleleOperation;

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
/*
        Go::ButtonPass * b = new Go::ButtonPass(&s, gui, irr::core::rect<irr::s32>(800-100,50,800,80), L"Passer", NULL);
        //irr::gui::IGUIButton * passer = gui->addButton(, NULL, -1, );

        gui->addButton(irr::core::rect<irr::s32>(800-100,80,800,110), NULL, -1, L"Abandonner");
        gui->addStaticText(L"Equipe 1 : 0 points", irr::core::rect<irr::s32>(800-100,130,800,150));
        gui->addStaticText(L"Neckara", irr::core::rect<irr::s32>(800-80,150,800,180));
        gui->addStaticText(L"Equipe 2 : 0 points", irr::core::rect<irr::s32>(800-100,190,800,210));
        gui->addStaticText(L"NeckaraBis", irr::core::rect<irr::s32>(800-80,210,800,230));

*/
        Network::Server * server = new Network::Server(4000);

        IRC::IRCClient irc2(NULL, irr::core::rect<irr::s32>(0,480,800,600), gui, *server, paralleleOperation);

        irc = &irc2;
        irc->setHandle(&s);
 /*
        l = gui->addListBox(irr::core::rect<irr::s32>(0,480,800,580), NULL, -1, true);
        l->insertItem(0, L"tutu", 0);
        for(int i = 1; i != 30; ++i)
        {
            l->insertItem(i, L"toto", 0);// attention n'aime pas les retours à la ligne
            //l->setItemHeight();
            l->setSelected(i);
        }
        //gui->addTab(irr::core::rect<irr::s32>(780,480,800,580))->; */


        int i = 0;
        /* gestionnaire d'event */
        device->setEventReceiver(this);

        paralleleOperation.lock();

        while (device->run())
        {
            //server.m_run(1);
            paralleleOperation.unlock();
            paralleleOperation.lock();
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

        paralleleOperation.unlock();

        delete server;

        device->drop();
    }

    bool TestElementGUI::OnEvent(const irr::SEvent & event)
    {
        if( event.EventType == irr::EET_KEY_INPUT_EVENT
                && event.KeyInput.PressedDown
                && event.KeyInput.Key == irr::KEY_RETURN)
        {
            return irc->OnEvent(event);
        }
        return false;
    }
}
