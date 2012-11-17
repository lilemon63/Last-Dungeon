#include<iostream>

#include "pawn.h"
#include "plinth.h"

namespace Go
{
    Pawn::Pawn()
        : m_vue(NULL),
          m_plinth(NULL)
    {
    }

    void Pawn::set(irr::scene::ISceneManager * scene , Plinth * pl)
    {
        m_vue = new VuePawn(scene, pl);
        m_plinth = pl;
    }

    Pawn::~Pawn()
    {
        if(m_vue){ delete m_vue; }
        if(m_plinth)
            m_plinth->setPawn(NULL);
    }
}
