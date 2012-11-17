#ifndef SERVERGO_H
#define SERVERGO_H

#include <string>

#include "../Vue/vue.h"

namespace Go
{
    /** @brief Controlor for Go.<br/>
      It will send data to the server, look if action are authorized and more.
        /!\ Now it's just a test */
    class ServerGo
    {
    public:
        /** @brief const std::string & path : path of the file which describe the Go's map
            @brief const Preferences & : Go preferences */
        ServerGo(const std::string & path, Preferences & pref);

        virtual ~ServerGo(void);

        /** @brief Try to put a pawn.<br/>
          TODO : We should also specified the pawn to put.
            @param Plinth * plinth : plinth where the pawn should be put. */
        void putPawn(Plinth * plinth);
    private :

        /** @brief Go::Vue, it's the Vue for the go
           @see Go::Vue */
        Vue m_vue;

        /** @brief all plinth of this board */
        Plinth * m_plinth;
    };
}
#endif // SERVERGO_H
