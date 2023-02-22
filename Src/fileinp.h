//
// Created by Karthik on 2023-02-20.
//

#ifndef ZCX_FILEINP_H
#define ZCX_FILEINP_H

#if defined(IDOS)
#include <fstream.h>
#else //defined(IDOS)
#include <fstream>
using namespace std;
#endif //defined(IDOS)

#if defined(IUNI)
#define ios_binary 0
#else //defined(IUNI)
#define ios_binary ios::binary
#endif //defined(IUNI)

#define getFileLength(fileLength, infile)  infile.seekg(0, ios::end); fileLength = (long_t) infile.tellg(); infile.seekg(0, ios::beg);

#endif //ZCX_FILEINP_H
