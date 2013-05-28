#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <assert.h>
#include <algorithm>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct vec { float x, y, z; };
struct mapmodelinfo { int rad, h, zoff, snap; char *name; };

extern void endianswap(void *, int, int);