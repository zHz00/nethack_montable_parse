import csv
from math import floor
from operator import itemgetter
import curses as c

from nhconstants import *

colors_table={
    0:c.COLOR_WHITE,#it must be COLOR_BLACK, but certain monsters are marked as black, but they are actually white (gray)
    1:c.COLOR_RED,
    2:c.COLOR_GREEN,
    3:c.COLOR_YELLOW,
    4:c.COLOR_BLUE,
    5:c.COLOR_MAGENTA,
    6:c.COLOR_CYAN,
    7:c.COLOR_WHITE
}

bold=0




cur_len_res=66
cur_len_con=44
cur_len_atk=94

max_len_res=0
max_len_con=0
max_len_atk=0

table=dict()
table_temp=[]
disable_sorting=False

def read_monsters():
    global table,table_temp
    global disable_sorting
    monfile=open("mondump370.csv","r")
    reader=csv.reader(monfile)
    for x, mon in enumerate(reader):
        if x==0:#skip header
            continue
        mon_copy=None
        if len(mon[rows["namef"]])>0 and len(mon[rows["namef"]])>0:#two-gender monster
            mon_copy=mon.copy()
            mon_copy[rows["flags2"]]+="|M2_NEUTER"
            table[mon[rows["name"]]]=mon_copy
        else:
            table[mon[rows["name"]]]=mon
        if len(mon[rows["namef"]])>0:
            mon_copy=mon.copy()
            mon_copy[rows["flags2"]]+="|M2_FEMALE"
            table[mon[rows["namef"]]]=mon_copy
        if len(mon[rows["namem"]])>0:
            mon_copy=mon.copy()
            mon_copy[rows["flags2"]]+="|M2_MALE"
            table[mon[rows["namem"]]]=mon_copy

BK=18
INV=19
BK_CARD=20
INV_CARD=21
SCR_WIDTH=80
LIST_WIDTH=SCR_WIDTH-7

def out_input(s,in_str):

    s.clear()
    s.addstr(0,0,">"+in_str,c.color_pair(BK))
    s.chgat(-1,c.color_pair(BK))
    s.clrtoeol()
    s.refresh()

def out_results(s,results,sel,skip):
    selected_appeared=False
    s.move(1,0)
    if len(results)==0:
        s.addstr("(none)")
        selected_appeared=True#actually false, but we don't want to check selection in empty results
    start_ch=0
    cur=0
    for mon in results:
        if cur<skip:
            cur+=1
            continue
        if(start_ch+len(mon)>LIST_WIDTH):
            s.addstr(f"(+{len(results)-cur})")
            break
        start_ch+=len(mon)+1#for "|"
        if cur-skip==sel:
            s.addstr(mon,c.color_pair(INV))
            selected_appeared=True
        else:
            s.addstr(mon,c.color_pair(BK))
        s.addstr("|")
        cur+=1
    s.chgat(c.color_pair(BK))
    s.refresh()
    return (cur-skip,selected_appeared)

def move_to_in(s,in_str):
    s.move(0,1+len(in_str))
    c.curs_set(1)

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

def out_symbol(s,mon):
    color=colors_table[int(mon[rows["color"]])&0x7]
    if bold==1:
        if int(mon[rows["color"]])>8:
            s.addstr(monsym[mon[rows["symbol"]]],c.color_pair(color+1)|c.A_BOLD)
        else:
            s.addstr(monsym[mon[rows["symbol"]]],c.color_pair(color+1))
    if bold==0:
        if int(mon[rows["color"]])==0:
            s.addstr(monsym[mon[rows["symbol"]]],c.color_pair(9))
        if int(mon[rows["color"]])>8:
            s.addstr(monsym[mon[rows["symbol"]]],c.color_pair(color+9))
        if int(mon[rows["color"]])<=8 and int(mon[rows["color"]])>0:
            s.addstr(monsym[mon[rows["symbol"]]],c.color_pair(color+1))


