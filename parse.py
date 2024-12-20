import csv
from math import floor
from operator import itemgetter
import time

monsym= {'S_ANT':'a',
'S_BLOB':'b',
'S_COCKATRICE':'c',
'S_DOG':'d',
'S_EYE':'e',
'S_FELINE':'f',
'S_GREMLIN':'g',
'S_HUMANOID':'h',
'S_IMP':'i',
'S_JELLY':'j',
'S_KOBOLD':'k',
'S_LEPRECHAUN':'l',
'S_MIMIC':'m',
'S_NYMPH':'n',
'S_ORC':'o',
'S_PIERCER':'p',
'S_QUADRUPED':'q',
'S_RODENT':'r',
'S_SPIDER':'s',
'S_TRAPPER':'t',
'S_UNICORN':'u',
'S_VORTEX':'v',
'S_WORM':'w',
'S_XAN':'x',
'S_LIGHT':'y',
'S_ZRUTY':'z',
'S_ANGEL':'A',
'S_BAT':'B',
'S_CENTAUR':'C',
'S_DRAGON':'D',
'S_ELEMENTAL':'E',
'S_FUNGUS':'F',
'S_GNOME':'G',
'S_GIANT':'H',
'S_JABBERWOCK':'J',
'S_KOP':'K',
'S_LICH':'L',
'S_MUMMY':'M',
'S_NAGA':'N',
'S_OGRE':'O',
'S_PUDDING':'P',
'S_QUANTMECH':'Q',
'S_RUSTMONST':'R',
'S_SNAKE':'S',
'S_TROLL':'T',
'S_UMBER':'U',
'S_VAMPIRE':'V',
'S_WRAITH':'W',
'S_XORN':'X',
'S_YETI':'Y',
'S_ZOMBIE':'Z',
'S_HUMAN':'@',
'S_GHOST':' ',
'S_GOLEM':'\'',
'S_DEMON':'&',
'S_EEL':';',
'S_LIZARD':':',
'S_INVISIBLE':'I',
'S_WORM_TAIL':'~',
'S_MIMIC_DEF':']',
}

at={'AT_CLAW':'Claw',
'AT_BITE':'Bite',
'AT_KICK':'Kick',
'AT_BUTT':'Butt',
'AT_TUCH':'Touch',
'AT_STNG':'Sting',
'AT_HUGS':'Hug',
'AT_SPIT':'Spit',
'AT_ENGL':'Engulf',
'AT_BREA':'Breath',
'AT_EXPL':'Explode',
'AT_BOOM':'Explode',
'AT_GAZE':'Gaze',
'AT_TENT':'Suck',
'AT_WEAP':'Weapon',
'AT_MAGC':'Spell',
'AT_NONE':"Passive"}

ad={'AD_PHYS':'',
'AD_MAGM':' M. Missile',
'AD_FIRE':' Fire',
'AD_COLD':' Cold',
'AD_SLEE':' Sleep',
'AD_DISN':' Disint.',
'AD_ELEC':' Shock',
'AD_DRST':' Poison (St)',
'AD_ACID':' Acid',
'AD_SPC1':' SPC1',
'AD_SPC2':' SPC2',
'AD_BLND':' Blind',
'AD_STUN':' Stun',
'AD_SLOW':' Slow',
'AD_PLYS':' Paralyse',
'AD_DRLI':' Drain life',
'AD_DREN':' Drain Pw',
'AD_LEGS':' Legs',
'AD_STON':' Petrify',
'AD_STCK':' Sticky',
'AD_SGLD':' Steal gold',
'AD_SITM':' Steal',
'AD_SEDU':' Steal',#сейчас работают идентично
'AD_TLPT':' Teleport',
'AD_RUST':' Rust',
'AD_CONF':' Conf',
'AD_DGST':' Digest',
'AD_HEAL':' Heal',
'AD_WRAP':' Drowning',
'AD_WERE':' Lycantropy',
'AD_DRDX':' Poison (Dx)',
'AD_DRCO':' Poison (Co)',
'AD_DRIN':' -In',
'AD_DISE':' Disease',
'AD_DCAY':' Decay organics',
'AD_SSEX':' Seduce',
'AD_HALU':' Hallu',
'AD_DETH':' Deadly touch',
'AD_PEST':' Plus disease',
'AD_FAMN':' Plus hunger',
'AD_SLIM':' Slime',
'AD_ENCH':' Disenchant',
'AD_CORR':' Corrode',
'AD_CLRC':' Clerical',
'AD_SPEL':' Mage',
'AD_RBRE':' Random',
'AD_SAMU':' Steal Artifact',
'AD_CURS':' Steal intrinsic',
'AD_CNCL':' Cancel',
'AD_POLY':' Polymorph'}

