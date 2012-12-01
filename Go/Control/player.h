#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>

namespace Go
{
    class GroupPlayer;
    class Player
    {
    public:
        enum Color{Red, Blue};
        Player(unsigned int id) : m_id(id), m_team(NULL){}
        void setTeam(GroupPlayer * m_team);
        GroupPlayer * getTeam(void){ return m_team; }
        unsigned int getIdTeam(void);
        void setColor(Color c){ m_color = c; }
        Color getColor(void){ return m_color;}
        unsigned int getId(void){ return m_id; }
    private :
        unsigned int m_id;
        GroupPlayer * m_team;
        Color m_color;
    };
}

#endif // PLAYER_H
