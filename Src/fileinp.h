//
// Created by Karthik on 2023-02-20.
//

#ifndef ZCX_FILEINP_H
#define ZCX_FILEINP_H

#if defined(IDOS) && !defined(__GNUC__)
#include <fstream.h>
#else // defined(IDOS) && !defined(__GNUC__)
#include <fstream>
using namespace std;
#endif // defined(IDOS) && !defined(__GNUC__)

#if defined(IUNI)
#define ios_binary 0
#else // defined(IUNI)
#define ios_binary ios::binary
#endif // defined(IUNI)

#define detectFileLength(fileLength, infile) \
    infile.seekg(0, ios::end);               \
    fileLength = (long_t)infile.tellg();     \
    infile.seekg(0, ios::beg);

#if defined(DEBUG)
#define blockRead(element, length, infile)                  \
    printf("DEBUG: [blockRead] Offset: %ld, Length: %ld\n", \
           (long_t)infile.tellg(), length);                 \
    infile.read((char*)&element, length);

#define blockWrite(element, length, outfile)                 \
    printf("DEBUG: [blockWrite] Offset: %ld, Length: %ld\n", \
           (long_t)outfile.tellp(), length);                 \
    outfile.write((char*)&element, length);

#define blockReadPtr(ptr, length, infile)                      \
    printf("DEBUG: [blockReadPtr] Offset: %ld, Length: %ld\n", \
           (long_t)infile.tellg(), length);                    \
    infile.read((char*)ptr, length);

#define blockWritePtr(ptr, length, outfile)                     \
    printf("DEBUG: [blockWritePtr] Offset: %ld, Length: %ld\n", \
           (long_t)outfile.tellp(), length);                    \
    outfile.write((char*)ptr, length);

#else // defined(DEBUG)

#define blockRead(element, length, infile) \
    infile.read((char*)&element, length);
#define blockWrite(element, length, outfile) \
    outfile.write((char*)&element, length);
#define blockReadPtr(ptr, length, infile) \
    infile.read((char*)(ptr), length);
#define blockWritePtr(ptr, length, outfile) \
    outfile.write((char*)(ptr), length);

#endif // defined(DEBUG)

#endif // ZCX_FILEINP_H
