/***************************************************************/
/*  On définit les librairies à inclure lorsque nous compilons */
/*  pour un système windows ou unix.                           */
/*  Nous avons aussi redéfinit certaines fonctions appelées en */
/*  windows pour leur équivalent unix                          */
/***************************************************************/

#if _WIN32
#include<windows.h>
#include<conio.h>
#ifndef cvm.h
#include"cvm.h"
#endif // !cvm.h
#elif __unix__
#include<stddef.h>
#include<stdio.h>
#define clrscr() system("clear") 
#define _getch() getchar()
#endif

//includes
#include<iostream>

/* Utiliser "namespace std" est une mauvaise pratique et          */
/* pourrait causer des erreurs lorsque d'autres librairies		  */
/* ont des noms de fonctions identiques à celle contenu dans"std".*/
using std::cout;
using std::endl;
using std::cin;