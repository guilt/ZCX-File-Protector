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
#ifndef perform1
#define perform1(x) \
    {               \
        x;          \
    }
#endif // perform1

#ifndef perform2
#define perform2(x) \
    perform1(x);    \
    perform1(x)
#endif // perform2

#ifndef perform4
#define perform4(x) \
    perform2(x);    \
    perform2(x)
#endif // perform4

#ifndef perform8
#define perform8(x) \
    perform4(x);    \
    perform4(x)
#endif // perform8

#ifndef perform16
#define perform16(x) \
    perform8(x);     \
    perform8(x)
#endif // perform16

#ifndef perform32
#define perform32(x) \
    perform16(x);    \
    perform16(x)
#endif // perform32

#ifndef perform64
#define perform64(x) \
    perform32(x);    \
    perform32(x)
#endif // perform64

#ifndef perform128
#define perform128(x) \
    perform64(x);     \
    perform64(x)
#endif // perform128

// Unset on Debug Mode.
#ifdef DEBUG
#undef rest
#define rest 1
#endif // DEBUG

// Set Unrolling level.
// Set to 8 by default.
#ifndef rest
#define rest 8
#endif // rest

// Set Perform Rest.
#if (rest >= 128)
#define performrest perform128
#elif (rest >= 64)
#define performrest perform64
#elif (rest >= 32)
#define performrest perform32
#elif (rest >= 16)
#define performrest perform16
#elif (rest >= 8)
#define performrest perform8
#elif (rest >= 4)
#define performrest perform4
#elif (rest >= 2)
#define performrest perform2
#elif (rest >= 1)
#define performrest perform1
#else
#error rest should be at least 1.
#endif //(rest >= 128)

// Set Availability.
#if (rest >= 1)
#define avail1
#endif //(rest >= 1)
#if (rest >= 2)
#define avail2
#endif //(rest >= 2)
#if (rest >= 4)
#define avail4
#endif //(rest >= 4)
#if (rest >= 8)
#define avail8
#endif //(rest >= 8)
#if (rest >= 16)
#define avail16
#endif //(rest >= 16)
#if (rest >= 32)
#define avail32
#endif //(rest >= 32)
#if (rest >= 64)
#define avail64
#endif //(rest >= 64)
#if (rest >= 128)
#define avail128
#endif //(rest >= 128)

// Perform Task Macros.
#ifdef avail1
#define D_1(v, n, x) \
    if (v & 1)       \
    {                \
        perform1(x); \
        v -= 1;      \
    }
#define D_S_1(v, n, x)       \
    if (v & 1)               \
    {                        \
        perform1(x; v -= 1); \
    }
#define U_1(v, n, x) \
    if ((n - v) & 1) \
    {                \
        perform1(x); \
        v += 1;      \
    }
#define U_S_1(v, n, x)       \
    if ((n - v) & 1)         \
    {                        \
        perform1(x; v += 1); \
    }
#else
#define D_1(v, n, x)
#define D_S_1(v, n, x)
#define U_1(v, n, x)
#define U_S_1(v, n, x)
#endif // avail1

#ifdef avail2
#define D_2(v, n, x) \
    if (v & 2)       \
    {                \
        perform2(x); \
        v -= 2;      \
    }
#define D_S_2(v, n, x)       \
    if (v & 2)               \
    {                        \
        perform2(x; v -= 1); \
    }
#define U_2(v, n, x) \
    if ((n - v) & 2) \
    {                \
        perform2(x); \
        v += 2;      \
    }
#define U_S_2(v, n, x)       \
    if ((n - v) & 2)         \
    {                        \
        perform2(x; v += 1); \
    }
#else
#define D_2(v, n, x)
#define D_S_2(v, n, x)
#define U_2(v, n, x)
#define U_S_2(v, n, x)
#endif // avail2

#ifdef avail4
#define D_4(v, n, x) \
    if (v & 4)       \
    {                \
        perform4(x); \
        v -= 4;      \
    }
#define D_S_4(v, n, x)       \
    if (v & 4)               \
    {                        \
        perform4(x; v -= 1); \
    }
#define U_4(v, n, x) \
    if ((n - v) & 4) \
    {                \
        perform4(x); \
        v += 4;      \
    }
#define U_S_4(v, n, x)       \
    if ((n - v) & 4)         \
    {                        \
        perform4(x; v += 1); \
    }
#else
#define D_4(v, n, x)
#define D_S_4(v, n, x)
#define U_4(v, n, x)
#define U_S_4(v, n, x)
#endif // avail4

