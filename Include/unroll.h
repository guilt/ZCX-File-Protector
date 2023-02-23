#ifndef _UNROLL_H_
#define _UNROLL_H_

// Header file which has useful macros for unrolling.
//
//
// Typical Usage:
//
// Let's say you have a for loop like this:
// for(i = 0; i < 20; ++i) {
//     echoFoo();
// }
//
// You would unroll it like this:
// U_unroll(i, 20, {
//     echoFoo();
// });
//
// If you were doing something with i, such
// as accessing its value in the code block,
// you may want to use this instead:
//
// U_S_unroll(i, 20, {
//    doStuffWithIndex(i);
// }
//
// Why would I need this?
//
// Reduces the number of if conditions needed to run a for
// loop. Makes things faster.
//
// We have 4 variants of Unrolling.
//
// U_unroll makes i go 0 to length-1 in exponential steps
// U_S_unroll makes i go 0 to length-1 in single steps
//
// D_unroll makes i go length to 1 in exponential steps
// D_S_unroll makes i go length to 1 in single steps

// Unit Macros. Overwrite if you have a different
// or a better replacement for these.
#ifndef _unroll1
#define _unroll1(x) \
    {               \
        x;          \
    }
#endif // _unroll1

#ifndef _unroll2
#define _unroll2(x) \
    _unroll1(x);    \
    _unroll1(x)
#endif // _unroll2

#ifndef _unroll4
#define _unroll4(x) \
    _unroll2(x);    \
    _unroll2(x)
#endif // _unroll4

#ifndef _unroll8
#define _unroll8(x) \
    _unroll4(x);    \
    _unroll4(x)
#endif // _unroll8

#ifndef _unroll16
#define _unroll16(x) \
    _unroll8(x);     \
    _unroll8(x)
#endif // _unroll16

#ifndef _unroll32
#define _unroll32(x) \
    _unroll16(x);    \
    _unroll16(x)
#endif // _unroll32

#ifndef _unroll64
#define _unroll64(x) \
    _unroll32(x);    \
    _unroll32(x)
#endif // _unroll64

#ifndef _unroll128
#define _unroll128(x) \
    _unroll64(x);     \
    _unroll64(x)
#endif // _unroll128

// Set Unrolling level.
// Set to 8 by default.
#ifndef unrollLevel
#define unrollLevel 8
#endif // unrollLevel

// Set _unroll unrollLevel.
#if (unrollLevel >= 128)
#define _unrollRest _unroll128
#elif (unrollLevel >= 64)
#define _unrollRest _unroll64
#elif (unrollLevel >= 32)
#define _unrollRest _unroll32
#elif (unrollLevel >= 16)
#define _unrollRest _unroll16
#elif (unrollLevel >= 8)
#define _unrollRest _unroll8
#elif (unrollLevel >= 4)
#define _unrollRest _unroll4
#elif (unrollLevel >= 2)
#define _unrollRest _unroll2
#elif (unrollLevel >= 1)
#define _unrollRest _unroll1
#else
#error unrollLevel should be at least 1.
#endif //(unrollLevel >= 128)

// Set Availability.
#if (unrollLevel >= 1)
#define _avail1
#endif //(unrollLevel >= 1)
#if (unrollLevel >= 2)
#define _avail2
#endif //(unrollLevel >= 2)
#if (unrollLevel >= 4)
#define _avail4
#endif //(unrollLevel >= 4)
#if (unrollLevel >= 8)
#define _avail8
#endif //(unrollLevel >= 8)
#if (unrollLevel >= 16)
#define _avail16
#endif //(unrollLevel >= 16)
#if (unrollLevel >= 32)
#define _avail32
#endif //(unrollLevel >= 32)
#if (unrollLevel >= 64)
#define _avail64
#endif //(unrollLevel >= 64)
#if (unrollLevel >= 128)
#define _avail128
#endif //(unrollLevel >= 128)

// _unroll Task Macros.
#ifdef _avail1
#define D_1(v, n, x) \
    if (v & 1)       \
    {                \
        _unroll1(x); \
        v -= 1;      \
    }
#define D_S_1(v, n, x)       \
    if (v & 1)               \
    {                        \
        _unroll1(x; v -= 1); \
    }
#define U_1(v, n, x) \
    if ((n - v) & 1) \
    {                \
        _unroll1(x); \
        v += 1;      \
    }
