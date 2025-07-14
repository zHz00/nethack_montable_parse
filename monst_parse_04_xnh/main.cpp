#include <iostream>
#include <fstream>
#include <cstdlib>
#define uchar unsigned char
#define schar signed char
#define NEARDATA
#include <cstring>
#include <ctime>
#include <locale>
using namespace std;
typedef unsigned char boolean;

#define MAIL_STRUCTURES
#define TEXTCOLOR

//#include "config.h"
#include "monsym.h"
#include "permonst.h"

#define NO_ATTK    \
    {              \
        0, 0, 0, 0 \
    }




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

char mlet_s[][40]={
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
"S_ANGEL",
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
"S_GOLEM",
"S_DEMON",
"S_EEL",
"S_LIZARD",
"S_WORM_TAIL",
"S_MIMIC_DEF"
};

struct dict_s
{

    char value[40];
    unsigned int key;
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
{"MR2_SEE_INVIS", 0x0100},
{"MR2_LEVITATE", 0x0200 },
{"MR2_WATERWALK", 0x0400},
{"MR2_MAGBREATH", 0x0800},
{"MR2_DISPLACED", 0x1000},
{"MR2_STRENGTH", 0x2000 },
{"MR2_FUMBLING", 0x4000 },




{"",0}

};
struct dict_s f1_s[]=
{
{"M1_FLY",0x00000001L},
{"M1_SWIM",0x00000002L},
{"M1_AMORPHOUS",0x00000004L},
{"M1_WALLWALK",0x00000008L},
{"M1_CLING",0x00000010L},
{"M1_TUNNEL",0x00000020L},
{"M1_NEEDPICK",0x00000040L},
{"M1_CONCEAL",0x00000080L},
{"M1_HIDE",0x00000100L},
{"M1_AMPHIBIOUS",0x00000200L},
{"M1_BREATHLESS",0x00000400L},
{"M1_NOTAKE",0x00000800L},
{"M1_NOEYES",0x00001000L},
{"M1_NOHANDS",0x00002000L},
{"M1_NOLIMBS",0x00004000L},//{"M1_NOLIMBS",0x00006000L},
{"M1_NOHEAD",0x00008000L},
{"M1_MINDLESS",0x00010000L},
{"M1_HUMANOID",0x00020000L},
{"M1_ANIMAL",0x00040000L},
{"M1_SLITHY",0x00080000L},
{"M1_UNSOLID",0x00100000L},
{"M1_THICK_HIDE",0x00200000L},
{"M1_OVIPAROUS",0x00400000L},
{"M1_REGEN",0x00800000L},
{"M1_SEE_INVIS",0x01000000L},
{"M1_TPORT",0x02000000L},
{"M1_TPORT_CNTRL",0x04000000L},
{"M1_ACID",0x08000000L},
{"M1_POIS",0x10000000L},
{"M1_CARNIVORE",0x20000000L},
{"M1_HERBIVORE",0x40000000L},
//{"M1_OMNIVORE",0x60000000L},
{"M1_METALLIVORE",0x80000000UL},
{"",0}

};

struct dict_s f2_s[]=
{
{"M2_NOPOLY",0x00000001L},
{"M2_UNDEAD",0x00000002L},
{"M2_WERE",0x00000004L},
{"M2_HUMAN",0x00000008L},
{"M2_ELF",0x00000010L},
{"M2_DWARF",0x00000020L},
{"M2_GNOME",0x00000040L},
{"M2_ORC",0x00000080L},
{"M2_DEMON",0x00000100L},
{"M2_MERC",0x00000200L},
{"M2_LORD",0x00000400L},
{"M2_PRINCE",0x00000800L},
{"M2_MINION",0x00001000L},
{"M2_GIANT",0x00002000L},
{"M2_SHAPESHIFTER",0x00004000L},
{"M2_MALE",0x00010000L},
{"M2_FEMALE",0x00020000L},
{"M2_NEUTER",0x00040000L},
{"M2_PNAME",0x00080000L},
{"M2_HOSTILE",0x00100000L},
{"M2_PEACEFUL",0x00200000L},
{"M2_DOMESTIC",0x00400000L},
{"M2_WANDER",0x00800000L},
{"M2_STALK",0x01000000L},
{"M2_NASTY",0x02000000L},
{"M2_STRONG",0x04000000L},
{"M2_ROCKTHROW",0x08000000L},
{"M2_GREEDY",0x10000000L},
{"M2_JEWELS",0x20000000L},
{"M2_COLLECT",0x40000000L},
{"M2_MAGIC",0x80000000UL},
{"",0}

};

