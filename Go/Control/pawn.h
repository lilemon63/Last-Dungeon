#ifndef PAWN_H
#define PAWN_H

#include<iostream>
#include<irrlicht/irrlicht.h>
#include"../Vue/vuepawn.h"


namespace Go
{
    class Plinth;
    class Player;
    class GroupPawn;

    /** @brief Represent a Pawn (pion/pierre in french).<br/>
      All Pawn must herit of the class Pawn.<br/>
      This class represent a standart pawn with no specific design.<br/>
      This class is a test class it's isn't finish yet.
        */
    class Pawn
    {
    public:
        /** @brief Construct a pawn.<br/>
            TODO : put an typed enum for the pawn's type */
        Pawn(Player * player);

        /** @brief Put a pawn on a plinth (socle in french).<br/>
        /!\ Only the Go::Vue should call this method
        @param irr::scene::ISceneManager * : scene manager used for this game
        @param Plinth * : plinth where the pawn is put */
        void set(irr::scene::ISceneManager * , Plinth *);

        /** @brief Remove the pawn.<br/>
            /!\ Only the Go::Vue should call this method.<br/>
            /!\ After the call of this method, the objet is destroyed, you can not used it after.*/
        void remove(void){ delete this; }

        /** @brief delete the pawn.<br/>
            /!\ If the pawn is already put on a plinth, you mustn't destroy the pawn. */
        virtual ~Pawn();

        /** @brief Get the node of the pawn. A node is an 3D element which have a 3D position, orientation and
            have the graphism (mesh) of one graphic element.<br/>
            Nodes are in a scene manager node's tree.
            @return irr::scene::ISceneNode * : pawn's node */
        irr::scene::ISceneNode * getNode(void){ return m_vue->getNode(); }

        Player * getPlayer(void){ return m_player; }

        void setGroup(GroupPawn * g){ m_group = g; }

        unsigned int getIdGroup(void);

        unsigned int getPlinthId(void);

        unsigned int getFreedom(void);

        GroupPawn * getGroup(void){ return m_group;}
    private :

        /** @brief VuePawn define the pawn's graphisme. */
        VuePawn * m_vue;

        /** @brief Plinth where the pawn is on. If m_plinth is NULL, the pawn isn't in a plinth yet. */
        Plinth * m_plinth;

        Player * m_player;

        GroupPawn * m_group;
    };
}

#endif // PAWN_H
