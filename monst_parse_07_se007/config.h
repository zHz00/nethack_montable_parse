typedef unsigned char uchar;
typedef unsigned char boolean;
typedef signed char schar;
typedef signed char xchar;
typedef struct nhcoord {
	xchar x,y;
} coord;
#define Bitfield(x,n)	unsigned x:n
#define NDECL(f) f()
#define TEXTCOLOR
#define NEARDATA

#define COLNO	80
#define ROWNO	21
#define PL_NSIZ		32	/* name of player, ghost, shopkeeper */
#define MAIL
#define KOPS
#define SEDUCE
#define TOURIST
