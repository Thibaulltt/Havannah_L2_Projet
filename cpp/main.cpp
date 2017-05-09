#include <iostream>
#include <string>
#include "../h/jeu.h"

/*! \file main.cpp */
/** 
\mainpage Havannah
Bienvenue sur la documentation du projet de l'année universitaire 2016/2017 de L2 Informatique.

Cette année, le projet est la contruction d'un jeu de Havannah.
Ce jeu est un jeu de société, joué sur un plateau hexagonal à cases hexagonales. Le but du jeu est simple, il faut faire une des 3 figures géométriques permises par les règles :
	-# Un pont entre 2 coins du plateau
	-# Une fourche reliant 3 côtés du tableau (les coins ne sont pas comptés comme côtés)
	-# Une boucle ayant au minimum 1 case vide en son centre

Le jeu se joue habituellement sur un plateau de longueur de côté 10, mais rin n'empêche le joueur de paramétrer cela autrement quand il prends le jeu en main.
\author Thibault de Villèle, L2 Informatique CERI Avignon
\date Début du projet : 21 Janvier 2017
\date Dernière modification : Aujourd'hui
\version 0.4
*/

using namespace std;

//! Fonction affichant le menu au joueur
/*
	\return booléen permettant d'arrêter l'exécution du programme si l'utilisateur venait à le vouloir.
*/
bool menu();
//! Fonction permettant de lancer la partie avec les paramètres prédéfinis
void lancer_partie();
//! Fonction permettant de changer les paramètres
void changer_param();

int default_taille_plateau = 8;		/*!< Taille par défaut. */
int default_nb_player = 2;		/*!< Nombre de joueurs par défaut. */

int main()
{
	while (menu())
		continue;
	std::cout << std::endl << " Merci d'avoir joué ! À bientôt !" << std::endl << std::endl;
	return 0;
}

bool menu()
{
	std::string s;
	int choix = -1;
	cout << " Bienvenue au menu principal ! \n Choisissez une option : " << endl;
	cout << " 1. Jouer au jeu avec les paramètres par défaut" << endl;
	cout << " 2. Personnaliser les paramètres de la partie" << endl;
	cout << " 0. Quitter le programme" << endl;
	cin.ignore();
	while (choix < 0 || choix > 2) {
		cout << " Votre choix : ";
		s = cin.get();
		try {
			choix = stoi(s);
			if (choix >= 0 && choix <= 2)
				break;
			else
				cout << " Valeur erronée" << endl;
		}
		catch (...) {
			cout << " Erreur dans la saisie. Veuillez choisir une autre valeur" << endl;
		}
	}
	switch (choix) {
		case 1:
			lancer_partie();
			break;
		case 2:
			changer_param();
			break;
		default:
			return 0;
	}
	cin.sync();
	return 1;
}

void lancer_partie()
{
	jeu j(default_taille_plateau, default_nb_player);
	j.a();
	while (!j.check_win())
	{
		j.tour();
		j.a();
	}
	return;
}

void changer_param()
{
	return;
}
