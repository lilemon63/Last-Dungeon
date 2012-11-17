#include "vuepawn.h"
#include "../Control/plinth.h"

namespace Go
{
    VuePawn::VuePawn(irr::scene::ISceneManager * manager, Plinth * p)
    {
        m_node = manager->addAnimatedMeshSceneNode(  manager->getMesh("Pierre_non_anime.3ds"),
                                                     p->getVue()->getNode(),
                                                     -1,
                                                     irr::core::vector3df(0,3,0)  );
    }

    VuePawn::~VuePawn(void)
    {
        if(m_node)
            m_node->remove();
    }
}
