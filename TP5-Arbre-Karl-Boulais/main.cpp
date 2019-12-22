#ifndef cvm.h
#include"cvm.h"
#endif // !cvm.h
#ifndef main.h
#include "main.h"
#endif // !main.h
#ifndef ArbreAVL.h
#include "ArbreAVL.h"
#endif // !ArbreAVL.h
#ifndef Affichage.h
#include"Affichage.h"
#endif // !Affichage.h
#ifndef userInput.h
#include "userInput.h"
#endif // !userInput.h





#include<string>
#include<iostream>

int main()
{
#if _WIN32
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
#endif

	ArbreAVL<int> arbreAVL;

	size_t menuSelect, value;

	const int ajouts[] = { 15, 10, 5, 1, 3, 25, 35, 45, 40 };
	//const int ajouts[] =   { 1, 3, 5, 10, 15, 25, 35, 40, 45 };
	
	/*for (size_t i{ 0 }; i < 9; i++) {
		arbreAVL.AjouterArbreMain(ajouts[i]);
	}*/
	for (size_t i{ 1 }; i < 30; i++) {
		arbreAVL.AjouterArbreMain(i);
	}
	
	/*do {

		clrscr();
		PrintMenu();

		FlushTampons();
		cin >> menuSelect;

		switch (menuSelect) {
		case 1:		cin >> value; arbreAVL.AjouterArbreMain(value); break;
		case 2:		arbreAVL.afficherGraphique(); _getch();				break;
		case 3:		cin >> value; arbreAVL.RetirerNoeudMain(value); _getch(); break;
		case 4:		arbreAVL.AfficherParcours();_getch();	break;
		case 5:														break;
		}

	} while (menuSelect != 5);*/
	
	arbreAVL.showTree(arbreAVL._arbre->_racine, arbreAVL.calculerHauteur(arbreAVL._arbre->_racine));

	_getch();

	return 0;
}

