#include "servergo.h"
#include "plinth.h"
#include "../Vue/playervue.h"
#include "pawn.h"

namespace Go
{
    ServerGo::ServerGo(const std::string &, Preferences & pref)
        : m_vue(pref, this)
    {

        pref.addServerGo(this);
        //useless, it's the loading of map which will put the scene

        irr::scene::ISceneNode *i = m_vue.setBoard(irr::core::vector3df(0,0,0) ); //put into a Board class

        m_plinth = new Plinth[9*6];

        for(int j = 1; j != 4; ++j) //TODO put plinth relative to other plinth
        {
            m_vue.setPlinth(irr::core::vector3df(-5,0,(j-1)*5+5), irr::core::vector3df(0,0,0), i, &m_plinth[3*(j-1)]);
            m_vue.setPlinth(irr::core::vector3df(0,0,(j-1)*5+5), irr::core::vector3df(0,0,0), i, &m_plinth[3*(j-1)+1]);
            m_vue.setPlinth(irr::core::vector3df(5,0,(j-1)*5+5), irr::core::vector3df(0,0,0), i, &m_plinth[3*(j-1)+2]);
        }

        for(int j = 1; j != 4; ++j)
        {
            m_vue.setPlinth(irr::core::vector3df(-5,-(j)*5+2,+2), irr::core::vector3df(-90,0,0), i, &m_plinth[3*(j-1)+9]);
            m_vue.setPlinth(irr::core::vector3df(0,-(j)*5+2,+2), irr::core::vector3df(-90,0,0), i, &m_plinth[3*(j-1)+10]);
            m_vue.setPlinth(irr::core::vector3df(5,-(j)*5+2,+2), irr::core::vector3df(-90,0,0), i, &m_plinth[3*(j-1)+11]);
        }

        for(int j = 1; j != 4; ++j)
        {
            m_vue.setPlinth(irr::core::vector3df(-5,-(j)*5+2,3+5*3), irr::core::vector3df(90,0,0), i, &m_plinth[3*(j-1)+18]);
            m_vue.setPlinth(irr::core::vector3df(0,-(j)*5+2,3+5*3), irr::core::vector3df(90,0,0), i, &m_plinth[3*(j-1)+19]);
            m_vue.setPlinth(irr::core::vector3df(5,-(j)*5+2,3+5*3), irr::core::vector3df(90,0,0), i, &m_plinth[3*(j-1)+20]);
        }

        for(int j = 1; j != 4; ++j)
        {
            m_vue.setPlinth(irr::core::vector3df(+8,-3,(j-1)*5+5), irr::core::vector3df(0,0,-90), i, &m_plinth[3*(j-1)+27]);
            m_vue.setPlinth(irr::core::vector3df(+8,-8,(j-1)*5+5), irr::core::vector3df(0,0,-90), i, &m_plinth[3*(j-1)+28]);
            m_vue.setPlinth(irr::core::vector3df(+8,-13,(j-1)*5+5), irr::core::vector3df(0,0,-90), i, &m_plinth[3*(j-1)+29]);
        }

        for(int j = 1; j != 4; ++j)
        {
            m_vue.setPlinth(irr::core::vector3df(-8,-3,(j-1)*5+5), irr::core::vector3df(0,0,+90), i, &m_plinth[3*(j-1)+36]);
            m_vue.setPlinth(irr::core::vector3df(-8,-8,(j-1)*5+5), irr::core::vector3df(0,0,+90), i, &m_plinth[3*(j-1)+37]);
            m_vue.setPlinth(irr::core::vector3df(-8,-13,(j-1)*5+5), irr::core::vector3df(0,0,+90), i, &m_plinth[3*(j-1)+38]);
        }

        for(int j = 1; j != 4; ++j)
        {
            m_vue.setPlinth(irr::core::vector3df(-5,-16,(j-1)*5+5), irr::core::vector3df(180,180,0), i, &m_plinth[3*(j-1)+45]);
            m_vue.setPlinth(irr::core::vector3df(0,-16,(j-1)*5+5), irr::core::vector3df(180,180,0), i, &m_plinth[3*(j-1)+46]);
            m_vue.setPlinth(irr::core::vector3df(5,-16,(j-1)*5+5), irr::core::vector3df(180,180,0), i, &m_plinth[3*(j-1)+47]);
        }
        //m_vue.setSkyDome("/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/skydome.jpg", 16, 16, 0.9, 2., 1000);
        /* m_vue.setSkyCube("/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/irrlicht2_up.jpg",
                         "/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/irrlicht2_dn.jpg",
                         "/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/irrlicht2_lf.jpg",
                         "/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/irrlicht2_rt.jpg",
                         "/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/irrlicht2_ft.jpg",
                         "/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/irrlicht2_bk.jpg");
        std::string img[6] = {"/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/irrlicht2_up.jpg",
                           "/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/irrlicht2_dn.jpg",
                           "/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/irrlicht2_lf.jpg",
                           "/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/irrlicht2_rt.jpg",
                           "/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/irrlicht2_ft.jpg",
                           "/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/irrlicht2_bk.jpg"};
        m_vue.setCube(img, irr::core::vector3df(1000,1000,1000)); */

           m_vue.setNbPlayer(1);
           m_vue.addPlayer( 0, new PlayerVue( m_vue.addCamera() ) );
           m_vue.setPlayer(0);
    }

    ServerGo::~ServerGo(void)
    {
        delete [] m_plinth;
    }


    void ServerGo::putPawn(Plinth * plinth) //TODO add Pawn
    {
        Pawn * p = new Pawn();
        if( plinth->setPawn(p) )
        {
            m_vue.putPawn(p , plinth);
        }

        else
        {
            Vue::Groupe g;
            g.push_back(plinth->getPawn() );
            m_vue.deleteGroupe(&g);
            delete p;
        }
    }
}
