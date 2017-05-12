/*! \file

	Fichier source contenant les fonctions de la classe plateau.
	Pour le plateau, j'ai choisi de représenter la grille hexagonale comme un
	tableau de dimensions (2*taillecote)-1 on doit faire un affichage en hexagone,
	pour cela j'ai choisi le symbole en "ascii art" de l'hexagone suivant :

		  ____
		 /    \
		/      \
		\      / 
		 \____/
	Ce qui nous donne des grilles ressemblant à :

				____ 
		       /    \
		  ____/      \____
		 /    \      /    \
		/      \____/      \
		\      /    \      /
		 \____/------\____/
		 /    \------/    \
		/======\____/======\
		\======/    \======/
		 \____/------\____/
		      \------/
		       \____/
	Les pièces appartenant à des joueurs différents seront différenciées par
	le symbole qui les remplit.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../h/plateau.h"

using namespace std;

plateau::plateau()
{
	string s;
	int nn;
	cout << " Donnez une taille pour la grille : ";
	cin >> nn;
	while ( nn < 3 )
	{
		cout << " Grille demandée trop petite, veuillez resaisir une nouvelle valeur : ";
		try
		{
			cin.ignore();
			s = cin.get();
			nn = stoi(s);
		}
		catch (...)
		{
			// Pour N'IMPORTE QUELLE EXCEPTION
			cout << " Une erreur s'est produite. \n Le programme revient à sa valeur par défaut : 8." << endl;
			nn = 8;
			break;
		}
	}
	// Fonction de construction
	taillecote = nn;
	int a = taillecote;
	int t = taillecote*2 - 1;
	der_ligne = t;
	hexa = new vector<int>[t];
	for (int i = 0; i < taillecote; ++i)
	{
		for (int j = 0; j < a; ++j)
		{
			hexa[i].push_back(-2147483648);	// Valeur case vide
		}
		a++;
	}
	a--;
	for (int i = taillecote; i < t; i++)
	{
		a--;
		for (int j = 0; j < a; ++j)
		{
			hexa[i].push_back(-2147483648);		// Valeur case vide
		}
	}
}

plateau::plateau(int nn)
{
	taillecote = nn;
	int a = taillecote;
	int t = taillecote*2 - 1;
	der_ligne = t;
	hexa = new vector<int>[t];
	for (int i = 0; i < taillecote; ++i)
	{
		for (int j = 0; j < a; ++j)
		{
			hexa[i].push_back(-2147483648);		// Valeur case vide
		}
		a++;
	}
	a--;
	for (int i = taillecote; i < t; i++)
	{
		a--;
		for (int j = 0; j < a; ++j)
		{
			hexa[i].push_back(-2147483648);		// Valeur case vide
		}
	}
}

plateau::~plateau()
{
	for (int i = 0; i<der_ligne; ++i)
	 	hexa[i].clear();
}

void plateau::afficher(char* p)
{
	cout << endl;
	int aff_taillecote = taillecote;			// Nombre d'hexagones à faire en haut et en bas
	int aff_separateur = (der_ligne - taillecote)/2;
	for (int i = 0; i < taillecote; ++i)
	{
		aff_haut_hexa(i, (der_ligne - taillecote - i), (i!=0), (i==0) , (i==taillecote-1), p);
	}
	for (int i = taillecote-1; i < der_ligne; i++)
	{
		aff_bas_hexa(i, (i==der_ligne), (i-taillecote+1), (i==0), p);
	}
	cout << endl;
}

void plateau::afficher2(char* p)
{
	cout << endl;
	int aff_taillecote = taillecote;			// Nombre d'hexagones à faire en haut et en bas
	int aff_separateur = (der_ligne - taillecote)/2;
	for (int i = 0; i < taillecote; ++i)
	{
		// Ici on va faire la première partie de 
		// l'affichage des lignes, avant que l'on 
		// atteigne la ligne du milieu de la grille
		// (qui est, par ailleurs, la plus longue)
		aff_haut_hexa2(i, (der_ligne - taillecote - i), (i!=0), (i==0) , (i==taillecote-1), p);
	}
	for (int i = taillecote-1; i < der_ligne; i++)
	{
		// Pareil que la boucle d'avant, mais pour le bas du
		// plateau, avec les conditions necessaires
		aff_bas_hexa2(i, (i==der_ligne), (i-taillecote+1), (i==0), p);
	}
	cout << endl;
}

void plateau::aff_haut_hexa(int a, int sep, bool e_l, bool p_l, bool l_l, char* p)
{
	// Arguments :
	// a   = indice de la ligne de l'hexa a afficher
	// sep = le nombre d'espaces à mettre avant 
	//	 chaque ligne (x6)
	// e_l = est-ce que l'on est entre 2 lignes ?
	//	 si oui, afficher des underscore
	// p_l = sert à déterminer si on est sur la 
	//	 première ligne de la grille. ce 
	//	 booléen permet d'enlever un des appels 
	//	 de la fonction et de rajouter une 
	//	 ligne pour rien
	// l_l = determine si on est en derniere ligne
	// p   = donne les player id

	// Haut de l'hexagone :
	//
	//	  ____		= Ligne 1 (necessaire seulement pour le haut de la grille)
	//	 /    \		= Ligne 2
	//	/      \	= Ligne 3

	// On prends le nb d'éléments à afficher
	int nb = hexa[a].size();
	
	// PREMIERE LIGNE
	if (p_l)
	{
		// Separateur debut ligne
		for (int j = 0; j < sep; ++j)
		{
			cout << "      ";
		}
		// Affichage ligne haut
		for (int i = 0; i < nb; ++i)
		{
			cout << "  ____      ";
		}
		cout << endl;
	}

	// LIGNE MILIEU

	// Separateur debut ligne
	for (int j = 0; j < sep-1; ++j)
	{
		cout << "      ";
	}
	if (sep != 0)
	{
		cout << "       ";
	}
	else
	{
		cout << " ";
	}
	// Affichage ligne milieu
	for (int i = 0; i < nb; ++i)
	{
		cout << "/";
		aff_contenu(hexa[a][i], 4, p);
		cout << "\\";
		if (a > 0 && a < (der_ligne)  // La condition du 'if' !!!
		&& i >= 0 && i < hexa[a-1].size()) // est sur les 2 lignes !!!
		{
			aff_contenu(hexa[a-1][i], 6, p);
		}
		else
		{
			cout << "      ";
		}
	}
	cout << endl;

	// DERNIERE LIGNE

	// Separateur debut ligne
	for (int j = 0; j < sep-1; ++j)
	{
		cout << "      ";
	}
	if (sep != 0)
	{
		cout << "  ____";
	}
	// Affichage 3* ligne, avec rajout haut hexagone 
	// d'en dessous si necessaire
	for (int i = 0; i < nb; ++i)
	{
		cout << "/";
		aff_contenu(hexa[a][i], 6, p);
		cout << "\\";
		if (!l_l)				// Si on est pas sur la dernière ligne à afficher
		{
			if (i!=nb)			// Si on est pas à la fin de la ligne
			{
				cout << "____";		// On affiche un dessous d'hexagone
			}
			else
			{
				cout << "    ";		// Sinon on affiche un espace
			}
		}
		else					// Et si on est à la dernière ligne
		{
			if (i!=nb-1)			// et que l'on n'est pas à l'avant dernier hexagone
			{
				cout << "____";		// On affiche un dessous d'hexagone
			}
			else
			{
				cout << "    ";		// Sinon des espaces
			}
		}
	}
	cout << endl;
}

void plateau::aff_haut_hexa2(int a, int sep, bool e_l, bool p_l, bool l_l, char* p)
{
	// Arguments :
	// a   = indice de la ligne de l'hexa a afficher
	// e_l = est-ce que l'on est entre 2 lignes ?
	//	 si oui, afficher des underscore
	// sep = le nombre d'espaces à mettre avant 
	//	 chaque ligne (x6)
	// p_l = sert à déterminer si on est sur la 
	//	 première ligne de la grille. ce 
	//	 booléen permet d'enlever un des appels 
	//	 de la fonction et de rajouter une 
	//	 ligne pour rien
	// l_l = determine si on est en derniere ligne
	// p   = donne les player id

	// Haut de l'hexagone :
	//
	//	  	= Ligne 1 (necessaire seulement pour le haut de la grille)
	//	 /\	= Ligne 2
	//	/  \	= Ligne 3

	// On prends le nb d'éléments à afficher
	int nb = hexa[a].size();
	
	// PREMIERE LIGNE

	// LIGNE MILIEU

	// Separateur debut ligne
	for (int j = 0; j < sep-1; ++j)
	{
		cout << "  ";
	}
	if (sep != 0)
	{
		cout << "   ";
	}
	else
	{
		cout << " ";
	}
	// Affichage ligne milieu
	for (int i = 0; i < nb; ++i)
	{
		cout << "/";
		cout << "\\";
		if (a > 0 && a < (der_ligne)  // La condition du 'if' !!!
		&& i >= 0 && i < hexa[a-1].size()) // est sur les 2 lignes !!!
		{
			aff_contenu(hexa[a-1][i], 2, p);
		}
		else
		{
			cout << "  ";
		}
	}
	cout << endl;

	// DERNIERE LIGNE

	// Separateur debut ligne
	for (int j = 0; j < sep-1; ++j)
	{
		cout << "  ";
	}
	if (sep != 0)
	{
		cout << "  ";
	}
	// Affichage 3* ligne, avec rajout haut hexagone 
	// d'en dessous si necessaire
	for (int i = 0; i < nb; ++i)
	{
		cout << "/";
		aff_contenu(hexa[a][i], 2, p);
		cout << "\\";
	}
	cout << endl;
}

void plateau::aff_bas_hexa(int a, bool e_l, int sep, bool p_l, char* p)
{
	// On prends le nb d'éléments à afficher
	int nb = hexa[a].size();

	// Separateur debut ligne
	for (int j = 0; j < sep; ++j)
	{
		cout << "      ";
	}
	// Affichage ligne milieu
	for (int i = 0; i < nb; ++i)
	{
		cout << "\\";
		aff_contenu(hexa[a][i], 6, p);
		cout << "/";
		if (a >= 0 && a < (der_ligne-1) // La condition du 'if' (!!!)
		&& i >= 0 && i < hexa[a+1].size()) // est sur les 2 lignes (!!!)
		{
			aff_contenu(hexa[a+1][i], 4, p);
		}
		else
		{
			cout << "    ";
		}
	}
	cout << endl;

	// Separateur debut ligne
	for (int j = 0; j < sep; ++j)
	{
		cout << "      ";
	}
	cout << " ";

	// Affichage 3* ligne, avec rajout haut hexagone 
	// d'en dessous si necessaire
	for (int i = 0; i < nb; ++i)
	{
		cout << "\\____/";
		if (a >= 0 && a < (der_ligne-1) && i >= 0 && i < hexa[a+1].size())
		{
			aff_contenu(hexa[a+1][i], 6, p);
		}
		else
		{
			cout << "      ";
		}
	}
	cout << endl;
}

void plateau::aff_bas_hexa2(int a, bool e_l, int sep, bool p_l, char* p)
{
	// Arguments :
	// a   = indice de la ligne de l'hexa a afficher
	// e_l = est-ce que l'on est entre 2 lignes ?
	//	 si oui, afficher des underscore
	// sep = le nombre d'espaces à mettre avant 
	//	 chaque ligne (x4)
	// p_l = sert à déterminer si on est sur la 
	//	 première ligne de la grille. ce 
	//	 booléen permet d'enlever un des appels 
	//	 de la fonction et de rajouter une 
	//	 ligne pour rien

	// On prends le nb d'éléments à afficher
	int nb = hexa[a].size();

	// Separateur debut ligne
	for (int j = 0; j < sep; ++j)
	{
		cout << "  ";
	}
	// Affichage ligne milieu
	for (int i = 0; i < nb; ++i)
	{
		cout << "\\";
		aff_contenu(hexa[a][i], 2, p);
		cout << "/";
	}
	cout << endl;

	// Separateur debut ligne
	for (int j = 0; j < sep; ++j)
	{
		cout << "  ";
	}
	cout << " ";

	// Affichage 3* ligne, avec rajout haut hexagone 
	// d'en dessous si necessaire
	for (int i = 0; i < nb; ++i)
	{
		cout << "\\/";
		if (a >= 0 && a < (der_ligne-1) && i >= 0 && i < hexa[a+1].size())
		{
			aff_contenu(hexa[a+1][i], 2, p);
		}
		else
		{
			cout << "  ";
		}
	}
	cout << endl;
}

void plateau::aff_contenu(int c, int nb, char* p)
{
	// Arguments :
	// c 	= contenu de la case demandée
	// nb 	= le nombre de symboles à afficher
	// p 	= les player ids

	for (int k = 0; k < nb; ++k) {
		if (c == -2147483648)
		{
			cout << " ";
		}
		if (c == int(p[0]))
		{
			cout << p[0];
		}
		if (c == int(p[1]))
		{
			cout << p[1];
		}
		if (c == int(p[2]))
		{
			cout << p[2];
		}
	}
}

std::pair<int,int> plateau::placerpion(std::pair<std::pair<int,int>,char> choix_joueur)
{
	// Arguments :
	// choix_joueur	= paire contenant les coordonnées 
	//		  du pion à placer et l'id du joueur

	int x = choix_joueur.first.first;
	int y = choix_joueur.first.second;
	char id = choix_joueur.second;

	if (x >= 0 && y >= 0 && x < der_ligne && y < der_ligne)
	{
		if (hexa[x][y] == -2147483648)
		{
			// Placer pion
			hexa[x][y] = int(id);
			std::pair<int,int> resultat(x,y);
			return resultat;
		}
		else
		{
			// afficher un message d'erreur
			cout << "\n /!\\ Case déjà utilisée /!\\\n" << endl;
			std::pair<int,int> fail(-1,-1);
			return fail;
		}
	}
	else
		cout << "\n /!\\ Case non existante /!\\\n" << endl;
	std::pair<int,int> nope(-1,-1);
	return nope;
}

std::multimap<char, std::pair<int,int>> plateau::retParticuliers()
{
	std::multimap<char, std::pair<int,int>> res;		// Multimap à retourner
	char key = 1;
	
	// Ajout des coins 1 par 1

	// Coin Haut Gauche
	std::pair<int,int> coin_H_G(0, 0);
	std::pair<char, std::pair<int,int>> coinHG(key++, coin_H_G);
	res.insert(coinHG);
	// Coin Haut Droit
	std::pair<int,int> coin_H_D(0, hexa[0].size()-1);
	std::pair<char, std::pair<int,int>> coinHD(key++, coin_H_D);
	res.insert(coinHD);
	// Coin Milieu Gauche
	std::pair<int,int> coin_M_G(taillecote - 1, 0);
	std::pair<char, std::pair<int,int>> coinMG(key++, coin_M_G);
	res.insert(coinMG);
	// Coin Milieu Droit
	std::pair<int,int> coin_M_D(taillecote - 1, hexa[taillecote - 1].size()-1);
	std::pair<char, std::pair<int,int>> coinMD(key++, coin_M_D);
	res.insert(coinMD);
	// Coin Bas Gauche
	std::pair<int,int> coin_B_G(der_ligne - 1, 0);
	std::pair<char, std::pair<int,int>> coinBG(key++, coin_B_G);
	res.insert(coinBG);
	// Coin Bas Droit
	std::pair<int,int> coin_B_D(der_ligne - 1, hexa[der_ligne - 1].size()-1);
	std::pair<char, std::pair<int,int>> coinBD(key++, coin_B_D);
	res.insert(coinBD);

	// Ajout des côtés (en excluant les coins)

	// On exlut les coins car les côtés pris ci dessous sont utilisés pour voir
	// si le joueur a fait une forme en fourche avec ses pions. La forme en
	// fourche (selon les règles du jeu) est censée relier 3 côtés (adjacents 
	// ou non). Les coins étant le point de liaison entre 2 côtés ils ne comptent
	// donc pas dans la forme en fourche. Il compterons dans la forme en pont
	// reliant 2 côtés.

	for(int i = 0; i < der_ligne; ++i)
	{
		for(int j = 0; j < hexa[i].size(); ++j)
		{
			// On ne prends pas les coins
			if (	(i == 0 && j == 0) ||
				(i == 0 && j == hexa[i].size()-1) ||
				(i == taillecote - 1 && j == 0) ||
				(i == taillecote - 1 && j == hexa[taillecote - 1].size() - 1) ||
				(i == der_ligne - 1 && j == 0) || 
				(i == der_ligne - 1 && j == hexa[der_ligne - 1].size() - 1) )
				continue;
			else
			{
				if ( i == 0 || j == 0 || j == hexa[i].size()-1 || i == der_ligne - 1 )
				{
					std::pair<int,int> cote1(i,j);
					std::pair<char, std::pair<int,int>> cote(key++, cote1);
					res.insert(cote);
					continue;
				}
			}
		}
	}
	return res;
}

bool plateau::check_win(player p)
{
	std::cout << "Verification gagne joueurs ..." << std::endl;

	// Variables nécessaires à la vérification :
	arbre<int,int> cheminJoueurs;				// Vont stocker les chemins joueurs selon leur apparition dans la recherche sur plateau
	vector<noeud<int,int>*> indexCheminJoueur;	// Vont stocker des pointeurs vers tous les noeuds de l'arbre pour avoir une fonction de recherche BEAUCOUP plus rapide que celle des arbres.

	// Prise ID joueur :
	char playerId = p.returnId();

	// Vérifications joueur :
	for(int i = 0; i < der_ligne; ++i)
	{
		for(int j = 0; j < hexa[i].size(); ++j)
		{
			noeud<int,int> pointeurNoeud(i,j);
			if( hexa[i][j] == int(playerId) && ! find_in_node_vector(indexCheminJoueur, std::make_pair(i,j) ) )
			{
				// Alors on a trouvé un noeud qui n'est pas dans les chemins analysés
				std::cout << "Suivre le chemin ..." << std::endl;
				endGame cheminAccepte = suivreChemin(i,j,cheminJoueurs,indexCheminJoueur);
				if (cheminAccepte == RING || cheminAccepte == BRIDGE)
					return true;
			}
		}
	}
	return false;
}

plateau::endGame plateau::suivreChemin(int i, int j, arbre<int,int>& cheminJoueurs, vector<noeud<int,int>*>& indexCheminJoueur)
{
	std::cout << " Ajout noeud dans arbre ... ";
	noeud<int,int>* noeudAjoute = cheminJoueurs.ajouter_noeud(std::make_pair(i,j),cheminJoueurs.racine);
	std::cout << "noeud ajouté ";
	indexCheminJoueur.push_back(noeudAjoute);
	std:cout << "dans le vecteur" << std::endl;
	/* 
	Analyse des voisins : 

	Pattern 1 : (si l'on est dans la partie haute du plateau)
		● ●		( 1 2   )
		● x ●	( 3 x 4 )
		  ● ●	(   5 6 )

		x : point de ref
		● : points à analyser

	Pattern 2 : (si l'on est sur la ligne du milieu du plateau)
		● ●		( 1 2   )
		● x ●	( 3 x 4 )
		● ●		( 5 6   )

		x : point de ref
		● : points à analyser

	Pattern 3 : (si l'on est dans la partie basse du plateau)
		  ● ●	(   1 2 )
		● x ●	( 3 x 4 )
		● ●		( 5 6   )

		x : point de ref
		● : points à analyser
	*/
	if (i < taillecote)													// Pattern 1
	{
		if (i-1 > 0 && j-1 > 0 && hexa[i-1][j-1] == hexa[i][j]) 		// Point 1
		{
			int ni = i-1;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if (i-1 > 0 && hexa[i-1][j] == hexa[i][j])						// Point 2
		{
			int ni = i-1;
			int nj = j;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if (j-1 > 0 && hexa[i][j-1] == hexa[i][j])						// Point 3
		{
			int ni = i;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if (j+1 > 0 && hexa[i][j+1] == hexa[i][j])						// Point 4
		{
			 
			int ni = i;
			int nj = j+1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if (i+1 > 0 && hexa[i+1][j] == hexa[i][j])						// Point 5
		{
			 
			int ni = i+1;
			int nj = j;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if (i+1 > 0 && j+1 > 0 && hexa[i+1][j+1] == hexa[i][j])			// Point 6
		{
			 
			int ni = i+1;
			int nj = j+1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
	}
	if (i == taillecote)												// Pattern 2
	{
		if ( i-1 > 0 && j-1 > 0 && hexa[i-1][j-1] == hexa[i][j] )		// Point 1
		{
			 
			int ni = i-1;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( i-1 > 0 && hexa[i-1][j] == hexa[i][j] )					// Point 2
		{
			 
			int ni = i-1;
			int nj = j;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( j-1 > 0 && hexa[i][j-1] == hexa[i][j] )					// Point 3
		{
			 
			int ni = i;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( j+1 > 0 && hexa[i][j+1] == hexa[i][j] )					// Point 4
		{
			 
			int ni = i;
			int nj = j+1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( i+1 > 0 && j-1 > 0 && hexa[i+1][j-1] == hexa[i][j] )		// Point 5
		{
			 
			int ni = i+1;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( i+1 > 0 && hexa[i+1][j] == hexa[i][j] )					// Point 6
		{
			 
			int ni = i+1;
			int nj = j;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
	}
	if (i > taillecote)													// Pattern 3
	{
		if ( i-1 > 0 && hexa[i-1][j] == hexa[i][j] )					// Point 1
		{
			 
			int ni = i-1;
			int nj = j;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( i-1 > 0 && j+1 < hexa[i-1].size() && hexa[i-1][j+1] )		// Point 2
		{
			 
			int ni = i-1;
			int nj = j+1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( j-1 > 0 && hexa[i][j-1] == hexa[i][j] )					// Point 3
		{
			 
			int ni = i;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( j+1 < hexa[i].size() && hexa[i][j+1] == hexa[i][j] )		// Point 4
		{
			 
			int ni = i;
			int nj = j+1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( i+1 < der_ligne && j-1 > 0 && hexa[i+1][j-1] == hexa[i][j] )// Point 5
		{
			 
			int ni = i+1;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( i+1 < der_ligne && hexa[i+1][j] == hexa[i][j] )
		{
			 
			int ni = i+1;
			int nj = j;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudAjoute);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
	}
	return NONE;
}

plateau::endGame plateau::suivreChemin(int i, int j, arbre<int,int>& cheminJoueurs, vector<noeud<int,int>*>& indexCheminJoueur, noeud<int,int>* noeudActuel)
{
	bool node_found = false;
	if (i < taillecote)													// Pattern 1
	{
		if (i-1 > 0 && j-1 > 0 && hexa[i-1][j-1] == hexa[i][j]) 		// Point 1
		{
			 
			int ni = i-1;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if (i-1 > 0 && hexa[i-1][j] == hexa[i][j])						// Point 2
		{
			 
			int ni = i-1;
			int nj = j;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if (j-1 > 0 && hexa[i][j-1] == hexa[i][j])						// Point 3
		{
			 
			int ni = i;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if (j+1 > 0 && hexa[i][j+1] == hexa[i][j])						// Point 4
		{
			 
			int ni = i;
			int nj = j+1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if (i+1 > 0 && hexa[i+1][j] == hexa[i][j])						// Point 5
		{
			 
			int ni = i+1;
			int nj = j;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if (i+1 > 0 && j+1 > 0 && hexa[i+1][j+1] == hexa[i][j])			// Point 6
		{
			 
			int ni = i+1;
			int nj = j+1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
	}
	if (i == taillecote)												// Pattern 2
	{
		if ( i-1 > 0 && j-1 > 0 && hexa[i-1][j-1] == hexa[i][j] )		// Point 1
		{
			 
			int ni = i-1;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( i-1 > 0 && hexa[i-1][j] == hexa[i][j] )					// Point 2
		{
			 
			int ni = i-1;
			int nj = j;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( j-1 > 0 && hexa[i][j-1] == hexa[i][j] )					// Point 3
		{
			 
			int ni = i;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( j+1 > 0 && hexa[i][j+1] == hexa[i][j] )					// Point 4
		{
			 
			int ni = i;
			int nj = j+1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( i+1 > 0 && j-1 > 0 && hexa[i+1][j-1] == hexa[i][j] )		// Point 5
		{
			 
			int ni = i+1;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( i+1 > 0 && hexa[i+1][j] == hexa[i][j] )					// Point 6
		{
			 
			int ni = i+1;
			int nj = j;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
	}
	if (i > taillecote)													// Pattern 3
	{
		if ( i-1 > 0 && hexa[i-1][j] == hexa[i][j] )					// Point 1
		{
			 
			int ni = i-1;
			int nj = j;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( i-1 > 0 && j+1 < hexa[i-1].size() && hexa[i-1][j+1] )		// Point 2
		{
			 
			int ni = i-1;
			int nj = j+1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( j-1 > 0 && hexa[i][j-1] == hexa[i][j] )					// Point 3
		{
			 
			int ni = i;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( j+1 < hexa[i].size() && hexa[i][j+1] == hexa[i][j] )		// Point 4
		{
			 
			int ni = i;
			int nj = j+1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( i+1 < der_ligne && j-1 > 0 && hexa[i+1][j-1] == hexa[i][j] )// Point 5
		{
			int ni = i+1;
			int nj = j-1;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
		if ( i+1 < der_ligne && hexa[i+1][j] == hexa[i][j] )
		{
			int ni = i+1;
			int nj = j;
			std::cout << "    verif " << ni << " " << nj << " ... ";
			noeud<int,int>* nouveauNoeudTrouve = cheminJoueurs.ajouter_noeud(std::make_pair(ni,nj),noeudActuel);
			if ( ! find_in_node_vector( indexCheminJoueur, std::make_pair(ni,nj) ) )	// Si le noeud n'est pas trouvé dans le vecteur
			{
				std::cout << " trouve." << std::endl;
				node_found = true;
				indexCheminJoueur.push_back(nouveauNoeudTrouve);
				suivreChemin(ni,nj,cheminJoueurs,indexCheminJoueur,nouveauNoeudTrouve);
			}
			std::cout << std::endl;
		}
	}
	// Condition d'arrêt : si l'on ne trouve que des voisins du noeud actuel présents dans l'arbre
	if (!node_found)
	{
		//if ()
		std::multimap<char, std::pair<int,int>> casesPart = retParticuliers();
		// Si coin :
		for (int i = 0; i < 6; i++)
		{
			if ( casesPart.find( char(i))->second == std::make_pair(i,j) )
			{
				noeud<int,int> currentNode(i,j);
				noeud<int,int>* fatherNode = cheminJoueurs.voirPere( *(find(indexCheminJoueur.begin(), indexCheminJoueur.end(), &currentNode)), 1, 0, 0 );
				if ( casesPart.find( char(i) )->second == fatherNode->info )
					return BRIDGE;
			}
		}
		for (int i = 6; i < casesPart.size(); i++)
		{
			if ( casesPart.find( char(i) )->second == std::make_pair(i,j) )
			{
				noeud<int,int> currentNode(i,j);
			}
		}
	}
	return NONE;
}

bool plateau::find_in_node_vector(vector<noeud<int,int>*> sourceVector, std::pair<int,int> information)
{
	std::cout << "find_in_node_vector()" << std::endl;
	for (int i = 0; i < sourceVector.size(); i++)
	{
		std::cout << "ok : " << i << " " << sourceVector[i] << std::endl;
		if (*sourceVector[i] == information)
			return true;
	}
	return false;
}



























