#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <locale>
using namespace std;

#include "config.h"
#include "monsym.h"
#include "permonst.h"

#define NO_ATTK    \
    {              \
        0, 0, 0, 0 \
    }

#define TEXTCOLOR

#ifdef C
#undef C
#endif
#ifdef TEXTCOLOR
#include "color.h"
#define C(color) color
#define HI_DOMESTIC CLR_WHITE /* use for player + friendlies */
#define HI_LORD CLR_MAGENTA
#else
#define C(color)
#endif

char mlet_s[][65]={
    "",
    "S_ANT",
"S_BLOB",
"S_COCKATRICE",
"S_DOG",
"S_EYE",
"S_FELINE",
"S_GREMLIN",
"S_HUMANOID",
"S_IMP",
"S_JELLY",
"S_KOBOLD",
"S_LEPRECHAUN",
"S_MIMIC",
"S_NYMPH",
"S_ORC",
"S_PIERCER",
"S_QUADRUPED",
"S_RODENT",
"S_SPIDER",
"S_TRAPPER",
"S_UNICORN",
"S_VORTEX",
"S_WORM",
"S_XAN",
"S_LIGHT",
"S_ZRUTY",
"S_LAW_ANGEL",
"S_NEU_ANGEL",
"S_CHA_ANGEL",
"S_BAT",
"S_CENTAUR",
"S_DRAGON",
"S_ELEMENTAL",
"S_FUNGUS",
"S_GNOME",
"S_GIANT",
"S_invisible",
"S_JABBERWOCK",
"S_KOP",
"S_LICH",
"S_MUMMY",
"S_NAGA",
"S_OGRE",
"S_PUDDING",
"S_QUANTMECH",
"S_RUSTMONST",
"S_SNAKE",
"S_TROLL",
"S_UMBER",
"S_VAMPIRE",
"S_WRAITH",
"S_XORN",
"S_YETI",
"S_ZOMBIE",
"S_HUMAN",
"S_GHOST",
"S_SHADE",
"S_GOLEM",
"S_DEMON",
"S_EEL",
"S_LIZARD",
"S_PLANT",
"S_NEU_OUTSIDER",
"S_WORM_TAIL",
"S_MIMIC_DEF"
};

struct dict_s
{

    char value[40];
    unsigned int key;
};

/*
all new arrays:
mr_s//resists
fmm_s//motility
fmt_s//thoughts
fmb_s//body blan
fms_s//skills
fmv_s//vision
fmg_s//game mechanics
fma_s//race
fmw_s//wards

*/
//this goes to flags4 bc these is completely new flags
struct dict_s fmf_s[]=
{
{"M4_MARTIAL_B",0x01},
{"M4_MARTIAL_S",0x02},
{"M4_MARTIAL_E",0x04},
{"M4_BAB_FULL",0x08},
{"M4_BAB_HALF",0x10},
{"M4_LEVEL_30",0x20},
{"M4_LEVEL_45",0x40},
{"M4_PHYS_SCALING",0x80},
{"",0}
};

struct dict_s fmw_s[]=
{
{"M4_ELDER_SIGN",0x01},
{"M4_EYE_OF_YGG",0x02},
{"M4_ELDER_EYE_ELEM",0x04},
{"M4_ELDER_EYE_ENERGY",0x08},
{"M4_ELDER_EYE_PLANES",0x10},
{"",0}
};

struct dict_s mr_s[]=
{{"MR_FIRE",0x01},
{"MR_COLD",0x02},
{"MR_SLEEP",0x04},
{"MR_DISINT",0x08},
{"MR_ELEC",0x10},
{"MR_POISON",0x20},
{"MR_ACID",0x40},
{"MR_STONE",0x80},
{"MR_DRAIN",0x100},
{"MR_SICK",0x200},
{"MR_MAGIC",0x400},
{"MR_REFLECT",0x800},
/*{"MR2_SEE_INVIS", 0x0100},
{"MR2_LEVITATE", 0x0200 },
{"MR2_WATERWALK", 0x0400},
{"MR2_MAGBREATH", 0x0800},
{"MR2_DISPLACED", 0x1000},
{"MR2_STRENGTH", 0x2000 },
{"MR2_FUMBLING", 0x4000 },*/
{"",0}

};
struct dict_s fmm_s[]=//flags1->flagsm (motility)
{
{"M1_FLY",0x00000001L},//MM_FLY
{"M1_SWIM",0x00000002L},//MM_SWIM
{"M1_AMORPHOUS",0x00000004L},//MM_AMORPHOUS
{"M1_WALLWALK",0x00000008L},//MM_WALLWALK
{"M1_CLING",0x00000010L},//MM_CLING
{"M1_TUNNEL",0x00000020L},//MM_TUNNEL
{"M1_NEEDPICK",0x00000040L},//MM_NEEDPICK
{"M1_AMPHIBIOUS",0x00000080L},//MM_AMPHIBIOUS
{"M1_BREATHLESS",0x00000100L},//MM_BREATHLESS
{"M1_TPORT",0x00000200L},//MM_TPORT
{"M1_TPORT_CNTRL",0x00000400L},//MM_TPORT_CNTRL
{"M1_TENGTPORT",0x00000800L},//MM_TENGTPORT
{"M3_STATIONARY",0x00001000L},//MM_STATIONARY
{"M1_FLOAT",0x00002000L},//MM_FLOAT
{"M1_NOTONL",0x00004000L},//MM_NOTONL
{"M1_FLEETFLEE",0x00008000L},//MM_FLEETFLEE
{"M1_WEBRIP",0x00010000L},//MM_WEBRIP
{"M1_DOORBUST",0x00020000L},//MM_DOORBUST,
{"M1_AQUATIC",0x00040000L},//MM_AQUATIC


{"",0}

};

