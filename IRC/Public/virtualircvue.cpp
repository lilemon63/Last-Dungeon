#include "virtualircvue.h"
#include "../Private/irccontrolor2.h"

namespace LD
{
    namespace IRC
    {

        VirtualIRCVue::VirtualIRCVue()
            : m_control(new Private::IRCControlor)
        {
        }

        VirtualIRCVue::~VirtualIRCVue()
        {
            delete m_control;
        }

        bool VirtualIRCVue::handle(const std::string & data)
        {
            m_control->handleTyping(data);
        }
    }
}
