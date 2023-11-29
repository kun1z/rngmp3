//----------------------------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <inttypes.h>
typedef   unsigned char        u8     ;   typedef   char         s8     ;
typedef   uint16_t             u16    ;   typedef   int16_t      s16    ;
typedef   uint32_t             u32    ;   typedef   int32_t      s32    ;
typedef   uint64_t             u64    ;   typedef   int64_t      s64    ;
typedef   __uint128_t          u128   ;   typedef   __int128_t   s128   ;
typedef   unsigned int         ui     ;   typedef   int          si     ;
typedef   unsigned long        ul     ;   typedef   long         sl     ;
typedef   unsigned long long   ull    ;   typedef   long long    sll    ;
typedef   float                r32    ;   typedef   double       r64    ;
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
//----------------------------------------------------------------------------------------------------------------------
#include "blake2bmod.h"
//----------------------------------------------------------------------------------------------------------------------
static u64 tick(void);
static u8 rng(u8 buckets);
static u8 rng8(void);
static void output_silence(const ul milliseconds);
//----------------------------------------------------------------------------------------------------------------------
// Signed 16-bit PCM, LE, Mono, 48kHz
static s8 const * const files[20] =
{
    "1_one.raw", "2_two.raw", "3_three.raw", "4_four.raw", "5_five.raw", "6_six.raw", "7_seven.raw", "8_eight.raw",
    "9_nine.raw", "10_ten.raw", "11_eleven.raw", "12_twelve.raw", "13_thirteen.raw", "14_forteen.raw",
    "15_fifteen.raw", "16_sixteen.raw", "17_seventeen.raw", "18_eighteen.raw", "19_nineteen.raw", "20_twenty.raw"
};
static s8 buf[512];
//----------------------------------------------------------------------------------------------------------------------