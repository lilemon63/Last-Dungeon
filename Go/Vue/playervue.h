#ifndef PLAYERVUE_H
#define PLAYERVUE_H

#include<irrlicht/irrlicht.h>

namespace Go
{
    /** @brief PlayerVue regroup the options (for the moment only a camera) of each player who are in this cumputer. */
    class PlayerVue
    {
    public:
        /** @brief create a new PlayerVue.
           @param irr::scene::ICameraSceneNode * camera : camera for the player.<br/>
           each player should have his own camera but it's isn't an obligation. */
        PlayerVue(irr::scene::ICameraSceneNode * camera);

        /** @brief get the player's camera
          @return irr::scene::ICameraSceneNode * : player's camera */
        irr::scene::ICameraSceneNode * getCamera(void){ return m_camera; }
    private :
        /** @brief player's camera */
        irr::scene::ICameraSceneNode* m_camera;
    };
}

#endif // PLAYERVUE_H
