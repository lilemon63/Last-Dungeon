#ifndef PREFERENCES_H
#define PREFERENCES_H

#include<irrlicht/irrlicht.h>
#include<map>
#include<iostream>

namespace Go
{
    /** @brief identifier for all action.<br/>
      TODO: add deplacement of "pointer to socle" and board.
        */
    enum IdAction{/// go to the top (Y + speed)
                  CAMERA_UP,
                  /// go to the down (Y - speed)
                  CAMERA_DOWN,
                  /// go to the left (X - speed)
                  CAMERA_LEFT,
                  /// go to the right (X + speed)
                  CAMERA_RIGHT,
                  /// go to the front (Z + speed)
                  CAMERA_FRONT,
                  /// go to the back (Z - speed)
                  CAMERA_BACK,
                  /// look to the top
                  CAMERA_LOOK_UP,
                  /// look to the down
                  CAMERA_LOOK_DOWN,
                  /// look to the left
                  CAMERA_LOOK_LEFT,
                  /// look to the right
                  CAMERA_LOOK_RIGHT,
                  /// no sence
                  CAMERA_LOOK_FRONT,
                  /// no sence
                  CAMERA_LOOK_BACK,
                  /// reinit the camera's position and angle
                  CAMERA_INIT_POSITION
                 };

    /** @brief List of all the shortcut for the Go.<br/>
      irr::EKEY_CODE : keyboard code<br/>
      IdAction : action to do when the keyboard code match */
    typedef std::map<irr::EKEY_CODE, IdAction> ListShortCut;

    class ServerGo;

    /** @brief Preferences/Option for the Go */
    class Preferences
    {
    public:
        /** Create preferences for the Go.<br/>
          /!\ It's not the current preferences/options for the go !<br/>
          The synchronisation beetwen Preferences and Go isn't automatic.
        @param irr::gui::IGUIEnvironment * env : the gui where the go will be showed.
        @param irr::scene::ISceneManager * manager : current scene manager which is used
        @param const irr::core::rect<irr::s32> & area : coordinate of the Go::Vue's elementGUI where the go will be showed.<br/>
        Firts the coordonate of the corner at the top left of the elementGUI relative to his parent.<br/>
        And then the widht and the length of the elementGUI.
        @param irr::gui::IGUIElement * parent : parent of the Go::Vue in the gui's tree node.
        @param bool createNewSceneManager = true : if true create a specific scene manager for Go
        if false, use the sceneManager for the Go.
        @see Go::ElementGUI
        */
        Preferences(irr::gui::IGUIEnvironment * env, irr::scene::ISceneManager * manager,
                    const irr::core::rect<irr::s32> & area, irr::gui::IGUIElement * parent,
                    bool createNewSceneManager = true);

        virtual ~Preferences(){}

        /** @brief Get the coordinate of the Go::Vue.<br/>
        Firts the coordonate of the corner at the top left of the elementGUI relative to his parent.<br/>
        And then the widht and the length of the elementGUI.
        @return const irr::core::rect<irr::s32> & : coordinate of the Go::Vue
        @see Go::ElementGUI */
        const irr::core::rect<irr::s32> & getArea(void) const { return m_area; }

        /** @brief Get the Go::Vue's parent in the gui.
            @return irr::gui::IGUIElement * : parent of the Go::Vue or NULL if it hasn't parent */
        irr::gui::IGUIElement * getParent(void) const { return m_parent; }

        /** @brief Get the gui
          @brief irr::gui::IGUIEnvironment * : get the gui where the go will be showed */
        irr::gui::IGUIEnvironment * getEnv(void) const { return m_env; }

        /** @brief Get the scene manager for the Go
            @return irr::scene::ISceneManager * : scene manager which will used for the go. */
        irr::scene::ISceneManager * getManager(void) const { return m_manager; }

        /** @brief Get the list of all go's keyboard shortcut
            @return const ListShortCut & : all go's keyboard shortcut */
        const ListShortCut & getShortcut( void ) const { return m_listShortcut; }


        /** @brief add a go's keyboard shortcut. If the action is already specified for this keyboard code, replace the action.
          @param const irr::EKEY_CODE & code : keyboard code
          @param IdAction action : action todo when the keyboard code match.
          */
        void setShortcut(const irr::EKEY_CODE & code, IdAction action){ m_listShortcut[code] = action;}

    private :

        /** @brief save the ServerGo which use the Go Preferences so when preferences are modified,
          they can be appliqued.<br/>
            Only the ServerGo can call this method */
        void addServerGo(ServerGo * s){ m_server = s; }

        /** @brief Only one serverGo can use this preferences.<br/>
            It's used to apply the changes to the Go */
        ServerGo * m_server;

        /** @brief coordinate of the Go::Vue's elementGUI where the go will be showed.<br/>
        Firts the coordonate of the corner at the top left of the elementGUI relative to his parent.<br/>
        And then the widht and the length of the elementGUI.
        @see Go::ElementGUI */
        irr::core::rect<irr::s32> m_area;

        /** @brief parent of the Go::Vue in the gui's tree node, NULL if no parents */
        irr::gui::IGUIElement * m_parent;

        /** @brief gui where the go will be showed */
        irr::gui::IGUIEnvironment * m_env;

        /** @brief scene Manager */
        irr::scene::ISceneManager * m_manager;

        /** @brief list of all the shorcut for the Go */
        ListShortCut m_listShortcut;

        friend class ServerGo;
    };
}

#endif // PREFERENCES_H
