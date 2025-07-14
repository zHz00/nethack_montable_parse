#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <locale>
using namespace std;
typedef unsigned char boolean;

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
{"AT_SPIT",10},
{"AT_ENGL",11},
{"AT_BREA",12},
{"AT_EXPL",13},
{"AT_BOOM",14},
{"AT_GAZE",15},
{"AT_TENT",16},
{"AT_WEAP",254},
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
{"AD_CLRC",240},
{"AD_SPEL",241},
{"AD_RBRE",242},
{"AD_SAMU",252},
{"AD_CURS",253},
{"AD_POLY",43},
{"AD_CNCL",44},
{"",0}
};

char *get_prob(struct permonst *m,char *resist)
{
    static char res[80];
    float d=15.0;
    float prob=-1.0;
    /*if(strcmp(resist,"MR_ACID")==0)
    {
        d=3.0;
    }
    if(strcmp(resist,"MR_STONE")==0)
    {
        d=3.0;
    }*/ //only in 3.7.0+
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

/* returns True if monster can attack at range */
boolean
ranged_attk(struct permonst *ptr)
{
    register int i, atyp;
    long atk_mask = (1L << AT_BREA) | (1L << AT_SPIT) | (1L << AT_GAZE);

    /* was: (attacktype(ptr, AT_BREA) || attacktype(ptr, AT_WEAP)
     *       || attacktype(ptr, AT_SPIT) || attacktype(ptr, AT_GAZE)
     *       || attacktype(ptr, AT_MAGC));
     * but that's too slow -dlc
     */
    for (i = 0; i < NATTK; i++) {
        atyp = ptr->mattk[i].aatyp;
        if (atyp >= AT_WEAP)
            return true;
        /* assert(atyp < 32); */
        if ((atk_mask & (1L << atyp)) != 0L)
            return true;
    }
    return false;
}

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
        else if (strcmp(ptr->mname, "grid bug"))
            n += (tmp2 != AD_PHYS);
        n += ((int) (ptr->mattk[i].damd * ptr->mattk[i].damn) > 23);
    }

    /*	Leprechauns are special cases.  They have many hit dice so they
	can hit and are hard to kill, but they don't really do much damage. */
    if (!strcmp(ptr->mname, "leprechaun"))
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
    std::sprintf(fname,"..\\mondump-%s-nh367.csv",timeString);
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
        /* 3*/fout << mons[x].mname<< ",";
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
                if((1<<bit)==MR_STONE||(1<<bit)==MR_ACID)
                    continue;//stone and acid resistances conveyed are not implemented in 3.4.3/un6
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
                if((1<<bit)==MR_STONE||(1<<bit)==MR_ACID)
                    continue;//stone and acid resistances conveyed are not implemented in 3.6.x
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

        if(strcmp(mons[x].mname,"floating eye")==0||strcmp(mons[x].mname,"mind flayer")==0||strcmp(mons[x].mname,"master mind flayer")==0)
        {
            if(flag_found==true)
                fout<<"|";
            flag_found=true;
            fout<<get_prob(&(mons[x]),"Telepathy");
        }

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
