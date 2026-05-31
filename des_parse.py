import json
variant=input("Enter variant short name:")
q_fname="temp"
n=0
while(q_fname!=""):
    q_fname=input("Enter file name:")
    if q_fname=="":
        break
    q_short_fname=q_fname.split("\\")[-1]
    q_role=q_short_fname.split(".")[0]
    print("role:"+q_role)
    q_file=open(q_fname,"r",encoding="utf-8")
    monsters=[]
    lines=q_file.readlines()
    for line in lines:
        m_to_add=[]        
        splitted=line.strip().split(":")
        if splitted[0]=="MONSTER":
            if len(splitted)>2:#some : in line
                splitted[1]=":".join(splitted[1:])
            splitted=splitted[1].split(",")
            if splitted[1].strip()=="random" or (splitted[1].strip()[0]==("(") and len(splitted[0].strip())<5):
                char_str=splitted[0].strip()
                if char_str[0]=="\\":#escaped
                    char=char_str[2]
                else:
                    char=char_str[1]
                m_to_add=[char]
            else:
                if len(splitted[0].strip())<5:
                    m_to_add=[splitted[1].strip().replace("\"","").replace("(","").replace(")","").strip()]
                else:
                    m_to_add_expr=splitted[0].strip().replace("\"","").replace("(","").replace(")","").strip()
                    if m_to_add_expr=="\\'":#golem with backslash
                        m_to_add_expr='\''
                    m_to_add=[m_to_add_expr]
        if splitted[0]=="ALTAR":#test for shrine
            if line.find("shrine")!=-1:#found shrine
                m_to_add=["aligned priest|aligned cleric"]
        if splitted[0]=="REGION" or splitted[0]=="ROOM":#test for morgue, barracks etc
            if line.find("\"morgue\"")!=-1:
                m_to_add=["V","Z","&","ghost","wraith"]
            if line.find("\"barracks\"")!=-1:
                m_to_add=["soldier","lieutenant","sergeant","captain"]
            if line.find("\"shop\"")!=-1:
                m_to_add=["shopkeeper"]
            #if line.find("\"temple\"")!=-1:
                #m_to_add=["aligned priest|aligned cleric"]
        if len(m_to_add)>0:
            for m in m_to_add:
                if m not in monsters:
                    monsters.append(m)
    n+=1
    print("List:"+str(monsters)+f"\nN={n}\n")
    filter_fname="filters_q.json"
    filter_f=open(filter_fname,"r",encoding="utf-8")
    filters=json.load(filter_f)
    filter_f.close()
    f_cur=dict()
    f_cur["variants"]=[variant]
    f_cur["name"]=q_role
    f_cur["name_short"]=q_role
    f_cur["type"]="monsters_list"
    f_cur["highlight"]=[]
    f_cur["monsters"]=monsters
    filters[0]["filters_list"].append(f_cur)
    filter_fname="filters_q.json"
    filter_f=open(filter_fname,"w",encoding="utf-8")
    json.dump(filters,filter_f,indent=4)
    filter_f.close()