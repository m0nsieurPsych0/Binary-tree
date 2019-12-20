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
		Noeud<T>* _debut{NULL};
		Noeud<T>* _droite{NULL};
		Noeud<T>* _gauche{NULL};
		Noeud<T>* _parent{NULL};
		int _debalancement{};
		size_t _hauteur{};

		
	};
	Noeud<T>* _arbre = new Noeud<T>;
	int compteur = 0;


		int calculerHauteur(Noeud<T>* noeud)			/*Fonction récursive pour calculer la hauteur d'un seul noeud*/
		{
			if (noeud == NULL)
				return -1;
			else
				return Max(calculerHauteur(noeud->_gauche), calculerHauteur(noeud->_droite)) + 1;
		}

		void MiseAJourHauteur(Noeud<T>* noeud) /*Fonction pour mettre à jour la hauteur de chacun des noeuds en partant de la fin*/
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


		int Equilibre(Noeud<T>* noeud) /*Fonction de calcul de l'équilibre d'une branche */
		{
			int balance_factor, hauteurD, hauteurG;
			if (noeud->_droite != NULL) { hauteurD = (noeud->_droite->_hauteur) + 1; }
			else hauteurD = 0;
			if (noeud->_gauche != NULL) { hauteurG = (noeud->_gauche->_hauteur) + 1; }
			else hauteurG = 0;

			balance_factor = hauteurG - hauteurD;

			return balance_factor;
		}

		Noeud<T>* ParcourirArbre(Noeud<T>* noeud)/*Fonction pour trouver et retourné le noeud débalancé en paratant du dernier ajout*/
		{
			if (noeud == NULL)
				return NULL;

			else if (Equilibre(noeud) < -1 || Equilibre(noeud) > 1)
				return noeud;
			else
				ParcourirArbre(noeud->_parent);
		}



		void ajouter(T valeur)
		{
			Noeud<T>* nouveauNoeud = new Noeud<T>;
			Noeud<T>* NoeudDebalance = NULL;
			nouveauNoeud->_valeur = valeur;
			if (_arbre->_debut == NULL)		/*On vérifie si le début est vide. S'il l'est, c'est que l'arbre est vide et on*/
			{						/*peut assigner une valeur à _debut*/
				_arbre->_debut = nouveauNoeud;
			}
			else
			{
				Noeud<T>* NoeudDummy = _arbre->_debut; /*Création d'un itérateur pour passer au travers de l'arbre*/
				while (nouveauNoeud->_parent == NULL)/*Tant que le nouveau noeud n'a pas de parent, on continue*/
				{
					if (nouveauNoeud->_valeur < NoeudDummy->_valeur) /*Si la valeur qu'on ajoute est plus petite que la valeur */
					{												 /*du noeud temporaire, on va chercher dans le sous-arbre gauche */
						if (NoeudDummy->_gauche == NULL)
						{
							nouveauNoeud->_parent = NoeudDummy;
							NoeudDummy->lierEnfantGauche(nouveauNoeud);
						}
						else
							NoeudDummy = NoeudDummy->_gauche;

					}
					else if (nouveauNoeud->_valeur >= NoeudDummy->_valeur)/*Sinon, on va dans le sous-arbre droit*/
					{
						if (NoeudDummy->_droite == NULL)
						{
							nouveauNoeud->_parent = NoeudDummy;
							NoeudDummy->lierEnfantDroite(nouveauNoeud);
						}
						else
							NoeudDummy = NoeudDummy->_droite;
					}
				}
			}
			afficherGraphique();

			MiseAJourHauteur(_arbre->_debut); /*Appel de la fonction de mise à jour de la hauteur de chacun de noeud */

			if (_arbre->_debut->_hauteur > 1) {
				NoeudDebalance = ParcourirArbre(nouveauNoeud); /*On trouve et on assigne le noeud débalancé le plus proche du dernier ajout */

				if (NoeudDebalance != NULL)/*Le il y a débalancement dans l'arbre, on procède au test pour effectuer les rotations*/
				{
					/*Gauche Gauche*/
					if (Equilibre(NoeudDebalance) > 1 && valeur < NoeudDebalance->_gauche->_valeur) /*Si l'équilibre est plus grand que 1, on sait que le déséquilibre arrive dans le sous-arbre gauche*/
					{																				/*Si la valeur du dernier ajout est plus petite que la valeur du noeud débalancé, on sait qu'il s'agit de l'enfant gauche*/
						compteur++;
						cout << "Debalancement " << compteur << " - Gauche gauche" << endl;
						rotationnerDroite(NoeudDebalance);

					}
					/*Gauche Droite*/
					if (Equilibre(NoeudDebalance) > 1 && valeur > NoeudDebalance->_gauche->_valeur)
					{
						compteur++;
						cout << "Debalancement " << compteur << " - Gauche droite" << endl;
						rotationnerGauche(NoeudDebalance->_gauche);
						rotationnerDroite(NoeudDebalance);
					}
					/*Droite Droite*/
					if (Equilibre(NoeudDebalance) < -1 && valeur > NoeudDebalance->_droite->_valeur)
					{
						compteur++;
						cout << "Debalancement " << compteur << " - Droite droite" << endl;
						rotationnerGauche(NoeudDebalance);
					}
					/*Droite Gauche*/
					if (Equilibre(NoeudDebalance) < -1 && valeur < NoeudDebalance->_droite->_valeur)
					{
						compteur++;
						cout << "Debalancement " << compteur << " - Droite gauche" << endl;
						rotationnerDroite(NoeudDebalance->_droite);
						rotationnerGauche(NoeudDebalance);
					}
				}
			}
		}

		void rotationnerGauche(Noeud<T>* pivot)
		{
			Noeud<T>* Temp1 = pivot->_droite;
			Noeud<T>* Temp2 = Temp1->_gauche;
			cout << "Rotation gauche de " << Temp1->_valeur << " et " << pivot->_valeur << endl;
			Temp1->_gauche = pivot;
			Temp1->_parent = pivot->_parent;

			pivot->_parent = Temp1;
			pivot->_droite = Temp2;
			if (pivot == _arbre->_debut)
			{
				_arbre->_debut = Temp1;
			}
			else if (Temp1->_valeur < Temp1->_parent->_valeur)
				Temp1->_parent->_gauche = Temp1;
			else if (Temp1->_valeur >= Temp1->_parent->_valeur)
				Temp1->_parent->_droite = Temp1;
			afficherGraphique();

		}

		void rotationnerDroite(Noeud<T>* pivot)
		{
			Noeud<T>* Temp1 = pivot->_gauche;
			Noeud<T>* Temp2 = Temp1->_droite;
			cout << "Rotation droite de " << Temp1->_valeur << " et " << pivot->_valeur << endl;
			Temp1->_droite = pivot;
			Temp1->_parent = pivot->_parent;

			pivot->_parent = Temp1;
			pivot->_gauche = Temp2;
			if (pivot == _arbre->_debut)
			{
				_arbre->_debut = Temp1;
			}
			else if (Temp1->_valeur < Temp1->_parent->_valeur)
				Temp1->_parent->_gauche = Temp1;
			else if (Temp1->_valeur >= Temp1->_parent->_valeur)
				Temp1->_parent->_droite = Temp1;
			afficherGraphique();
		}

		int calculerHauteur()
		{

			return calculerHauteurRecursif(_arbre->_debut);
		}

		int calculerHauteurRecursif(Noeud<T>* noeud)
		{																   // Pour calculer la hauteur, il faut procédé par étape
			if (noeud == NULL)											   //1: Si le noeud est NULL on retourne 0;
				return 0;												   //
			int MaxGauche = calculerHauteurRecursif(noeud->_gauche);	   //2: On évalue le sous arbre gauche
			int MaxDroit = calculerHauteurRecursif(noeud->_droite);		   //3: On évalue le sous arbre droit 
			int max = ((MaxGauche > MaxDroit) ? MaxGauche : MaxDroit);	   //4: On détermine le maximum entre les 2
			return max + 1; // Une fois qu'on a rencontrer null une fois, on ajoute 1 pour chacuns des noeuds qu'on croise
		}

		void afficherGraphique()
		{

			if (_arbre->_debut == NULL)
				return;

			// Permet de cacher les noeuds NULL au lieu d'afficher des XX
			bool afficherGraphiqueNoeudsNull = true;

			string arbre = "";
			string espace = "  ";
			string lienGauche = " /";
			string lienDroite = "\\ ";
			string noeudNull = afficherGraphiqueNoeudsNull ? "XX" : "  ";

			vector< Noeud<T>* > noeuds;
			int largeurParent = 1;
			int indexParent = 0;

			int hauteur = calculerHauteur();
			while (hauteur > 0)
			{
				if (noeuds.empty())
				{
					// Afficher le premier noeud de l'arbre
					noeuds.push_back(_arbre->_debut);
					for (int i = 0; i < pow(2, hauteur - 1); ++i)
						arbre += espace;

					char debutString[10] = "  ";
					if (_arbre->_debut != NULL)
						sprintf_s(debutString, "%2d", _arbre->_debut->_valeur);
					arbre += debutString;
				}
				else
				{
					// Afficher les lignes entre les noeuds
					for (int i = 0; i < largeurParent; ++i)
					{
						int espaceAvant = (int)pow(2, hauteur) - 1;
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

						int espaceAvant = (int)pow(2, hauteur - 1);
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

				hauteur -= 1;
			}

			cout << arbre.c_str();
			cout << "\n";
		}
	};

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
