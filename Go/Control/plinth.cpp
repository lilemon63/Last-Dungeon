#include "board.h"

#include "plinth.h"


namespace Go
{
    irr::scene::ISceneNode * Plinth::set(const irr::core::vector3df & position,
                                                 const irr::core::vector3df & angle,
                                                 irr::scene::ISceneNode * parent,
                                                 irr::scene::ISceneManager * manager)
    {
        m_vue = new VuePlinth(position, angle, parent, manager);
        return m_vue->getNode();
    }


    bool Plinth::setPawn(Pawn * pawn)
    {
            if(pawn == NULL)
            {
                m_pawn = NULL; return true;
            }
            if(m_pawn){
                return false;
            }
            m_pawn = pawn;
            return true;
    }

    const std::set<unsigned int> & Plinth::getNeighbourg(void)
    {
        return m_board->getNeighbourg(m_id);
    }

}
