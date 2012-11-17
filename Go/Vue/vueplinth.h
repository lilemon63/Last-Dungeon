#ifndef VUEPLINTH_H
#define VUEPLINTH_H

#include <irrlicht/irrlicht.h>

namespace Go
{

    /** @brief Plinth's graphism */
    class VuePlinth
    {
    public:
        /** @brief create a plinth's graphism.<br/>
          Only Go::Plinth should call this constructor.
          @param const irr::core::vector3df & position : plinth's position relative to his parent
          @param const irr::core::vector3df & angle : plinth's angle relative to his parent
          @param irr::scene::ISceneNode * parent : parent of the plinth, it must be an board's or a Plinth's node.
          @param irr::scene::ISceneManager * sceneManager : Go's scene manager. */
        VuePlinth(const irr::core::vector3df & position,
                  const irr::core::vector3df & angle,
                  irr::scene::ISceneNode * parent,
                  irr::scene::ISceneManager * sceneManager);

        virtual ~VuePlinth(void){
        }

        /** @brief Get the node of the plinth. A node is an 3D element which have a 3D position, orientation and
            have the graphism (mesh) of one graphic element.<br/>
            Nodes are in a scene manager node's tree.
            @return irr::scene::ISceneNode * : plinth's node */
        irr::scene::ISceneNode * getNode(void){ return m_node; }
    private :

        /** @brief node of the plinth. A node is an 3D element which have a 3D position, orientation and
            have the graphism (mesh) of one graphic element.<br/>
            Nodes are in a scene manager node's tree. */
        irr::scene::IMeshSceneNode* m_node;
    };
}

#endif // VUEPLINTH_H
