#include<algorithm>
#include <iterator>
#include "ofstream.h"

Ofstream::Ofstream(const std::string & path) : std::ofstream(path.c_str() )
{
}


Ofstream & operator<<(Ofstream & out, const char * const t)
{
    out.write(t, strlen(t) + 1 );
    return out;
}

Ofstream & operator<<(Ofstream & out, const std::string & t)
{
    __uint32_t size = t.size();
    out << size;
    std::copy(t.begin(), t.end(), std::ostream_iterator<char>(out) );
    return out;
}

