#include "virtualircsendcommand.h"

namespace LD
{
    namespace IRC
    {
        VirtualIRCSendCommand::VirtualIRCSendCommand(const std::string & name, VirtualIRCVue * vue)
            : name(name), vue(vue)
        {
        }

        VirtualIRCSendCommand::~VirtualIRCSendCommand(void)
        {

        }
    }
}
