#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "monsym.h"
#include "monattk.h"
#include "permonst.h"
#include "pm.h"
#include "wards.h"

#define boolean int
#define FALSE 0
#define TRUE 1



struct attack *
dmgtype_fromattack(ptr, dtyp, atyp)
struct permonst *ptr;
int dtyp, atyp;
{
    struct attack *a;

    for (a = &ptr->mattk[0]; a < &ptr->mattk[NATTK]; a++)
	if (a->adtyp == dtyp && (atyp == AT_ANY || a->aatyp == atyp))
	    return a;

    return (struct attack *)0;
}

boolean
dmgtype(ptr, dtyp)
struct permonst *ptr;
int dtyp;
{
    return dmgtype_fromattack(ptr, dtyp, AT_ANY) ? TRUE : FALSE;
}

#define rn2(x) 0
#define d(x,y) 1

#define is_primordial(ptr)	(((ptr)->mflagsa & MA_PRIMORDIAL) != 0L)

#define is_were(ptr)		(((ptr)->mflagsa & MA_WERE) != 0L)

#define is_elf(ptr)			(((ptr)->mflagsa & MA_ELF) != 0L && !is_drow(ptr))
#define is_drow(ptr)		(((ptr)->mflagsa & MA_DROW) != 0L)
#define is_myrkalfr(ptr)	((ptr)->mtyp == PM_MYRKALFAR_WARRIOR || (ptr)->mtyp == PM_MYRKALFAR_MATRON || (ptr)->mtyp == PM_MYRKALFR || (ptr)->mtyp == PM_ALIDER)
#define is_dwarf(ptr)		(((ptr)->mflagsa & MA_DWARF) != 0L)
#define is_gnome(ptr)		(((ptr)->mflagsa & MA_GNOME) != 0L)
#define is_gizmo(ptr)		((ptr)->mlet == S_GNOME && is_clockwork(ptr))
#define is_szcultist(ptr)		((ptr)->mtyp == PM_SHATTERED_ZIGGURAT_CULTIST \
								|| (ptr)->mtyp == PM_SHATTERED_ZIGGURAT_KNIGHT \
								|| (ptr)->mtyp == PM_SHATTERED_ZIGGURAT_WIZARD)
#define is_orc(ptr)		(((ptr)->mflagsa & MA_ORC) != 0L)
#define is_ogre(ptr)		((ptr)->mlet == S_OGRE)
#define is_troll(ptr)		((ptr)->mlet == S_TROLL)
#define is_kobold(ptr)		((ptr)->mlet == S_KOBOLD)
#define is_ettin(ptr)		((ptr)->mtyp == PM_ETTIN)
#define is_human(ptr)		(((ptr)->mflagsa & MA_HUMAN) != 0L)


#define is_angel(ptr)		((((ptr)->mflagsa & MA_MINION) != 0L) && ((ptr)->mlet == S_LAW_ANGEL || (ptr)->mlet == S_NEU_ANGEL || (ptr)->mlet == S_CHA_ANGEL))

#define is_undead(ptr)		(((ptr)->mflagsa & MA_UNDEAD) != 0L)

#define is_keter(ptr)		((ptr)->mlet == S_KETER)

#define is_golem(ptr)		((ptr)->mlet == S_GOLEM)

#define is_demon(ptr)		(((ptr)->mflagsa & MA_DEMON) != 0L)

#define is_great_old_one(ptr)	(((ptr)->mflagsa & MA_G_O_O) != 0L)

#define mindless(ptr)		(((ptr)->mflagst & MT_MINDLESS) != 0L || ((ptr)->mflagst & MT_DETACHED) != 0L || 0/*on_level(&valley_level, &u.uz)*/)


#define is_auton(ptr)		(	(ptr)->mtyp == PM_MONOTON ||\
								(ptr)->mtyp == PM_DUTON ||\
								(ptr)->mtyp == PM_TRITON ||\
								(ptr)->mtyp == PM_QUATON ||\
								(ptr)->mtyp == PM_QUINON ||\
								(ptr)->mtyp == PM_AXUS\
                        )

#define is_molochan(ptr)	((ptr)->maligntyp == MON_A_NONE)
#define is_voidalign(ptr)	((ptr)->maligntyp == MON_A_VOID)

