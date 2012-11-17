#include "vue.h"
#include "../Control/plinth.h"
#include "playervue.h"
#include "../Control/servergo.h"
#include "../Control/pawn.h"
#include <iostream>

#include<cmath>

namespace Go
{
    Vue::Vue(const Preferences & pref ,ServerGo * control) :
        ElementGUI(pref.getParent(),
                   pref.getArea(),
                   pref.getEnv() ),
        m_control( control ),
        driver( pref.getEnv()->getVideoDriver() ),
        sceneManager( pref.getManager() ),
        camera( NULL ),
        m_shortcut( pref.getShortcut() )

    {
       pref.getEnv()->setFocus(this);
       //sceneManager->addMeshSceneNode(sceneManager->getMesh("Amphi.3ds"), NULL, -1, irr::core::vector3df(0,-20,10)); add any type of graphic object.
    }

    void Vue::setSkyDome(const std::string & path, irr::u32 resolutionHorizontal, irr::u32 resolutionVertical,
                      irr::f32, irr::f32, irr::f32)
    {
        sceneManager->addSkyDomeSceneNode( driver->getTexture(path.c_str() ), resolutionHorizontal,resolutionVertical,
                                           0.9,2.0,500.);

    }

    void Vue::setSkyCube(const std::string & path_up, const std::string & path_dn, const std::string & path_lf,
                         const std::string & path_ft, const std::string & path_rt, const std::string & path_bk)
    {
        sceneManager->addSkyBoxSceneNode( driver->getTexture(path_up.c_str()),
                                          driver->getTexture(path_dn.c_str()),
                                          driver->getTexture(path_lf.c_str()),
                                          driver->getTexture(path_ft.c_str()),
                                          driver->getTexture(path_rt.c_str()),
                                          driver->getTexture(path_bk.c_str()) );
    }


    void Vue::draw(void)
    {
        driver->setViewPort( AbsoluteRect );
        sceneManager->setActiveCamera(camera);
        sceneManager->drawAll();
    }

    bool Vue::OnEvent(const irr::SEvent &event)
    {
        if(! camera)
            return false;
        if(event.EventType == irr::EET_MOUSE_INPUT_EVENT && event.MouseInput.isRightPressed())
        {
            irr::scene::ISceneNode * i = sceneManager->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(irr::core::vector2d<irr::s32>(event.MouseInput.X, event.MouseInput.Y));
            ListPlinth::const_iterator const end = m_listPlinth.end();
            ListPlinth::iterator it = m_listPlinth.find(i); //get the plinth where we click on.
            if(it != end)
                m_control->putPawn( it->second );//put a pawn in this plinth TODO : different pawn
            else
            {
            }
        }
        if( event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown )
        {
            //execute the shortcut keyboard
            ListShortCut::const_iterator const end = m_shortcut.end();
            ListShortCut::const_iterator it = m_shortcut.find(event.KeyInput.Key);
            if( it == end )
                return false;
            IdAction act = it->second;
            switch(act)
            {
                case CAMERA_INIT_POSITION :
                    camera->setRotation( irr::core::vector3df(0,0,0) );
                    camera->setPosition( irr::core::vector3df(0,0,0) );
                break;
                case CAMERA_UP :
                    changeCameraPos(0,1,0);
                break;
                case CAMERA_DOWN :
                    changeCameraPos(0,-1,0);
                break;
                case CAMERA_LEFT :
                    changeCameraPos(-1,0,0);
                break;
                case CAMERA_RIGHT :
                    changeCameraPos(1,0,0);
                break;
                case CAMERA_FRONT :
                    changeCameraPos(0,0,1);
                break;
                case CAMERA_BACK :
                    changeCameraPos(0,0,-1);
                break;
                case CAMERA_LOOK_UP :
                    changeCameraAngle(0,1,0);
                break;
                case CAMERA_LOOK_DOWN :
                    changeCameraAngle(0,-1,0);
                break;
                case CAMERA_LOOK_LEFT :
                    changeCameraAngle(-1,0,0);
                break;
                case CAMERA_LOOK_RIGHT :
                    changeCameraAngle(1,0,0);
                break;
                case CAMERA_LOOK_FRONT :
                    changeCameraAngle(0,0,1);
                break;
                case CAMERA_LOOK_BACK :
                    changeCameraAngle(0,0,-1);
                break;

                default :
                    return false;
            }
            return true;
        }
        //be carefull do not absorb the focus!

        return false;
    }

    irr::scene::ISceneNode * Vue::setBoard(const irr::core::vector3df & position)
    {
        irr::scene::ISceneNode * i = sceneManager->addEmptySceneNode(NULL);
        i->setPosition(irr::core::vector3df(position) );
        return i;
    }

    void Vue::setPlinth(const irr::core::vector3df & position, const irr::core::vector3df & angle,
                                            irr::scene::ISceneNode * parent, Plinth * p)
    {
        irr::scene::ISceneNode * i = p->set(position, angle, parent, sceneManager);
        m_listPlinth[i] = p;
    }

    void Vue::setPlayer(unsigned int num)
    {
        camera = m_listPlayer[num]->getCamera();
        sceneManager->setActiveCamera( camera );
        sceneManager->addLightSceneNode(camera, irr::core::vector3df(0, 0, 0) );
    }

    Vue::~Vue(void)
    {
        ListPlayer::const_iterator const end = m_listPlayer.end();
        ListPlayer::iterator it = m_listPlayer.begin();
        for( ; it != end; ++it)
            delete *it;
    }


    irr::scene::ICameraSceneNode * Vue::addCamera(void)
    {
        return sceneManager->addCameraSceneNodeFPS(NULL);
    }

    void Vue::changeCameraPos(irr::f32 x, irr::f32 y, irr::f32 z )
    {
        irr::core::vector3df pos = camera->getPosition();
        pos.X += x;
        pos.Y += y;
        pos.Z += z;
        camera->setPosition(pos);
    }

    void Vue::changeCameraAngle(irr::f32 x, irr::f32 y, irr::f32 z )
    {
        irr::core::vector3df angle = camera->getRotation();
        angle.X += x;
        angle.Y += y;
        angle.Z += z;
        camera->setRotation(angle);
    }

    void Vue::putPawn(Pawn * pa, Plinth * pl)
    {
        pa->set(sceneManager, pl);
    }

    void Vue::deleteGroupe(Groupe * g)
    {
        Groupe::const_iterator const end = g->end();
        Groupe::iterator it = g->begin();
        for( ; it != end; ++it)
        {
            (*it)->remove();
        }
    }
}
