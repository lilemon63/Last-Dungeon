#ifndef IRCCONTROLOR_H
#define IRCCONTROLOR_H

#include<string>

namespace LD
{

    namespace IRC
    {
        namespace Private
        {
            class ListIRCSendCommand;

            class IRCControlor
            {
            public:
                IRCControlor();
                ~IRCControlor();

                bool handleTyping(std::string data);
            private:
                ListIRCSendCommand * m_sendCommand;
            };
        }
    }
}

#endif // IRCCONTROLOR_H