#define is_lawful(ptr)		((ptr)->maligntyp > A_NEUTRAL && !is_molochan(ptr) && !is_voidalign(ptr))
#define is_lawful_mon(mon) is_lawful((mon))
#define is_neutral(ptr)		((ptr)->maligntyp == A_NEUTRAL)
#define is_neutral_mon(mon)  is_neutral((mon))
#define is_chaotic(ptr)		((ptr)->maligntyp < A_NEUTRAL && !is_molochan(ptr) && !is_voidalign(ptr))
#define is_chaotic_mon(mon)	  is_chaotic((mon))


#define is_minion(ptr)		((ptr)->mflagsa & MA_MINION)

#define is_lminion(mon)		(is_minion((mon)) && is_lawful_mon(mon))

#define is_nminion(mon)		(is_minion((mon)) && is_neutral_mon(mon))

#define is_cminion(mon)		(is_minion((mon)) && is_chaotic_mon(mon))

#define is_bird(ptr)		(((ptr)->mflagsa & MA_AVIAN) != 0L)

#define is_bat(ptr)		((ptr)->mtyp == PM_BAT || \
				 (ptr)->mtyp == PM_GIANT_BAT || \
				 (ptr)->mtyp == PM_BATTLE_BAT || \
				 (ptr)->mtyp == PM_WARBAT || \
				 (ptr)->mtyp == PM_VAMPIRE_BAT)
#define is_thief(ptr)		( dmgtype(ptr, AD_SGLD)  || dmgtype(ptr, AD_SITM) || dmgtype(ptr, AD_SEDU) )
#define is_rider(ptr)		((ptr)->mflagsg & MG_RIDER)


#define standardUnwardable(mtmp) (mtmp->mtyp==PM_SHOPKEEPER || mtmp->mtyp==PM_WIZARD_OF_YENDOR || is_rider(mtmp))

#define	wingWarded(data)	(data->mlet == S_COCKATRICE \
			|| data->mlet == S_RODENT \
			|| data->mlet == S_NAGA \
			|| data->mlet == S_SNAKE \
			|| data->mlet == S_LIZARD \
			|| data->mtyp == PM_TOVE \
			|| data->mtyp == PM_KRAKEN \
		)

#define	catWarded(data)	(is_bird(data) \
			|| is_bat(data) \
			|| data->mlet == S_RODENT \
			|| data->mlet == S_SNAKE \
			|| data->mlet == S_SPIDER \
			|| data->mlet == S_EEL \
			|| data->mlet == S_LIZARD \
			|| data->mtyp == PM_TOVE \
		)

#define	touWarded(data)	(data->mlet == S_DOG || data->mlet == S_FELINE)

#define	dreWarded(data)	(is_bird(data)\
			|| is_bat(data) \
			|| data->mlet == S_QUADRUPED \
			|| data->mlet == S_UNICORN \
		)

#define	veiWarded(data)	(data->mlet == S_EEL)

#define	thjWarded(data)	(data->mlet == S_LEPRECHAUN \
			|| data->mlet == S_NYMPH \
			|| is_thief(data) \
		)

#define	queenWarded(data)	(data->mlet == S_ANT \
			|| data->mlet == S_XAN \
			|| data->mlet == S_SPIDER \
			|| data->mlet == S_RUSTMONST \
		)

#define	eeyeWarded(data)	( \
			jsjk;sfdlksakslakldskkflskals \
		)

#define	hamWarded(data)	(is_auton(data) \
			|| data->mtyp == PM_FLOATING_EYE \
			|| data->mtyp == PM_BEHOLDER \
			|| data->mtyp == PM_APHANACTONAN_ASSESSOR \
			|| data->mtyp == PM_EYE_OF_DOOM \
			|| data->mtyp == PM_MANY_EYED_SEEKER \
			|| data->mtyp == PM_GROTESQUE_PEEPER \
			|| data->mtyp == PM_JRT_NETJER \
			|| data->mtyp == PM_YOCHLOL \
			|| data->mtyp == PM_TRUTH_SEER \
			|| data->mtyp == PM_DREAM_EATER \
			|| data->mtyp == PM_PARASITIZED_DOLL \
		)

#define	hexWarded(data)	((is_minion(data) \
			|| data->mtyp == PM_HELL_HOUND \
			|| data->mtyp == PM_HELL_HOUND_PUP \
			|| data->mtyp == PM_EYE_OF_DOOM \
			|| data->mtyp == PM_SON_OF_TYPHON \
			|| is_golem(data) \
			|| is_angel(data) \
			|| is_keter(data) \
			|| data->mlet == S_QUANTMECH \
			|| data->mlet == S_IMP \
			|| is_demon(data) \
		) && !( \
			(data->mtyp == PM_CHOKHMAH_SEPHIRAH) || \
			(data->mtyp == PM_ELDER_PRIEST) || \
			(data->mtyp == PM_GREAT_CTHULHU) \
		))

