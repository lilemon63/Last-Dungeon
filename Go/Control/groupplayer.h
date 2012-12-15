#ifndef GROUPPLAYER_H
#define GROUPPLAYER_H

#include<vector>

namespace Go
{
    class Player;
    class GroupPlayer
    {
    public:
        GroupPlayer(unsigned int id, unsigned int score = 0);
        void setPlayer(Player * p){ m_team.push_back(p); }
        unsigned int getId(void){ return m_id; }

        unsigned int getScore(void){ return m_score; }
        void addPoint(unsigned int score){ m_score += score; }
    private :
        typedef std::vector<Player *> ListPlayer;
        ListPlayer m_team;
        unsigned int m_id;
        unsigned int m_score;
    };
}

#endif // GROUPPLAYER_H