resists={'MR_FIRE':'Fire',
'MR_COLD':'Cold',
'MR_SLEEP':'Sleep',
'MR_DISINT':'Disint.',
'MR_ELEC':'Shock',
'MR_POISON':'Poison',
'MR_ACID':'Acid (temp)',
'MR_STONE':'Stoning (temp)',}

rows={"index":0,
"namem":1,
"namef":2,
"name":3,
"symbol":4,
"level":5,
"speed":6,
"ac":7,
"mr":8,
"alignment":9,
"geno":10,
"attack1":11,
"attack2":12,
"attack3":13,
"attack4":14,
"attack5":15,
"attack6":16,
"weight":17,
"nutrition":18,
"sound":19,
"size":20,
"res":21,
"resconv":22,
"flags1":23,
"flags2":24,
"flags3":25,
"color":26,
"comment1":27,
"comment2":28,
"comment3":29,
"difficulty":30,
"difficulty2":31,

}

table=[]
table_temp=[]
disable_sorting=False

def insert (source_str, insert_str, pos):
    return source_str[:pos]+insert_str+source_str[pos:]

def split_line(line:str,mid:int)->str:
    if len(line)<mid:
        return line
    mid=int(len(line)/2+.5)
    pos2=line.find(",",mid)
    pos1=line.rfind(",",0,mid)
    if(pos1==-1 and pos2 ==-1):
        return line
    insert_before=insert(line,"\n",pos1+2)
    insert_after=insert(line,"\n",pos2+2)
    if(pos1==-1):
        return insert_after
    if(pos2==-1):
        return insert_before
    if(pos2-mid<mid-pos1):
        return insert_after
    return insert_before

def append_to_table(entry):
    global table,table_temp
    global disable_sorting
    if len(table_temp)==0:
        table_temp.append(entry)
        return
    if table_temp[-1][0]==entry[0] and entry[1]!="Lord Carnarvon":
        table_temp.append(entry)
        return
    #table_temp=sorted(table_temp,key=itemgetter(0))
    if not disable_sorting:
        table_temp.sort(key=lambda x:x[1].lower())
    if entry[1]=="Lord Carnarvon":
        disable_sorting=True
    table+=table_temp
    table_temp=[]
    table_temp.append(entry)

