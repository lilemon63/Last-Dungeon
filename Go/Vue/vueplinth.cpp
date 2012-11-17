#include "vueplinth.h"


namespace Go
{

    VuePlinth::VuePlinth(const irr::core::vector3df & position,
              const irr::core::vector3df & angle,
              irr::scene::ISceneNode * parent,
              irr::scene::ISceneManager * sceneManager)
    {
        //m_node = sceneManager->addCubeSceneNode(3, parent, -1, position, angle);
        //m_node->setMesh(sceneManager->getMesh("/home/neckara/Documents/Irrlicht/irrlicht-1.7.3/media/skydome.jpg")); //cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
        // m_node = sceneManager->addMeshSceneNode(sceneManager->getMesh("Socle_non_anime.3ds") , parent, -1, position, angle);
       m_node = sceneManager->addMeshSceneNode(sceneManager->getMesh("/home/neckara/Bureau/Socle_dabou_optimisation.3ds") , parent, -1, position, angle);
        // anode->setAnimationSpeed(15); for animated graphism
    }
}
