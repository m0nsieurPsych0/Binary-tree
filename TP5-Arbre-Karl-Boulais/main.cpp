#ifndef cvm.h
#include"cvm.h"
#endif // !cvm.h
#ifndef main.h
#include "main.h"
#endif // !main.h
#ifndef ArbreAVL.h
#include "ArbreAVL.h"
#endif // !ArbreAVL.h



#include<string>
#include<iostream>

int main()
{
#if _WIN32
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
#endif

	ArbreAVL<int> arbreAVL;

	const int ajouts[] = { 15, 10, 5, 1, 3, 25, 35, 45, 40 };
	//const int ajouts[] =   { 1, 3, 5, 10, 15, 25, 35, 40, 45 };
	
	for (size_t i{ 0 }; i < 9; i++) {
		arbreAVL.AjouterArbreMain(ajouts[i]);
	}
	
	//cout << arbreAVL.CalculerLaHauteurArbre();

	//arbreAVL.AfficherParcours();

	//int input{ 25 };
	//arbreAVL.RetirerNoeudMain(input);

	//cout << endl << arbreAVL.TrouvezLePlusPetit(arbreAVL._arbre->_racine);
	//arbreAVL.AfficherParcours();
	arbreAVL.afficherGraphique();

	_getch();

	return 0;
}

