#include<iostream>
#include<stdio.h>
#include<fstream>
#include<algorithm>
#include<stdlib.h>
#include "map.h"
#include "servergo.h"
#include "plinth.h"
#include "pawn.h"
#include "grouppawn.h"

typedef float float32;

namespace Go
{

    Map::Map(const std::string & file, ServerGo * server)
        : name(file.begin(), std::find(file.begin(), file.end(), '.') ),
          m_server(server),
          state(lua_open())
    {

        std::ifstream config( file.c_str(), std::ios_base::binary );
        if( ! config )
        {
            exit(2); //error loading configuration
        }

        std::string fileScript;
        std::getline(config, description, '\r');
        std::cerr << description << std::endl;
        std::getline(config, img, '\r');
        std::getline(config, fileScript, '\r');

        //load data Team

        //load board
        unsigned char nbBoard;
        config >> nbBoard;
        tabBoard = new Board[nbBoard];
        std::string scriptBoard, vueBoard;
        for(int i = 0; i != nbBoard; ++i)
        {
            std::getline(config, vueBoard, '\r');
            std::getline(config, scriptBoard, '\r');
            float32 x,y,z, a,b,c;
            config >> x >> y >> z >> a >> b >> c;
            m_server->setBoard(x,y,z,a,b,c);
            tabBoard[i].create(vueBoard, scriptBoard, this, i);
        }


        config.close();
        lua_settop(state,0);
        lua_tablibopen(state);
        lua_iolibopen(state);
        lua_baselibopen(state);
        lua_strlibopen(state);
        lua_mathlibopen(state);
        lua_dblibopen(state);
        Lunar<Map>::Register(state);
        if( lua_dofile(state, fileScript.c_str() ) != 0)
        {
            exit(1); //error loading script
        }
        Lunar<Map>::push(state,this);
        Lunar<Map>::call(state,"onCreate",0,0);
    }

    int Map::onCreate(lua_State*)
    {
        return 0;
    }

    Map::~Map(void)
    {
        lua_close(state);
        delete [] tabBoard;
    }


    const char Map::className[] = "Map";

    #define method(class, name) {#name, &class::name}


    Lunar<Map>::RegType Map::methods[] = {
      method(Map, onCreate),
      method(Map, getNumberBoard),
      method(Map, onCreateBoard),
      method(Map, canPlayerPutPawn),
      method(Map, putPawn),
      method(Map, isPlinthEmpty),
      method(Map, setPlayer),
      method(Map, getPlayer),
      method(Map, getNeightbourg),
      method(Map, getGroupeTeam),
      method(Map, getGroupe),
      method(Map, getGroupFreedom),
      method(Map, getCurrentPlayerTeam),
      method(Map, onPutPawn),
      method(Map, addFrontier),
      method(Map, destroyGroup),
      method(Map, fusionGroup),
      method(Map, pass),
      method(Map, setPoint),
      method(Map, finPartie),
      {0,0}
    };

    Map::Map(lua_State  *)
    {
    }

    int Map::onPutPawn(lua_State *)
    {
        return 1;
    }

    void Map::setPlinth(float x, float y, float z, float a, float b, float c, int board, Plinth * p)
    {
        m_server->setPlinth(x,y,z,a,b,c,board, p);
    }

    int Map::putPawn(lua_State *)
    {
        fprintf(stderr, "Plinth : %u\n", m_currentPlinth->getId() );
        unsigned int freedom = lua_tonumber(state, 1);
        GroupPawn * g = new GroupPawn(m_currentPawn, freedom);
        m_currentPlinth->setPawn(m_currentPawn);
        m_server->putPawnOnPlinth(m_currentPlinth, m_currentPawn);
        return 1;
    }


    bool Map::putPawn(Plinth * pl, Pawn * pa)
    {
        m_currentPlinth = pl;
        m_currentPawn = pa;
        Lunar<Map>::push(state,this);
        Lunar<Map>::call(state,"canPlayerPutPawn",0,1);
        std::cerr << "err: " << lua_tostring(state,-1) << std::endl;
        fprintf(stderr, "fin script");
        return lua_toboolean(state, -1);
    }