#define	pentWarded(data)	((is_demon(data) \
			|| data->mtyp == PM_HELL_HOUND \
			|| data->mtyp == PM_HELL_HOUND_PUP \
			|| data->mtyp == PM_GARGOYLE \
			|| data->mtyp == PM_WINGED_GARGOYLE \
			|| data->mtyp == PM_DJINNI \
			|| data->mtyp == PM_SANDESTIN \
			|| data->mtyp == PM_SALAMANDER \
			|| data->mlet == S_ELEMENTAL \
			|| data->mlet == S_IMP \
		) && !( \
			(data->mtyp == PM_CHOKHMAH_SEPHIRAH) || \
			(data->mtyp == PM_ELDER_PRIEST) || \
			(data->mtyp == PM_GREAT_CTHULHU) \
		))

#define	circleWarded(data)	((data->mtyp == PM_CERBERUS || is_undead(data)) \
			&& !(mtmp->mtyp == PM_MAANZECORIAN))

#define gorgUnwardable(mtmp)	(standardUnwardable(mtmp) || is_lminion(mtmp) || mtmp->mtyp == PM_ANGEL)

#define	gorgWarded(data)	(!mindless(data) \
			&& !is_great_old_one(data) \
			&& (data->mtyp != PM_CHOKHMAH_SEPHIRAH) \
			&& (data->mtyp != PM_ELDER_PRIEST) \
			&& (data->mtyp != PM_LUGRIBOSSK) \
			&& (data->mtyp != PM_MAANZECORIAN) \
		)

#define heptUnwardable(mtmp)	(standardUnwardable(mtmp) || 0/*!! mtmp->isgd*/ || is_lminion(mtmp) || mtmp->mtyp == PM_ANGEL || 0/*mtmp->mpeaceful*/)

#define	heptWarded(data)	(( !(is_human(data) || is_elf(data) \
			|| is_drow(data) || is_dwarf(data) \
			|| is_gnome(data) || is_orc(data)) \
			|| is_undead(data) || is_were(data) \
		) && !( \
			data->mtyp == PM_CHOKHMAH_SEPHIRAH \
		))

#define yellowUnwardable(mtmp)	(standardUnwardable(mtmp) || 0/*mtmp->mpeaceful*/ || (mtmp->mtyp == PM_STRANGER) || (mtmp->mtyp == PM_SUZERAIN) || (mtmp->mtyp == PM_ELDER_PRIEST) || 0/*(has_template(mtmp, YELLOW_TEMPLATE))*/)

#define	yellowWarded(data)	(!heptWarded(data) && !is_undead(data) && !is_were(data) && !is_primordial(data) )

#define catWardInactive FALSE


boolean
scaryWings(complete, mtmp)
int complete;
struct permonst *mtmp;
{
	if(complete <= 0) return FALSE;
	if(standardUnwardable(mtmp))
		return FALSE;
	return 	wingWarded(mtmp)*100;
}

boolean
scaryCat(complete, mtmp)
int complete;
struct permonst *mtmp;
{
	if(complete <= 0) return FALSE;
	if(standardUnwardable(mtmp) || catWardInactive)
		return FALSE;
	else if(mtmp->mlet == S_FELINE){ /* && mvitals[PM_KITTEN].died == 0*/
            //PACIFY
		return 255;//PACIFY
	}
	return 	catWarded(mtmp)*100;//100%
}

boolean
scaryTou(int complete,struct permonst *mtmp)
{
	if(standardUnwardable(mtmp))
			return FALSE;
	return 	touWarded(mtmp)*100;
}

boolean
scaryDre(int complete,struct permonst *mtmp)
{
	if(standardUnwardable(mtmp))
		return FALSE;
	return 	dreWarded(mtmp)*100;
}
boolean
scaryVei(int complete,struct permonst *mtmp)
{
	if(standardUnwardable(mtmp))
		return FALSE;
	return 	veiWarded(mtmp)*100;
}
boolean
scaryThj(int complete,struct permonst *mtmp)
{
	if(standardUnwardable(mtmp))
		return FALSE;
	return 	thjWarded(mtmp)*100;
}

