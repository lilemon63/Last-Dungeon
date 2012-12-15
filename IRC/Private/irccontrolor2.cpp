#include "irccontrolor2.h"
#include "listircsendcommand.h"

namespace LD
{
    namespace IRC
    {
        namespace Private
        {

            IRCControlor::IRCControlor()
                : m_sendCommand(new ListIRCSendCommand)
            {
            }


            IRCControlor::~IRCControlor()
            {
                delete m_sendCommand;
            }

            bool IRCControlor::handleTyping(std::string data)
            {
                char typeCommand = data[0];
                std::stringstream is(data);
                std::string command;

                ListIRCSendCommand * sendCommand = m_sendCommand;
                if(typeCommand == '!')
                    ;// sendCommand = ...;

                if(typeCommand != '/' && typeCommand != '!') //PRIVMSG
                    command = "PRIVMSG";
                else  //get command
                {
                    char typeCommandChar;
                    is.get(typeCommandChar);
                    is >> command;
                }

                std::string message = sendCommand->createMessage(command, is);
                if(message != "")
                    ;//send message
                else
                {
                    //m_vue->invalidCommand(command, is);
                    return false;
                }
                return true;
            }
        }
    }
}
