/**

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY 
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE 
COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM 
ÅgAS ISÅh WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR 
IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM 
IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE 
COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

*/

#ifndef CMNLIB_CMNLIBCORE_MISC_HPP__
#define CMNLIB_CMNLIBCORE_MISC_HPP__

/****************************************************************************************\
*                              Compile-time tuning parameters                            *
\****************************************************************************************/

/* maximum size of dynamic memory buffer.
   clAlloc reports an error if a larger block is requested. */
#define  CL_MAX_ALLOC_SIZE    (((size_t)1 << (sizeof(size_t)*8-2)))

/* the alignment of all the allocated buffers */
#define  CL_MALLOC_ALIGN    16

/* default alignment for dynamic data strucutures, resided in storages. */
#define  CL_STRUCT_ALIGN    (static_cast<int>(sizeof(double)))

/* default storage block size */
#define  CL_STORAGE_BLOCK_SIZE   ((1<<16) - 128)

/* default memory block for sparse array elements */
#define  CL_SPARSE_MAT_BLOCK    (1<<12)

/* initial hash table size */
#define  CL_SPARSE_HASH_SIZE0    (1<<10)

/* maximal average node_count/hash_size ratio beyond which hash table is resized */
#define  CL_SPARSE_HASH_RATIO    3

/* max length of strings */
#define  CL_MAX_STRLEN  1024

/* maximum possible number of threads in parallel implementations */
#ifdef _OPENMP
#define CL_MAX_THREADS 128
#else
#define CL_MAX_THREADS 1
#endif

#if 0 /*def  CL_CHECK_FOR_NANS*/
    #define CL_CHECK_NANS( arr ) clCheckArray((arr))
#else
    #define CL_CHECK_NANS( arr )
#endif

/****************************************************************************************\
*                                  Common declarations                                   *
\****************************************************************************************/

#ifdef __GNUC__
#define CL_DECL_ALIGNED(x) __attribute__ ((aligned (x)))
#elif defined _MSC_VER
#define CL_DECL_ALIGNED(x) __declspec(align(x))
#else
#define CL_DECL_ALIGNED(x)
#endif

/* ! DO NOT make it an inline function */
#define clStackAlloc(size) clAlignPtr( alloca((size) + CL_MALLOC_ALIGN), CL_MALLOC_ALIGN )

#if defined _MSC_VER || defined __BORLANDC__
    #define CL_BIG_INT(n)   n##I64
    #define CL_BIG_UINT(n)  n##UI64
#else
    #define CL_BIG_INT(n)   n##LL
    #define CL_BIG_UINT(n)  n##ULL
#endif

/* IEEE754 constants and macros */
#define  CL_POS_INF       0x7f800000
#define  CL_NEG_INF       0x807fffff /* CL_TOGGLE_FLT(0xff800000) */
#define  CL_1F            0x3f800000
#define  CL_TOGGLE_FLT(x) ((x)^(static_cast<int>(x) < 0 ? 0x7fffffff : 0))
#define  CL_TOGGLE_DBL(x) \
    ((x)^(static_cast<int64>(x) < 0 ? CL_BIG_INT(0x7fffffffffffffff) : 0))

#define  CL_NOP(a)      (a)
#define  CL_ADD(a, b)   ((a) + (b))
#define  CL_SUB(a, b)   ((a) - (b))
#define  CL_MUL(a, b)   ((a) * (b))
#define  CL_AND(a, b)   ((a) & (b))
#define  CL_OR(a, b)    ((a) | (b))
#define  CL_XOR(a, b)   ((a) ^ (b))
#define  CL_ANDN(a, b)  (~(a) & (b))
#define  CL_ORN(a, b)   (~(a) | (b))
#define  CL_SQR(a)      ((a) * (a))

#define  CL_LT(a, b)    ((a) < (b))
#define  CL_LE(a, b)    ((a) <= (b))
#define  CL_EQ(a, b)    ((a) == (b))
#define  CL_NE(a, b)    ((a) != (b))
#define  CL_GT(a, b)    ((a) > (b))
#define  CL_GE(a, b)    ((a) >= (b))

#define  CL_NONZERO(a)      ((a) != 0)
#define  CL_NONZERO_FLT(a)  (((a)+(a)) != 0)

#define  CL_PASTE2(a,b) a##b
#define  CL_PASTE(a,b)  CL_PASTE2(a,b)

#define  CL_EMPTY
#define  CL_MAKE_STR(a) #a

#define  CL_ZERO_OBJ(x) memset((x), 0, sizeof(*(x)))

#define  clUnsupportedFormat "Unsupported format"

#define  CL_DESCALE(x,n)     (((x) + (1 << ((n)-1))) >> (n))
#define  CL_FLT_TO_FIX(x,n)  clRound((x)*(1<<(n)))

// Define the NULLPTR value
#ifndef NULLPTR
#define NULLPTR 0
#endif

//****************************************************************************************
//                            Common cycle declaration                         
//****************************************************************************************

#define REP(i,n) for(int i=0;i<(n);++i)
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(b);--i)
#define FOREACH(i,c) for(__typeof((c).begin()) i=(c).begin();i!=(c).end();++i)
#define ALL(x) (x).begin(),(x).end()

#endif /* CMNLIB_CMNLIBCORE_MISC_HPP__ */