struct dict_s fmb_s[]=//flags1->flagsb (body plan)
{
{"M1_NOEYES",0x00000001L},
{"M1_NOHANDS",0x00000002L},
{"M1_NOLIMBS",0x00000004L},//{"M1_NOLIMBS",0x00006000L},
{"M1_NOHEAD",0x00000008L},
{"M1_HUMANOID",0x00000010L},
{"M1_ANIMAL",0x00000020L},//CAUTION! animal both in MB_ANIMAL and MT_ANIMAL!
{"M1_SLITHY",0x00000040L},
{"M1_UNSOLID",0x00000080L},
{"M1_THICK_HIDE",0x00000100L},
{"M1_OVIPAROUS",0x00000200L},
{"M1_ACID",0x00000400L},
{"M1_POIS",0x00000800L},
{"M1_CHILL",0x00001000L},
{"M1_TOSTY",0x00002000L},
{"M1_HALUC",0x00004000L},
{"M2_MALE",0x00008000L},
{"M2_FEMALE",0x00010000L},
{"M2_NEUTER",0x00020000L},
{"M2_STRONG",0x00040000L},
{"M1_WINGS",0x00080000L},
{"M1_LONGHEAD",0x00100000L},
{"M1_LONGNECK",0x00200000L},
{"M1_NOFEET",0x00400000L},
{"M1_HAS_FEET",0x00800000L},
{"M1_CAN_AMULET",0x01000000L},
{"M1_INDIGESTIBLE",0x02000000L},
{"M1_INSUBSTANTIAL",0x04000000L},
{"M1_NOGLOVES",0x08000000L},
{"M1_NOHAT",0x10000000L},
{"M1_SKELETAL",0x20000000L},//MB_SKELETAL
//#define MB_SNAKELEG	(MB_HUMANOID|MB_SLITHY)
//#define MB_CENTAUR	(MB_HUMANOID|MB_ANIMAL)
{"",0}
};


struct dict_s fmv_s[]=
{
{"M3_NORMAL",0x00000001L},
{"M3_INFRAVISION",0x00000002L},
{"M3_DARKSIGHT",0x00000004L},
{"M3_LOWLIGHT2",0x00000008L},
{"M3_LOWLIGHT3",0x00000010L},
{"M3_CATSIGHT",0x00000020L},
{"M3_ECHOLOCATE",0x00000040L},
{"M3_DUMMY",0x00800000L},//bc of 0x00800040L for M3_ECHOLOCATE
{"M3_BLOODSENSE",0x00000080L},
{"M3_LIFESENSE",0x00000100L},
{"M3_EXTRAMISSION",0x00000200L},
{"M3_TELEPATHIC",0x00000400L},
{"M3_RLYEHIAN",0x00000800L},
{"M1_SEE_INVIS",0x00001000L},
{"M3_DETECTION",0x00002000L},
{"M3_OMNI",0x00004000L},
{"M3_SCENT",0x00008000L},
{"M3_EARTHSENSE",0x00010000L},
{"M3_DUMMY",0x00040000L},//bug in crow-winged half-dragon (MG_VSLASH in MV field)
{"M3_DUMMY",0x00100000L}//bug in crow-winged half-dragon (MG_VSLASH in MV field)
};

struct dict_s fmg_s[]=
{
{"M1_REGEN",0x00000001L},
{"M2_NOPOLY",0x00000002L},
{"M2_MERC",0x00000004L},
{"M2_PNAME",0x00000008L},
{"M2_LORD",0x00000010L},
{"M2_PRINCE",0x00000020L},
{"M2_NASTY",0x00000040L},
{"M3_INFRAVISIBLE",0x0080},
{"M3_OPAQUE",0x0100},
{"M3_DISPLACES",0x0200},//MG_DISPLACEMENT
{"M4_HATESSILVER",0x00000400L},
{"M4_HATESIRON",0x00000800L},
{"M4_HATESUNHOLY",0x00001000L},
{"M4_HATESHOLY",0x00002000L},
{"M3_RIDER",0x00004000L},
{"M3_DEADLY",0x00008000L},
{"M3_TRACKER",0x00010000L},
{"M3_NOSPELLCOOLDOWN",0x00020000L},
{"M4_RBLUNT",0x00040000L},
{"M4_RSLASH",0x00080000L},
{"M4_RPIERCE",0x00100000L},
{"M4_WRESIST",0x00200000L},
{"M3_NOTAME",0x00400000L},
{"M3_NOWISH",0x00800000L},
{"M3_BACKSTAB",0x01000000L},
{"M3_COMMANDER",0x02000000L},
{"M3_SANLOSS",0x04000000L},
{"M3_INSIGHT",0x08000000L},
{"M3_RIDER_HP",0x10000000L},
{"M3_FUTURE_WISH",0x20000000L},
{"M4_HATESUNBLESSED",0x40000000L},
};

struct dict_s fma_s[]=
{
{"MH_UNDEAD",0x00000001L},
{"MH_WERE",0x00000002L},
{"MH_HUMAN",0x00000004L},
{"MH_ELF",0x00000008L},
{"MH_DROW",0x00000010L},
{"MH_DWARF",0x00000020L},
{"MH_GNOME",0x00000040L},
{"MH_ORC",0x00000080L},
{"MH_VAMPIRE",0x00000100L},
{"MH_CLOCK",0x00000200L},
{"MH_UNLIVING",0x00000400L},
{"MH_PLANT",0x00000800L},
{"MH_GIANT",0x00001000L},
{"MH_INSECTOID",0x00002000L},
{"MH_SPIDER",0x00004000L},//MA_ARACHNID
{"MH_AVIAN",0x00008000L},
{"MH_REPTILIAN",0x00010000L},
{"MH_ANIMAL",0x00020000L},
{"MH_AQUATIC",0x00040000L},
{"MH_DEMIHUMAN",0x00080000L},
{"MH_FEY",0x00100000L},
{"MH_ELEMENTAL",0x00200000L},
{"MH_DRAGON",0x00400000L},
{"MH_DEMON",0x00800000L},
{"MH_MINION",0x01000000L},
{"MH_PRIMORDIAL",0x02000000L},
{"MH_ET",0x04000000L},
{"MH_G_O_O",0x08000000L},
{"MH_XORN",0x10000000L},
};

