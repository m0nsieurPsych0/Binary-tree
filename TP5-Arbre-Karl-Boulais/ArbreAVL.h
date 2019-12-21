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

	int calculerHauteur()
	{
		return calculerHauteurRecursif(_arbre->_racine);
	}
	int calculerHauteur(Noeud<T>* noeud)			/*Fonction récursive pour calculer la hauteur d'un seul noeud*/
	{
		if (noeud == NULL)
			return -1;
		else
			return Max(calculerHauteur(noeud->_gauche), calculerHauteur(noeud->_droite)) + 1;
	}

	int calculerHauteurRecursif(Noeud<T>* noeud)
	{																
		if (noeud == NULL)											  
			return 0;												   
		int MaxGauche = calculerHauteurRecursif(noeud->_gauche);	   
		int MaxDroit = calculerHauteurRecursif(noeud->_droite);		    
		int max = ((MaxGauche > MaxDroit) ? MaxGauche : MaxDroit);	   
		return max + 1;													
	}

	/*Fonction pour mettre à jour la hauteur de chacun des noeuds en partant de la fin*/
	void MiseAJourHauteur(Noeud<T>* noeud) 
	{
		if (noeud == NULL)
			return;
		else
		{
			MiseAJourHauteur(noeud->_gauche);
			noeud->_hauteur = calculerHauteur(noeud);
			MiseAJourHauteur(noeud->_droite);
		}

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
		//TestDebalancement(noeud);
		return noeud;
	}

	void AjouterArbreMain(T valeur) {
		AjouterArbre(_arbre->_racine, valeur);
	}

	void AjouterArbre(Noeud<T>* pointeur, T valeur) {

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
		TestDebalancement(pointeur);
	}

	/********************************************************************************************************************/
														//RETIRER//
	/********************************************************************************************************************/
	//removeMatch()
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
	//RemoveRootMatch()
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
	//RemoveNode()
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
	void TestDebalancement(Noeud<T>* nouveauNoeud ) {
		Noeud<T>* NoeudDebalance = NULL;
		size_t compteur{0};
		MiseAJourHauteur(_arbre->_racine);
		if (_arbre->_hauteur > 1) {

			/*On trouve et on assigne le noeud débalancé le plus proche du dernier ajout */
			NoeudDebalance = TrouverDebalancement(nouveauNoeud); 

			/*Le il y a débalancement dans l'arbre, on procède au test pour effectuer les rotations*/
			if (NoeudDebalance != NULL)
			{
				
				/*Si l'équilibre est plus grand que 1, on sait que le déséquilibre arrive dans le sous-arbre gauche*/
				/*Si la valeur du dernier ajout est plus petite que la valeur du noeud débalancé, on sait qu'il s'agit de l'enfant gauche*/

				if (Equilibre(NoeudDebalance) > 1 && nouveauNoeud->_valeur < NoeudDebalance->_gauche->_valeur){/*Gauche Gauche*/
					compteur++;
					cout << "Debalancement " << compteur << " - Gauche gauche" << endl;
					RotationDroite(NoeudDebalance);
				}
				
				if (Equilibre(NoeudDebalance) > 1 && nouveauNoeud->_valeur > NoeudDebalance->_gauche->_valeur){/*Gauche Droite*/
					compteur++;
					cout << "Debalancement " << compteur << " - Gauche droite" << endl;
					RotationGauche(NoeudDebalance->_gauche);
					RotationDroite(NoeudDebalance);
				}
				
				if (Equilibre(NoeudDebalance) < -1 && nouveauNoeud->_valeur > NoeudDebalance->_droite->_valeur){/*Droite Droite*/
					compteur++;
					cout << "Debalancement " << compteur << " - Droite droite" << endl;
					RotationGauche(NoeudDebalance);
				}
				
				if (Equilibre(NoeudDebalance) < -1 && nouveauNoeud->_valeur < NoeudDebalance->_droite->_valeur){/*Droite Gauche*/
					compteur++;
					cout << "Debalancement " << compteur << " - Droite gauche" << endl;
					RotationDroite(NoeudDebalance->_droite);
					RotationGauche(NoeudDebalance);
				}
			}
		}
	}
	/*Fonction de calcul de l'équilibre d'une branche */
	int Equilibre(Noeud<T>* noeud) 
	{
		int balance_factor, hauteurD, hauteurG;
		if (noeud->_droite != NULL)
			hauteurD = (noeud->_droite->_hauteur) + 1;
		else 
			hauteurD = 0 ;
		if (noeud->_gauche != NULL)
			hauteurG = (noeud->_gauche->_hauteur) + 1;
		else 
			hauteurG = 0 ;

		balance_factor = hauteurG - hauteurD;

		return balance_factor;
	}

	/*Fonction pour trouver et retourné le noeud débalancé en paratant du dernier ajout*/
	Noeud<T>* TrouverDebalancement(Noeud<T>* noeud)
	{
		if (noeud == NULL)
			return NULL;

		else if (Equilibre(noeud) < -1 || Equilibre(noeud) > 1)
			return noeud;
		else
			TrouverDebalancement(noeud->_parent);
	}

	void RotationGauche(Noeud<T>* pivot)
	{
		Noeud<T>* Temp1 = pivot->_droite;
		Noeud<T>* Temp2 = Temp1->_gauche;
		cout << "Rotation gauche de " << Temp1->_valeur << " et " << pivot->_valeur << endl;
		Temp1->_gauche = pivot;
		Temp1->_parent = pivot->_parent;

		pivot->_parent = Temp1;
		pivot->_droite = Temp2;
		if (pivot == _arbre->_racine)
		{
			_arbre->_racine = Temp1;
		}
		else if (Temp1->_valeur < Temp1->_parent->_valeur)
			Temp1->_parent->_gauche = Temp1;
		else if (Temp1->_valeur >= Temp1->_parent->_valeur)
			Temp1->_parent->_droite = Temp1;
		

	}
	void RotationDroite(Noeud<T>* pivot)
	{
		Noeud<T>* Temp1 = pivot->_gauche;
		Noeud<T>* Temp2 = Temp1->_droite;
		cout << "Rotation droite de " << Temp1->_valeur << " et " << pivot->_valeur << endl;
		Temp1->_droite = pivot;
		Temp1->_parent = pivot->_parent;

		pivot->_parent = Temp1;
		pivot->_gauche = Temp2;
		if (pivot == _arbre->_racine)
		{
			_arbre->_racine = Temp1;
		}
		else if (Temp1->_valeur < Temp1->_parent->_valeur)
			Temp1->_parent->_gauche = Temp1;
		else if (Temp1->_valeur >= Temp1->_parent->_valeur)
			Temp1->_parent->_droite = Temp1;
		
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

	void afficherGraphique()
	{

		if (_arbre->_racine == NULL)
			return;

		// Permet de cacher les noeuds NULL au lieu d'afficher des XX
		bool afficherGraphiqueNoeudsNull = true;

		std::string arbre = "";
		std::string espace = "  ";
		std::string lienGauche = " /";
		std::string lienDroite = "\\ ";
		std::string noeudNull = afficherGraphiqueNoeudsNull ? "XX" : "  ";

		std::vector< Noeud<T>* > noeuds;
		int largeurParent = 1;
		int indexParent = 0;

		_arbre->_hauteur = calculerHauteur();

		while (_arbre->_hauteur > 0)
		{
			if (noeuds.empty())
			{
				// Afficher le premier noeud de l'arbre
				noeuds.push_back(_arbre->_racine);
				for (int i = 0; i < pow(2, _arbre->_hauteur - 1); ++i)
					arbre += espace;

				char debutString[10] = "  ";
				if (_arbre->_racine != NULL)
					sprintf_s(debutString, "%2d", _arbre->_racine->_valeur);
				arbre += debutString;
			}
			else
			{
				// Afficher les lignes entre les noeuds
				for (int i = 0; i < largeurParent; ++i)
				{
					int espaceAvant = (int)pow(2, _arbre->_hauteur) - 1;
					int espaceApres = espaceAvant - 1;

					int espaceGauche = (i != 0 ? espaceApres : 0) + espaceAvant;
					for (int i = 0; i < espaceGauche; ++i)
						arbre += espace;

					Noeud<T>* parent = noeuds[indexParent + i];
					Noeud<T>* gauche = parent != NULL ? parent->_gauche : NULL;
					Noeud<T>* droite = parent != NULL ? parent->_droite : NULL;

					arbre += (gauche == NULL && !afficherGraphiqueNoeudsNull) ? espace : lienGauche;
					arbre += espace;
					arbre += (droite == NULL && !afficherGraphiqueNoeudsNull) ? espace : lienDroite;
				}

				arbre += "\n";

				// Afficher une hauteur de noeuds de l'arbre
				for (int i = 0; i < largeurParent; ++i)
				{
					Noeud<T>* parent = noeuds[indexParent++];
					Noeud<T>* gauche = parent != NULL ? parent->_gauche : NULL;
					Noeud<T>* droite = parent != NULL ? parent->_droite : NULL;
					noeuds.push_back(gauche);
					noeuds.push_back(droite);

					int espaceAvant = (int)pow(2, _arbre->_hauteur - 1);
					int espaceApres = espaceAvant - 1;

					int espaceGauche = (i != 0 ? espaceApres : 0) + espaceAvant;
					for (int i = 0; i < espaceGauche; ++i)
						arbre += espace;

					if (gauche != NULL)
					{
						char temp[10];
						sprintf_s(temp, "%2d", gauche->_valeur);
						arbre += temp;
					}
					else
					{
						arbre += noeudNull;
					}

					int espaceDroite = espaceApres + espaceAvant;
					for (int i = 0; i < espaceDroite; ++i)
						arbre += espace;

					if (droite != NULL)
					{
						char temp[10];
						sprintf_s(temp, "%2d", droite->_valeur);
						arbre += temp;
					}
					else
					{
						arbre += noeudNull;
					}
				}

				largeurParent *= 2;
			}

			arbre += "\n";

			_arbre->_hauteur -= 1;
		}

		cout << arbre.c_str();
		cout << "\n";
	}

};

