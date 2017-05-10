#ifndef ARBRE_H
#define ARBRE_H
#pragma once

//! template d'arbres n-aires
/*!
	Ce template permet de construire des arbres avec des paires de données appartenant à deux classes différentes en tant que données d'un noeud.
	Il est utile notamment pour pouvoir construire l'arbre des coups du joueur pendant le jeu de havannah.

	Librairies utilisées :
		- vector
		- ../h/noeud.h
*/
#include "../h/noeud.h"
#include <vector>

using namespace std;

template<class T, class U> class arbre {
	public:
		//! Les données contenues dans les noeuds. Elles seront donc du type de l'arbre demandé.
		noeud<T,U>* racine;
		//! Constructeur par défaut.
		/*!
			Il initialise la racine à NULL.
		*/
		arbre() {
			racine = NULL;
		}
		//! Constructeur à deux arguments
		arbre(T info, U info2) {
			racine = new noeud<T,U>(info, info2);
		}
		~arbre(){};
		//! Cherche un noeud
		noeud<T,U>* find(T res, U res2) {
			std::pair<T,U> f = new std::pair<T,U>(res,res2);
			noeud<T,U> * c = racine;
			if (c->info == f)
				return c;
			c = c->filsgauche;
			while (c != NULL)
			{
				if (c->info == f)
					return c;
				else
				{
					// faire sur le freredroit
					if (c->filsgauche != NULL)
					{
						find(res, res2, c->filsgauche);
					}
					if (c->freredroit != NULL)
					{
						find(res, res2, c->freredroit);
					}
					c = c->freredroit;
				}
			}
		}
		//! Cherche un noeud
		noeud<T,U>* find(T res, U res2, noeud<T,U>* c) {
			if (c->info == res)
				return c;
			while (c != NULL)
			{
				if (c->filsgauche != NULL)
					find(res, c->filsgauche);
				else
				{
					if (c->freredroit != NULL)
						find(res, c->freredroit);
					c = c->freredroit;
				}
			}
		}
		//! Ajoute un noeud fils à un noeud spécifié
		noeud<T,U>* ajouter_noeud(std::pair<T,U> info, noeud<T,U>* source) {
			if (source != NULL)
			{
				if (source->filsgauche == NULL)
				{
					source->filsgauche = new noeud<T,U>(info.first, info.second, source, NULL, NULL);
					return source->filsgauche;
				}
				else
				{
					noeud<T,U>* c = source->filsgauche;
					cout << "Ajout frere" << endl << flush;
					while (c != NULL && c->freredroit != NULL)
						c = c->freredroit;
					cout << "Trouve" << endl << flush;
					c->freredroit = new noeud<T,U>(info.first, info.second, source, NULL, NULL);
					cout << "Node created" << endl << flush;
					return c->freredroit;
				}
			}
		}
		//! Renvoie le père pénultime de la branche contenant le noeud source
		noeud<T,U>* voirPere(noeud<T,U>* source, bool verifCoin, bool verifFourche, bool verifPont)
		{
			if (source == racine)
				return NULL;
			while (source->pere != NULL && source->pere != racine)
				source = source->pere;
			return source;
		}
};

#endif