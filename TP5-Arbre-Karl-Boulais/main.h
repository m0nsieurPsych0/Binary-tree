/***************************************************************/
/*  On d�finit les librairies � inclure lorsque nous compilons */
/*  pour un syst�me windows ou unix.                           */
/*  Nous avons aussi red�finit certaines fonctions appel�es en */
/*  windows pour leur �quivalent unix                          */
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
/* ont des noms de fonctions identiques � celle contenu dans"std".*/
using std::cout;
using std::endl;
using std::cin;