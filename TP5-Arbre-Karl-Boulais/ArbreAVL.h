#ifndef main.h
#include"main.h"
#endif // !main.h
#ifndef Affichage.h
#include "Affichage.h"
#endif // !Affichage.h


#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <Windows.h>



template<typename T>
struct ArbreAVL
{

	template<typename T>
	struct Noeud
	{
		T _valeur{};
		Noeud<T>* _racine{ NULL };
		Noeud<T>* _droite{ NULL };
		Noeud<T>* _gauche{ NULL };
		Noeud<T>* _parent{ NULL };
		int _debalancement{};
		size_t _hauteur{};

	};
	Noeud<T>* _arbre = new Noeud<T>;

	/********************************************************************************************************************/
												//FONCTION DE SOUTIENS//
	/********************************************************************************************************************/
	int Max(int gauche, int droite)
	{
		int max = (gauche > droite) ? gauche : droite;
		return max;
	}

	
	char CompareValeur(T valeurPointeur, T valeurAjouter) {

		if (valeurAjouter < valeurPointeur)
			return '<';
		else if (valeurAjouter > valeurPointeur)
			return '>';
		else
			return '=';
	}

	size_t TrouvezLePlusPetit(Noeud<T>* pointeur) {

		if (pointeur->_gauche != NULL)
			return TrouvezLePlusPetit(pointeur->_gauche);
		else
			return pointeur->_valeur;
	}

	Noeud<T>* TrouverUneValeurMain(T valeur) {
		return TrouverUneValeur(_arbre->_racine, valeur);
	}

	Noeud<T>* TrouverUneValeur(Noeud<T>* pointeur, T valeur) {

		if (pointeur != NULL) {
			if (pointeur->_valeur == valeur) {
				return pointeur;
			}
			else {
				switch (CompareValeur(pointeur->_valeur, valeur)) {
				case '<':	return TrouverUneValeur(pointeur->_gauche, valeur);

				case '>':	return TrouverUneValeur(pointeur->_droite, valeur);
				}
			}
		}
		else
			return NULL;
	}

	int calculerHauteur(Noeud<T>* noeud)
	{
		if (noeud == NULL) 
			return -1;
		return Max(calculerHauteur(noeud->_droite), calculerHauteur(noeud->_gauche)) + 1;
	}
	

	/********************************************************************************************************************/
														//AJOUT//
	/********************************************************************************************************************/

	Noeud<T>* AjouterNoeud(Noeud<T>* pointeur, T valeur) {

		Noeud<T>* noeud = new Noeud<T>;
		//noeud = pointeur;
		noeud->_valeur = valeur;
		noeud->_gauche = NULL;
		noeud->_droite = NULL;
		if (_arbre->_racine != NULL)
			noeud->_parent = pointeur;
		//return noeud;
		return Balancement(noeud);
	}

	void AjouterArbreMain(T valeur) {
		AjouterArbre(_arbre->_racine, valeur);
	}

	void AjouterArbre(Noeud<T>* pointeur, T valeur) {

		//Détermine la racine
		if (_arbre->_racine == NULL) {
			_arbre->_racine = AjouterNoeud(pointeur, valeur);
		}
		else {
			switch (CompareValeur(pointeur->_valeur, valeur)) {
			case '<'://Va à gauche
				if (pointeur->_gauche != NULL) {
					AjouterArbre(pointeur->_gauche, valeur);
				}
				else {
					pointeur->_gauche = AjouterNoeud(pointeur, valeur);
				}
				break;
			case '>'://Va à droite
				if (pointeur->_droite != NULL) {
					AjouterArbre(pointeur->_droite, valeur);
				}
				else {
					pointeur->_droite = AjouterNoeud(pointeur, valeur);
				}
				break;
			case '='://Choisir une autre valeur
				ValeurDejaPresente(valeur);
			}

		}
	
	}

	/********************************************************************************************************************/
														//RETIRER//
	/********************************************************************************************************************/
	
