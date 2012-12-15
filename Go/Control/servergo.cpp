#include "servergo.h"
#include "plinth.h"
#include "../Vue/playervue.h"
#include "pawn.h"
#include "groupplayer.h"
#include "player.h"
#include "grouppawn.h"
#include "map.h"

namespace Go
{
    ServerGo::ServerGo(const std::string & file, Preferences & pref)
        : m_vue(pref, this),
          m_map(file, this)
    {
        GroupPlayer * g = new GroupPlayer(1);
        Player * p = new Player(0);
        p->setColor(Player::Blue);
        p->setTeam(g);
        m_listGroup.push_back(g);

        GroupPlayer * g2 = new GroupPlayer(2);
        Player * p2 = new Player(1);
        p2->setColor(Player::Red);
        p2->setTeam(g2);
        m_listGroup.push_back(g2);

        pref.addServerGo(this);
/*
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

           m_vue.setNbPlayer(2);
           irr::scene::ICameraSceneNode * c = m_vue.addCamera();
           m_vue.addPlayer( 0, new PlayerVue( c, p ) );
           m_vue.addPlayer( 1, new PlayerVue( c , p2) );
           m_vue.setPlayer(0);
    }

    ServerGo::~ServerGo(void)
    {
    }

    void ServerGo::setBoard(float x, float y, float z, float a, float b, float c)
    {
        m_vue.setBoard(irr::core::vector3df(x,y,z), irr::core::vector3df(a, b,c) );
    }


    bool ServerGo::putPawn(Plinth * plinth, Pawn * p) //TODO add Pawn
    {
        return m_map.putPawn(plinth, p);
    }

    void ServerGo::setPlinth(float x, float y, float z, float a, float b, float c, int board, Plinth * p)
    {
        m_vue.setPlinth(irr::core::vector3df(x,y,z), irr::core::vector3df(a,b,c), board, p);
    }

    void ServerGo::putPawnOnPlinth(Plinth * plinth, Pawn * p)
    {
        m_vue.putPawn(p, plinth);
    }

    void ServerGo::pass(void)
    {
        m_map.pass();
    }

    bool ServerGo::handle(const std::string & string, IRC::IRCClient * chat)
    {
        std::stringstream is(string);
        std::string command;
        is >> command;
        if(command == "pass")
        {
           if( m_map.pass() )
           {
                chat->printMessage(L"Choisissez les groupes à ignorer puis comptez vos points à moins que vous ne préfériez continuer");
           }
           std::cerr << "pass" << std::endl;
        }
        else if(command == "surrender" || command == "abandonner")
        {
            chat->printMessage(L"Vous avez perdu !");
            std::cerr << "suite de surrender non-implémenté" << std::endl;

        }
        else if(command == "getpoint" || command == "getPoint" || command == "getscore" || command == "getScore")
        {
            IRC::IRCClient::LineList l;

            ListGroupPlayer::iterator it = m_listGroup.begin();
            ListGroupPlayer::const_iterator const end = m_listGroup.end();

            l.push_back("-----Scores-------");

            for( ; it != end; ++it)
            {
                std::stringstream os;
                os << "Groupe " << (*it)->getId() << ":     " << (*it)->getScore();
                l.push_back( os.str() );
            }

            l.push_back("-----Fin Scores---");

            chat->printMessage(l);
        }
        else
            return false;

        //TODO tourner plateau

        return true;
    }

    void ServerGo::addPoint(unsigned int team, unsigned int point)
    {
        m_listGroup[team-1]->addPoint(point);
    }

    void ServerGo::finPartie(void)
    {
        std::cerr << "fin de la partie" << std::endl;
    }

}
