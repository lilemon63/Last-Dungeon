#ifndef IFSTREAM_H
#define IFSTREAM_H

#include <fstream>
#include <string.h>
#include<iostream>
#include<stdio.h>

class Ifstream : public std::ifstream
{
public:
    Ifstream(const std::string & path);
    bool isAtEOF(void);
    operator bool const();
};

Ifstream & operator>>(Ifstream & in, char * t);
Ifstream & operator>>(Ifstream & in, std::string & t);

template<typename Type>
Ifstream & operator>>(Ifstream & in, Type & t)
{
    in.read( (char *)&t, sizeof(t));
    return in;
}

#endif // IFSTREAM_H