#define U_S_1(v, n, x)       \
    if ((n - v) & 1)         \
    {                        \
        _unroll1(x; v += 1); \
    }
#else
#define D_1(v, n, x)
#define D_S_1(v, n, x)
#define U_1(v, n, x)
#define U_S_1(v, n, x)
#endif // _avail1

#ifdef _avail2
#define D_2(v, n, x) \
    if (v & 2)       \
    {                \
        _unroll2(x); \
        v -= 2;      \
    }
#define D_S_2(v, n, x)       \
    if (v & 2)               \
    {                        \
        _unroll2(x; v -= 1); \
    }
#define U_2(v, n, x) \
    if ((n - v) & 2) \
    {                \
        _unroll2(x); \
        v += 2;      \
    }
#define U_S_2(v, n, x)       \
    if ((n - v) & 2)         \
    {                        \
        _unroll2(x; v += 1); \
    }
#else
#define D_2(v, n, x)
#define D_S_2(v, n, x)
#define U_2(v, n, x)
#define U_S_2(v, n, x)
#endif // _avail2

#ifdef _avail4
#define D_4(v, n, x) \
    if (v & 4)       \
    {                \
        _unroll4(x); \
        v -= 4;      \
    }
#define D_S_4(v, n, x)       \
    if (v & 4)               \
    {                        \
        _unroll4(x; v -= 1); \
    }
#define U_4(v, n, x) \
    if ((n - v) & 4) \
    {                \
        _unroll4(x); \
        v += 4;      \
    }
#define U_S_4(v, n, x)       \
    if ((n - v) & 4)         \
    {                        \
        _unroll4(x; v += 1); \
    }
#else
#define D_4(v, n, x)
#define D_S_4(v, n, x)
#define U_4(v, n, x)
#define U_S_4(v, n, x)
#endif // _avail4

#ifdef _avail8
#define D_8(v, n, x) \
    if (v & 8)       \
    {                \
        _unroll8(x); \
        v -= 8;      \
    }
#define D_S_8(v, n, x)       \
    if (v & 8)               \
    {                        \
        _unroll8(x; v -= 1); \
    }
#define U_8(v, n, x) \
    if ((n - v) & 8) \
    {                \
        _unroll8(x); \
        v += 8;      \
    }
#define U_S_8(v, n, x)       \
    if ((n - v) & 8)         \
    {                        \
        _unroll8(x; v += 1); \
    }
#else
#define D_8(v, n, x)
#define D_S_8(v, n, x)
#define U_8(v, n, x)
#define U_S_8(v, n, x)
#endif // _avail8

#ifdef _avail16
#define D_16(v, n, x) \
    if (v & 16)       \
    {                 \
        _unroll16(x); \
        v -= 16;      \
    }
#define D_S_16(v, n, x)       \
    if (v & 16)               \
    {                         \
        _unroll16(x; v -= 1); \
    }
#define U_16(v, n, x) \
    if ((n - v) & 16) \
    {                 \
        _unroll16(x); \
        v += 16;      \
    }
#define U_S_16(v, n, x)       \
    if ((n - v) & 16)         \
    {                         \
        _unroll16(x; v += 1); \
    }
#else
#define D_16(v, n, x)
#define D_S_16(v, n, x)
#define U_16(v, n, x)
#define U_S_16(v, n, x)
#endif // _avail16

#ifdef _avail32
#define D_32(v, n, x) \
    if (v & 32)       \
    {                 \
        _unroll32(x); \
        v -= 32;      \
    }
#define D_S_32(v, n, x)       \
    if (v & 32)               \
    {                         \
        _unroll32(x; v -= 1); \
    }
#define U_32(v, n, x) \
    if ((n - v) & 32) \
    {                 \
        _unroll32(x); \
        v += 32;      \
    }
#define U_S_32(v, n, x)       \
    if ((n - v) & 32)         \
    {                         \
        _unroll32(x; v += 1); \
    }
#else
#define D_32(v, n, x)
#define D_S_32(v, n, x)
#define U_32(v, n, x)
#define U_S_32(v, n, x)
#endif // _avail32

#ifdef _avail64
#define D_64(v, n, x) \
    if (v & 64)       \
    {                 \
        _unroll64(x); \
        v -= 64;      \
    }
#define D_S_64(v, n, x)       \
    if (v & 64)               \
    {                         \
        _unroll64(x; v -= 1); \
    }
