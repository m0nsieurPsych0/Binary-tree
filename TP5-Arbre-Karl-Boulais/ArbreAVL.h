#pragma once
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
	char CompareValeur(T valeurPointeur, T valeurAjouter) {

		if (valeurAjouter < valeurPointeur)
			return '<';
		else if (valeurAjouter > valeurPointeur)
			return '>';
		else
			return '=';
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

	/*size_t CalculerLaHauteurArbre() {
		size_t gauche = HauteurBrancheGauche(_arbre->_racine);
		size_t droite = HauteurBrancheDroite(_arbre->_racine);
		return (( gauche > droite) ? gauche : droite) + 1;
	}

	size_t HauteurBrancheGauche(Noeud<T>* pointeur) {
		if (pointeur == NULL)
			return 0;
		size_t brancheGauche = HauteurBrancheGauche(pointeur->_gauche);
	}
	size_t HauteurBrancheDroite(Noeud<T>* pointeur) {
		if (pointeur == NULL)
			return 0;
		size_t brancheDroite = HauteurBrancheDroite(pointeur->_gauche);
	}*/


	size_t TrouvezLePlusPetit(Noeud<T>* pointeur) {

		if (pointeur->_gauche != NULL)
			return TrouvezLePlusPetit(pointeur->_gauche);
		else
			return pointeur->_valeur;
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

	//	//int hauteur = calculerHauteur();
	//	while (hauteur > 0)
	//	{
	//		if (noeuds.empty())
	//		{
	//			// Afficher le premier noeud de l'arbre
	//			noeuds.push_back(_arbre->_debut);
	//			for (int i = 0; i < pow(2, hauteur - 1); ++i)
	//				arbre += espace;

	//			char debutString[10] = "  ";
	//			if (_arbre->_debut != NULL)
	//				sprintf_s(debutString, "%2d", _arbre->_debut->_valeur);
	//			arbre += debutString;
	//		}
	//		else
	//		{
	//			// Afficher les lignes entre les noeuds
	//			for (int i = 0; i < largeurParent; ++i)
	//			{
	//				int espaceAvant = (int)pow(2, hauteur) - 1;
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

	//				int espaceAvant = (int)pow(2, hauteur - 1);
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

	//		hauteur -= 1;
	//	}

	//	cout << arbre.c_str();
	//	cout << "\n";
	//}

};

/*****************************************************************************************************************************************/

//Affichage custom

//	int get_tree_height(node<T>* root) const
//	{
//		if (root == nullptr) return 0;
//		const int left_height = get_tree_height(root->get_left());
//		const int right_height = get_tree_height(root->get_right());
//		return left_height > right_height ? left_height + 1 : right_height + 1;
//	}
//
//	
//	int get_nodes_count(int level)
//	{
//		//return int(pow(2, level));
//		return int(pow(2, level));
//	}
//
//	
//	int get_subtree_width(int level)
//	{
//		const auto levels_below = tree_height_ - level - 1;
//		const auto nodes_count = get_nodes_count(levels_below);
//		const auto spaces_count = nodes_count - 1;
//		return node_length_ * nodes_count + space_length_ * spaces_count;
//	}
//
//	void visualize()
//	{
//
//		size_t last_level = _arbre->_hauteur - 1;
//
//
//		for (size_t level{ 0 }; level < _arbre->_hauteur; level++)
//		{
//			size_t nodes_count = get_nodes_count(level);
//			size_t last_node = nodes_count - 1;
//			size_t subtree_width = get_subtree_width(level);
//			size_t node_indentation = subtree_width / 2 - node_shift_factor_;
//			size_t nodes_spacing = subtree_width - 2 * (node_shift_factor_ - space_shift_factor_);
//			size_t branch_height = (subtree_width + 1) / 4;
//
//			cout << std::string(node_indentation, ' ');
//
//			for (auto node = 0; node < nodes_count; node++)
//			{
//				const auto node_value = values_[level][node].empty() ? empty_node_ : values_[level][node];
//				cout << setw(node_length_) << setfill('0') << node_value;
//				cout << std::string(nodes_spacing * (node != last_node), ' ');
//			}
//
//			cout << endl;
//
//			for (size_t i = 0; i < branch_height && level != last_level; i++)
//			{
//				size_t branch_indentation = subtree_width / 2 - 1 - i;
//				cout << std::string(branch_indentation, ' ');
//
//				for (size_t node = 0; node < nodes_count; node++)
//				{
//					size_t has_left_child = !values_[level + 1][2 * node].empty();
//					size_t has_right_child = !values_[level + 1][2 * node + 1].empty();
//					size_t branch_width = node_type_ + 2 * i;
//					size_t branches_spacing = nodes_spacing + 2 * (node_shift_factor_ - 1 - i);
//
//					cout << (has_left_child ? '/' : ' ');
//					cout << std::string(branch_width, ' ');
//					cout << (has_right_child ? '\\' : ' ');
//					cout << std::string(branches_spacing * (node != last_node), ' ');
//				}
//
//				cout << endl;
//			}
//		}
//
//	}
//};