boolean
scaryQueen(complete, mtmp)
int complete;
struct permonst *mtmp;
{
	if(complete <= 0) return FALSE;
	if(standardUnwardable(mtmp))
		return FALSE;
	return 	queenWarded(mtmp)*100;
}

boolean
scaryEye(complete, mtmp)
int complete;
struct permonst *mtmp;
{
	if(complete <= 0) return FALSE;
	switch(mtmp->mtyp)
	{
        case PM_CHAOS:
            return 50;
        case PM_DEMOGORGON:
            return 33;
        case PM_LAMASHTU:
            return 33;
        case PM_ASMODEUS:
            return 11;
	}
	if(standardUnwardable(mtmp) ||
			(mtmp->mtyp == PM_CHAOS && rn2(2)) ||
			(mtmp->mtyp == PM_DEMOGORGON && rn2(3)) ||
			(mtmp->mtyp == PM_LAMASHTU && rn2(3)) ||
			(mtmp->mtyp == PM_ASMODEUS && rn2(9))
		) return FALSE;
	return 100*((mtmp->mflagsw&MW_ELDER_EYE_ELEM) || (complete >= 4 && (mtmp->mflagsw&MW_ELDER_EYE_ENERGY)) || (complete >= 7 && (mtmp->mflagsw&MW_ELDER_EYE_PLANES)));
}

boolean
scarySign(complete, mtmp)
int complete;
struct permonst *mtmp;
{
	if(complete <= 0) return FALSE;
	if(mtmp->mtyp == PM_DEMOGORGON)
        return 33;
	if(standardUnwardable(mtmp) || (mtmp->mtyp == PM_DEMOGORGON && rn2(3)))
		return FALSE;
	return 100*((mtmp->mflagsw&MW_ELDER_SIGN) || (complete >= 6 && (mtmp->mflagsw&MW_EYE_OF_YGG)));
}

boolean
scaryHam(complete, mtmp)
int complete;
struct permonst *mtmp;
{
	if(complete <= 0) return FALSE;
	else if(standardUnwardable(mtmp))
		return FALSE;
	return 	hamWarded(mtmp)*100;
}

boolean
scaryHex(complete, mtmp)
int complete;
struct permonst *mtmp;
{
	if(complete <= 0) return FALSE;
    switch(mtmp->mtyp)
	{
        case PM_CHAOS:
            return 50;
        case PM_DEMOGORGON:
            return 33;
        case PM_LAMASHTU:
            return 33;
        case PM_ASMODEUS:
            return -122;//12% per completion, min 2
	}
	if(standardUnwardable(mtmp) || FALSE/*mtmp->mpeaceful*/ ||
			(mtmp->mtyp == PM_CHAOS && rn2(2)) ||
			(mtmp->mtyp == PM_DEMOGORGON && rn2(3)) ||
			(mtmp->mtyp == PM_LAMASHTU && rn2(3)) ||
			(mtmp->mtyp == PM_ASMODEUS && complete <= d(1,8))
		) return FALSE;
	return 	hexWarded(mtmp)*100;
}

boolean
scaryPent(complete, mtmp)
int complete;
struct permonst *mtmp;
{
	if(complete <= 0) return FALSE;
    switch(mtmp->mtyp)
	{
        case PM_CHAOS:
            return 50;
        case PM_DEMOGORGON:
            return 33;
        case PM_LAMASHTU:
            return 33;
        case PM_ASMODEUS:
            return 88;
	}
	if(standardUnwardable(mtmp) ||
			(mtmp->mtyp == PM_CHAOS && rn2(2)) ||
			(mtmp->mtyp == PM_DEMOGORGON && rn2(3)) ||
			(mtmp->mtyp == PM_LAMASHTU && rn2(3)) ||
			(mtmp->mtyp == PM_ASMODEUS && !rn2(9))
		) return FALSE;
	return 	pentWarded(mtmp)*100;
}

boolean
scaryCircle(complete, mtmp)
int complete;
struct permonst *mtmp;
{
	if(complete <= 0) return FALSE;
	else if(standardUnwardable(mtmp))
		return FALSE;
	return circleWarded(mtmp)*100;
}

