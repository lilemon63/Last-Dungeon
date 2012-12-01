#include "grouppawn.h"
#include "player.h"
#include "groupplayer.h"
#include "pawn.h"

namespace Go
{
    GroupPawn::GroupPawn(Pawn * p, unsigned int freedom)
        : m_listPawn(1, p),
          m_team(p->getPlayer()->getTeam() ),
          m_freedom(freedom)
    {
        p->setGroup(this);
    }

    unsigned int GroupPawn::getId(void)
    {
        fprintf(stderr, "ptr ? %x", *(m_listPawn.begin()));



        int i;

        return (*m_listPawn.begin() )->getPlinthId() ;
    }

    void GroupPawn::remove(void)
    {
        {
            ListPawn::iterator it =  m_listPawn.begin();
            ListPawn::iterator end = m_listPawn.end();
            for( ; it != end; ++it)
                (*it)->remove();
        }
        {
            Frontier::iterator it = m_frontier.begin();
            Frontier::iterator end = m_frontier.end();
            for( ; it != end; ++it)
            {
                it->first->m_freedom += it->second;
                it->first->m_frontier.erase(this);
            }
        }

        delete this;
    }


    void GroupPawn::addFrontier(GroupPawn * group, unsigned int nb)
    {
        m_frontier[group] += nb;
        group->m_frontier[this] += nb;
        group->m_freedom -= nb;
    }


    void GroupPawn::fusion(GroupPawn * gp, unsigned int nb)
    {
        {
            ListPawn::iterator it = gp->m_listPawn.begin();
            ListPawn::iterator end = gp->m_listPawn.end();
            for( ; it != end; ++it)
                (*it)->setGroup(this);
            m_listPawn.insert( m_listPawn.end(), gp->m_listPawn.begin(), gp->m_listPawn.end() );
            m_freedom += gp->m_freedom;
            m_freedom -= nb;
        }
        {
            Frontier::iterator it = gp->m_frontier.begin();
            Frontier::iterator end = gp->m_frontier.end();
            for( ; it != end ; ++it)
                m_frontier[it->first] += it->second;
        }
        delete gp;
    }

}
