#ifndef GROUPPLAYER_H
#define GROUPPLAYER_H

#include<vector>

namespace Go
{
    class Player;
    class GroupPlayer
    {
    public:
        GroupPlayer(unsigned int id);
        void setPlayer(Player * p){ m_team.push_back(p); }
        unsigned int getId(void){ return m_id; }
    private :
        typedef std::vector<Player *> ListPlayer;
        ListPlayer m_team;
        unsigned int m_id;
    };
}

#endif // GROUPPLAYER_H
