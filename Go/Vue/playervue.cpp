#include "playervue.h"

namespace Go
{
    PlayerVue::PlayerVue(irr::scene::ICameraSceneNode *camera, Player *player)
        : m_camera(camera),
          m_player(player)
    {
    }
}
