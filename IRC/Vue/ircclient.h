#ifndef IRCCLIENT_H
#define IRCCLIENT_H

#include<list>
#include<irrlicht/irrlicht.h>
#include<string>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "elementgui.h"
#include "../Control/irccontrolor.h"
#include "../../Network/server.h"

namespace 	IRC
{
    class IRCExternHandle;

    class IRCClient : public ElementGUI
    {
    public:
        IRCClient(irr::gui::IGUIElement *parent, const irr::core::rect<irr::s32> &area,
                  irr::gui::IGUIEnvironment *env, Network::Server & server,
                  boost::mutex & paralleleOperation);
        void draw(void);
        bool OnEvent(const irr::SEvent &event);

        typedef std::list<std::string> LineList;

        static std::string narrow(const std::wstring& ws);
        static std::wstring widen(const std::string& s);

        void setHandle(IRCExternHandle *);

        void printMessage(std::wstring );

        void printMessage(LineList & list);

    private :

        void print(const std::string & texte);
        void print(LineList & list);

        irr::gui::IGUIComboBox * listChannel;
        irr::gui::IGUIEditBox * text;
        irr::gui::IGUIListBox * chat;

        /** @brief because Irrlicht focus sucks */
        std::list<irr::gui::IGUIElement *> giveBackFocus;

        irr::gui::IGUIFont *font;

        void handleText(void);

        /** @brief Because Irrlicht Sucks...
          return true if parent have the child or is the child
          if parent is NULL, use the rootElement as parent */
        bool irrlichtSucks( irr::gui::IGUIElement * parent, irr::gui::IGUIElement * child);

        IRCControlor m_control;

        boost::mutex & paralleleOperation;

        friend class IRCControlor;

    };
}

#endif // IRCCLIENT_H
