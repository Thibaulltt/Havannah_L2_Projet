#ifndef JEU_H
#define JEU_H
#pragma once

#include <iostream>
#include "../h/plateau.h"
#include "../h/player.h"

//! classe jeu
/*!
	Regroupe tous les éléments du jeu : le plateau, les joueurs, et les fonctions pour les coups.

	Librairies incluses : 
		- iostream
		- player.h
		- plateau.h
*/
class jeu
{
	//! Le plateau en question.
	plateau* hav;
	//! Nombre de joueurs pour le jeu
	char nb_players;
	//! Nombre d'IA à gérer
	char nb_ia;
	//! Nombre de tours qui sont passés depuis le début de la partie.
	int nbturn;
	//! Tableau de pointeurs vers tous les joueurs (classe player)
	player** players;
	//! Tableau de tous les identifiants joueur
	char* playerids;
	//! Map de toutes les cases particulières du plateau
	std::multimap<char, std::pair<int,int>> part_plateau;
	
	public:
		//! Destructeur du jeu.
		~jeu();
		//! Constructeur du jeu.
		/*!
			Constructeur de jeu qui est appelée depuis la fonction main.
			\param tp La taille désirée  du plateau.
			\param nbp Nombre de joueurs.
		*/
		jeu(int tp, int nbp);
		//! Interface pour le menu.
		void menu();
		//! Affichage des informations du tour.
		void a();
		//! Fonction permettant aux joueurs de faire un nouveau tour.
		void tour();
		//! Fonction permettant de vérifier si un joueur a gagné.
		bool check_win();
};

#endif