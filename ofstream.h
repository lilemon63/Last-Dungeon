#ifndef OFSTREAM_H
#define OFSTREAM_H

#include <fstream>
#include <string.h>

class Ofstream : public std::ofstream
{
public:
    Ofstream(const std::string & path);
};

Ofstream & operator<<(Ofstream & out, const char * const t);
Ofstream & operator<<(Ofstream & out, const std::string & t);

template<typename Type>
Ofstream & operator<<(Ofstream & out, const Type & t)
{
    out.write( (char *)&t , sizeof(t));
    return out;
}

#endif // OFSTREAM_H
