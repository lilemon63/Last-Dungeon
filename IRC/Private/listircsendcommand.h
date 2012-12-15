#ifndef LISTIRCSENDCOMMAND_H
#define LISTIRCSENDCOMMAND_H


#include <map>
#include <string>
#include <sstream>

#include "../Public/virtualircsendcommand.h"

namespace LD
{

    namespace IRC
    {
        namespace Private
        {
            class ListIRCSendCommand
            {
            public:
                ~ListIRCSendCommand(void);
                void addCommand(VirtualIRCSendCommand *);
                void removeCommand(VirtualIRCSendCommand *);
                inline void removeCommand(const std::string &);
                std::string createMessage(const std::string & name, const std::stringstream & flux);
            private :
                typedef std::map<std::string, VirtualIRCSendCommand *> m_List;
                m_List m_listCommand;
            };


            void ListIRCSendCommand::removeCommand(const std::string & name)
            {
                m_List::iterator it = m_listCommand.find( name );
                if( it != m_listCommand.end() )
                {
                    delete it->second;
                    m_listCommand.erase(it);
                }
            }
        }
    }

}

#endif // LISTIRCSENDCOMMAND_H
