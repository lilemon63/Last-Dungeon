#include<algorithm>
#include <iterator>
#include "ifstream.h"

Ifstream::Ifstream(const std::string &path) :  std::ifstream(path.c_str() )
{
}


Ifstream & operator>>(Ifstream & in, char * t)
{
    char tmp;
    do
    {
        in.get(tmp);
        *(t++) = tmp;
    }while(tmp);

    return in;
}

Ifstream & operator>>(Ifstream & in, std::string & t)
{
    __uint32_t size;
    in >> size;
    std::cerr << "taille :" << size << std::endl;
    t.resize( size);
    std::string::iterator it = t.begin();
    for(__uint32_t i = 0; i != size; ++i, ++it)
        in.get(*it);

    return in;
}

bool Ifstream::isAtEOF(void)
{
    char tmp;
    get(tmp);
    if( eof() )
        return true;
    this->unget();
    return false;
}

Ifstream::operator bool const()
{
    if( isAtEOF() )
        return false;
    return true;
}
