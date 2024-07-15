#ifndef BASE_H
#define BASE_H

typedef unsigned char byte;
typedef unsigned short word;

#define deref(x) (*((byte*)(x)))
#define derefw(x) (*((word*)(x)))

#endif
