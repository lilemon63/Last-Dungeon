#include<iostream>

#include "pawn.h"
#include "plinth.h"
#include "player.h"
#include "grouppawn.h"

namespace Go
{
    Pawn::Pawn(Player *player)
        : m_vue(NULL),
          m_plinth(NULL),
          m_player(player)
    {
    }

    void Pawn::set(irr::scene::ISceneManager * scene , Plinth * pl)
    {
        m_vue = new VuePawn(scene, pl, m_player->getColor() );
        m_plinth = pl;
    }

    Pawn::~Pawn()
    {
        if(m_vue){ delete m_vue; }
        if(m_plinth)
            m_plinth->setPawn(NULL);
    }

    unsigned int Pawn::getIdGroup(void)
    {
        return m_group->getId();
    }

    unsigned int Pawn::getPlinthId(void)
    {
        return m_plinth->getId();
    }

    unsigned int Pawn::getFreedom(void)
    {
        return m_group->getFreedom();
    }
}