struct dict_s fmt_s[]=//flags3->flagst (thoughts)
{
    {"M3_WANTSAMUL",0x0001},
{"M3_WANTSBELL",0x0002},
{"M3_WANTSBOOK",0x0004},
{"M3_WANTSCAND",0x0008},
{"M3_WANTSARTI",0x0010},
//{"M3_WANTSALL",0x001f},
{"M3_WAITFORU",0x0020},
{"M3_CLOSE",0x0040},
//{"M3_COVETOUS",0x001f},
//{"M3_WAITMASK",0x00c0},
{"M2_PEACEFUL",0x00000080L},
{"M2_DOMESTIC",0x00000100L},
{"M2_WANDER",0x00000200L},
{"M2_STALK",0x00000400L},
{"M2_ROCKTHROW",0x00000800L},
{"M2_GREEDY",0x00001000L},
{"M2_JEWELS",0x00002000L},
{"M2_COLLECT",0x00004000L},
{"M2_MAGIC",0x00008000L},
{"M1_CONCEAL",0x00010000L},
{"M1_HIDE",0x00020000L},
{"M1_MINDLESS",0x00040000L},
{"M1_ANIMAL",0x00080000L},
{"M1_CARNIVORE",0x00100000L},
{"M1_HERBIVORE",0x00200000L},
//{"M1_OMNIVORE",0x60000000L},
{"M2_HOSTILE",0x00400000L},
{"M3_TRAITOR",0x00800000L},
{"M1_NOTAKE",0x01000000L},
{"M1_METALLIVORE",0x02000000L},
{"M1_MAGIVORE",0x04000000L},
{"M3_BOLD",0x08000000L},
{"M3_DETACHED",0x10000000L},
{"",0}

};

struct dict_s mz_s[]=
{
    {"MZ_TINY",0},
{"MZ_SMALL",1},
{"MZ_MEDIUM",2},
{"MZ_LARGE",3},
{"MZ_HUGE",4},
{"MZ_GIGANTIC",7},
{"",0}

};

struct dict_s ms_36_s[]=
{
{"MS_SILENT",0},
{"MS_BARK",1},
{"MS_MEW",2},
{"MS_ROAR",3},
{"MS_GROWL",4},
{"MS_SQEEK",5},
{"MS_SQAWK",6},
{"MS_HISS",7},
{"MS_BUZZ",8},
{"MS_GRUNT",9},
{"MS_NEIGH",10},
{"MS_WAIL",11},
{"MS_SHEEP",12},
{"MS_GURGLE",13},
{"MS_BURBLE",14},
{"MS_JUBJUB",15},
{"MS_ANIMAL",15},
{"MS_HOWL",16},
{"MS_SHRIEK",17},
{"MS_SHOG",18},
{"MS_BONES",19},
{"MS_LAUGH",20},
{"MS_MUMBLE",21},
{"MS_IMITATE",22},
{"MS_ORC",9},
{"MS_HUMANOID",23},
{"MS_ARREST",24},
{"MS_SOLDIER",25},
{"MS_GUARD",26},
{"MS_DJINNI",27},
{"MS_NURSE",28},
{"MS_SEDUCE",29},
{"MS_VAMPIRE",30},
{"MS_BRIBE",31},
{"MS_CUSS",32},
{"MS_RIDER",33},
{"MS_LEADER",34},
{"MS_NEMESIS",35},
{"MS_GUARDIAN",36},
{"MS_SELL",37},
{"MS_ORACLE",38},
{"MS_PRIEST",39},
{"MS_SPELL",40},
{"MS_WERE",41},
{"MS_BOAST",42},
{"MS_DREAD",43},
{"MS_OONA",44},
{"MS_SONG",45},
{"MS_INTONE",46},
{"MS_FLOWER",47},
{"MS_TRUMPET",48},
{"MS_UNCURSE",49},
{"MS_STATS",50},
{"MS_GLYPHS",51},
{"MS_SECRETS",52},
{"MS_SCREAM",53},
{"MS_HARROW",54},
{"MS_APOC",55},
{"MS_COUGH",56},
{"MS_RIBBIT",57},
{"",0}

};
struct dict_s ms_s[]=
{
{"MS_SILENT",0},
{"MS_BARK",1},
{"MS_MEW",2},
{"MS_ROAR",3},
{"MS_BELLOW",4},
{"MS_GROWL",5},
{"MS_SQEEK",6},
{"MS_SQAWK",7},
{"MS_CHIRP",8},
{"MS_HISS",9},
{"MS_BUZZ",10},
{"MS_GRUNT",11},
{"MS_NEIGH",12},
{"MS_MOO",13},
{"MS_WAIL",14},
{"MS_GURGLE",15},
{"MS_BURBLE",16},
{"MS_TRUMPET",17},
{"MS_ANIMAL",17},
{"MS_SHRIEK",18},
{"MS_BONES",19},
{"MS_LAUGH",20},
{"MS_MUMBLE",21},
{"MS_IMITATE",22},
{"MS_WERE",23},
{"MS_ORC",24},
{"MS_HUMANOID",25},
{"MS_ARREST",26},
{"MS_SOLDIER",27},
{"MS_GUARD",28},
{"MS_DJINNI",29},
{"MS_NURSE",30},
{"MS_SEDUCE",31},
{"MS_VAMPIRE",32},
{"MS_BRIBE",33},
{"MS_CUSS",34},
{"MS_RIDER",35},
{"MS_LEADER",36},
{"MS_NEMESIS",37},
{"MS_GUARDIAN",38},
{"MS_SELL",39},
{"MS_ORACLE",40},
{"MS_PRIEST",41},
{"MS_SPELL",42},
{"MS_BOAST",43},
{"MS_GROAN",44},

};

struct dict_s geno_s[]=
{
{"G_DEPTHS",0x00200000},
{"G_SPCORPSE",0x00100000},
{"G_UNIQ",0x2000},
{"G_PLANES",0x1000},
{"G_NOHELL",0x0800},
{"G_HELL",0x0400},
{"G_NOGEN",0x0200},
{"G_SGROUP",0x0080},
{"G_LGROUP",0x0040},
{"G_GENO",0x0020},
{"G_NOCORPSE",0x0010},
{"",0}
//{"G_FREQ",0x0007},

};