	void RetirerUneValeur(Noeud<T>* pointeur, Noeud<T>* match, bool enfantGauche) {//bool enfantGauche = si c'est vrai c'est la valeur de gauche
		if (_arbre->_racine != NULL) {
			Noeud<T>* delPointeur;
			T valeurMatch = match->_valeur;
			T LePlusPetitDansDroit;

			//Cas 1 -> 0 enfant ni à Gauche ni à Droite
			if (match->_gauche == NULL && match->_droite == NULL) {

				delPointeur = match;
				enfantGauche == true ? pointeur->_gauche = NULL : pointeur->_droite = NULL;
				delete delPointeur;
			}
			//Cas 2 -> 1 enfant à Droite
			else if (match->_gauche == NULL && match->_droite != NULL) {

				enfantGauche == true ? pointeur->_gauche = match->_droite : pointeur->_droite = match->_droite;
				match->_droite = NULL;
				delPointeur = match;
				delete delPointeur;

			}
			//Cas 3 -> 1 enfant à Gauche
			else if (match->_gauche != NULL && match->_droite == NULL) {

				enfantGauche == true ? pointeur->_gauche = match->_gauche : pointeur->_droite = match->_gauche;
				match->_gauche = NULL;
				delPointeur = match;
				delete delPointeur;
			}
			//Cas 4 -> 2 enfants
			else {

				LePlusPetitDansDroit = TrouvezLePlusPetit(match->_droite);
				RetirerNoeud(match, LePlusPetitDansDroit);
				match->_valeur = LePlusPetitDansDroit;
			}

		}
		else {
			//Erreur l'arbre est vide
		}


	}
	
	void RetirerLaRacine() {
		if (_arbre->_racine != NULL) {
			Noeud<T>* delPointeur = _arbre->_racine;
			//T valeurRacine = _arbre->_racine->_valeur;
			T LePlusPetitDansDroit{};

			//Cas 1 -> 0 enfant Gauche-Droite
			if (_arbre->_racine->_gauche == NULL && _arbre->_racine->_droite == NULL) {

				_arbre->_racine = NULL;
				delete delPointeur;
			}
			//Cas 2 -> 1 enfant à Droite
			else if (_arbre->_racine->_gauche == NULL && _arbre->_racine->_droite != NULL) {

				_arbre->_racine = _arbre->_racine->_droite;
				delPointeur->_droite = NULL;
				delete delPointeur;

			}
			//Cas 3 -> 1 enfant à Gauche
			else if (_arbre->_racine->_gauche != NULL && _arbre->_racine->_droite == NULL) {

				_arbre->_racine = _arbre->_racine->_gauche;
				delPointeur->_gauche = NULL;
				delete delPointeur;
			}
			//Cas 4 -> 2 enfants
			else {

				LePlusPetitDansDroit = TrouvezLePlusPetit(_arbre->_racine->_droite);
				RetirerNoeud(_arbre->_racine, LePlusPetitDansDroit);
				_arbre->_racine->_valeur = LePlusPetitDansDroit;
			}
		}
		else
			cout << "erreur";//Message d'erreur

	}

	void RetirerNoeudMain(T valeur) {
		RetirerNoeud(_arbre->_racine, valeur);
	}
	
	void RetirerNoeud(Noeud<T>* pointeur, T valeur) {

		if (_arbre->_racine != NULL) {
			if (_arbre->_racine->_valeur == valeur)
				RetirerLaRacine();
			else {
				if (valeur < pointeur->_valeur && pointeur->_gauche != NULL) {
					pointeur->_gauche->_valeur == valeur ?
						RetirerUneValeur(pointeur, pointeur->_gauche, true) :
						RetirerNoeud(pointeur->_gauche, valeur);
				}
				else if (valeur > pointeur->_valeur&& pointeur->_droite != NULL) {
					pointeur->_droite->_valeur == valeur ?
						RetirerUneValeur(pointeur, pointeur->_droite, false) :
						RetirerNoeud(pointeur->_droite, valeur);
				}
				else
					cout << "Erreur la valeur est absente";
			}

		}
		else
			cout << "L'arbre est vide";
	}
	/********************************************************************************************************************/
														//BALANCEMENT//
	/********************************************************************************************************************/
	
