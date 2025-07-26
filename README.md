# NetHack External Pokedex supplemental: Parsing NetHack sources

## What is it?

This is set of utilities made to generate csv-files, containing monsters properties. After creation, files must be copied to the External Pokedex "data" folder. Then you can browse them using search.py script.

I created a separated project for each variant, because difference in source code is too big.

If you simply use External Pokedex, you don't need these projects. I already generated all needed data. But if you want to update databases or include new variant into set, you can use these projects as starting point.

## How to update projects

All projects are made in Code::Blocks using Windows EOL convention.

1. Replace files in the project directory with corresponding files from src/ and include/ folders. Don't copy config.h file.  
2. For dNetHack you must also rebuild pm.h file. You need linux machine or WSL to make it. Please read dNetHack build instructions.  
3. Try to build project. If it fails, then, probably some flags or attacks was added. Examine source code and diffs.  
4. Run project and check for errors in the output. If you see errors about "0xXXXXXXXX not found! First value is AAAA", then you must open main.cpp and find dict_s array, beginning with AAAA value. Then add new flag, attack etc., found by code 0xXXXXXXXX.  
5. Take resulting csv file and copy it to data/ folder of NetHack External Pokedex.  
6. Run tests, pressing F1. If you got an error, then open nhconstants_flags_raw.py and add new values to corresponding dicts. Also, add these values to dicts in nhconstants_atk.py and/or nhconstants_flags.py. You must think by yourself, how to modify these files. New flags must go to the correct category of flags.

## How to add new variant

1. Make a copy of similar project and rename it. Moslty, variants are similar to 3.4.3, 3.6.7 or 3.7 vanilla. Some variants are forked from another variant, for example notdNetHack is a fork of dNetHack, so it is better to take dNetHack as a base.  
2. See steps 1-6 from paragraph above. If new variant is very different, you must take additional files from sources.

Update and addings procedures are not automatic. You must use your C knowledge and NetHack source knowledge to make it work.

## Licence and author information

NETHACK GENERAL PUBLIC LICENSE. See LICENCE file for details.  
(C) 2022-2025 zHz  
You can contact me via Telegram @zHz01  
Also, please visit project's github page:  
https://github.com/zHz00/nethack_montable_parse

Main Pokedex project:  
https://github.com/zHz00/nethack_external_pokedex