#ifdef avail8
#define D_8(v, n, x) \
    if (v & 8)       \
    {                \
        perform8(x); \
        v -= 8;      \
    }
#define D_S_8(v, n, x)       \
    if (v & 8)               \
    {                        \
        perform8(x; v -= 1); \
    }
#define U_8(v, n, x) \
    if ((n - v) & 8) \
    {                \
        perform8(x); \
        v += 8;      \
    }
#define U_S_8(v, n, x)       \
    if ((n - v) & 8)         \
    {                        \
        perform8(x; v += 1); \
    }
#else
#define D_8(v, n, x)
#define D_S_8(v, n, x)
#define U_8(v, n, x)
#define U_S_8(v, n, x)
#endif // avail8

#ifdef avail16
#define D_16(v, n, x) \
    if (v & 16)       \
    {                 \
        perform16(x); \
        v -= 16;      \
    }
#define D_S_16(v, n, x)       \
    if (v & 16)               \
    {                         \
        perform16(x; v -= 1); \
    }
#define U_16(v, n, x) \
    if ((n - v) & 16) \
    {                 \
        perform16(x); \
        v += 16;      \
    }
#define U_S_16(v, n, x)       \
    if ((n - v) & 16)         \
    {                         \
        perform16(x; v += 1); \
    }
#else
#define D_16(v, n, x)
#define D_S_16(v, n, x)
#define U_16(v, n, x)
#define U_S_16(v, n, x)
#endif // avail16

#ifdef avail32
#define D_32(v, n, x) \
    if (v & 32)       \
    {                 \
        perform32(x); \
        v -= 32;      \
    }
#define D_S_32(v, n, x)       \
    if (v & 32)               \
    {                         \
        perform32(x; v -= 1); \
    }
#define U_32(v, n, x) \
    if ((n - v) & 32) \
    {                 \
        perform32(x); \
        v += 32;      \
    }
#define U_S_32(v, n, x)       \
    if ((n - v) & 32)         \
    {                         \
        perform32(x; v += 1); \
    }
#else
#define D_32(v, n, x)
#define D_S_32(v, n, x)
#define U_32(v, n, x)
#define U_S_32(v, n, x)
#endif // avail32

#ifdef avail64
#define D_64(v, n, x) \
    if (v & 64)       \
    {                 \
        perform64(x); \
        v -= 64;      \
    }
#define D_S_64(v, n, x)       \
    if (v & 64)               \
    {                         \
        perform64(x; v -= 1); \
    }
#define U_64(v, n, x) \
    if ((n - v) & 64) \
    {                 \
        perform64(x); \
        v += 64;      \
    }
#define U_S_64(v, n, x)       \
    if ((n - v) & 64)         \
    {                         \
        perform64(x; v += 1); \
    }
#else
#define D_64(v, n, x)
#define D_S_64(v, n, x)
#define U_64(v, n, x)
#define U_S_64(v, n, x)
#endif // avail64

#ifdef avail128
#define D_128(v, n, x) \
    if (v & 128)       \
    {                  \
        perform128(x); \
        v -= 128;      \
    }
#define D_S_128(v, n, x)       \
    if (v & 128)               \
    {                          \
        perform128(x; v -= 1); \
    }
#define U_128(v, n, x) \
    if ((n - v) & 128) \
    {                  \
        perform128(x); \
        v += 128;      \
    }
#define U_S_128(v, n, x)       \
    if ((n - v) & 128)         \
    {                          \
        perform128(x; v += 1); \
    }
#else
#define D_128(v, n, x)
#define D_S_128(v, n, x)
#define U_128(v, n, x)
#define U_S_128(v, n, x)
#endif // avail128

#ifdef performrest
#define D_rest(v, n, x) \
    while (v)           \
    {                   \
        performrest(x); \
        v -= rest;      \
    }
#define D_S_rest(v, n, x)       \
    while (v)                   \
    {                           \
        performrest(x; v -= 1); \
    }
#define U_rest(v, n, x) \
    while (n - v)       \
    {                   \
        performrest(x); \
        v += rest;      \
    }
#define U_S_rest(v, n, x)       \
    while (n - v)               \
    {                           \
        performrest(x; v += 1); \
    }
#else
#define D_rest(v, n, x)
#define D_S_rest(v, n, x)
#define U_rest(v, n, x)
#define U_S_rest(v, n, x)
#endif // performrest

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
