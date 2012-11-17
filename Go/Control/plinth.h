#ifndef PLINTH_H
#define PLINTH_H

#include<irrlicht/irrlicht.h>
#include<iostream>
#include"../Vue/vueplinth.h"

namespace Go
{
    class Pawn;

    /** @brief A plinth (socle in french) is an element where players can put pawn (pion/pierre in french).<br/>
        A board is composed of Plinth.
        All plinth must herit by this class. Each type of plinth can have special effect.<br/>
        /!\ It's a test class, it's isn't finish yet, Plinth should know their "voisins" */
    class Plinth
    {
    public:
        /** @brief Type of plinth.
            @enum Test : test plinth */
        enum Type{Test};

        /** @brief Create a plinth
          @param const Type type = Test : plinth's type by default a plinth is a plinth test. */
        Plinth(const Type type = Test) : m_type(type), m_vue(NULL), m_pawn(NULL){}

        /** @brief Set a plinth on a board.<br/>
            /!\ Only Go::Vue should call this method
            @param const irr::core::vector3df & position : relative position with the parent
            @param const irr::core::vector3df & angle : relative angle with the parent.<br/>
            Angle is a rotation with the axes in degree. It's "special", (180,180,0) is a retourned object.<br/>
            (90,0,0) is a rotation for 90° with X axes. : |  -> . -> |  -> .<br/>
            (0,90,0) is a rotation for 90° with Y axes :  -- -> . -> -- -> .<br/>
            (0,0,45) is a rotation for 45° with  axes :  |  -> / -> -- -> \ -> |
            @param irr::scene::ISceneNode * parent : parent in the node tree of the plinth.<br/>
            The parent must be a board or an another plinth.<br/>
            /!\ We should create to method one for plinth and one for board and save the
            Board where the plinth is.
            @param irr::scene::ISceneManager * manager : scene manager used for this game */
        virtual irr::scene::ISceneNode * set(const irr::core::vector3df & position,
                                             const irr::core::vector3df & angle,
                                             irr::scene::ISceneNode * parent,
                                             irr::scene::ISceneManager * manager);

        /** @brief delete a plinth<br/>
            /!\ didn't delete the pawn which is on the plinth.<br/>
            /!\ You shouldn't destroy a plinth which is already on a board. */
        virtual ~Plinth(){ if(m_vue) delete m_vue;}

        /** @brief Get the graphism of the Plinth.
            @return VuePlinth * : Plinth's graphism */
        VuePlinth * getVue(void){ return m_vue; }

        /** @brief Put a pawn on the plinth.<br/>
            If pawn is NULL unput the pawn but didn't remove the pawn. Only a pawn's destructor should do this.<br/>
            Else if there is already a put pawn, return false other put the pawn and return true.
            @param Pawn * pawn : pawn to put.
            @return bool : return true if the action have been handle. */
        bool setPawn(Pawn * pawn);


        /** @brief Get the pawn which is on the plinth.
            @return Pawn * : pawn which is put on the plinth else NULL */
        Pawn * getPawn(void){ return m_pawn; }
    protected :
        /** @brief type of plinth */
        const Type m_type;

        /** @brief pinth's graphism */
        VuePlinth * m_vue;

        /** @brief Pawn which is on this plinth */
        Pawn * m_pawn;
    };
}
#endif // PLINTH_H