	int FacteurDeBalancement(Noeud<T>* noeud) {

		if (noeud == NULL) 
			return 0;
		return   (calculerHauteur(noeud->_droite) + 1) - (calculerHauteur(noeud->_gauche) + 1);
	}

	/*Noeud<T>* DetermineOuDebalancement(Noeud<T>* noeud) {



	}*/

	bool isUnbalancedLeft(int factor) {
		return factor < -1;
	}

	bool isUnbalancedRight(int factor) {
		return factor > 1;
	}

	bool isUnbalanced(int factor) {

		return factor > 1 || factor < -1;
	}



	bool isSimpleLeftCase(int parentFactor, int childFactor) {

		return parentFactor == 2 && childFactor == 1;
	}

	bool isRightLeftCase(int parentFactor, int childFactor) {

		return parentFactor == 2 && childFactor == -1;
	}

	bool isSimpleRightCase(int parentFactor, int childFactor) {

		return parentFactor == -2 && childFactor == -1;
	}

	bool isLeftRightCase(int parentFactor, int childFactor) {

		return parentFactor == -2 && childFactor == 1;
	}



	Noeud<T>* simpleLeft(Noeud<T>* node) {

		Noeud<T>* X = node->_droite;
		Noeud<T>* Y = X->_gauche;

		X->_gauche = node;
		node->_droite = Y;
		return X;
	}

	Noeud<T>* simpleRight(Noeud<T>* node) {
		Noeud<T>* X = node->_gauche;
		Noeud<T>* Y = X->_droite;

		X->_droite = node;
		node->_gauche = Y;
		return X;

	}

	Noeud<T>* RightLeft(Noeud<T>* node) {

		node->_droite = simpleRight(node->_droite);
		node = simpleLeft(node);

		return node;
	}

	Noeud<T>* leftRight(Noeud<T>* node) {

		node->_gauche = simpleLeft(node->_gauche);
		node = simpleRight(node);

		return node;
	}


	Noeud<T>* Balancement(Noeud<T>* noeud) {


		int parentFactor = FacteurDeBalancement(noeud);

		if (isUnbalanced(parentFactor)) {

			if (isUnbalancedLeft(parentFactor)) {

				int childFactor = FacteurDeBalancement(noeud->_gauche);

				if (isSimpleRightCase(parentFactor, childFactor))
					noeud = simpleRight(noeud);

				else if (isLeftRightCase(parentFactor, childFactor))
					noeud = leftRight(noeud);

				else
					noeud = simpleRight(noeud);

			}
			if (isUnbalancedRight(parentFactor)) {

				int childFactor = FacteurDeBalancement(noeud->_droite);

				if (isSimpleLeftCase(parentFactor, childFactor))
					noeud = simpleLeft(noeud);

				else if (isRightLeftCase(parentFactor, childFactor))
					noeud = RightLeft(noeud);

				else
					noeud = simpleLeft(noeud);
			}

		}
		return noeud;
	}
	/********************************************************************************************************************/
														//PARCOURS//
	/********************************************************************************************************************/
	void ParcourInfixe(Noeud<T>* pointeur)
	{
		if (pointeur != NULL)
		{
			ParcourInfixe(pointeur->_gauche);
			ParcoursValeur(pointeur->_valeur);
			ParcourInfixe(pointeur->_droite);
		}
	}
	void ParcourPrefixe(Noeud<T>* pointeur)
	{
		if (pointeur != NULL)
		{
			ParcoursValeur(pointeur->_valeur);
			ParcourPrefixe(pointeur->_gauche);
			ParcourPrefixe(pointeur->_droite);
		}
	}