    int Map::isPlinthEmpty(lua_State *)
    {
        lua_pushboolean(state, !(bool)m_currentPlinth->getPawn() );
        return 1;
    }

    int Map::setPlayer(lua_State *)
    {
        unsigned int numP = lua_tonumber(state, 1);
        m_server->setPlayer(numP);
        return 1;
    }

    int Map::getPlayer(lua_State *)
    {
        fprintf(stderr, "getPlayer");
        lua_pushnumber(state, m_currentPawn->getPlayer()->getId() );
        fprintf(stderr, "endPlayer");
        return 1;
    }

    int Map::getNeightbourg(lua_State *)
    {
        std::set<unsigned int>neigh = m_currentPlinth->getNeighbourg();
        lua_newtable(state);
        int index = lua_gettop(state);


        std::set<unsigned int>::const_iterator const end = neigh.end();
        std::set<unsigned int>::const_iterator it = neigh.begin();
        for(int i = 1 ; it != end; ++it, ++i)
        {
           lua_pushnumber(state, i);
           lua_pushnumber(state, *it);
           lua_settable(state, -3);
           // lua_rawseti(state, newTable, i);
        }
        return 1;
    }


    int Map::getGroupeTeam(lua_State * )
    {
        unsigned int numSocle = lua_tonumber(state, 1);
        unsigned int numberTeam = m_currentPlinth->getBoard()->getTeam(numSocle);
        lua_pushnumber(state, numberTeam);
        return 1;
    }


    int Map::getGroupe(lua_State *)
    {
        unsigned int numSocle = lua_tonumber(state, 1);
        int group = m_currentPlinth->getBoard()->getGroup(numSocle);
        lua_pushnumber(state, group);
        return 1;
    }

    int Map::getGroupFreedom(lua_State *)
    {
        unsigned int group = lua_tonumber(state, 1);
        unsigned int freedom = m_currentPlinth->getBoard()->getFreedomGroup(group);
        std::cerr << "liberte : " << freedom << std::endl;
        lua_pushnumber(state, freedom);
        return 1;
    }

    int Map::getCurrentPlayerTeam(lua_State *)
    {
        unsigned int team = m_currentPawn->getPlayer()->getIdTeam();
        lua_pushnumber(state, team);
        return 1;
    }

    int Map::addFrontier(lua_State *)
    {
        fprintf(stderr, "addFrontier");
        unsigned int group = lua_tonumber(state, 1);
        unsigned int nb = lua_tonumber(state, 2);
        GroupPawn * g = m_currentPlinth->getBoard()->getPtrGroup(group);
        fprintf(stderr, "get");
        m_currentPawn->getGroup()->addFrontier(g , nb);
        fprintf(stderr, "fin");
        return 1;
    }

    int Map::destroyGroup(lua_State *)
    {
        unsigned int group = lua_tonumber(state, 1);
        GroupPawn * p = m_currentPlinth->getBoard()->getPtrGroup(group);

        lua_pushnumber(state, m_currentPlinth->getBoard()->getPtrGroup(group)->remove() );
        return 1;
    }

    int Map::fusionGroup(lua_State *)
    {
        unsigned int group = lua_tonumber(state, 1);
        unsigned int nb = lua_tonumber(state, 2);

        GroupPawn *g = m_currentPlinth->getBoard()->getPtrGroup(group);

                fprintf(stderr, "%x", g);

        g->fusion(m_currentPawn->getGroup(), nb);
                        fprintf(stderr, "koi2");
        return 1;
    }

    bool Map::pass(void)
    {
        Lunar<Map>::push(state,this);
        Lunar<Map>::call(state,"pass",0,1);
        return lua_toboolean(state, -1);
    }

    int Map::setPoint(lua_State *)
    {
        unsigned int team = lua_tonumber(state, 1);
        unsigned int nbPoint = lua_tonumber(state, 2);
        m_server->addPoint(team, nbPoint);
        return 1;
    }

    int Map::pass(lua_State*)
    {
        return 1;
    }

    int Map::finPartie(lua_State *)
    {
        fprintf(stderr, "fin de la partieX\n");
        m_server->finPartie();
        return 1;
    }
}