struct dict_s f3_s[]=
{
    {"M3_WANTSAMUL",0x0001},
{"M3_WANTSBELL",0x0002},
{"M3_WANTSBOOK",0x0004},
{"M3_WANTSCAND",0x0008},
{"M3_WANTSARTI",0x0010},
//{"M3_WANTSALL",0x001f},
{"M3_WAITFORU",0x0040},
{"M3_CLOSE",0x0080},
//{"M3_COVETOUS",0x001f},
//{"M3_WAITMASK",0x00c0},
{"M3_INFRAVISION",0x0100},
{"M3_INFRAVISIBLE",0x0200},
{"M3_DISPLACES",0x0400},
{"M3_NONCORPOREAL",0x0800},
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
{"MS_GURGLE",12},
{"MS_BURBLE",13},
{"MS_ANIMAL",13},
{"MS_SHRIEK",15},
{"MS_BONES",16},
{"MS_LAUGH",17},
{"MS_MUMBLE",18},
{"MS_IMITATE",19},
{"MS_HUMANOID",20},
{"MS_ARREST",21},
{"MS_SOLDIER",22},
{"MS_GUARD",23},
{"MS_DJINNI",24},
{"MS_NURSE",25},
{"MS_SEDUCE",26},
{"MS_VAMPIRE",27},
{"MS_BRIBE",28},
{"MS_CUSS",29},
{"MS_RIDER",30},
{"MS_LEADER",31},
{"MS_NEMESIS",32},
{"MS_GUARDIAN",33},
{"MS_SELL",34},
{"MS_ORACLE",35},
{"MS_PRIEST",36},
{"MS_SPELL",37},
{"MS_WERE",38},
{"MS_BOAST",39},
{"MS_FERRY",40},
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
{"MS_TROLL",45}

};

struct dict_s geno_s[]=
{
    {"G_UNIQ",0x1000},
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
{"AT_SPIT",8},
{"AT_ENGL",9},
{"AT_BREA",10},
{"AT_EXPL",11},
{"AT_BOOM",12},
{"AT_GAZE",13},
{"AT_TENT",14},
{"AT_WEAP",15},
{"AT_MAGC",16},
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
{"AD_CURS",43},
{"AD_POLY",44},
{"AD_PITS",45},
{"AD_WTHR",46},
{"AD_CLRC",47},
{"AD_SPEL",48},
{"AD_RBRE",49},
{"AD_SAMU",50},
{"",0}
};

char *get_prob(struct permonst *m,char *resist)
{
    static char res[80];
    float d=15.0;
    float prob=-1.0;
    if(strcmp(resist,"MR_ACID")==0)
    {
        d=3.0;
    }
    if(strcmp(resist,"MR_STONE")==0)
    {
        d=6.0;
    }
    if(strcmp(resist,"MR_POISON")==0)
    {
        if ((strcmp(m->pmnames[NEUTRAL],"killer bee")==0)||(strcmp(m->pmnames[NEUTRAL],"scorpion")==0))
        {
            prob=0.25*(1.0/*100%*/)+0.75*(m->mlevel/15.0);
            goto skip;
        }
        else
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
        if
            (
                (strcmp(m->pmnames[NEUTRAL],"floating eye")==0)||
                (strcmp(m->pmnames[NEUTRAL],"mind flayer")==0)||
                (strcmp(m->pmnames[NEUTRAL],"master mind flayer")==0)
            )
            d=1.0;
        else
            d=20.0;
    }
    prob=m->mlevel/d;
skip:
    prob*=100.0;
    if(prob>100.0)
        prob=100.0;
    sprintf(res,"%s=%2.0f",resist,prob);
    return res;

}

