#ifndef GROUPPAWN_H
#define GROUPPAWN_H

#include <list>
#include <map>

namespace Go
{
    class Pawn;
    class GroupPlayer;
    class GroupPawn
    {
    public:
        GroupPawn(Pawn * p, unsigned int freedom);
        unsigned int getId(void);
        unsigned int getFreedom(void){ return m_freedom; }
        void addFrontier(GroupPawn * group, unsigned int nb);
        void remove(void);

        void fusion(GroupPawn *, unsigned int nb);
    private :
        typedef std::list<Pawn *> ListPawn;
        ListPawn m_listPawn;
        GroupPlayer * m_team;
        unsigned int m_freedom;
        typedef std::map<GroupPawn *, unsigned int> Frontier;
        Frontier m_frontier;
    };
}

#endif // GROUPPAWN_H