#define U_64(v, n, x) \
    if ((n - v) & 64) \
    {                 \
        _unroll64(x); \
        v += 64;      \
    }
#define U_S_64(v, n, x)       \
    if ((n - v) & 64)         \
    {                         \
        _unroll64(x; v += 1); \
    }
#else
#define D_64(v, n, x)
#define D_S_64(v, n, x)
#define U_64(v, n, x)
#define U_S_64(v, n, x)
#endif // _avail64

#ifdef _avail128
#define D_128(v, n, x) \
    if (v & 128)       \
    {                  \
        _unroll128(x); \
        v -= 128;      \
    }
#define D_S_128(v, n, x)       \
    if (v & 128)               \
    {                          \
        _unroll128(x; v -= 1); \
    }
#define U_128(v, n, x) \
    if ((n - v) & 128) \
    {                  \
        _unroll128(x); \
        v += 128;      \
    }
#define U_S_128(v, n, x)       \
    if ((n - v) & 128)         \
    {                          \
        _unroll128(x; v += 1); \
    }
#else
#define D_128(v, n, x)
#define D_S_128(v, n, x)
#define U_128(v, n, x)
#define U_S_128(v, n, x)
#endif // _avail128

#ifdef _unrollRest
#define D_rest(v, n, x)         \
    while (v)                   \
    {                           \
        _unrollRest(x);         \
        v -= unrollLevel;       \
    }
#define D_S_rest(v, n, x)       \
    while (v)                   \
    {                           \
        _unrollRest(x; v -= 1); \
    }
#define U_rest(v, n, x)         \
    while (n - v)               \
    {                           \
        _unrollRest(x);         \
        v += unrollLevel;       \
    }
#define U_S_rest(v, n, x)       \
    while (n - v)               \
    {                           \
        _unrollRest(x; v += 1); \
    }
#else
#define D_rest(v, n, x)
#define D_S_rest(v, n, x)
#define U_rest(v, n, x)
#define U_S_rest(v, n, x)
#endif // _unrollRest

//  D_unroll(v, n, x); Performs: x; n times. v goes from n to 1
//  exponentially. x shouldn't try to access v.
#define D_unroll(v, n, x)    \
    {                        \
        if (n)               \
        {                    \
            v = n;           \
            D_1(v, n, x);    \
            D_2(v, n, x);    \
            D_4(v, n, x);    \
            D_8(v, n, x);    \
            D_16(v, n, x);   \
            D_32(v, n, x);   \
            D_64(v, n, x);   \
            D_128(v, n, x);  \
            D_rest(v, n, x); \
        }                    \
    }

//  D_S_unroll(v, n, x); Performs: x; n times. v goes from n to 1
//  linearly. x can access v.
#define D_S_unroll(v, n, x)    \
    {                          \
        if (n)                 \
        {                      \
            v = n;             \
            D_S_1(v, n, x);    \
            D_S_2(v, n, x);    \
            D_S_4(v, n, x);    \
            D_S_8(v, n, x);    \
            D_S_16(v, n, x);   \
            D_S_32(v, n, x);   \
            D_S_64(v, n, x);   \
            D_S_128(v, n, x);  \
            D_S_rest(v, n, x); \
        }                      \
    }

//  U_unroll(v, n, x); Performs: x; n times. v goes from 0 to n-1
//  exponentially. x shouldn't try to access v.
#define U_unroll(v, n, x)    \
    {                        \
        if (n)               \
        {                    \
            v = 0;           \
            U_1(v, n, x);    \
            U_2(v, n, x);    \
            U_4(v, n, x);    \
            U_8(v, n, x);    \
            U_16(v, n, x);   \
            U_32(v, n, x);   \
            U_64(v, n, x);   \
            U_128(v, n, x);  \
            U_rest(v, n, x); \
        }                    \
    }

//  U_S_unroll(v, n, x); Performs: x; n times. v goes from 0
//  to n-1 linearly. x can access v.
#define U_S_unroll(v, n, x)    \
    {                          \
        if (n)                 \
        {                      \
            v = 0;             \
            U_S_1(v, n, x);    \
            U_S_2(v, n, x);    \
            U_S_4(v, n, x);    \
            U_S_8(v, n, x);    \
            U_S_16(v, n, x);   \
            U_S_32(v, n, x);   \
            U_S_64(v, n, x);   \
            U_S_128(v, n, x);  \
            U_S_rest(v, n, x); \
        }                      \
    }
#endif //_UNROLL_H_