int
experience(struct permonst *ptr)
{
    int i, tmp, tmp2;

    tmp = 1 + ptr->mlevel*ptr->mlevel;

    /*  For higher ac values, give extra experience */
    if ((i =ptr->ac) < 3)
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
            else if (tmp2 == AT_MAGC)
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
    if ((ptr->mflags2) & M2_NASTY)
        tmp += (7 * ptr->mlevel);

    /*  For higher level monsters, an additional bonus is given */
    if (ptr->mlevel > 8)
        tmp += 50;

    /* Mail daemons put up no fight. */
    if (strcmp(ptr->pmnames[2],"mail daemon")==0)
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

struct class_sym {
    char sym;
    const char *name;
    const char *explain;
};


//void NDECL(monst_init);
/*
 *      Entry Format:   (from permonst.h)
 *
 *      name, symbol (S_* defines),
 *      base monster level, move rate, armor class, magic resistance,
 *      alignment, creation/geno flags (G_* defines),
 *      6 * attack structs ( type , damage-type, # dice, # sides ),
 *      weight (WT_* defines), nutritional value, extension length,
 *      sounds made (MS_* defines), physical size (MZ_* defines),
 *      resistances, resistances conferred (both MR_* defines),
 *      3 * flag bitmaps (M1_*, M2_*, and M3_* defines respectively),
 *      difficulty, symbol color (C(x) macro)
 *
 *      For AT_BREA attacks, '# sides' is ignored; 6 is used for most
 *      damage types, 25 for sleep, not applicable for death or poison.
 */

/* monster type with single name */
#define MON(nam, sym, lvl, gen, atk, siz, mr1, mr2, \
            flg1, flg2, flg3, d, col, bn)           \
    {                                                                   \
        nam, PM_##bn,                                                   \
        sym, lvl, gen, atk, siz, mr1, mr2, flg1, flg2, flg3, d, col     \
    }

/* LVL() and SIZ() collect several fields to cut down on number of args
 * for MON().  Using more than 15 would fail to conform to the C Standard.
 * ATTK() and A() are to avoid braces and commas within args to MON().
 * NAM() and NAMS() are used for both reasons.
 */
#define NAM(name) { (const char *) 0, (const char *) 0, name }
#define NAMS(namm, namf, namn) { namm, namf, namn }
#define LVL(lvl, mov, ac, mr, aln) lvl, mov, ac, mr, aln
#define SIZ(wt, nut, snd, siz) wt, nut, snd, siz
#define ATTK(at, ad, n, d) { at, ad, n, d }
#define A(a1, a2, a3, a4, a5, a6) { a1, a2, a3, a4, a5, a6 }

/*
 *      Rule #1:        monsters of a given class are contiguous in the
 *                      mons[] array.
 *
 *      Rule #2:        monsters of a given class are presented in ascending
 *                      order of strength.
 *
 *      Rule #3:        monster frequency is included in the geno mask;
 *                      the frequency can be from 0 to 7.  0's will also
 *                      be skipped during generation.
 *
 *      Rule #4:        monster subclasses (e.g. giants) should be kept
 *                      together, unless it violates Rule 2.  NOGEN monsters
 *                      won't violate Rule 2.
 *
 * Guidelines for color assignment:
 *
 *      * Use the same color for all `growth stages' of a monster (ex.
 *        little dog/big dog, baby naga/full-grown naga.
 *
 *      * Use colors given in names wherever possible. If the class has `real'
 *        members with strong color associations, use those.
 *
 *      * Favor `cool' colors for cold-resistant monsters, `warm' ones for
 *        fire-resistant ones.
 *
 *      * Try to reserve purple (magenta) for powerful `ruler' monsters (queen
 *        bee, kobold lord, &c.).
 *
 *      * Subject to all these constraints, try to use color to make as many
 *        distinctions as the / command (that is, within a monster letter
 *        distinct names should map to distinct colors).
 *
 * The aim in assigning colors is to be consistent enough so a player can
 * become `intuitive' about them, deducing some or all of these rules
 * unconsciously. Use your common sense.
 */

