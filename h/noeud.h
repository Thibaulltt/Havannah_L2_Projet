#ifndef NOEUD_H
#define NOEUD_H
#pragma once

template <class T,class U> class noeud {
	public:
		//! Pointeur vers le père du noeud
		noeud* pere;
		//! Pointeur vers le frère du noeud
		noeud* freredroit;
		//! Pointeur vers le fils du noeud
		noeud* filsgauche;
		//! Information stockée
		std::pair<T, U> info;
		//! Constructeur sans argument
		noeud() {
			pere = NULL;
			freredroit = NULL;
			filsgauche = NULL;
		}
		//! Destructeur de noeud
		~noeud() {}
		//! Constructeur de noeud avec données à remplir
		noeud(T info, U info2) {
			this->info = std::make_pair(info,info2);
			pere = NULL;
			freredroit = NULL;
			filsgauche = NULL;
		}
		//! Constructeur de noeud relationnel (avec les pointeurs déjà attribués)
		noeud(T i, U j, noeud* p, noeud* fg, noeud* fd) {
			info = std::pair<T,U>(i,j);
			pere = p;
			freredroit = fd;
			filsgauche = fg;
		}
		//! Fonction d'affichage d'un noeud
		void aff() {
			try {
				std::cout << "(" << info.first << info.second << ")";
			}
			catch (...) {
				std::cout << "objet non affichable";
			}
		}
		//! Surcharge d'opérateur d'égalité pour voir si une paire est égale à celle d'un noeud
		bool operator== (std::pair<T,U> paireComparee)
		{
			bool op1, op2;
			// On compare l'élement 1
			try
			{
				op1 = this->info.first == paireComparee.first;
			}
			catch (...)
			{
				std::cout << "Comparaison élément 1 impossible." << std::endl;
				return false;
			}
			// On compare l'élément 2
			try
			{
				op2 = this->info.second == paireComparee.second;
			}
			catch (...)
			{
				std::cout << "Comparaison élément 1 impossible." << std::endl;
				return false;
			}
			// Si les deux sont egaux, ca veut dire que soit c'est la même paire,
			// soit la paire est différente sur les deux parties, donc on renvoie
			// op1 pour avoir le résultat
			// Si op1 =/= op2 alors paire non égale, donc renvoie faux
			return op1 == op2 ? op1 : false;
		}
};

#endif