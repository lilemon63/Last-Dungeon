#ifndef VIRTUALIRCSENDCOMMAND_H
#define VIRTUALIRCSENDCOMMAND_H

#include<string>
#include<sstream>

namespace LD
{
    namespace IRC
    {
        class VirtualIRCVue;

        class VirtualIRCSendCommand
        {
        public:
            VirtualIRCSendCommand(const std::string & name, VirtualIRCVue * vue);
            virtual ~VirtualIRCSendCommand(void);
            virtual std::string createMessage(const std::stringstream &) const = 0;
            const std::string & getName(void){ return name; }

        protected :
            //acquisition d'informations pour construire les messages.
        private:
            const std::string name;
            VirtualIRCVue * vue;
        };
    }
}


#endif // VIRTUALIRCSENDCOMMAND_H
