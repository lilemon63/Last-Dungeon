#ifndef SERVERGO_H
#define SERVERGO_H

#include <string>

#include "../Vue/vue.h"
#include "map.h"

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
            @param Plinth * plinth : plinth where the pawn should be put. */
        bool putPawn(Plinth * plinth, Pawn * p);

        void putPawnOnPlinth(Plinth * plinth, Pawn * p);

        void setBoard(float x, float y, float z, float a, float b, float c);

        void setPlinth(float x, float y, float z, float a, float b, float c, int board, Plinth * p);

        void setPlayer(unsigned int numP){ m_vue.setPlayer(numP); }
    private :
        /** @brief Go::Vue, it's the Vue for the go
           @see Go::Vue */
        Vue m_vue;

        Map m_map;
    };
}
#endif // SERVERGO_H
