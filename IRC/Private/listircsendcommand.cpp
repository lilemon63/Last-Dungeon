#include "listircsendcommand.h"

namespace LD
{
    namespace IRC
    {
        namespace Private
        {
            void ListIRCSendCommand::addCommand(VirtualIRCSendCommand * command)
            {
                m_List::iterator it = m_listCommand.find(command->getName() );
                if( it != m_listCommand.end() )
                {
                    delete it->second;
                    it->second = command;
                }
                else
                    m_listCommand[ command->getName() ] = command;

            }



            ListIRCSendCommand::~ListIRCSendCommand(void)
            {
                m_List::iterator it = m_listCommand.begin();
                m_List::const_iterator const end = m_listCommand.end();
                for( ; it != end; ++it)
                    delete it->second;

            }

            void ListIRCSendCommand::removeCommand(VirtualIRCSendCommand * c)
            {
                removeCommand(c->getName() );
            }

            std::string ListIRCSendCommand::createMessage(const std::string & name, const std::stringstream & flux)
            {
                m_List::iterator it = m_listCommand.find(name);
                if( it != m_listCommand.end() )
                    return it->second->createMessage(flux);
                else
                    return "";
            }
        }
    }
}