NO_ATTK="NO_ATTK"
def make_card(mon,format_length=0):
    global max_len_atk,max_len_res,max_len_con
    out_line=[]
    #out_line.append("Color:"+mon[rows["color"]])
    #Difficulty
    out_line.append(f"|Dif:{mon[rows['difficulty']]:2}")
    out_line.append(f"|Lv:{mon[rows['level']]:2}")
    out_line.append(f"|Exp:{mon[rows['exp']]:4}")

    #Speed
    out_line.append(f"|Spd:{mon[rows['speed']]:2}")
    #AC
    out_line.append(f"|AC:{mon[rows['ac']]:3}")
    #MR
    out_line.append(f"|MR:{mon[rows['mr']]:3}")
    #Size
    out_line.append(f"|Sz:{szs[mon[rows['size']]]:8}")
    #Align
    out_line.append(f"|Align:{mon[rows['alignment']]}\n")

    flags1=mon[rows["flags1"]].split("|")
    flags2=mon[rows["flags2"]].split("|")
    flags3=mon[rows["flags3"]].split("|")
    gen_flags=mon[rows["geno"]].split("|")

    if format_length>0:
        for x in range(len(gen_flags)):
            gen_flags[x]=gen_flags[x].strip()
        freq_s=""
        freq=gen_flags[-1]
        if freq!="0":
            freq_s+=freq+", "
        freq_s+=freq_str[freq]+", "
        if "G_UNIQ" in gen_flags:
            freq_s+="Unique, "
        if "G_SGROUP" in gen_flags:
            freq_s+="Small Groups, "
        if "G_LGROUP" in gen_flags:
            freq_s+="Large Groups, "
        if "G_NOHELL" in gen_flags:
            freq_s+="No Gehennom, "
        if "G_HELL" in gen_flags:
            freq_s+="Only Gehennom, "
        if "G_NOHELL" not in gen_flags and "G_HELL" not in gen_flags:
            freq_s+="Everywhere, "
        if freq_s.endswith(", "):
            freq_s=freq_s[:-2]
        freq_s+="|"
        freq_s="Gen:"+freq_s
        out_line.append(freq_s)
        if "G_GENO" in gen_flags:
            out_line.append(f"Genocide: Yes|")
        else:
            out_line.append(f"Genocide: No |")
        if "M2_NOPOLY" in flags2:
            out_line.append(f"Poly to: No |")
        else:
            out_line.append(f"Poly to: Yes|")