#ifndef SPLITMON_2
NEARDATA struct permonst mons[] = {
    /*
     * ants
     */
#include "monsters.h"
    /*
     * array terminator
     */
#undef MON
#define MON(nam, sym, lvl, gen, atk, siz, mr1, mr2, \
            flg1, flg2, flg3, d, col, bn)           \
    {                                                                   \
        nam, NON_PM,                                                    \
        sym, lvl, gen, atk, siz, mr1, mr2, flg1, flg2, flg3, d, col     \
    }
    MON(NAM(""), 0,
        LVL(0, 0, 0, 0, 0), G_NOGEN | G_NOCORPSE,
        A(NO_ATTK, NO_ATTK, NO_ATTK, NO_ATTK, NO_ATTK, NO_ATTK),
        SIZ(0, 0, 0, 0), 0, 0,
        0L,  M2_NOPOLY, 0,
        0, 0, 0),
};
#endif /* !SPLITMON_1 */

#ifndef SPLITMON_1
/* dummy routine used to force linkage */
void
monst_init()
{
    return;
}

const struct attack sa_yes[NATTK] = SEDUCTION_ATTACKS_YES;
const struct attack sa_no[NATTK] = SEDUCTION_ATTACKS_NO;
#endif

/*monst.c*/

bool no_attk(struct attack a)
{
    if(a.aatyp==0&&a.adtyp==0&&a.damd==0&&a.damn==0)
        return true;
    return false;
}

#define DISTANCE_ATTK_TYPE(atyp) ((atyp) == AT_SPIT \
                                  || (atyp) == AT_BREA \
                                  || (atyp) == AT_MAGC \
                                  || (atyp) == AT_GAZE)

static bool ranged_attk(struct permonst *ptr)
{
    int i;

    for (i = 0; i < NATTK; i++)
        if (DISTANCE_ATTK_TYPE(ptr->mattk[i].aatyp))
            return true;
    return false;
}