struct dict_s at_s[]=
{
    {"AT_NONE",0},
{"AT_CLAW",1},
{"AT_BITE",2},
{"AT_KICK",3},
{"AT_BUTT",4},
{"AT_TUCH",5},
{"AT_STNG",6},
{"AT_HUGS",7},
{"AT_SPIT",10},
{"AT_ENGL",11},
{"AT_BREA",12},
{"AT_BRSH",13},
{"AT_EXPL",14},
{"AT_BOOM",15},
{"AT_GAZE",16},
{"AT_TENT",17},
{"AT_ARRW",18},
{"AT_WHIP",19},
{"AT_LRCH",20},
{"AT_HODS",21},
{"AT_LNCK",22},
{"AT_MMGC",23},
{"AT_ILUR",24},
{"AT_HITS",25},
{"AT_WISP",26},
{"AT_TNKR",27},
{"AT_SRPR",28},
{"AT_BEAM",29},
{"AT_DEVA",30},
{"AT_5SQR",31},
{"AT_5SBT",32},
{"AT_WDGZ",33},
{"AT_REND",34},
{"AT_VINE",35},
{"AT_BKGT",36},
{"AT_BKG2",37},
{"AT_XSPR",38},
{"AT_MSPR",39},
{"AT_DSPR",40},
{"AT_ESPR",41},
{"AT_OBIT",42},
{"AT_WBIT",43},
{"AT_TAIL",44},
{"AT_TONG",45},
{"AT_VOMT",46},
{"AT_WEAP",252},
{"AT_XWEP",253},
{"AT_MARI",254},
{"AT_MAGC",255},
{"",0}
};

struct dict_s ad_s[]=
{
    {"AD_PHYS",0},
{"AD_MAGM",1},
{"AD_FIRE",2},
{"AD_COLD",3},
{"AD_SLEE",4},
{"AD_DISN",5},
{"AD_ELEC",6},
{"AD_DRST",7},
{"AD_ACID",8},
{"AD_SPC1",9},
{"AD_SPC2",10},
{"AD_BLND",11},
{"AD_STUN",12},
{"AD_SLOW",13},
{"AD_PLYS",14},
{"AD_DRLI",15},
{"AD_DREN",16},
{"AD_LEGS",17},
{"AD_STON",18},
{"AD_STCK",19},
{"AD_SGLD",20},
{"AD_SITM",21},
{"AD_SEDU",22},
{"AD_TLPT",23},
{"AD_RUST",24},
{"AD_CONF",25},
{"AD_DGST",26},
{"AD_HEAL",27},
{"AD_WRAP",28},
{"AD_WERE",29},
{"AD_DRDX",30},
{"AD_DRCO",31},
{"AD_DRIN",32},
{"AD_DISE",33},
{"AD_DCAY",34},
{"AD_SSEX",35},
{"AD_HALU",36},
{"AD_DETH",37},
{"AD_PEST",38},
{"AD_FAMN",39},
{"AD_SLIM",40},
{"AD_ENCH",41},
{"AD_CORR",42},
{"AD_POSN",43},
{"AD_WISD",44},
{"AD_VORP",45},
{"AD_SHRD",46},
{"AD_SLVR",47},
{"AD_BALL",48},
{"AD_BLDR",49},
{"AD_VBLD",50},
{"AD_TCKL",51},
{"AD_WET",52},
{"AD_LETHE",53},
{"AD_BIST",54},
{"AD_CNCL",60},
{"AD_DEAD",61},
{"AD_SUCK",62},
{"AD_MALK",63},
{"AD_UVUU",64},
{"AD_ABDC",65},
{"AD_KAOS",66},
{"AD_LSEX",67},
{"AD_HLBD",68},
{"AD_SPNL",69},
{"AD_MIST",70},
{"AD_TELE",71},
{"AD_POLY",72},
{"AD_PSON",73},
{"AD_GROW",74},
{"AD_SOUL",75},
{"AD_TENT",76},
{"AD_JAILER",77},
{"AD_AXUS",78},
{"AD_UNKNWN",79},
{"AD_SOLR",80},
{"AD_CHKH",81},
{"AD_HODS",82},
{"AD_CHRN",83},
{"AD_LOAD",84},
{"AD_GARO",85},
{"AD_GARO_MASTER",86},
{"AD_LVLT",87},
{"AD_BLNK",88},
{"AD_WEEP",89},
{"AD_SPOR",90},
{"AD_FNEX",91},
{"AD_SSUN",92},
{"AD_MAND",93},
{"AD_BARB",94},
{"AD_LUCK",95},
{"AD_VAMP",96},
{"AD_WEBS",97},
{"AD_ILUR",98},
{"AD_TNKR",99},
{"AD_FRWK",100},
{"AD_STDY",101},
{"AD_OONA",102},
{"AD_NTZC",103},
{"AD_WTCH",104},
{"AD_SHDW",105},
{"AD_STTP",106},
{"AD_HDRG",107},
{"AD_STAR",108},
{"AD_EELC",109},
{"AD_EFIR",110},
{"AD_EDRC",111},
{"AD_ECLD",112},
{"AD_EACD",113},
{"AD_CNFT",114},
{"AD_BLUD",115},
{"AD_SURY",116},
{"AD_NPDC",117},
{"AD_GLSS",118},
{"AD_MERC",119},
{"AD_GOLD",120},
{"AD_ACFR",121},
{"AD_DESC",122},
{"AD_BLAS",123},
{"AD_SESN",124},
{"AD_POLN",125},
{"AD_BDFN",126},
{"AD_SPHR",127},
{"AD_DARK",128},
{"AD_LRVA",129},
{"AD_NPDS",133},
{"AD_NPDD",134},
{"AD_NPDR",135},
{"AD_NPDA",136},
{"AD_HOOK",130},
{"AD_MDWP",131},
{"AD_SSTN",132},
{"AD_DOBT",137},
{"AD_APCS",138},
{"AD_PULL",139},
{"AD_PAIN",140},
{"AD_MROT",141},
{"AD_LAVA",142},
{"AD_PYCL",143},
{"AD_MOON",144},
{"AD_HOLY",145},
{"AD_UNHY",146},
{"AD_PERH",147},
{"AD_SVPN",148},
{"AD_HLUH",149},
{"AD_TSMI",150},
{"AD_BYAK",151},
{"AD_BSTR",152},
{"AD_UNRV",153},
{"AD_MADF",154},
{"AD_FATK",155},
{"AD_DRHP",156},
{"AD_PUSH",157},
{"AD_FATK",158},
{"AD_FATK",159},
{"AD_FATK",160},


{"AD_DUNSTAN",161},
{"AD_IRIS",162},
{"AD_NABERIUS",163},
{"AD_OTIAX",164},
{"AD_SIMURGH",165},

{"AD_CMSL",166},
{"AD_FMSL",167},
{"AD_EMSL",168},
{"AD_SMSL",169},
{"AD_WMTG",170},

{"AD_CLRC",171},
{"AD_SPEL",172},
{"AD_RBRE",173},
{"AD_RGAZ",174},
{"AD_RETR",175},

{"AD_SAMU",176},
{"AD_CURS",177},
{"AD_SQUE",178},

{"",0}
};