#        if "G_NOCORPSE" in gen_flags:
#            out_line.append(f"Corpse: No |")
#        else:
#            out_line.append(f"Corpse: Yes|")
        out_line.append("\n")

    #Attacks
    attacks=""
    interrupted=0
    for attack_n in range(rows["attack1"],rows["attack6"]+1):
        attack=mon[attack_n]
        attack_raw=mon[attack_n]
        attack_s=""

        if mon[attack_n]==NO_ATTK:
            attacks=attacks[:-2]
            interrupted=1
            break

        attack=attack[5:]
        attack=attack[:-1]
        attack=attack.split(",")
        if(attack[2].strip()=="0" and attack[3].strip()=="0"):
            attack_s+=at[attack[0].strip()]+ad[attack[1].strip()]+", "#0d0 смотреть бесполезно
        else:
            attack_s+=at[attack[0].strip()]+" "+attack[2].strip()+"d"+attack[3].strip()+ad[attack[1].strip()]+", "
        attacks+=attack_s
    
    if interrupted==0:#используются все шесть атак, значит надо убрать последнюю запятую
        attacks=attacks[:-2]
    if len(attacks)>max_len_atk:
        max_len_atk=len(attacks)
    
    attacks_list=attacks.split(",")
    attacks_list.append(NO_ATTK)
    for x in range(len(attacks_list)):
        attacks_list[x]=attacks_list[x].strip()
    attacks_list_condensed=[]
    cnt=0
    for x in range(len(attacks_list)):

        if x>0:
            if attacks_list[x]==attacks_list[x-1]:
                cnt+=1
            else:
                if cnt==0:
                    attacks_list_condensed.append(attacks_list[x-1])
                else:
                    attacks_list_condensed.append(attacks_list[x-1]+f" (x{cnt+1})")
                    cnt=0
    attacks_condensed=", ".join(attacks_list_condensed)
    out_line.append("Atk: "+attacks_condensed+"\n")



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
        ress+=resists_mon[res.strip()]+", "

    for flag in mon[rows["flags1"]].split("|"):
        flag=flag.strip()
        if(flag=="M1_SEE_INVIS"):
            ress+="SeeInvis, "
    if ress.endswith(", "):
        ress=ress[:-2]
    if len(ress)==0:
        ress="Resistances: None\n"
    else:
        ress="Resistances: "+ress+"\n"
    out_line.append(ress)


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
        ress_conv+=resists_conv[res.strip()]+", "

    for flag in mon[rows["flags1"]].split("|"):
        flag=flag.strip()
        if flag=="M1_TPORT":
            ress_conv+="Teleportitis, "
        if flag=="M1_TPORT_CNTRL":
            ress_conv+="T. control, "

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

    if len(ress_conv)==0:
        if nocorpse:
            ress_conv="Conveyed: No corpse"
        else:
            ress_conv="Conveyed: None"
    else:
        ress_conv="Conveyed: "+ress_conv
    out_line.append(ress_conv+"\n")

    #Wt
    out_line.append(f"Wt:{mon[rows['weight']]:4}")
    #Nutrition
    out_line.append(f"|Nut:{mon[rows['nutrition']]:4}")

    #вредные эффекты при еде
    #Eat Danger
    bad=""
    badn=0
    for flag in mon[rows["flags1"]].split("|"):
        flag=flag.strip()
        if flag=="M1_POIS":
            bad+="POISON, "
        if flag=="M1_ACID":
            bad+="ACID, "

    for flag in mon[rows["flags2"]].split("|"):
        flag=flag.strip()
        if flag=="M2_HUMAN":
            bad+="human, "
        if flag=="M2_DWARF":
            bad+="dwarf, "
        #if flag=="M2_ORC":#орки едят орков -- им разрешён каннибализм
        #    bad+="orc\n"
        if flag=="M2_ELF":
            bad+="elf, "
        if flag=="M2_GNOME":
            bad+="gnome, "

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
            bad+="HALLU, "
            break


    if mon[rows["name"]] in ["kitten","housecat","large cat","little dog","dog","large dog"]:
        bad+="Aggravate, "
    if mon[rows["name"]] in ["cockatrice","chickatrice","Medusa"]:
        bad+="PETRIFY, "
    if mon[rows["name"]] in ["Death","Pestilence","Famine"]:
        bad+="FATAL, "
    if mon[rows["name"]] in ["green slime"]:
        bad+="SLIME, "
    if mon[rows["name"]] in ["stalker","yellow light","giant bat","bat"]:
        bad+="Stun, "
    if mon[rows["name"]] in ["small mimic","large mimic","giant mimic"]:
        bad+="Mimic, "
    

    bad=bad[:-2]
    if len(bad)==0:
        out_line.append("|Eat danger: Safe\n")
    else:
        out_line.append("|Eat danger: "+bad+"\n")

    if format_length>0:#flags
        flags_all=""
        for f in flags1_str.keys():
            if f in flags1:
                flags_all+=flags1_str[f]+", "
        for f in flags2_str.keys():
            if f in flags2:
                flags_all+=flags2_str[f]+", "
        for f in flags3_str.keys():
            if f in flags3:
                flags_all+=flags3_str[f]+", "
        flags_all=flags_all[:-2]+"\n"
        #out_line.append(flags_all)

    #FLAGS PARSING

    #LINE1. CATEGORY. GENDER. DIET
    if format_length>0:
        line=""
        flags_str=""

        prefix="Catetory: "
        found=False
        for flag in flags_category.keys():
            if flag in flags2:
                found=True
                flag_str=flags_category[flag]+"|"
        if found==False:
            flag_str="Ordinary|"
        line+=prefix+flag_str

        prefix="Gender: "
        found=False
        for flag in flags_gender.keys():
            if flag in flags2:
                found=True
                flag_str=flags_gender[flag]+"|"
        if found==False:
            flag_str="None|"
        line+=prefix+flag_str

        prefix="Diet: "
        found=False
        if "M1_CARNIVORE" in flags1 and "M1_HERBIVORE" in flags1:
            found=True
            flag_str="Omnivore"
        else:
            for flag in flags_diet.keys():
                if flag in flags1:
                    found=True
                    flag_str=flags_diet[flag]+"|"
        if found==False:
            flag_str="Inediate|"
        prefix="Infravisible: "
        if "M3_INFRAVISIBLE" in flags3:
            flag_str="Yes"
        else:
            flag_str="No"
        line+=prefix+flag_str+"\n"

        out_line.append(line)
        line=""
    #LINE 2. BODY PLAN
        flag_str=""
        prefix="Body type: "
        found=False
        for flag in flags_body.keys():
            if flag in flags1:
                found=True
                flag_str=flags_body[flag]+"|"
        if found==False:
            flag_str="Unknown|"

        line+=prefix+flag_str

        prefix="Body parts: "
        flag_str=""
        no_limbs=False
        if "M1_NOLIMBS" in flags_parts_no.keys() and "M1_NOHANDS" not in flags_parts_no.keys():
            no_limbs=no_limbs
        for flag in flags_parts_no.keys():
            if flag in flags1:
                if flag=="M1_NOLIMBS":
                    no_limbs=True
                if flag=="M1_NOHANDS" and no_limbs:
                    continue
                flag_str+=flags_parts_no[flag]+", "
            else:
                flag_str+=flags_parts_have[flag]+", "
        flag_str=flag_str[:-2]
        line+=prefix+flag_str+"\n"
        out_line.append(line)
        line=""

        #LINE 3. BEHAVIOR: DEMEANOR, MOVEMENT, WANTS, PICK
        prefix="Demeanor: "
        found=False
        for flag in flags_demeanor.keys():
            if flag in flags2 or flag in flags3:
                found=True
                flag_str=flags_demeanor[flag]+", "
        if found==False:
            flag_str="None, "
        flag_str=flag_str[:-2]+"|"
        line+=prefix+flag_str

        prefix="Move: "
        flag_str=""
        found=False
        for flag in flags_move.keys():
            if flag in flags1 or flag in flags1:
                found=True
                flag_str+=flags_move[flag]+", "
        if found==False:
            flag_str="Walk, "
        flag_str=flag_str[:-2]+"|"
        line+=prefix+flag_str

        prefix="Picks: "
        flag_str=""
        found=False
        for flag in flags_pick.keys():
            if flag in flags1 or flag in flags2:
                found=True
                flag_str+=flags_pick[flag]+", "
        if found==False:
            flag_str+="None, "
        if "M1_NOTAKE" in flags1:
            flags_str+="Can't, "
        flag_str=flag_str[:-2]+"\n"
        line+=prefix+flag_str

        prefix="Wants: "
        flag_str=""
        found=False
        for flag in flags_covet.keys():
            if flag in flags3:
                found=True
                flag_str+=flags_covet[flag]+", "
        if found==False:
            flag_str="None, "
        flag_str=flag_str[:-2]
        line+=prefix+flag_str+"\n"

        out_line.append(line)
        line=""

        prefix="Perks: "
        flag_str=""
        found=False
        for flag in flags_perks.keys():
            if flag in flags1 or flag in flags2 or flag in flags3:
                found=True
                flag_str+=flags_perks[flag]+", "
        if found==False:
            flag_str="None, "
        flag_str=flag_str[:-2]
        line+=prefix+flag_str+"\n"

        out_line.append(line)
        line=""




    
    #Preparing string
    out_line_s="".join(out_line)
    return out_line_s


