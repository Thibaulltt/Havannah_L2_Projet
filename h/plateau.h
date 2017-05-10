#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "./player.h"
#include "../h/arbre.h"
#include "../h/noeud.h"

using namespace std;

//! classe plateau 
/*!
	La classe contenant tout le plateau. Interagit fortement avec la classe jeu, et à moindre envergure avec la classe player.

	Librairies incluses :
		- iostream
		- vector
		- map
*/

class plateau
{
	//! Taille d'un côté du plateau.
	int taillecote;
	//! Indice de la dernière ligne.
	int der_ligne;
	//! La structure de données pour le jeu.
	vector<int>* hexa;
	//! Différentes possibilités de finir le jeu
	enum endGame {
		NONE,	//!< Le joueur n'a pas gagné la partie
		FORK,	//!< Le joueur a fait une fourche entre 3 côtés
		RING,	//!< Le joueur a fait un cercle avec au moins un trou au mileu
		BRIDGE	//!< Le joueur a fait un pont entre 2 coins
	};
	
	public:
		//! Constructeur par défaut
		/*!
			Demande une taille de plateau au joueur et ensuite crée un plateau de la taille demandée, avec des cases contenant la valeur minimale des entiers dans C++ (-2147483648) pour signifier que la case est vide.
		*/
		plateau();
		//! Destructeur du plateau
		~plateau();
		//! Constructeur avec arguments
		/*!
			Permet à la classe jeu de créer un plateau sans pour autant demander au joueur quoi que ce soit. La taille passée en argument sera donc déterminée par la classe jeu.
			\param n taille demandée pour le plateau.
		*/
		plateau(int n);
		
		//! Affichage plateau avec des hexagones
		/*!
			Cette visualisation du plateau est une visualisation en hexagone, donnant une vision facile de l'état du plateau. En revanche, celle-ci est assez compressée en hauteur.
			Cette méthode contient 2 étapes :
				1. On va faire la première partie de l'affichage des lignes, avant que l'on atteigne la ligne du milieu de la grille (qui est, par ailleurs, la plus longue). Le haut des haxagones sera donc affiché avec le fonction aff_haut_hexa()
				2. Pareil que la partie d'avant, mais pour le bas du plateau, avec la fonction aff_bas_hexa()
			&nbsp;
			
			\param p Les identifiants joueur pour que l'on puisse afficher leur cases avec les identifiants choisis auparavant.
			\sa aff_haut_hexa() and aff_bas_hexa()

		*/
		void afficher(char* p);
		//! affichage du plateau avec des losanges
		/*!
			Les losanges représentent les hexagones. Cette visualisation permet de voir le plateau de manière plus compacte.
			Cette méthode contient 2 étapes :
				1. On va faire la première partie de l'affichage des lignes, avant que l'on atteigne la ligne du milieu de la grille (qui est, par ailleurs, la plus longue). Le haut des haxagones sera donc affiché avec le fonction aff_haut_hexa2()
				2. Pareil que la partie d'avant, mais pour le bas du plateau, avec la fonction aff_bas_hexa2()
			&nbsp;

			\param p Les identifiants joueur pour que l'on puisse afficher leur cases avec les identifiants choisis auparavant.
			\sa aff_haut_hexa2() and aff_bas_hexa2()

		*/
		void afficher2(char* p);
		
		//! Affiche contenu d'une case "n" fois
		/*!
			Permet d'afficher le contenu (l'identifiant qui est contenu dans la case) un nombre de fois donné par la fonction aff_bas_hexa(), aff_bas_hexa2(), aff_haut_hexa(), et aff_haut_hexa2().
			\param cont Le contenu de la case en question
			\param nb Le nombre de fois qu'on souhaite afficher les caractères
			\param p Les identifiants joueur pour savoir quel caractère afficher
			\sa aff_bas_hexa(), aff_bas_hexa2(), aff_haut_hexa() and aff_haut_hexa2()

		*/
		void aff_contenu(int cont, int nb, char* p);
		//! Donne la valeur de la dernière ligne
		int r_der_ligne(){return der_ligne;};
		//! Donne la valeur de la taille demandée par le joueur
		int Rtaillecote(){return taillecote;};
		