boolean
scaryGorg(complete, mtmp)
int complete;
struct permonst *mtmp;
{
	if(complete <= 0) return FALSE;
	switch(mtmp->mtyp)
	{
        case PM_CHAOS:
            return 50;
        case PM_DEMOGORGON:
            return 33;
        case PM_LAMASHTU:
            return 33;
        case PM_ASMODEUS:
            return 11;
	}
	if(gorgUnwardable(mtmp)
		|| (mtmp->mtyp == PM_CHAOS && rn2(2))
		|| (mtmp->mtyp == PM_DEMOGORGON && rn2(3))
		|| (mtmp->mtyp == PM_LAMASHTU && rn2(3))
		|| (mtmp->mtyp == PM_ASMODEUS && rn2(9))
	)
		return FALSE;
	else if(mtmp->mlet == S_SNAKE && 1/*mvitals[PM_MEDUSA].killed == 0*/){
//PACIFY
		return 255;//pacify
	}
	if(gorgWarded(mtmp))
        return -331;//33% per completion
    else
        return 0;
}

boolean
scaryHept(complete, mtmp)
int complete;
struct permonst *mtmp;
{
	if(complete <= 0) return FALSE;
    switch(mtmp->mtyp)
	{
        case PM_ELDER_PRIEST:
            return -145;//5 min, 14% per completion
        case PM_GREAT_CTHULHU:
            return -145;
        case PM_CHAOS:
            return 50;
        case PM_DEMOGORGON:
            return 33;
        case PM_LAMASHTU:
            return 33;
        case PM_ASMODEUS:
            return -102;//2 min, 10% per completion
	}
	if(heptUnwardable(mtmp) ||
			(mtmp->mtyp == PM_ELDER_PRIEST && complete <= d(2,4)+2) ||
			(mtmp->mtyp == PM_GREAT_CTHULHU && complete <= d(2,4)+2) ||
			(mtmp->mtyp == PM_CHAOS && rn2(2)) ||
			(mtmp->mtyp == PM_DEMOGORGON && rn2(3)) ||
			(mtmp->mtyp == PM_LAMASHTU && rn2(3)) ||
			(mtmp->mtyp == PM_ASMODEUS && complete <= d(1,10))
		) return FALSE;
	return heptWarded(mtmp)*100;

}



boolean
scaryLol(int LOLTH_HIGH_POWER,struct permonst * mtmp)
{
  //if(Infuture) return FALSE;
  //if(u.ualign.type == A_VOID) return FALSE;
  if(LOLTH_HIGH_POWER){
	if (mtmp->mtyp==PM_SHOPKEEPER || mtmp->mtyp==PM_GUARD || mtmp->mtyp==PM_WIZARD_OF_YENDOR || 0/*is_blind(mtmp)*/ ||
	    0/*mtmp->mpeaceful*/ || (mtmp->mlet == S_HUMAN && 1/*!mtmp->mtemplate*/) ||
	    (is_rider(mtmp))
	)
		return(FALSE);
    switch(mtmp->mtyp)
	{
        case PM_CHAOS:
            return 50;
        case PM_DEMOGORGON:
            return 33;
        case PM_ASMODEUS:
            return 11;//2 min, 10% per completion
	}
	return (boolean)100*( (mtmp->mtyp != PM_ELDER_PRIEST) &&
					(mtmp->mtyp != PM_GREAT_CTHULHU) &&
					(mtmp->mtyp != PM_CHOKHMAH_SEPHIRAH) &&
					(mtmp->mtyp != PM_CHAOS || rn2(2)) &&
					(mtmp->mtyp != PM_DEMOGORGON || !rn2(3)) &&
					(mtmp->mtyp != PM_LAMASHTU) &&
					(mtmp->mtyp != PM_ASMODEUS || !rn2(9))
                    );
  } else return(FALSE);
}

boolean
scaryYellow(complete, mtmp)
int complete;
struct permonst *mtmp;
{
	if(complete <= 0) return FALSE;
	else if(yellowUnwardable(mtmp))
		return FALSE;
	if(yellowWarded(mtmp)){
        return 254;//crazy+10%scare
    }
	return FALSE;
}

