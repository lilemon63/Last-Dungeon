#include "vuepawn.h"
#include "../Control/plinth.h"

namespace Go
{
    VuePawn::VuePawn(irr::scene::ISceneManager * manager, Plinth * p, Player::Color c)
    {
        irr::scene::IAnimatedMesh * mesh;
        if(c == Player::Blue)
            mesh = manager->getMesh("/home/neckara/Bureau/Pierre_non_anime_bleu.3ds");
        else
            mesh = manager->getMesh("/home/neckara/Bureau/Pierre_non_anime_rouge.3ds");
        mesh->setHardwareMappingHint(irr::scene::EHM_STATIC);
        //m_node = manager->addAnimatedMeshSceneNode(  manager->getMesh("Pierre_non_anime.3ds"),
        m_node = manager->addAnimatedMeshSceneNode(  mesh,
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
