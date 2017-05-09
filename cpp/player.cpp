#include <iostream>
#include "../h/player.h"

player::player()
{
	std::cout << " Création d'un nouveau joueur ! " << std::endl;
	std::cin.ignore();

	std::cout << " Saisissez un nom : " ;
	std::getline(std::cin, nom);
	while (nom == "")
	{
		std::cout << " Nom vide. Appuyez sur entrée et choisissez un nom valide (au moins 1 lettre). \n";
		std::cin.sync();
		std::cout << " Nom : ";
		nom = std::cin.get();
	}

	std::string s_ia;
	std::cout << " Voulez vous que le joueur " << nom << " soit une IA dans le jeu ? [o/n] ";
	std::getline(std::cin, s_ia);
	for (int i = 0; i < s_ia.length(); ++i)
		s_ia[i] = std::tolower(s_ia[i]);
	if (s_ia == "o")
		ia = true;
	if (s_ia == "n")
		ia = false;
	else {
		std::cout << " Valeur non comprise. Type joueur : humain" << std::endl;
		ia = false;
	}
	int p;
	
	std::cout << " Déterminez un identifiant numérique pour ce joueur [1/10] : ";
	try {
		std::cin >> p;
		p += 34;
		id = char(p);
	}
	catch (...) {
		std::cout << " Valeur non comprise. Identifiant par défaut : 10" << std::endl;
		id = 44;
	}
}

player::~player() 
{
}

std::pair<std::pair<int,int>,char> player::placer_pion()
{
	std::cout << " Tour du joueur " << nom << " avec l'identifiant " << id << " : " << std::endl;
	int p = -1;
	int pp= -1;
	std::cout << " Choisissez une case où placer votre pion : \n Coordonnée X : ";
	try {
		std::cin >> p;
	}
	catch (...){
		std::cout << " Valeur erronnée." << std::endl;
		p = 0;
	}
	std::cout << " Coordonnée Y : ";
	try {
		std::cin >> pp;
	}
	catch (...){
		std::cout << " Valeur erronnée." << std::endl;
		pp = 0;
	}
	std::pair<int,int> coord(p,pp);
	std::pair<std::pair<int,int>,char> ret_v(coord,id);
	return ret_v;
}

bool player::est_voisin(std::pair<int,int> a, std::pair<int,int> b, int taille)
{
	// Arguments :
	// a 		= coordonnées point de référence
	// b 		= coordonnées point à ajouter
	// taille	= taille plateau

	int ax = a.second;
	int ay = a.first;
	int bx = b.second;
	int by = b.first;

	if (ax <= taille/2){
		// Forme à analyser :
		// ● ●
		// ● x ●
		//   ● ●
		// x : point de ref
		// ● : points à analyser
		if (
			(bx - 1 == ax && by - 1 == ay) ||
			(bx + 1 == ax && by + 1 == ay) ||
			(bx == ax && by - 1 == ay) ||
			(bx == ax && by + 1 == ay) ||
			(bx - 1 == ax && by == ay) ||
			(bx + 1 == ax && by == ay) )
		{
			return true;
		}
	}
	if (ax == taille/2+taille%2){
		// Forme à analyser :
		// ● ●
		// ● x ●
		// ● ●
		// x : point de ref
		// ● : points à analyser
		if (
			(bx - 1 == ax && by - 1 == ay) ||
			(bx - 1 == ax && by + 1 == ay) ||
			(bx - 1 == ax && by == ay) ||
			(bx == ax && by - 1 == ay) ||
			(bx == ax && by + 1 == ay) ||
			(bx + 1 == ax && by == ay) )
		{
			return true;
		}
	}
	if (ax > taille/2+taille%2){
		// Forme à analyser :
		//   ● ●
		// ● x ●
		// ● ●
		// x : point de ref
		// ● : points à analyser
		if (
			(bx - 1 == ax && by + 1 == ay) ||
			(bx + 1 == ax && by - 1 == ay) ||
			(bx == ax && by - 1 == ay) ||
			(bx == ax && by + 1 == ay) ||
			(bx - 1 == ax && by == ay) ||
			(bx + 1 == ax && by == ay) )
		{
			return true;
		}
	}
	return false;
}