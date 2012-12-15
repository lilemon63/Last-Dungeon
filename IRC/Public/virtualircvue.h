#ifndef VIRTUALIRCVUE_H
#define VIRTUALIRCVUE_H

#include <string>


namespace LD
{
    namespace IRC
    {
        namespace Private
        {
            class IRCControlor;
        }

        class VirtualIRCVue
        {
        public:
            VirtualIRCVue();
            virtual ~VirtualIRCVue();
            bool handle(const std::string &);
        private :
            Private::IRCControlor * m_control;
        };
    }
}

#endif // VIRTUALIRCVUE_H