int mstrength(struct permonst * ptr)
{
    int	i, tmp2, n, tmp = ptr->mlevel;
    if(!strcmp(ptr->pmnames[NEUTRAL],"freezing sphere"))
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
    n += (ptr->ac < 4);
    n += (ptr->ac < 0);

    /*	For very fast monsters */
    n += (ptr->mmove >= 18);

    /*	For each attack and "special" attack */
    for (i = 0; i < NATTK; i++) {
        tmp2 = ptr->mattk[i].aatyp;
        n += (tmp2 > 0);
        n += (tmp2 == AT_MAGC);
        n += (tmp2 == AT_WEAP && (ptr->mflags2 & M2_STRONG));
    }

    /*	For each "special" damage type */
    for (i = 0; i < NATTK; i++) {
        tmp2 = ptr->mattk[i].adtyp;
        if ((tmp2 == AD_DRLI) || (tmp2 == AD_STON) || (tmp2 == AD_DRST)
            || (tmp2 == AD_DRDX) || (tmp2 == AD_DRCO) || (tmp2 == AD_WERE))
            n += 2;
        else if (strcmp(ptr->pmnames[NEUTRAL], "grid bug"))
            n += (tmp2 != AD_PHYS);
        n += ((int) (ptr->mattk[i].damd * ptr->mattk[i].damn) > 23);
    }

    /*	Leprechauns are special cases.  They have many hit dice so they
	can hit and are hard to kill, but they don't really do much damage. */
    if (!strcmp(ptr->pmnames[NEUTRAL], "leprechaun"))
        n -= 2;

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
    std::sprintf(fname,"..\\mondump-%s-xnh9.csv",timeString);
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

    while(mons[x].pmnames[NEUTRAL][0]!='\0')
    {
        ///* 0*/fout << x << ",";
        fout << ",";//we ignore index bc it has no purpose
        //* 1*/fout << def_monsyms[mons[x].mlet].sym << ",";
        if(mons[x].pmnames[MALE]!=NULL)
        /* 1*/fout << mons[x].pmnames[MALE];
        fout << ",";
        if(mons[x].pmnames[FEMALE]!=NULL)
        /* 2*/fout << mons[x].pmnames[FEMALE];
        fout << ",";
        /* 3*/fout << mons[x].pmnames[NEUTRAL] << ",";
        /* 4*/fout << mlet_s[mons[x].mlet] << ",";
        if(mons[x].mlevel>49)
        {
            int hp_sp=2 * (mons[x].mlevel - 6);
            mons[x].mlevel=hp_sp/4;
        }
        /* 5*/fout << (int)mons[x].mlevel << ",";//lvl
        /* 6*/fout << (int)mons[x].mmove << ",";//speed
        /* 7*/fout << (int)mons[x].ac << ",";
        /* 8*/fout << (int)mons[x].mr << ",";
        /* 9*/fout << (int)mons[x].maligntyp << ",";//align


        /*10 -- geno*/

        bool flag_found=false;
        for(bit=4;bit<32;bit++)
        {
            if(mons[x].geno&(1<<bit))
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

        for(attk_no=0;attk_no<NATTK;attk_no++)
        {
            if(no_attk(mons[x].mattk[attk_no]))
                fout << "NO_ATTK,";
            else
            {

                fout <<"\"ATTK(";
                fout <<search_dict(at_s,mons[x].mattk[attk_no].aatyp)<<",";
                fout <<search_dict(ad_s,mons[x].mattk[attk_no].adtyp)<<",";
                fout <<(int)mons[x].mattk[attk_no].damn<<",";
                fout <<(int)mons[x].mattk[attk_no].damd<<")\",";
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
                fout<<search_dict(ms_s,bit)<<",";
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

        /* 23 -- flags1 */
        flag_found=false;
        for(bit=0;bit<32;bit++)
        {
            if(mons[x].mflags1&(1<<bit))
            {
                if(flag_found==true)
                    fout<<"|";
                fout<<search_dict(f1_s,1<<bit);
                flag_found=true;
            }

        }
        fout<<",";

        /* 24 -- flags2 */
        flag_found=false;
        for(bit=0;bit<32;bit++)
        {
            if(mons[x].mflags2&(1<<bit))
            {
                if(flag_found==true)
                    fout<<"|";
                fout<<search_dict(f2_s,1<<bit);
                flag_found=true;
            }

        }
        fout<<",";

        /* 25 -- flags3 */
        flag_found=false;
        for(bit=0;bit<32;bit++)
        {
            if(mons[x].mflags3&(1<<bit))
            {
                if(flag_found==true)
                    fout<<"|";
                fout<<search_dict(f3_s,1<<bit);
                flag_found=true;
            }

        }
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
        fout << (int)mons[x].difficulty<<",";
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
                if(flag_found==true)
                    fout<<"|";
                char *resist=search_dict(mr_s,1<<bit);
                fout<<get_prob(&(mons[x]),resist);
                flag_found=true;
            }

        }
        if(mons[x].mflags1&M1_TPORT)
        {
            if(flag_found==true)
                fout<<"|";
            flag_found=true;
            fout<<get_prob(&(mons[x]),"M1_TPORT");
        }

        if(mons[x].mflags1&M1_TPORT_CNTRL)
        {
            if(flag_found==true)
                fout<<"|";
            flag_found=true;
            fout<<get_prob(&(mons[x]),"M1_TPORT_CNTRL");
        }

        if
            (
                strcmp(mons[x].pmnames[NEUTRAL],"floating eye")==0||
                strcmp(mons[x].pmnames[NEUTRAL],"mind flayer")==0||
                strcmp(mons[x].pmnames[NEUTRAL],"master mind flayer")==0||
                strcmp(mons[x].pmnames[NEUTRAL],"orc shaman")==0||
                strcmp(mons[x].pmnames[NEUTRAL],"kobold shaman")==0||
                strcmp(mons[x].pmnames[NEUTRAL],"gnomish wizard")==0
            )
        {
            if(flag_found==true)
                fout<<"|";
            flag_found=true;
            fout<<get_prob(&(mons[x]),"Telepathy");
        }

        fout << endl;


        x++;
        if (strcmp(mons[x].pmnames[2],"ghost")==0)
            cout<<"";
        fout.flush();
    }
    fout.close();
    cout<<x<<" monsters dumped\n";
    return 0;
}
