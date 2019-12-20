#ifndef main.h
#include"main.h"
#endif // !main.h

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


template<typename T>
struct ArbreAVL
{
	/*Création de la structure noeud avec l'ajout du paramètre hauteur pour facilité le calcul de l'équilibre*/
	template<typename T>
	struct Noeud
	{
		T _valeur{};
		Noeud<T>* _racine{NULL};
		Noeud<T>* _droite{NULL};
		Noeud<T>* _gauche{NULL};
		Noeud<T>* _parent{NULL};
		int _debalancement{};
		size_t _hauteur{};

		
	};
	Noeud<T>* _arbre = new Noeud<T>;
	



	bool ValeurPresente(T valeur) {
		
	}

	bool PlusPetit(T valeurPointeur, T valeurAjouter) {

		if (valeurAjouter < valeurPointeur)
			return true;
		else
			return false;
	}

	Noeud<T>* AjouterNoeud(Noeud<T>* parent, T valeur) {

		Noeud<T>* noeud = new Noeud<T>*;
		noeud->_valeur = valeur;
		noeud->_gauche = NULL;
		noeud->_droit = NULL;
		noeud->_parent = parent;

		return noeud;
	}


	void AjouterArbre(Noeud<T>* pointeur, T valeur) {

		if (pointeur->_valeur == NULL) {
			_arbre->_racine->_valeur = valeur;
			_arbre->_racine->_gauche = NULL;
			_arbre->_racine->_droite = NULL;
		}
		switch (PlusPetit(pointeur->_valeur, valeur)) {
			case true://Va à gauche
				if (pointeur->_gauche != NULL) {
					AjouterArbre(pointeur->_gauche, valeur);
				}
				else {
					pointeur->_gauche = AjouterNoeud(pointeur, valeur);
				}
			case false://Va à droite
				if (pointeur->_droite != NULL) {
					AjouterArbre(pointeur->_droit, valeur);
				}
				else {
					pointeur->_droit = AjouterNoeud(pointeur, valeur);
				}

		}
		
		else if (valeur < pointeur->_valeur) {
			if (pointeur->_gauche != NULL) {
				Ajouter(pointeur->_gauche, valeur);
			}
			else {
				pointeur->_gauche = AjouterNoeud(pointeur, valeur);
			}
		}
		else
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