def main(s):
    global bold
    if c.COLORS<16:
        bold=1
    else:
        bold=0
    c.raw()
    c.mousemask(-1)
    c.mouseinterval(0)
    c.curs_set(1)
    s.clear()
    c.init_pair(BK,c.COLOR_WHITE,c.COLOR_BLUE)
    c.init_pair(INV,c.COLOR_BLUE,c.COLOR_WHITE)
    c.init_pair(BK_CARD,c.COLOR_WHITE,c.COLOR_BLACK)
    c.init_pair(INV_CARD,c.COLOR_BLACK,c.COLOR_WHITE)
    if bold==1:
        for x in range(1,9):
            c.init_pair(x,x-1,c.COLOR_BLACK)
    else:
        for x in range(1,17):
            c.init_pair(x,x-1,c.COLOR_BLACK)        
    c.update_lines_cols()
    lines=c.LINES
    cols=c.COLS
    s.bkgd(' ',c.color_pair(BK))
    s.clear()
    s.refresh()
    colors_n=c.COLORS
    for x in range(1,17):
        s.addstr(f"TEST:{x-1} ",c.color_pair(x))
    s.refresh()
    in_str=""
    sel=0
    skip=0
    max_sel=0
    tries=0
    format_length=0
    search_win=c.newwin(2,c.COLS,0,0)
    search_win.keypad(1)
    search_win.bkgd(' ',c.color_pair(BK))
    search_win.clear()
    search_win.refresh()  
    card_win=c.newwin(c.LINES-2,c.COLS,2,0)
    card_win.bkgd(' ',c.color_pair(BK_CARD))
    card_win.clear()
    card_win.refresh()    
    while True:
        results=[]
        for mon in table.keys():
            if mon.lower().find(in_str.lower())!=-1:
                results.append(mon)
        card_win.clear()
        card_win.refresh()
        if len(results)>0 and len(in_str)>0:
            card_win.chgat(-1,c.color_pair(BK_CARD))
            out_symbol(card_win,table[results[sel+skip]])
            card_win.addstr(0,1,make_card(table[results[sel+skip]],format_length),c.color_pair(BK_CARD))
            card_win.chgat(-1,c.color_pair(BK_CARD))
            card_win.refresh()

        out_input(search_win,in_str)
        if len(in_str)>0:
            (max_sel,appeared)=out_results(search_win,results,sel,skip)
            if appeared==False:#next selected monster too long
                skip+=1
                sel-=1
                tries+=1
                if tries<5:
                    continue
                else:
                    tries=tries
        tries=0
        move_to_in(search_win,in_str)
        search_win.refresh()
        ch=search_win.getch()
        key=c.keyname(ch).decode("utf-8")
        if key=="KEY_F(10)":
            break
        if key=="KEY_F(1)":
            s.clear()
            failed_lines=0
            failed_monsters=0
            total=0
            failed_current_monster=False
            report=open("report-long.txt","w",encoding="utf-8")
            for mon in table.keys():
                total+=1
                test=make_card(table[mon],format_length=0)
                test=test.split("\n")
                for ln in test:
                    len_test=len(ln)
                    if len_test>SCR_WIDTH:
                        failed_lines+=1
                        failed_current_monster=True
                        report.write(f"LONG({len_test}):{mon}|[{ln[SCR_WIDTH:]}]\n")
                        report.write(ln[:SCR_WIDTH]+"\n===\n")
                    
                if failed_current_monster==True:
                    failed_monsters+=1
                    failed_current_monster=False
            report.close()
            s.addstr(f"DONE-FULL. Failed: {failed_monsters} of {total}, long lines: {failed_lines}\n")

            failed_lines=0
            failed_monsters=0
            total=0
            failed_current_monster=False
            report=open("report-short.txt","w",encoding="utf-8")
            for mon in table.keys():
                total+=1
                test=make_card(table[mon],format_length=1)
                test=test.split("\n")
                for ln in test:
                    len_test=len(ln)
                    if len_test>SCR_WIDTH:
                        failed_lines+=1
                        failed_current_monster=True
                        report.write(f"LONG({len_test}):{mon}|[{ln[SCR_WIDTH:]}]\n")
                        report.write(ln[:SCR_WIDTH]+"\n===\n")
                    
                if failed_current_monster==True:
                    failed_monsters+=1
                    failed_current_monster=False
            report.close()

            s.addstr(f"DONE-SHORT. Failed: {failed_monsters} of {total}, long lines: {failed_lines}\n")
            s.getch()

        if len(key)==1:
            in_str+=key
            sel=0
            skip=0
        if key=="KEY_RIGHT":
            sel+=1
            if sel>max_sel-1:
                sel=max_sel-1
                if sel+skip<len(results)-1:
                    skip+=1
        if key=="KEY_LEFT":
            sel-=1
            if sel<0:
                if skip>0:
                    skip-=1
                sel=0
        if key=="KEY_UP" or key=="KEY_DOWN":
            format_length=1 if format_length==0 else 0
        if key=="KEY_BACKSPACE" or key=="^H":
            in_str=in_str[:-1]
            sel=0
            skip=0






if __name__=="__main__":
    read_monsters()
    c.wrapper(main)
