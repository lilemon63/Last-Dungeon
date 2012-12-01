#include "player.h"
#include "groupplayer.h"

namespace Go
{
    void Player::setTeam(GroupPlayer * team)
    {
        m_team = team;
        team->setPlayer(this);
    }

    unsigned int Player::getIdTeam(void)
    {
        return m_team->getId();
    }
}
