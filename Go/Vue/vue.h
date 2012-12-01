#ifndef VUE_H
#define VUE_H

#include<string>
#include<algorithm>
#include<vector>
#include<map>

#include "../../elementgui.h"

#include "../preferences.h"

namespace Go
{
    class ServerGo;
    class Plinth;
    class PlayerVue;
    class Pawn;

    /** @brief Go::Vue is a elementGUI which show the Go tu the player.<br/>
        Only a serverGo should build a Go::Vue.*/
    class Vue : public ElementGUI
    {
    public:
        /** @brief Create a Go::Vue
            @param const Preferences & pref : preference/options
            @param ServerGo * control : controler */
        Vue(const Preferences & pref ,ServerGo * control);

        /** @brief draw the Go::Vue into its area.<br/>
            You haven't to call this method, the gui do it for you. */
        void draw(void);

        /** @brief handle a received event.<br/>
          You haven't to call this method, the gui do it for you.
            @param const irr::SEvent &event : received event
            @return bool : return true if the Go::Vue was the event's target. */
        bool OnEvent(const irr::SEvent &event);

        /** @brief add a board (plateau in french). A board is a set of plinth.<br/>
          Only the serverGo should call this method.
            @param const irr::core::vector3df & position : position of the board in the map. */
        void setBoard(const irr::core::vector3df & position, const irr::core::vector3df & rotation);

        /** @brief add a plinth (socle in french). A plinth is where you will put pawn (pion/pierre in french).<br/>
            Only the serverGo should call this method.
            @param const irr::core::vector3df & position : plinth's position relative to the parent.
            @param const irr::core::vector3df & angle : plinth's angle relative to the parent.
            @param irr::scene::ISceneNode * parent : plinth's parent in the scene manager's tree it must be a board or another plinth.
            @param Plinth * p : plinth to add. */
        void setPlinth(const irr::core::vector3df & position,
                       const irr::core::vector3df & angle,
                       int parent,
                       Plinth * p);

        /** @brief Add the sky dome
            Do not use this method now. */
        void setSkyDome(const std::string & path, irr::u32 , irr::u32, irr::f32, irr::f32, irr::f32);

        /** @brief Add the sky cube
            Do not use this method new */
        void setSkyCube(const std::string & path_up, const std::string & path_dn, const std::string & path_lf,
                        const std::string & path_ft, const std::string & path_rt, const std::string & path_bk);


        /** @brief set the number of player in this cumputer
            @param unsigned int nb : number of player who'll play in this computer */
        void setNbPlayer(unsigned int nb){ m_listPlayer.reserve(nb); }

        /** @brief add a new player.<br/>
          Only serverGo should call this method.
            @brief unsigned int num : player's number, it must be in [[0, nb[[ where nb is the number of player in this cumputer.
            @param PlayerVue * p : player */
        void addPlayer(unsigned int num, PlayerVue * p){ m_listPlayer[num] = p; }


        /** @brief Change the current player and put his own camera and other specific option.
            @param unsigned int num : number of new current player */
        void setPlayer(unsigned int num);

        /** @brief create a new camera
            @return irr::scene::ICameraSceneNode * : the new created camera. */
        irr::scene::ICameraSceneNode * addCamera(void);

        /** @brief Put a pawn on a plinth.<br/>
          Only serverGo should call this method.
            @param Pawn * : pawn to put
            @param Plinth * : plinth where the pawn will be put. */
        void putPawn(Pawn *, Plinth *);

        /** @brief delete the vue.<br/>
            /!\ You shouldn't call it directly, you should call remove() instead. */
        ~Vue(void);
    private :

        /** @brief controlor of this vue */
        ServerGo * m_control;

        /** @brief Graphic Driver */
        irr::video::IVideoDriver* driver;

        /** @brief sceneManager */
        irr::scene::ISceneManager *sceneManager;

        /** @brief current camera */
        irr::scene::ICameraSceneNode* camera;

        PlayerVue * currentPlayer;

        typedef std::vector<PlayerVue *> ListPlayer;
        /** @brief List of local player in this cumputer */
        ListPlayer m_listPlayer;

        /** @brief List of all keybord shortcut */
        const ListShortCut m_shortcut;

        /** @brief change the relative position of the camera */
        void changeCameraPos(irr::f32 x, irr::f32 y, irr::f32 z );

        /** @brief change the relative angle of the camera */
        void changeCameraAngle(irr::f32 x, irr::f32 y, irr::f32 z );

        typedef std::map<irr::scene::ISceneNode *, Plinth *> ListPlinth;
        /** @brief list of plinth */
        ListPlinth m_listPlinth;

        typedef std::vector<irr::scene::ISceneNode *> ListBoard;
        ListBoard lBoard;
    };
}

#endif // VUE_H
