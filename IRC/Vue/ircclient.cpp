#include "ircclient.h"

#include <iostream>
#include <locale>
#include <vector>
#include <stdio.h>

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

namespace IRC
{


    std::string IRCClient::narrow(const std::wstring& ws)
    {
        std::string buffer(ws.begin(), ws.end() );
        return buffer;
    }
    std::wstring IRCClient::widen(const std::string& s)
    {
        std::string::const_iterator it = s.begin();
        std::string::const_iterator const end = s.end();

        std::wstring buffer;
        buffer.reserve(s.size() );
        for( ; it != end; ++it)
            buffer.push_back( *it > 0? *it: *it + 256 );
        return buffer;
    }




    IRCClient::IRCClient(irr::gui::IGUIElement * parent,
                         const irr::core::rect<irr::s32> & area,
                         irr::gui::IGUIEnvironment * env,
                         Network::Server & server,
                         boost::mutex &paralleleOperation) :
        ElementGUI(parent, area, env),
        listChannel(env->addComboBox(irr::core::rect<irr::s32>(0, area.getHeight() - 25,
                                                               150, area.getHeight() ), this ) ),
        text(env->addEditBox(L"", irr::core::rect<irr::s32>(150, area.getHeight() - 25,
                                                            area.getWidth(), area.getHeight() ), true, this ) ),
        chat(env->addListBox(irr::core::rect<irr::s32>(0, 0,
                                                       area.getWidth(), area.getHeight() - 25), this, -1, true )),
        giveBackFocus(NULL),
        font( env->getFont("fontlucida.png") ),
        m_control("Params/irc.param", server, this),
        paralleleOperation(paralleleOperation)
    {
        text->setOverrideFont(font);
        chat->setAutoScrollEnabled(true);
        listChannel->addItem(L"Admins");
        listChannel->addItem(L"Modo");
        listChannel->addItem(L"Tous");
    }



    void IRCClient::draw(void)
    {
        irr::gui::IGUIFont * tmpFont = this->Environment->getSkin()->getFont();
        this->Environment->getSkin()->setFont(font);

        listChannel->draw();
        text->draw();
        chat->draw();

        this->Environment->getSkin()->setFont(tmpFont);
    }

    bool IRCClient::OnEvent(const irr::SEvent &event)
    {

        if( event.EventType == irr::EET_KEY_INPUT_EVENT
                && event.KeyInput.PressedDown
                && event.KeyInput.Key == irr::KEY_RETURN)
        {
            /*
            if(this->Environment->getFocus()->getType() == 10)
            {
                std::cerr << "oui" << std::endl;
                return false;
            } */

            if( this->Environment->hasFocus(text) )
            {
                irr::gui::IGUIElement * tmp = NULL;
                while( irrlichtSucks(tmp, giveBackFocus.front() ) )
                {
                    tmp = giveBackFocus.front();
                    giveBackFocus.pop_front();
                    if( giveBackFocus.empty() )
                        break;
                }
                this->Environment->setFocus(tmp);
                //this->Environment->setFocus(giveBackFocus);
                handleText();
            }
            else
            {
                giveBackFocus.clear();
                irr::gui::IGUIElement * tmp = this->Environment->getFocus();
                while(tmp)
                {
                    giveBackFocus.push_front(tmp);
                    tmp = tmp->getParent();
                }
                this->Environment->setFocus(text);
            }
            return true;
        }
        return false;
    }


    void IRCClient::handleText(void)
    {
        irr::gui::IGUIFont * tmpFont = this->Environment->getSkin()->getFont();
        this->Environment->getSkin()->setFont(font);

        const wchar_t * texte = text->getText();
        if( wcscmp(texte, L"") )
        {
            m_control.handle( narrow(texte) );

            text->setText(L"");
        }

        this->Environment->getSkin()->setFont(tmpFont);
    }


    bool IRCClient::irrlichtSucks( irr::gui::IGUIElement * parent, irr::gui::IGUIElement * child)
    {
        if( ! parent)
            parent = this->Environment->getRootGUIElement();
        if(parent == child)
            return true;
        if( ! child)
            return false;
        irr::core::list<irr::gui::IGUIElement *>::ConstIterator it = parent->getChildren().begin();
        irr::core::list<irr::gui::IGUIElement *>::ConstIterator end = parent->getChildren().end();
        for( ; it != end; ++it)
        {
            if( *it == child)
                return true;
        }
        return false;
    }

    void IRCClient::print(const std::string & texteSTR)
    {
        std::wstring texte = widen(texteSTR);
        paralleleOperation.lock();

        printMessage(texte);

        paralleleOperation.unlock();
    }


    void IRCClient::printMessage(std::wstring texte )
    {
        irr::gui::IGUIFont * tmpFont = this->Environment->getSkin()->getFont();
        this->Environment->getSkin()->setFont(font);

        irr::u32 id = chat->getItemCount();
        irr::s32 i = font->getCharacterFromPos(texte.c_str() , AbsoluteRect.getWidth() - 20);
        while( i != -1 )
        {
            chat->insertItem( id , texte.substr(0, i-1).c_str(), 0);
            chat->setSelected( id );
            id++;
            texte.erase(0,i - 1);
            i = font->getCharacterFromPos(texte.c_str() , AbsoluteRect.getWidth() - 20);
        }

        chat->insertItem( id , texte.c_str(), 0);
        chat->setSelected( id );
        id++;

        this->Environment->getSkin()->setFont(tmpFont);
    }

    void IRCClient::printMessage(LineList & list)
    {
        irr::gui::IGUIFont * tmpFont = this->Environment->getSkin()->getFont();
        this->Environment->getSkin()->setFont(font);

        irr::u32 id = chat->getItemCount();

        while( ! list.empty() )
        {
            std::wstring texte = widen(list.front() );
            irr::s32 i = font->getCharacterFromPos(texte.c_str() , AbsoluteRect.getWidth() - 20);
            while( i != -1 )
            {
                chat->insertItem( id , texte.substr(0, i-1).c_str(), 0);
                chat->setSelected( id );
                id++;
                texte.erase(0,i - 1);
                i = font->getCharacterFromPos(texte.c_str() , AbsoluteRect.getWidth() - 20);
            }
            chat->insertItem( id , texte.c_str(), 0);
            chat->setSelected( id );
            id++;

            list.pop_front();
        }

        this->Environment->getSkin()->setFont(tmpFont);
    }

    void IRCClient::print(LineList & list)
    {
        paralleleOperation.lock();

        printMessage(list);

        paralleleOperation.unlock();
    }

    void IRCClient::setHandle(IRCExternHandle * handle)
    {
        m_control.setHandle(handle);
    }

}
