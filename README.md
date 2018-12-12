# MMake

A simple Makefile generator for C and C++ (respectively mmake and mmake++).  
  
There are two commands in this project :  
* mmake   : generate C Makefile
* mmake++ : generate C++ Makefile

Both commands are used the same way, here is the help message of MMAKE :  
mmake is a program made by Klevh (Baptiste Apollinaire PRUNIER)  

How to use it :
* mmake [--OUT=...] [--LF ...] [--CF ...] [--cc=...] [--h or --help] [--f or --forced]
  
Parameters :
* --OUT=...       : define the program's name as '...'
* --cc=...        : define the compiler's name as '...'
* --h or --help   : show this help
* --f or --forced : overwrite the Makefile file if it exists
* --LF ...        : define all flags to put during linking
* --CF ...        : define all flags to put during compilation