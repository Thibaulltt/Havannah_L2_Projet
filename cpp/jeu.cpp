#include <iostream>
#include "../h/jeu.h"
#include <vector>
#include <algorithm>

jeu::jeu(int tp, int nbp)
{
	// Arguments :
	// tp 	 = Taille plateau
	// nbp 	 = Nombre de joueurs

	// On crée tous les éléments d'un jeu de Havannah
	hav = new plateau(tp);
	nb_players = nbp;
	nb_ia = 0;
	players = new player*[nbp];
	playerids = new  char[nbp];
	for (int i = 0; i < nb_players; ++i) {
		players[i] = new player;
		playerids[i] = players[i]->returnId();
		for (int j = 0; j<i; ++j)
		{
			//
			// Permet de verifier & remplacer un 
			// playerId deja utilisé
			//
			while (playerids[j] == playerids[i])
			{
				int p;
				std::cout << " ID déjà attribué ! Choisissez en un autre : ";
				std::cin >> p;
				if (char(p+34) != playerids[i])
				{
					players[i]->newid(char(p+34));
					playerids[i] = char(p+34);
					break;
				}
			}
		}
		if (players[i]->returnIa())
			nb_ia++;
	}
	nbturn = 0;
	part_plateau = hav->retParticuliers();
}

jeu::~jeu()
{
	part_plateau.clear();
	delete hav;
	delete playerids;
	delete players;
	// return;
}

void jeu::a()
{
//	std::cout << " Voici l'état du jeu au tour " << nbturn << " : " << std::endl;
//	std::cout << " Nb IA : " << int(nb_ia) << "; Nb Players : " << int(nb_players) << std::endl;
//	std::cout << " Player ID's : [ ";
//	for (int i = 0; i < nb_players; ++i)
//		std::cout << " " << int(playerids[i]) << " ";
//	std::cout << "]" << std::endl;
//	for (int i = 0; i < nb_players; ++i)
//	{
//		std::cout << int(playerids[i]);
//		players[i]->affcoups();
//	}
	hav->afficher2(playerids);
}

void jeu::tour()
{
	std::pair<int,int> pion_place;
	for (int i = 0; i < nb_players; ++i)
	{
		if (nbturn == 0 && i != 0)
		{
			char r;
			std::cout << " Voulez-vous effectuer la règle du gateau ? [o/n] ";
			std::cin >> r;
			while (r != 'o' && r != 'n')
			{
				std::cout << " Valeur non reconnue : ";
				std::cin >> r;
			}
			if (r == 'o')
			{
				char old;
				old = players[i-1]->returnId();
				players[i-1]->newid(players[i]->returnId());
				players[i]->newid(old);
				std::cout << " Joueur " << players[i-1]->returnNom() << " joue maintenant avec l'id " << players[i-1]->returnId() << std::endl;
				std::cout << " Joueur " << players[i]->returnNom() << " joue maintenant avec l'id " << players[i]->returnId() << std::endl;
			}
			else
			{
				pion_place = hav->placerpion( players[i]->placer_pion() );
			}
		}
		else
		{
			pion_place = hav->placerpion( players[i]->placer_pion() );
		}
	}
	nbturn++;
}

bool jeu::check_win()
{
	for (int i = 0; i < nb_players; ++i)
	{
		if (hav->check_win(*players[i]))
		{
			std::cout << "Si vous voyez ceci, " << players[i]->returnNom() << ", cela veut dire que vous avez gagné le jeu." << std::endl;
			return true;
		}
	}
	return false;
}