char *get_prob(struct permonst *m,char *resist)
{
    static char res[80];
    char prefix[2]="~";
    float d=-1.0;
    float prob=-1.0;
    int multiplier=0,permanent=0;
    int nutval=m->cnutrit;
	if(m->mlevel < 5) multiplier = 5;
	else if (m->mlevel < 10) multiplier = 10;
	else if (m->mlevel < 15) multiplier = 15;
	else multiplier = 20;
	if(m->geno & G_UNIQ) multiplier = 20;
	if(m->geno & G_UNIQ && m->mlevel > 14) permanent = 1;

	long duration = nutval * multiplier;
    if(strcmp(resist,"MR_POISON")==0)
    {
        if ((strcmp(m->mname,"killer bee")==0)||(strcmp(m->mname,"scorpion")==0))
        {
            prob=0.25*(1.0/*100%*/)+0.75*(m->mlevel/15.0);
            goto skip;
        }
        else
            d=15.0;
    }
    if(strcmp(resist,"MR_DISINT")==0)
    {
        d=15.0;
    }
    if(strcmp(resist,"M1_TPORT")==0)
    {
        d=10.0;
    }
    if(strcmp(resist,"M1_TPORT_CNTRL")==0)
    {
        d=12.0;
    }
    if(strcmp(resist,"Telepathy")==0)
    {
        d=1.0;

    }
    if(strcmp(resist,"Displaced")==0)
    {
        if(strcmp(m->mname,"shimmering dragon")==0)
        {
            d=-1.0;//100% chance, timeout
            goto skip;
        }
        d=10.0;
    }
    prob=m->mlevel/d;
skip:
    if(d<0)
    {
        //we need duration
        if(permanent)
            sprintf(res,"%s=#",resist,duration);
        else
            sprintf(res,"%s=T%d",resist,duration);
    }
    else
    {
        //ordinary probability
        prob*=100.0;
        if(prob>100.0)
            prob=100.0;
        if(strcmp(resist,"Displaced")==0)
            sprintf(res,"%s=%2.0f;T%d",resist,prob,duration);
        else
            sprintf(res,"%s=%2.0f",resist,prob);

    }
    return res;

}

int
experience(struct permonst *ptr)
{
    int i, tmp, tmp2;
    if(strcmp(ptr->mname,"dancing blade")==0||
       strcmp(ptr->mname,"long sinuous tentacle")==0||
       strcmp(ptr->mname,"swarm of snaking tentacles")==0||
       strcmp(ptr->mname,"wide-clubbed tentacle")==0||
       strcmp(ptr->mname,"priest of a unknown god")==0||

       strcmp(ptr->mname,"dungeon fern spore")==0||
       strcmp(ptr->mname,"swamp fern spore")==0||
       strcmp(ptr->mname,"burning fern spore")==0
       )
        return 0;

    tmp = 1 + ptr->mlevel*ptr->mlevel;

    /*  For higher ac values, give extra experience */
    int base_ac=10 - ptr->nac - ptr->dac - ptr->pac;
    //this is very simplified formula, but we can't calculate correct ac without knowing
    //exact monster parameters during actual play, so we count some "base" AC
    if ((i =base_ac) < 3)
        tmp += (7 - i) * ((i < 0) ? 2 : 1);

    /*  For very fast monsters, give extra experience */
    if (ptr->mmove > NORMAL_SPEED)
        tmp += (ptr->mmove > (3 * NORMAL_SPEED / 2)) ? 5 : 3;

    /*  For each "special" attack type give extra experience */
    for (i = 0; i < NATTK; i++) {
        tmp2 = ptr->mattk[i].aatyp;
        if (tmp2 > AT_BUTT) {
            if (tmp2 == AT_WEAP)
                tmp += 5;
            else if (tmp2 == AT_MAGC|| tmp2 == AT_MMGC)
                tmp += 10;
            else
                tmp += 3;
        }
    }

    /*  For each "special" damage type give extra experience */
    for (i = 0; i < NATTK; i++) {
        tmp2 = ptr->mattk[i].adtyp;
        if (tmp2 > AD_PHYS && tmp2 < AD_BLND)
            tmp += 2 * ptr->mlevel;
        else if ((tmp2 == AD_DRLI) || (tmp2 == AD_STON) || (tmp2 == AD_SLIM))
            tmp += 50;
        else if (tmp2 != AD_PHYS)
            tmp += ptr->mlevel;
        /* extra heavy damage bonus */
        if ((int) (ptr->mattk[i].damd * ptr->mattk[i].damn) > 23)
            tmp += ptr->mlevel;
        if (tmp2 == AD_WRAP && ptr->mlet == S_EEL /*&& !Amphibious*/)
            //это базовый опыт, поэтому не учитываем дыхание игрока
            tmp += 1000;
    }

    /*  For certain "extra nasty" monsters, give even more */
    if ((ptr->mflagsg) & MG_NASTY)
        tmp += (7 * ptr->mlevel);

    /*  For higher level monsters, an additional bonus is given */
    if (ptr->mlevel > 8)
        tmp += 50;

    /* Mail daemons put up no fight. */
    if (strcmp(ptr->mname,"mail daemon")==0)
        tmp = 1;

    return (tmp);
}