		//! Affichage bas hexa normaux
		/*!
			Affiche le bas des hexagones.
			\param a indice de la ligne de l'hexa a afficher
			\param e_l est-ce que l'on est entre 2 lignes ? si oui, afficher des underscore
			\param sep le nombre d'espaces à mettre avant chaque ligne (x4)
			\param p_l sert à déterminer si on est sur la première ligne de la grille. ce booléen permet d'enlever un des appels de la fonction et de rajouter une ligne pour rien
			\param p les identifiants joueurs
		*/
		void aff_bas_hexa(int a, bool e_l, int sep, bool p_l, char* p);
		//! Affichage bas hexa normaux
		/*!
			Haut de l'hexagone :
			<pre>
			  ____		= Ligne 1 (necessaire seulement pour le haut de la grille)
			 /    \		= Ligne 2
			/      \	= Ligne 3
			</pre>
			\param a indice de la ligne de l'hexa a afficher
			\param sep le nombre d'espaces à mettre avant chaque ligne (x6)
			\param e_l est-ce que l'on est entre 2 lignes ? si oui, afficher des underscore
			\param p_l sert à déterminer si on est sur la première ligne de la grille. ce booléen permet d'enlever un des appels de la fonction et de rajouter une ligne pour rien
			\param l_l determine si on est en derniere ligne
			\param p donne les player id
			\sa afficher()
		*/
		void aff_haut_hexa(int a, int sep, bool e_l, bool p_l, bool l_l, char* p);
		//! Affichage bas hexa en losange
		/*!
			Affiche le bas des hexagones.
			\param a indice de la ligne de l'hexa a afficher
			\param e_l est-ce que l'on est entre 2 lignes ? si oui, afficher des underscore
			\param sep le nombre d'espaces à mettre avant chaque ligne (x4)
			\param p_l sert à déterminer si on est sur la première ligne de la grille. ce booléen permet d'enlever un des appels de la fonction et de rajouter une ligne pour rien
			\param p les identifiants joueurs
		*/
		void aff_bas_hexa2(int a, bool e_l, int sep, bool p_l, char* p);
		//! Affichage haut hexa en losange
		/*!
			Haut de l'hexagone :
			<pre>
			  		= Ligne 1 (necessaire seulement pour le haut de la grille)
			 /\		= Ligne 2
			/  \	= Ligne 3
			</pre>
			\param a indice de la ligne de l'hexa a afficher
			\param e_l est-ce que l'on est entre 2 lignes ? si oui, afficher des underscore
			\param sep le nombre d'espaces à mettre avant chaque ligne (x6)
			\param p_l sert à déterminer si on est sur la première ligne de la grille. ce booléen permet d'enlever un des appels de la fonction et de rajouter une ligne pour rien
			\param l_l determine si on est en derniere ligne
			\param p donne les player id

		*/
		void aff_haut_hexa2(int a, int sep, bool e_l, bool p_l, bool l_l, char* p);
		
		//! Retourne les coordonnées des pions aux coins et aux côtés
		/*!
			Permet de savoir quels cases sont aux coins pour pouvoir vérifier si le joueur
		*/
		std::multimap<char, std::pair<int,int>> retParticuliers();
		
		//! Permet de placer un pion ( = affecter une valeur à une case)
		std::pair<int,int> placerpion(std::pair<std::pair<int,int>,char>);

		int getTaille(){return taillecote;}

		int getTailleReelle(){return der_ligne;}

		//! Fonction permettant de savoir si un joueur 'p' a gagné
		bool check_win(player p);
		
		//! Fonction permettant de suivre le chemin qu'un joueur a créé sur le plateau.
		/*!
			Appelle suivreChemin(int i, int j, arbre<int,int>& cheminJoueurs, vector<noeud<int,int>*>& indexCheminJoueur, noeud<int,int>* nouedActuel) avec un noeud créé en racine de l'arbre
		*/
		endGame suivreChemin(int i, int j, arbre<int,int>& cheminJoueurs, vector<noeud<int,int>*>& indexCheminJoueur);

		//! Suit le chemin créé par les pions voisins utilisateur
		/*!
			- Regarde tous les vosins possibles selon la position dans le plateau
			- Si un voisin est trouvé, on le cherche dans le vecteur des noeuds de l'arbre :
			  - Il n'est pas trouvé, donc on  l'ajoute et on continue la recherche a partir de ce point là (on met le booléen node_found à 1)
			  - Si il est trouvé, on continue l'analyse
			- Si le booléen node_found est à 1, alors est pas en fin de chemin, donc on ne fait rien
			- Sinon, on regarde si le joueur a fait un cercle, une fourche ou un pont.
		*/
		endGame suivreChemin(int i, int j, arbre<int,int>& cheminJoueurs, vector<noeud<int,int>*>& indexCheminJoueur, noeud<int,int>* nouedActuel);

		bool find_in_node_vector(vector<noeud<int,int>*> sourceVector, std::pair<int,int> information);
};

#endif
