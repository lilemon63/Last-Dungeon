#ifndef VUEPAWN_H
#define VUEPAWN_H

#include<iostream>
#include<irrlicht/irrlicht.h>

#include "../Control/player.h"

namespace Go
{
    class Plinth;

    /** @brief pawn's graphism */
    class VuePawn
    {
    public:
        /** @brief create a VuePawn, only a pawn should call this constructor.
          @param irr::scene::ISceneManager * manager : Go's scene manager
          @param Plinth * p : plinth where the pawn'll put on.*/
        VuePawn(irr::scene::ISceneManager * manager, Plinth * p, Player::Color c);

        virtual ~VuePawn(void);


        /** @brief Get the node of the pawn. A node is an 3D element which have a 3D position, orientation and
            have the graphism (mesh) of one graphic element.<br/>
            Nodes are in a scene manager node's tree.
            @return irr::scene::ISceneNode * : pawn's node */
        irr::scene::ISceneNode * getNode(void){ return m_node; }
    private :

        /** @brief node of the pawn. A node is an 3D element which have a 3D position, orientation and
            have the graphism (mesh) of one graphic element.<br/>
            Nodes are in a scene manager node's tree. */
        irr::scene::IAnimatedMeshSceneNode * m_node;
    };
}

#endif // VUEPAWN_H
