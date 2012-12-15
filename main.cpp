#include <iostream>
#include <stdio.h>
#include <irrlicht/irrlicht.h>
#include <fstream>
#include <string>
#include "testelementgui.h"

#include "ofstream.h"
#include "ifstream.h"

#include "Go/Control/map.h"
#include "lunar.h"

int main()
{/*    state = state(lua_open() );
    lua_settop(state,0);
    lua_tablibopen(state);
    lua_iolibopen(state);
    lua_baselibopen(state);
    lua_strlibopen(state);
    lua_mathlibopen(state);
    lua_dblibopen(state);
    if( lua_dofile(state, fileScript.c_str() ) != 0)
    {
        exit(1); //error loading script
    }*/



    FILE * config = fopen("test.map", "wb");
    std::cerr << config << std::endl;
  /*  std::ofstream config( "test.map", std::ios_base::binary  | std::ios_base::trunc);
    if( ! config )
    {
        exit(2); //error loading configuration
    } */
    std::string fileScript = "test.lua";
    std::string des = "Map de test, normalement vous ne devriez\npas pouvoir y jouer";
    fprintf(config, "%s\r%s\r%s\r%c%s\r%s\r%f\r%f\r%f\r%f\r%f\r%f",
            des.c_str(),
            "Chemin bidon",
            fileScript.c_str(),
            (unsigned char)1,
            "test.board",
            "board.lua",
            0.,0.,0.,0.,0.,0.
            );
 /*   config << des << "\r"
           << "Chemin bidon" << "\r"
           << fileScript << "\r"
           << (unsigned char)1
           << "test.board" << "\r"
           << "board.lua" << "\r"
              << std::hex << (float)0. << (float)0. << (float)0. << (float)45. << (float)0. << (float)0.;
    config.close(); */
            fclose(config);

/*
            std::ofstream confB("test.board");
            confB << (unsigned int)54 << "\r";
            for(int j = 1; j != 4; ++j) //TODO put plinth relative to other plinth
            {
                confB << (float)-5 << "\r" << (float)0 << "\r" << (float)(j-1)*5+5 << "\r"
                      << (float)0 << "\r" << (float)0 << "\r" << (float)0 << "\r";
                confB << (float)0 << "\r" << (float)0 << "\r" << (float)(j-1)*5+5 << "\r"
                      << (float)0 << "\r" << (float)0 << "\r" << (float)0 << "\r";
                confB << (float)5 << "\r" << (float)0 << "\r" << (float)(j-1)*5+5 << "\r"
                      << (float)0 << "\r" << (float)0 << "\r" << (float)0 << "\r";
            }

            for(int j = 1; j != 4; ++j) //TODO put plinth relative to other plinth
            {
                confB << (float)-5 << "\r" << (float)-(j)*5+2 << "\r" << (float)2 << "\r"
                      << (float)-90 << "\r" << (float)0 << "\r" << (float)0 << "\r";
                confB << (float)0 << "\r" << (float)-(j)*5+2 << "\r" << (float)2 << "\r"
                      << (float)-90 << "\r" << (float)0 << "\r" << (float)0 << "\r";
                confB << (float)5 << "\r" << (float)-(j)*5+2 << "\r" << (float)2 << "\r"
                      << (float)-90 << "\r" << (float)0 << "\r" << (float)0 << "\r";
            }

            for(int j = 1; j != 4; ++j)
            {
                confB << (float)-5 << "\r" << (float)-(j)*5+2 << "\r" << (float)3+5*3 << "\r"
                      << (float)90 << "\r" << (float)0 << "\r" << (float)0 << "\r";
                confB << (float)0 << "\r" << (float)-(j)*5+2 << "\r" << (float)3+5*3 << "\r"
                      << (float)90 << "\r" << (float)0 << "\r" << (float)0 << "\r";
                confB << (float)5 << "\r" << (float)-(j)*5+2 << "\r" << (float)3+5*3 << "\r"
                      << (float)90 << "\r" << (float)0 << "\r" << (float)0 << "\r";
            }

            for(int j = 1; j != 4; ++j)
            {
                confB << (float)8 << "\r" << (float)-3 << "\r" << (float)(j-1)*5+5 << "\r"
                      << (float)0 << "\r" << (float)0 << "\r" << (float)-90 << "\r";
                confB << (float)8 << "\r" << (float)-8 << "\r" << (float)(j-1)*5+5 << "\r"
                      << (float)0 << "\r" << (float)0 << "\r" << (float)-90 << "\r";
                confB << (float)8 << "\r" << (float)-13 << "\r" << (float)(j-1)*5+5 << "\r"
                      << (float)0 << "\r" << (float)0 << "\r" << (float)-90 << "\r";
            }

            for(int j = 1; j != 4; ++j)
            {
                confB << (float)-8 << "\r" << (float)-3 << "\r" << (float)(j-1)*5+5 << "\r"
                      << (float)0 << "\r" << (float)0 << "\r" << (float)90 << "\r";
                confB << (float)-8 << "\r" << (float)-8 << "\r" << (float)(j-1)*5+5 << "\r"
                      << (float)0 << "\r" << (float)0 << "\r" << (float)90 << "\r";
                confB << (float)-8 << "\r" << (float)-13 << "\r" << (float)(j-1)*5+5 << "\r"
                      << (float)0 << "\r" << (float)0 << "\r" << (float)90 << "\r";
            }

            for(int j = 1; j != 4; ++j)
            {
                confB << (float)-5 << "\r" << (float)-16 << "\r" << (float)(j-1)*5+5 << "\r"
                      << (float)180 << "\r" << (float)180 << "\r" << (float)0 << "\r";
                confB << (float)0 << "\r" << (float)-16 << "\r" << (float)(j-1)*5+5 << "\r"
                      << (float)180 << "\r" << (float)180 << "\r" << (float)0 << "\r";
                confB << (float)5 << "\r" << (float)-16 << "\r" << (float)(j-1)*5+5 << "\r"
                      << (float)180 << "\r" << (float)180 << "\r" << (float)0 << "\r";
            }
            confB << "\n\n";
            confB.close();/**/

            Ofstream out("Params/irc.param");
            out << std::string("vive neckara") << std::string("81.56.196.139") << std::string("80") << std::string("Neckara");
            out.close();

    Test::TestElementGUI teste(NULL);
    return 0;
}