	void ParcourPostfixe(Noeud<T>* pointeur)
	{
		if (pointeur != NULL)
		{
			ParcourPostfixe(pointeur->_gauche);
			ParcourPostfixe(pointeur->_droite);
			ParcoursValeur(pointeur->_valeur);
		}
	}
	/********************************************************************************************************************/
														//AFFICHAGE//
	/********************************************************************************************************************/
	void ValeurDejaPresente(T valeur) {
		clrscr();
		cout << endl << endl << "\t La valeur " << valeur << " que vous voulez ajouter existe déjà!";
	}

	void ParcoursValeur(T valeur) {
		cout << "->" << valeur;
	}

	void AfficherParcours() {
		cout << "Parcours Infixe: " << endl;
		ParcourInfixe(_arbre->_racine);
		cout << endl << endl << "Parcours Postfixe: " << endl;
		ParcourPostfixe(_arbre->_racine);
		cout << endl << endl << "Parcours prefixe: " << endl;
		ParcourPrefixe(_arbre->_racine);

	}

	void AfficherUneValeur(T valeur) {
		Noeud<T>* pointeur = TrouverUneValeur(valeur);

		if (pointeur != NULL)
			cout << pointeur->_valeur;

		else
			cout << "La valeur " << valeur << " ne se trouve pas dans l'arbre!";
	}


	const int SCREEN_WIDTH = 120;
	const int INITIAL_Y = 0;
	Console c;

	int getDisplayedRowByDepth(int maxDepth, int depthOfNodeToPrint) {
		if (depthOfNodeToPrint == 0) {
			return 0;
		}
		int acc = (int)pow(2, maxDepth - (depthOfNodeToPrint - 1));

		int depth = getDisplayedRowByDepth(maxDepth, depthOfNodeToPrint - 1) + acc;
		return depth;

	}

	int getMaxWidth(int depth) {
		return (int)pow(2, depth + 2) - 2;
	}
	void printNode(Noeud<T>* node, int x, int y, int maxDepth, int nodeDepth) {
		cout << node->_valeur;
		int nextRowToPrint = getDisplayedRowByDepth(maxDepth, nodeDepth + 1);
		if (node->_gauche != NULL) {
			int leftX = x, leftY = y;
			printLeftLink(leftX, leftY, nextRowToPrint);
			gotoxy(--leftX, leftY);
			cout << std::setw(2) << std::right;
			printNode(node->_gauche, leftX, leftY, maxDepth, nodeDepth + 1);
		}
		if (node->_droite != NULL) {
			int rightX = x + 1, rightY = y;
			printRightLink(rightX, rightY, nextRowToPrint);
			gotoxy(rightX, rightY);
			cout << std::setw(2) << std::left;
			printNode(node->_droite, rightX, rightY, maxDepth, nodeDepth + 1);
		}
	}

	void showTree(Noeud<T>* root, int maxDepth) {
		if (root == NULL) {
			showEmptyTreeMessage();
		}
		else {
			int maxWidth = getMaxWidth(maxDepth);
			resizeScreen(maxWidth, getDisplayedRowByDepth(maxDepth, maxDepth));
			gotoxy(maxWidth / 2 + maxDepth, INITIAL_Y);
			printNode(root, maxWidth / 2 + maxDepth, INITIAL_Y, maxDepth, 0);
			_getch();
			//clrscr();
		}
	}

	void showEmptyTreeMessage() {
		cout << endl << endl << endl << endl << endl << endl
			<< "L'arbre est vide!"
			<< endl << endl << endl << endl;
		_getch();
		clrscr();
	}

	void resizeScreen(int maxWidth, int maxHeight)
	{
		int cols = c.get_wColumn();
		int rows = c.get_wLines();
		int x = maxWidth + 5 > cols ? maxWidth + 5 + 1 : cols;
		int y = maxHeight + 1 > rows ? maxHeight + 1 : rows;
		c.set_wSize(x, y);
	}

	void printRightLink(int& x, int& y, int stopAt)
	{
		gotoxy(++x, ++y);
		while (y < stopAt) {
			cout << '\\';
			gotoxy(++x, ++y);
		}
	}

	void printLeftLink(int& x, int& y, int stopAt)
	{
		gotoxy(--x, ++y);
		while (y < stopAt) {
			cout << '/';
			gotoxy(--x, ++y);
		}
	}

	










