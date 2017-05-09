#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include <iostream>
#include <vector>
#include <list>
#include "./arbre.h"
#include "./noeud.h"

//! class joueur
/*!
	La classe player sert à gérer toutes les infos du joueur lors du jeu.
	Permet de créer, détruire, stocker les coups, jouer, afficher l'état du joueur.
	Librairies incluses : 
		- iostream
		- vector
		- list
*/

class player
{
	//! Stocke le nom choisi par le joueur.
	std::string nom;
	//! Sert à savoir si un joueur est une IA ou pas.
	bool ia;
	//! Identificateur qui sert à différencier les joueur entre eux.
	char id;

	public:
		//! Constructeur vide.
		/*!
			Il sert à créer un joueur en demandant un nom, un identifiant et en demandant si le joueur sera une IA ou pas.

			Fonctionnement :
				-# On informe le joueur qu'on va créer son personnage dans le jeu
				-# On lui demande un nom ( via un getline() ):
					- Tant qu'il ne fournit pas de nom, on redemande la saisie.
					- On affecte ensuite le nom choisi à la variable nom.
				-# On demande si il souhaite que ce personnage soit une IA ( via un getline() suivi d'un tolower() pour normaliser l'entrée utilisateur ):
					- Si oui, on affecte le booléen ia à 1
				-# On lui demande un identifiant entre 1 et 10 :
					- Si il rentre un identifiant supèrieur, on ne gère pas
					- Si l'entrée utilisateur est non comprise, on affecte la valeur 10 par défaut
		*/
		player();
		//! Destructeur par défaut.
		~player();
		//! Retour de l'identifiant joueur.
		char returnId(){return id;};
		//! Retour de l'etat du joueur (humain ou non).
		bool returnIa(){return ia;};
		//! Réaffectation de l'identifiant joueur.
		void newid(char t){id = t;};
		//! Retour du nom du joueur.
		std::string returnNom(){return nom;};
		//! Demande du choix joueur pour son tour
		/*!
			Demande au joueur sur quelle case il souhaite placer le pion, sans se soucier de la taille du plateau.
			\return Une paire composée d'un identifiant, et de coordonnées x et y pour le placement sur le plateau.
			\sa ajouter_coup()
		*/
		std::pair<std::pair<int,int>,char> placer_pion();
		//! Vérifie le voisinage d'une case
		/*!
			Prends en argument 2 coordonnées x et y ainsi que la taille du plateau. Ensuite, vérifie si ceux ci sont voisins ou non selon leur place dans le plateau.
			\param point_orig Le point de référence à partir duquel on vérifie le voisinage.
			\param point_nouv Le point dont on veut vérifier la position.
			\param t Taille du plateau (pour déterminer la forme du voisinage dans le tableau).
			\return Un booléen permettant de savoir si les points sont voisins.
		*/
		bool est_voisin(std::pair<int,int> point_orig, std::pair<int,int> point_nouv, int t);
		//! Vérification de la victoire d'un joueur
		bool check_win();
		//! Affichage des coups joueur
		void affcoups();
};

#endif
