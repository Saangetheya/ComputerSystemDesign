# OS

## How memory is divided ?

> OS itself, master boot record for the FS (contains info about the file system , other system info's as well. System info's wil be written while boot loading the OS hardcoding but systematically we need to store these in the meory itself but i am unsure whether the  fgpa board allows you to do it ,mostly yes becoz we were able to store the  OS), bss+data(we assume same for simplicity), const, stack-heap segment, text or code segment, keyboard io memory map, display memory io map, File System (all files are arranged in order) ( it is kept in last becoz we can expand on run but only limited), temporary ( this is where we wil store all our newly uncommitted files and after save, we will write into 
the file system),OS kernel stack (here the info about the count of processes , process reg stack , some other info about them is also stored. Outline structure abt this is doubt. )

First os runs (this info is also stored)

some problems:

we are leaving the  user application to manage heap itself, thus they may encounter 
many error's (may be in future, we can add heap)

What we should intend to do should be done in the io memory map !!!

## What specification iss expected from asm ?
1. .data , .text , .const (these are the only sections that are globally displayed)
2. other stack and heap are used in runtime , not allocated during compile time
3. io memory map also comes under the same

## What can be done?
1. Assume everything in memory.

## What are the segments of os ? 
1. math.h
2. io.h
3. file.h
4. boot.h
5. global.h 
6. keyboard.h
7. screen.h
8. graphics.h
9. kcontext.h
10. types.h

## How our OS works? 
1. OS consists only of terminal that takes user input and does the stuffs we need to do in terminal.
2. Then after entering any command into the shell, that particular process related segment is 
loaded into the process run segment by the loader. loader is also part of OS that can be executed 
as a function. Then the loader changes the PC to run the process segment.