	//void afficherGraphique()
	//{

	//	if (_arbre->_racine == NULL)
	//		return;

	//	// Permet de cacher les noeuds NULL au lieu d'afficher des XX
	//	bool afficherGraphiqueNoeudsNull = true;

	//	std::string arbre = "";
	//	std::string espace = "  ";
	//	std::string lienGauche = " /";
	//	std::string lienDroite = "\\ ";
	//	std::string noeudNull = afficherGraphiqueNoeudsNull ? "XX" : "  ";

	//	std::vector< Noeud<T>* > noeuds;
	//	int largeurParent = 1;
	//	int indexParent = 0;

	//	_arbre->_hauteur = calculerHauteur(_arbre->_racine);

	//	while (_arbre->_hauteur > 0)
	//	{
	//		if (noeuds.empty())
	//		{
	//			// Afficher le premier noeud de l'arbre
	//			noeuds.push_back(_arbre->_racine);
	//			for (int i = 0; i < pow(2, _arbre->_hauteur - 1); ++i)
	//				arbre += espace;

	//			char debutString[10] = "  ";
	//			if (_arbre->_racine != NULL)
	//				sprintf_s(debutString, "%2d", _arbre->_racine->_valeur);
	//			arbre += debutString;
	//		}
	//		else
	//		{
	//			// Afficher les lignes entre les noeuds
	//			for (int i = 0; i < largeurParent; ++i)
	//			{
	//				int espaceAvant = (int)pow(2, _arbre->_hauteur) - 1;
	//				int espaceApres = espaceAvant - 1;

	//				int espaceGauche = (i != 0 ? espaceApres : 0) + espaceAvant;
	//				for (int i = 0; i < espaceGauche; ++i)
	//					arbre += espace;

	//				Noeud<T>* parent = noeuds[indexParent + i];
	//				Noeud<T>* gauche = parent != NULL ? parent->_gauche : NULL;
	//				Noeud<T>* droite = parent != NULL ? parent->_droite : NULL;

	//				arbre += (gauche == NULL && !afficherGraphiqueNoeudsNull) ? espace : lienGauche;
	//				arbre += espace;
	//				arbre += (droite == NULL && !afficherGraphiqueNoeudsNull) ? espace : lienDroite;
	//			}

	//			arbre += "\n";

	//			// Afficher une hauteur de noeuds de l'arbre
	//			for (int i = 0; i < largeurParent; ++i)
	//			{
	//				Noeud<T>* parent = noeuds[indexParent++];
	//				Noeud<T>* gauche = parent != NULL ? parent->_gauche : NULL;
	//				Noeud<T>* droite = parent != NULL ? parent->_droite : NULL;
	//				noeuds.push_back(gauche);
	//				noeuds.push_back(droite);

	//				int espaceAvant = (int)pow(2, _arbre->_hauteur - 1);
	//				int espaceApres = espaceAvant - 1;

	//				int espaceGauche = (i != 0 ? espaceApres : 0) + espaceAvant;
	//				for (int i = 0; i < espaceGauche; ++i)
	//					arbre += espace;

	//				if (gauche != NULL)
	//				{
	//					char temp[10];
	//					sprintf_s(temp, "%2d", gauche->_valeur);
	//					arbre += temp;
	//				}
	//				else
	//				{
	//					arbre += noeudNull;
	//				}

	//				int espaceDroite = espaceApres + espaceAvant;
	//				for (int i = 0; i < espaceDroite; ++i)
	//					arbre += espace;

	//				if (droite != NULL)
	//				{
	//					char temp[10];
	//					sprintf_s(temp, "%2d", droite->_valeur);
	//					arbre += temp;
	//				}
	//				else
	//				{
	//					arbre += noeudNull;
	//				}
	//			}

	//			largeurParent *= 2;
	//		}

	//		arbre += "\n";

	//		_arbre->_hauteur -= 1;
	//	}

	//	cout << arbre.c_str();
	//	cout << "\n";
	//}

};