char *search_dict(struct dict_s *dict,unsigned int key)
{
    int x=0;
    while(dict[x].value[0]!='\0')
    {
        if(dict[x].key==key)
            return dict[x].value;
        x++;
    }
    printf("%08x not found! First value is %s.\n",key,dict[0].value);
    return NULL;
}

char *convert_dnh_flags(int flags_n,struct permonst *mon)
{
    static char temp_str[1000]="";
    static struct dict_s *arrays_list[]=
    {
        fmm_s,//motility
        fmt_s,//thoughts
        fmb_s,//body blan
        fmf_s,//skills
        fmv_s,//vision
        fmg_s,//game mechanics
        fma_s,//race
        fmw_s,
        NULL//wards
    };
    unsigned long real_flags[]=
    {
        mon->mflagsm,
        mon->mflagst,
        mon->mflagsb,
        mon->mflagsf,
        mon->mflagsv,
        mon->mflagsg,
        mon->mflagsa,
        mon->mflagsw
    };

    char *flag_name=NULL;
    int a=0;
    int bit=0;
    temp_str[0]='\0';

    for(a=0;arrays_list[a]!=NULL;a++)
    {
        for(bit=0;bit<32;bit++)
            if(real_flags[a]&(1<<bit))
            {
                flag_name=search_dict(arrays_list[a],1<<bit);
                if(((int)flag_name[1])==48+flags_n)//48 is '0', so we search for M1_*, M2_* etc
                {
                    strcat(temp_str,flag_name);
                    strcat(temp_str,"|");
                }
            }
    }
    int len=strlen(temp_str);
    if(temp_str[len-1]=='|')
        temp_str[len-1]='\0';
    return temp_str;
}




struct class_sym {
    char sym;
    const char *name;
    const char *explain;
};


extern struct permonst mons[];
/*monst.c*/


bool no_attk(struct attack a)
{
    if(a.aatyp==0&&a.adtyp==0&&a.damd==0&&a.damn==0)
        return true;
    return false;
}

static bool ranged_attk(struct permonst *ptr)
{
    register int i, j;
    register int atk_mask = (1 << AT_BREA) | (1 << AT_SPIT) | (1 << AT_GAZE);

    for (i = 0; i < NATTK; i++) {
        if ((j = ptr->mattk[i].aatyp) >= AT_WEAP
            || (j < 32 && (atk_mask & (1 << j)) != 0))
            return true;
    }
    return false;
}

#define has_phys_scaling(ptr)		((ptr)->mflagsf&MF_PHYS_SCALING)

int mstrength(struct permonst * ptr)
{
    int	i, tmp2, n, tmp = ptr->mlevel;
    if(!strcmp(ptr->mname,"freezing sphere"))
        i=0;

    if (tmp > 49)		/* special fixed hp monster */
        tmp = 2 * (tmp - 6) / 4;

    /*	For creation in groups */
    n = (!!(ptr->geno & G_SGROUP));
    n += (!!(ptr->geno & G_LGROUP)) << 1;

    /*	For ranged attacks */
    if (ranged_attk(ptr))
        n++;

    /*	For higher ac values */
	tmp2 = 10-(ptr->nac+ptr->dac+ptr->pac);
	n += (tmp2 < 4);
	n += (tmp2 < 0);
	n += (tmp2 < -5);
	n += (tmp2 < -10);
	n += (tmp2 < -20);

    /*	For very fast monsters */
    n += (ptr->mmove >= 18);

    /*	For each attack and "special" attack */
    for (i = 0; i < NATTK; i++) {
		if(ptr->mlevel < ptr->mattk[i].lev_req)
			continue;

		if(ptr->mattk[i].ins_req > 0)
			continue;

        tmp2 = ptr->mattk[i].aatyp;
        n += (tmp2 > 0);
		n += (tmp2 == AT_MAGC || tmp2 == AT_MMGC ||
			tmp2 == AT_TUCH || tmp2 == AT_TNKR ||
			spirit_rapier_at(tmp2));
		n += (tmp2 == AT_WEAP && (ptr->mflagsb & MB_STRONG));
		if(has_phys_scaling(ptr) &&
		  (ptr->mattk[i].aatyp || ptr->mattk[i].adtyp || ptr->mattk[i].damn || ptr->mattk[i].damd)
		  &&!(
			tmp2 == AT_SPIT
			|| tmp2 == AT_BREA
			|| tmp2 == AT_BRSH
			|| tmp2 == AT_BOOM
			|| tmp2 == AT_GAZE
			|| tmp2 == AT_ARRW
			|| tmp2 == AT_MMGC
			|| tmp2 == AT_TNKR
			|| tmp2 == AT_WDGZ
			|| tmp2 == AT_MAGC
		))
			n += 2;
    }

	/*	For each "special" damage type */
	for (i = 0; i < NATTK; i++) {

		if(ptr->mlevel < ptr->mattk[i].lev_req)
			continue;

		if(ptr->mattk[i].ins_req > 0)
			continue;

		tmp2 = ptr->mattk[i].adtyp;
		if ((tmp2 == AD_DRLI) || (tmp2 == AD_STON) || (tmp2 == AD_DRST)
			|| (tmp2 == AD_DRDX) || (tmp2 == AD_DRCO) || (tmp2 == AD_WERE)
			|| (tmp2 == AD_SVPN)
			|| (tmp2 == AD_SHDW) || (tmp2 == AD_STAR) || (tmp2 == AD_BLUD)
			|| (tmp2 == AD_MOON) || (tmp2 == AD_HOLY) || (tmp2 == AD_UNHY) || (tmp2 == AD_HLUH)
			|| (tmp2 == AD_DETH) || (tmp2 == AD_PEST) || (tmp2 == AD_FAMN) || (tmp2 == AD_CNFT)
			|| (tmp2 == AD_BLAS)
		)
			n += 2;
		else if (strcmp(ptr->mname, "grid bug")) n += (tmp2 != AD_PHYS);
		n += ((int)(ptr->mattk[i].damd * ptr->mattk[i].damn) > 23);
	}

    /*	Leprechauns are special cases.  They have many hit dice so they
	can hit and are hard to kill, but they don't really do much damage. */
    if (!strcmp(ptr->mname, "leprechaun"))
        n -= 2;

	/*	Hooloovoo spawn many dangerous enemies. */
	if (!strcmp(ptr->mname, "hooloovoo")) n += 10;

/*	Some monsters have nonstandard groups that increase difficulty. */
	if (!strcmp(ptr->mname, "arcadian avenger")) n += 1;

	if (!strcmp(ptr->mname, "drow matron")) n += 2;
	if (!strcmp(ptr->mname, "Elvenking")) n += 2;
	if (!strcmp(ptr->mname, "Elvenqueen")) n += 2;
	if (!strcmp(ptr->mname, "chiropteran")) n += 2;

    /*	Finally, adjust the monster level  0 <= n <= 24 (approx.) */
    if (n == 0)
        tmp--;
    else if (n >= 6)
        tmp += (n / 2);
    else
        tmp += (n / 3 + 1);

    return (tmp >= 0) ? tmp : 0;
}

