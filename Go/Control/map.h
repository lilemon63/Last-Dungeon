#ifndef MAP_H
#define MAP_H

#include<iostream>
#include<string>
#include "lunar.h"
#include "board.h"

namespace Go
{
    class Board;
    class ServerGo;
    class Plinth;
    class Pawn;

    class Map
    {
    public:
        Map(const std::string & file, ServerGo * server);
        ~Map(void);

        void setPlinth(float x, float y, float z, float a, float b, float c, int board, Plinth * p);

        bool putPawn(Plinth * plinth, Pawn * p);

    private :
        std::string name;
        std::string description;
        std::string img;

        ServerGo * m_server;

        unsigned char nbBoard;
        Board * tabBoard;


        virtual int onCreate(lua_State*);
        int getNumberBoard(lua_State* state)
        {
            lua_pushnumber(state, nbBoard);//nbBoard
            return 0;
        }

        int onCreateBoard(lua_State*)
        {
            if(lua_isnumber(state, 1) )
            {
                unsigned int i = lua_tonumber(state, 1);
                if(i < nbBoard)
                    tabBoard[i].onCreate();
            }
            return 0;
        }

        virtual int canPlayerPutPawn(lua_State *)
        {
            lua_pushboolean(state, false);
            return 1;
        }

        int setPlayer(lua_State *);

        int putPawn(lua_State *);

        int isPlinthEmpty(lua_State *);

        int getPlayer(lua_State *);

        int getNeightbourg(lua_State *);


        int getGroupeTeam(lua_State * );

        int getGroupe(lua_State *);

        int getGroupFreedom(lua_State *);

        int getCurrentPlayerTeam(lua_State *);

        virtual int onPutPawn(lua_State *);

        int addFrontier(lua_State *);

        int destroyGroup(lua_State *);

        int fusionGroup(lua_State *);

        lua_State * state;
        Map(lua_State *state);
        friend class Lunar<Map>;
        static const char className[];
        static Lunar<Map>::RegType methods[];

        Plinth * m_currentPlinth;
        Pawn * m_currentPawn;
    };
}

#endif // MAP_H
