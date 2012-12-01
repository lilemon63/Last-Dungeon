#include <cstdlib>
#include <fstream>

#include "board.h"
#include "map.h"
#include "plinth.h"
#include "pawn.h"

namespace Go
{
    Board::Board()
        : state(NULL)
    {
    }

    void Board::create(const std::string & vue, const std::string & script, Map * map, int id)
    {
        m_map = map;
        m_id = id;

        std::ifstream config(vue.c_str(), std::ios_base::binary | std::ios_base::in);
        if( ! config)
        {
            exit(5); //error loading config
        }
        int nbPlinth;
        config >> nbPlinth;
        m_listPlinth.reserve(nbPlinth);
        float x,y,z,a,b,c;
        for(int i = 0; i != nbPlinth; ++i)
        {
            Plinth * p = new Plinth(this, i);
            config >> x >> y >> z >> a >> b >> c;
            m_map->setPlinth(x,y,z,a,b,c,id, p);
            m_listPlinth.push_back(p);
        }
        m_neighbourRelation.resize(nbPlinth);
        unsigned int plinthA, plinthB;

        while(config >> plinthA)
        {
            char c;
            config >> c;
            config >> plinthB;
            addRelation( plinthA, plinthB);
        }

        //TODO

        config.close();

        //charger vue
        state = lua_open();

        if( lua_dofile(state, script.c_str() ) != 0)
        {
            exit(4); //error loading script
        }
    }

    Board::~Board(void)
    {
        if(state)
            lua_close(state);

    }

    const char Board::className[] = "Board";

    #define method(class, name) {#name, &class::name}


    Lunar<Board>::RegType Board::methods[] = {
      method(Board, onCreate),
      {0,0}
    };

    int Board::getTeam(unsigned int numberPlinth)
    {
        Pawn * ptrPawn = m_listPlinth[numberPlinth]->getPawn();
        if(ptrPawn)
            return ptrPawn->getPlayer()->getIdTeam();
        else
            return 0;
    }

    int Board::getGroup(unsigned int numberPlinth)
    {
        Pawn * ptrPawn = m_listPlinth[numberPlinth]->getPawn();
        if(ptrPawn)
            return ptrPawn->getIdGroup();
        else
            return -1;
    }

    GroupPawn *  Board::getPtrGroup(unsigned int numberPlinth)
    {

        Pawn * ptrPawn = m_listPlinth[numberPlinth]->getPawn();
        if(ptrPawn)
            return ptrPawn->getGroup();
        else
            return NULL;

    }

    unsigned int Board::getFreedomGroup(unsigned int numberPlinth )
    {
        Pawn * ptrPawn = m_listPlinth[numberPlinth]->getPawn();
        if(ptrPawn)
            return ptrPawn->getFreedom();
        else
        {
            std::cout << "no pawn" << std::endl;
            return 0;
        }
    }

}