boolean
scaryElb(int ELBERETH_HIGH_POWER,struct permonst *mtmp)
{
  //if(Infuture) return FALSE;
  ELBERETH_HIGH_POWER--;//we want 0 and 1 instead of 1 and 2
  if(ELBERETH_HIGH_POWER){
	if (mtmp->mtyp==PM_SHOPKEEPER || mtmp->mtyp==PM_GUARD || mtmp->mtyp==PM_WIZARD_OF_YENDOR || 0/*is_blind(mtmp)*/ ||
	    0/*mtmp->mpeaceful*/ ||		(mtmp->mlet == S_HUMAN && 1/*!mtmp->mtemplate*/) ||
	    is_lminion(mtmp) || mtmp->mtyp == PM_ANGEL ||
	    (is_rider(mtmp) && !(mtmp->mtyp == PM_NAZGUL)) ||
		mtmp->mtyp == PM_MINOTAUR)
		return(FALSE);
	switch(mtmp->mtyp)
	{
        case PM_CHAOS:
            return 50;
        case PM_DEMOGORGON:
            return 33;
        case PM_ASMODEUS:
            return 11;
	}
	return (boolean)100*(
                    (mtmp->mtyp != PM_ELDER_PRIEST) &&
					(mtmp->mtyp != PM_GREAT_CTHULHU) &&
					(mtmp->mtyp != PM_CHOKHMAH_SEPHIRAH) &&
					(mtmp->mtyp != PM_CHAOS || rn2(2)) &&
					(mtmp->mtyp != PM_DEMOGORGON || !rn2(3)) &&
					(mtmp->mtyp != PM_LAMASHTU) &&
					(mtmp->mtyp != PM_ASMODEUS || !rn2(9))
                    );
  }
  else{
	if (mtmp->mtyp==PM_SHOPKEEPER || mtmp->mtyp==PM_GUARD || mtmp->mtyp==PM_WIZARD_OF_YENDOR || 0/*is_blind(mtmp)*/ ||
	    0/*mtmp->mpeaceful*/ ||		(mtmp->mlet == S_HUMAN && 1/*!mtmp->mtemplate*/) ||
	    is_lminion(mtmp) || mtmp->mtyp == PM_ANGEL ||
	    (is_rider(mtmp) && !(mtmp->mtyp == PM_NAZGUL)) ||
		mtmp->mtyp == PM_MINOTAUR)
		return(FALSE);
	return 100*((boolean) mtmp->mlet == S_ORC || mtmp->mlet == S_OGRE
				|| mtmp->mlet == S_TROLL || mtmp->mtyp == PM_ELVEN_WRAITH || mtmp->mtyp == PM_NAZGUL);
  }
}

char ward_list[][40]={
    "ELBERETH_1",
    "ELBERETH_2",
    "LOLTH",
    "HEPTAGRAM",
    "GORGONEION",
    "CIRCLE_OF_ACHERON",
    "PENTAGRAM",
    "HEXAGRAM",
    "HAMSA",
    "YELLOW_SIGN",
    "ELDER_SIGN_1",
    "ELDER_SIGN_6",
    "ELDER_ELEMENTAL_EYE_1",
    "ELDER_ELEMENTAL_EYE_5",
    "ELDER_ELEMENTAL_EYE_7",
    "SIGN_OF_THE_SCION_QUEEN",
    "CARTOUCHE_OF_THE_CAT_LORD",
    "WINGS_OF_GARUDA",
    "TOUSTEFNA",
    "DREPRUN",
    "VEIOISTAFUR",
    "THJOFASTAFUR",
    ""

};

typedef int (*fear_func)(int complete,struct permonst *mon);
fear_func ward_funcs[]={
    scaryElb,
    scaryElb,
    scaryLol,
    scaryHept,
    scaryGorg,
    scaryCircle,
    scaryPent,
    scaryHex,
    scaryHam,
    scaryYellow,
    scarySign,
    scarySign,
    scaryEye,
    scaryEye,
    scaryEye,
    scaryQueen,
    scaryCat,
    scaryWings,
    scaryTou,
    scaryDre,
    scaryVei,
    scaryThj,
    NULL

};


char *check_wards_list(struct permonst *mon)
{
    static char res[255];
    char tmp[30];
    int x=0;
    res[0]='\0';
    int len=0;
    int param=0;
    int prob=0;
    while(ward_list[x][0]!='\0')
    {
        len=strlen(ward_list[x]);
        if(ward_list[x][len-2]=='_')
            param=ward_list[x][len-1]-48;//"0"
        else
            param=1;
        prob=ward_funcs[x](param,mon);
        if(prob!=0)
           {
            strcat(res,ward_list[x]);
            strcat(res,"=");
            sprintf(tmp,"%d",prob);
            strcat(res,tmp);
            strcat(res,"|");
           }
        x++;
    }
    return res;
}