#define TIME_STR_LEN 50
int main()
{
    int x=0;
    int bit=0;
    int attk_no=0;

    std::ofstream fout;

    std::time_t time = std::time({});
    char timeString[TIME_STR_LEN];
    std::strftime(timeString, TIME_STR_LEN,"%Y-%m-%dT%H-%M-%S", std::localtime(&time));
    char fname[120]="mondump";
    std::sprintf(fname,"..\\mondump-%s-dnh.csv",timeString);
    std::cout<<"File name:"<<fname<<std::endl;
    fout.open(fname);

    fout<<"index,namem,namef,namen,symbol,Difficulty Lvl,Move Rate,Armor Class,";
    //     0     1     2     3     4      5              6         7
    fout<<"Magic Resist,Alignment,generation flags,Attack 1,Attack 2,Attack 3,";
    //     8            9         10               11       12       13
    fout<<"Attack 4,Attack 5,Attack 6,Weight,Nutrition,Sound,Size,Resistance,";
    //     14       15       16       17     18        19    20   21
    fout<<"Resist Conveyed,Flags 1,Flags 2,Flags 3,color,Comment,c2,c3,diff,";
    //     22              23      24      25      26    27      28 29 30
    fout<<"diff2,exp,conveyed_prob"<<endl;
    //     31    32  33


    while(mons[x].mname[0]!='\0')
    {
        ///* 0*/fout << x << ",";
        fout << ",";//we ignore index bc it has no purpose
        //* 1*/fout << def_monsyms[mons[x].mlet].sym << ",";
        fout << ",";//male name -- absent
        fout << ",";//female name -- absent

        /* 3 -- name*/
        bool escape_comma=false;
        if(strstr(mons[x].mname,",")!=NULL)
            escape_comma=true;
        if(escape_comma)
            fout<<"\"";
        fout << mons[x].mname;
        if(escape_comma)
            fout<<"\",";
        else
            fout<<",";
        /* 4*/fout << mlet_s[mons[x].mlet] << ",";
        if(mons[x].mlevel>49)
        {
            int hp_sp=2 * (mons[x].mlevel - 6);
            mons[x].mlevel=hp_sp/4;
        }
        /* 5*/fout << (int)mons[x].mlevel << ",";//lvl
        /* 6*/fout << (int)mons[x].mmove << ",";//speed
        /* 7*/fout << 10-((int)mons[x].nac+(int)mons[x].dac+(int)mons[x].pac) << ",";
        /* 8*/fout << (int)mons[x].mr << ",";
        /* 9*/fout << (int)mons[x].maligntyp << ",";//align


        /*10 -- geno*/

        bool flag_found=false;
        int geno_temp=mons[x].geno&(~G_INSTMSK);
        for(bit=4;bit<32;bit++)
        {
            if(geno_temp&(1<<bit))
            {
                if(flag_found==true)
                    fout<<"|";
                fout<<search_dict(geno_s,1<<bit);
                flag_found=true;
            }

        }
        if(flag_found)
            fout <<"|";
        fout << (mons[x].geno&0x7)<<",";//маска генерации

        /*11-16 -- ATTK */

        for(attk_no=0;attk_no<NATTK_DEFAULT;attk_no++)
        {
            if(no_attk(mons[x].mattk[attk_no]))
                fout << "NO_ATTK,";
            else
            {
                fout <<"\"ATTK(";
                fout <<search_dict(at_s,mons[x].mattk[attk_no].aatyp)<<",";
                fout <<search_dict(ad_s,mons[x].mattk[attk_no].adtyp)<<",";
                fout <<(int)mons[x].mattk[attk_no].damn<<",";
                fout <<(int)mons[x].mattk[attk_no].damd<<",";
                fout <<(int)mons[x].mattk[attk_no].lev_req<<",";
                fout <<(int)mons[x].mattk[attk_no].offhand<<",";
                fout <<(int)mons[x].mattk[attk_no].polywep<<",";
                fout <<(int)mons[x].mattk[attk_no].ins_req<<",";
                fout <<(int)mons[x].mattk[attk_no].san_req<<")\",";
            }
        }

        /* 17 -- weight*/
        fout << (int)mons[x].cwt << ",";
        /* 18 -- nutr*/
        fout << (int)mons[x].cnutrit << ",";
        /* 19 -- sound */
        for(bit=0;bit<255;bit++)
        {
            if(mons[x].msound==bit)
            {
                fout<<search_dict(ms_36_s,bit)<<",";
            }
        }
        /* 20 -- size */
        for(bit=0;bit<255;bit++)
        {
            if(mons[x].msize==bit)
            {
                fout<<search_dict(mz_s,bit)<<",";
            }
        }
        /* 21 -- resistances */
        flag_found=false;
        for(bit=0;bit<32;bit++)
        {
            if(mons[x].mresists&(1<<bit))
            {
                if(flag_found==true)
                    fout<<"|";
                fout<<search_dict(mr_s,1<<bit);
                flag_found=true;
            }

        }
        fout<<",";
        /* 22 -- conveys */
        flag_found=false;
        for(bit=0;bit<32;bit++)
        {
            if(mons[x].mconveys&(1<<bit))
            {
                if(flag_found==true)
                    fout<<"|";
                fout<<search_dict(mr_s,1<<bit);
                flag_found=true;
            }

        }
        fout<<",";

        /* 23 -- flags1 got from 8 other flag fields */
        fout << convert_dnh_flags(1,&(mons[x]));
        fout<<",";

        /* 24 -- flags2got from 8 other flag fields */
        fout << convert_dnh_flags(2,&(mons[x]));
        fout<<",";

        /* 25 -- flags3 got from 8 other flag fields  */
        fout << convert_dnh_flags(3,&(mons[x]));
        fout<<",";
        /* 26 -- color */
        fout<<int(mons[x].mcolor)<<",";
        /* 27 -- skip */
        fout<<"-,";
        /* 28 -- skip */
        fout<<"-,";
        /* 29 -- skip */
        fout<<"-,";
        /* 30*/
        fout << mstrength(&(mons[x]))<<",";//in 3.4.3 we have only calculated strength
        /* 31 -- alternate difficulty*/
        fout << mstrength(&(mons[x]))<<",";
        /* 32 -- base exp */
        fout << experience(&(mons[x]))<<",";
        /* 33 -- conveyed probabilities */
        flag_found=false;
        for(bit=0;bit<32;bit++)
        {
            if(mons[x].mconveys&(1<<bit))
            {
                if(1<<bit==MR_STONE)
                    continue;
                if(flag_found==true)
                    fout<<"|";
                char *resist=search_dict(mr_s,1<<bit);
                fout<<get_prob(&(mons[x]),resist);
                flag_found=true;
            }

        }
        if(mons[x].mflagsm&MM_TPORT)
        {
            if(flag_found==true)
                fout<<"|";
            flag_found=true;
            fout<<get_prob(&(mons[x]),"M1_TPORT");
        }

        if(mons[x].mflagsm&MM_TPORT_CNTRL)
        {
            if(flag_found==true)
                fout<<"|";
            flag_found=true;
            fout<<get_prob(&(mons[x]),"M1_TPORT_CNTRL");
        }

        if(mons[x].mflagsv & MV_TELEPATHIC)
        {
            if(flag_found==true)
                fout<<"|";
            flag_found=true;
            fout<<get_prob(&(mons[x]),"Telepathy");
        }
        if(mons[x].mflagsg&MG_DISPLACEMENT)
        {
            if(flag_found==true)
                fout<<"|";
            flag_found=true;
            fout<<get_prob(&(mons[x]),"Displace");
        }

        fout<<",";
        // 34 -- flags4
        fout << convert_dnh_flags(4,&(mons[x]));
        fout<<",";
        // 35 -- mhflags
        flag_found=false;
        for(bit=0;bit<32;bit++)
        {
            if(mons[x].mflagsa&(1<<bit))
            {
                if(flag_found==true)
                    fout<<"|";
                fout<<search_dict(fma_s,1<<bit);
                flag_found=true;
            }
        }
        fout<<",";        // now we are to parse new dNetHack fields

        //36-39 -- 4 more attacks
        for(attk_no=NATTK_DEFAULT;attk_no<NATTK;attk_no++)
        {
            if(no_attk(mons[x].mattk[attk_no]))
                fout << "NO_ATTK,";
            else
            {
                fout <<"\"ATTK(";
                fout <<search_dict(at_s,mons[x].mattk[attk_no].aatyp)<<",";
                fout <<search_dict(ad_s,mons[x].mattk[attk_no].adtyp)<<",";
                fout <<(int)mons[x].mattk[attk_no].damn<<",";
                fout <<(int)mons[x].mattk[attk_no].damd<<",";
                fout <<(int)mons[x].mattk[attk_no].lev_req<<",";
                fout <<(int)mons[x].mattk[attk_no].offhand<<",";
                fout <<(int)mons[x].mattk[attk_no].polywep<<",";
                fout <<(int)mons[x].mattk[attk_no].ins_req<<")\",";
            }
        }
        //40-42 -- new AC
        fout<<(int)mons[x].nac<<",";
        fout<<(int)mons[x].dac<<",";
        fout<<(int)mons[x].pac<<",";
        //43-47 -- base DR
        fout<<(int)mons[x].hdr<<",";
        fout<<(int)mons[x].bdr<<",";
        fout<<(int)mons[x].gdr<<",";
        fout<<(int)mons[x].ldr<<",";
        fout<<(int)mons[x].fdr<<",";
        //48-52 -- special DR
        fout<<(int)mons[x].spe_hdr<<",";
        fout<<(int)mons[x].spe_bdr<<",";
        fout<<(int)mons[x].spe_gdr<<",";
        fout<<(int)mons[x].spe_ldr<<",";
        fout<<(int)mons[x].spe_fdr<<",";
        //53 -- insight
        fout<<(int)(G_C_INST(mons[x].geno))<<",";
        //54 -- light radius
        fout<<(int)mons[x].light_radius;


        fout << endl;


        x++;
        if (strcmp(mons[x].mname,"kobold zombie")==0)
            cout<<"";
        fout.flush();
    }
    fout.close();
    cout<<x<<" monsters dumped\n";
    return 0;
}
