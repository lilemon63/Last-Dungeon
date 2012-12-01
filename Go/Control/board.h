#ifndef BOARD_H
#define BOARD_H

#include<string>
#include<iostream>
#include<vector>
#include<set>
#include "lunar.h"

namespace Go
{
    class Map;
    class Plinth;
    class GroupPawn;
    class Board
    {
    public:
        Board(void);
        ~Board(void);

        void create(const std::string & vue, const std::string & script, Map *map, int id);

        void onCreate(void){ onCreate(state); std::cerr << "call" << std::endl; }

        void addPlinth(Plinth * p)
        {
            m_listPlinth.push_back(p);
        }

        void addRelation(unsigned int idPlinthA, unsigned int idPlinthB)
        {
            m_neighbourRelation[idPlinthA].insert(idPlinthB);
        }

        const std::set<unsigned int> & getNeighbourg(unsigned int id){
            return m_neighbourRelation[id]; }

        int getTeam(unsigned int numberPlinth);

        int getGroup(unsigned int numberPlinth);
        GroupPawn * getPtrGroup(unsigned int numberPlinth);

        unsigned int getFreedomGroup(unsigned int numberPlinth );

    private:

        Map * m_map;
        int m_id;


        typedef std::vector<Plinth *> ListPlinth;
        ListPlinth m_listPlinth;
        typedef std::vector<std::set<unsigned int> > RelationPlinth;
        RelationPlinth m_neighbourRelation;

        lua_State * state;
        int onCreate(lua_State *){ return 0; }
        Board(lua_State *){}
        friend class Lunar<Board>;
        static const char className[];
        static Lunar<Board>::RegType methods[];
    };
}

#endif // BOARD_H