def make_table():

    global table,table_temp
    global disable_sorting

    dt=time.strftime("%Y-%m-%dT%H-%M-%S",time.localtime())

    monfile=open(input("Enter filename:"),"r")
    outfile=open("mon-edited"+dt+".csv","w",newline='')
    reader=csv.reader(monfile)
    writer=csv.writer(outfile)


    #x=0
    total=0
    #out_line_header=[" ","Name","Dif","Mv","AC","MR","Resistances","Conveyed","Attacks"]
    out_line_header=[" ","Name","Dif","Attacks","Mv","AC","MR","Resistances","Conveyed","Don't eat"]
    out_line=""
    max_len_res=0
    max_len_con=0
    max_len_atk=0

    #cur_len_res=56
    #cur_len_con=44
    #cur_len_atk=84
    cur_len_res=66
    cur_len_con=44
    cur_len_atk=94

    writer.writerow(out_line_header)

    for x, mon in enumerate(reader):
        #x+=1
        if x==0:#or x==1:
            continue
        out_line=[]

        #Symbol
        out_line.append(monsym[mon[rows["symbol"]]])
        #Name
        out_line.append(mon[rows["name"]])
        #Difficulty
        out_line.append(mon[rows["difficulty"]])


        #Attacks
        attacks=""
        interrupted=0
        for attack_n in range(rows["attack1"],rows["attack6"]+1):
            if mon[attack_n]=="NO_ATTK":
                attacks=attacks[:-2]
                interrupted=1
                break
            attack=mon[attack_n]
            attack=attack[5:]
            attack=attack[:-1]
            attack=attack.split(",")
            attack_s=""
            #if(attack_n==rows["attack3"]):
            #    attack_s="\n"
            #else:
            #    attack_s=""
            if(attack[2].strip()=="0" and attack[3].strip()=="0"):
                attack_s+=at[attack[0].strip()]+ad[attack[1].strip()]+", "#0d0 смотреть бесполезно
            else:
                attack_s+=at[attack[0].strip()]+" "+attack[2].strip()+"d"+attack[3].strip()+ad[attack[1].strip()]+", "
            attacks+=attack_s
        
        if interrupted==0:#используются все шесть атак, значит надо убрать последнюю запятую
            attacks=attacks[:-2]
        if len(attacks)>max_len_atk:
            max_len_atk=len(attacks)
        out_line.append(split_line(attacks,floor(cur_len_atk/2)))

        #Speed
        out_line.append(mon[rows["speed"]])
        #AC
        out_line.append(mon[rows["ac"]])
        #MR
        out_line.append(mon[rows["mr"]])

        #Resistances
        ress=""
        resn=0
        for res in mon[rows["res"]].split("|"):
            res=res.strip()
            if len(res)==0:
                break
            resn+=1
            if resn>4:
                resn=0
                #ress+="\n"
            ress+=resists[res.strip()]+", "

        for flag in mon[rows["flags1"]].split("|"):
            flag=flag.strip()
            if(flag=="M1_SEE_INVIS"):
                ress+="SeeInvis, "

        

        ress=ress[:-2]
        if len(ress)>max_len_res:
            max_len_res=len(ress)
        out_line.append(split_line(ress,floor(cur_len_res/2)))


        #Conveyed
        ress_conv=""
        resn=0
        nocorpse=False
        for geno in mon[rows["geno"]].split("|"):
            geno=geno.strip()
            if(len(geno)==0):
                break
            if geno=="G_NOCORPSE":
                nocorpse=True
        if nocorpse:
            ress_conv="("
        for res in mon[rows["resconv"]].split("|"):
            res=res.strip()
            if len(res)==0:
                break
            resn+=1
            if resn>3:
                resn=0
                #ress_conv+="\n"
            if res not in ["MR_ACID","MR_STONE"]:#эти резисты нельзя получить, т.к. они не прописаны в функции intrinsic_possible
                ress_conv+=resists[res.strip()]+", "

        for flag in mon[rows["flags1"]].split("|"):
            flag=flag.strip()
            if flag=="M1_TPORT":
                ress_conv+="Teleportitis, "
            if flag=="M1_TPORT_CNTRL":
                ress_conv+="Teleport control, "

        for flag in mon[rows["flags2"]].split("|"):
            flag=flag.strip()
            if flag=="M2_GIANT":
                ress_conv+="Gain St, "

        if mon[rows["name"]] in ["floating eye","mind flayer", "master mind flayer"]:
            ress_conv+="Telepathy, "

        #ничего не могу сделать, именно так это прописано в исходниках нетхака: конкретные типы монстров дают сопротивление. и это не в monst.c, это в eat.c!

        if mon[rows["name"]] in ["newt"]:
            ress_conv+="Energy boost, "
        if mon[rows["name"]] in ["wraith"]:
            ress_conv+="Gain level, "
        if mon[rows["name"]] in ["wererat","werejackal","werewolf"]:
            ress_conv+="Lycantropy, "
        if mon[rows["name"]] in ["nurse"]:
            ress_conv+="Heal, "
        if mon[rows["name"]] in ["stalker"]:
            ress_conv+="Invisibility, See invisible, "
        if mon[rows["name"]] in ["quantum mechanic"]:
            ress_conv+="Toggle speed, "
        if mon[rows["name"]] in ["lizard"]:
            ress_conv+="Reduce conf/stun, Stop petrification, "
        if mon[rows["name"]] in ["chameleon","doppelganger","sandestin"]:
            ress_conv+="Polymorph, "
        if mon[rows["name"]] in ["disenchanter"]:
            ress_conv+="Steal intrinsic, "
        if mon[rows["name"]] in ["mind flayer","master mind flayer"]:
            ress_conv+="Gain In, "
        if(len(ress_conv)>3):
            ress_conv=ress_conv[:-2]
        if nocorpse:
            ress_conv+=")"
        if ress_conv=="()":
            ress_conv=""

        if len(ress_conv)>max_len_con:
            max_len_con=len(ress_conv)
        out_line.append(split_line(ress_conv,floor(cur_len_con/2)))


        #вредные эффекты при еде
        #Eat Danger
        bad=""
        badn=0
        for flag in mon[rows["flags1"]].split("|"):
            flag=flag.strip()
            if flag=="M1_POIS":
                bad+="POISON\n"   
            if flag=="M1_ACID":
                bad+="ACID\n"

        for flag in mon[rows["flags2"]].split("|"):
            flag=flag.strip()
            if flag=="M2_HUMAN":
                bad+="human\n"
            if flag=="M2_DWARF":
                bad+="dwarf\n"
            #if flag=="M2_ORC":#орки едят орков -- им разрешён каннибализм
            #    bad+="orc\n"
            if flag=="M2_ELF":
                bad+="elf\n"
            if flag=="M2_GNOME":
                bad+="gnome\n"

        attacks=""
        for attack_n in range(rows["attack1"],rows["attack6"]+1):
            if mon[attack_n]=="NO_ATTK":
                attacks=attacks[:-2]
                interrupted=1
                break
            attack=mon[attack_n]
            attack=attack[5:]
            attack=attack[:-1]
            attack=attack.split(",")
            if attack[1]=="AD_STUN" or mon[rows["name"]]=="violet fungus":
                bad+="HALLU\n"
                break


        if mon[rows["name"]] in ["kitten","housecat","large cat","little dog","dog","large dog"]:
            bad+="Aggravate\n"
        if mon[rows["name"]] in ["cockatrice","chickatrice","Medusa"]:
            bad+="PETRIFY\n"
        if mon[rows["name"]] in ["Death","Pestilence","Famine"]:
            bad+="FATAL\n"
        if mon[rows["name"]] in ["green slime"]:
            bad+="SLIME\n"
        if mon[rows["name"]] in ["stalker","yellow light","giant bat","bat"]:
            bad+="Stun\n"
        if mon[rows["name"]] in ["small mimic","large mimic","giant mimic"]:
            bad+="Mimic\n"
        

        bad=bad[:-1]
        out_line.append(bad)


        
        #Preparing string
        out_line_m=""
        out_line_f=""
        out_line_gender_neutral=out_line
        append_to_table(out_line_gender_neutral)

        if len(mon[rows["namem"]])>0:
            out_line_m=out_line_gender_neutral.copy()
            out_line_m[1]=mon[rows["namem"]]
            append_to_table(out_line_m)
        if len(mon[rows["namef"]])>0:
            out_line_f=out_line_gender_neutral.copy()
            out_line_f[1]=mon[rows["namef"]]
            append_to_table(out_line_f)
        total=x

    append_to_table(out_line_header)#это нужно чтобы все болтающиеся строки прокрутились

    for row in table:
        writer.writerow(row)

    monfile.close()
    outfile.close()
    print(f"{total} monsters affected")
    print(f"max_len_res={max_len_res}")
    print(f"max_len_con={max_len_con}")
    print(f"max_len_atk={max_len_atk}")

            

if __name__=="__main__":
    make_table()