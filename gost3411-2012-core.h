/*
 * $Id$
 */

#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include "config.h"

#if defined   __GOST3411_HAS_SSE2__
#include "gost3411-2012-sse2.h"
#elif defined __GOST3411_HAS_MMX__ 
#include "gost3411-2012-mmx.h"
#else
#include "gost3411-2012-ref.h"
#endif

#define DEFAULT_DIGEST_SIZE 512
#define ALGNAME "GOST R 34.11-2012"

union uint512_u
{
    unsigned long long QWORD[8];
    uint8_t BYTE[64];
} uint512_u;

#include "gost3411-2012-const.h"

typedef struct GOST3411Context
{
    union uint512_u *buffer;
    union uint512_u *hash;
    union uint512_u *h;
    union uint512_u *N;
    union uint512_u *Sigma;
    size_t bufsize;
    uint32_t digest_size;
    char *hexdigest;
} GOST3411Context;

void *memalloc(const size_t size);
void final(GOST3411Context *CTX);
GOST3411Context * init(const uint32_t digest_size);
void destroy(GOST3411Context *CTX);
void update(GOST3411Context *CTX, const char *data, size_t len);
