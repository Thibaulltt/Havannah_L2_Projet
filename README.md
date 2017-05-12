Classes développées
-------------------

Classe Jeu :

La classe jeu est la classe à partir de laquelle le jeu va se lancer. Dans son constructeur, on construit un plateau, ainsi que des joueurs, on initialise certains paramètres pour le bon fonctionnement du jeu. 

- Contient un pointeur vers le plateau, pour que le plateau soit indépendant de l'instance de jeu en cours
- Contient un `char` permettant de savoir combien de joueurs sont dans la partie
- Contient un `char` permettant de savoir combien d'IA sont à gérer
- Contient un entier permettant de savoir combien de tours ont étés joués
- Contient un tableau de pointeurs vers des joueurs, afin que l'on uisse avoir autant de joueurs que possible
- Contient un tableau de `char` qui permet de stocker les identifiants joueur
- Contient une multimap (non utilisée dans la version "finale" du projet) qui stocke les indices des cases particulières (coins et côtés)

Classe Plateau :

La classe plateau est la classe qui permet de stocker la grille des cases, de vérifier si un joueur a gagné, d'afficher le plateau (2 manières : avec des hexagones & des losanges pour un affichage plus compact), de placer un pion, et de verifier les voisins d'une case.

- Contient un entier qui stocke la taille plateau demandée
- Contient un entier qui stocke l'indice de la dernière ligne
- Contient un pointeur de vecteurs d'entiers qui réprésente le plateau et ses cases
- Contient un énumérateur qui permet de voir par quel moyen e joueur a gagné, et de décider quoi faire

Classe Player :

La classe player sert à stocker un joueur en mémoire.

- Contient une chaine de caractères pour stocker le nom
- Contient un booléen pour déterminer si le joueur est une IA ou non

Classes arbre et noeud :

Ce sont des templates de classes qui permettent de créer un arbre contenant des paires de valeurs dans ses noeuds.

Fonctionnalités implémentées
----------------------------

| Fonctionnalité                                            | Implémenté(?) |
| ----------------------------------------------------------|---------------|
| Programme créé en C++                                     | Oui           |
| Compilation via la commande make                          | Oui           |
| Compilation possible sur machine CERI                     | Oui           |
| Paramétrage de la taille tableau                          | Oui           |
| Paramétrage du nombre de joueurs                          | Oui           |
| Paramétrage du nombre de joueurs (gérés par le programme) | Oui           |
| Choix du joueur démarrant la partie                       | Oui           |
| Règle du gâteau                                           | Oui           |
| Modélisation plateau en mémoire                           | Oui           |
| Modélisation joueurs en mémoire                           | Oui           |
| Placement de pions sur le plateau                         | Oui           |
| Intelligence semi-artificielle                            | Non           |
| Sauvegarde/reprise de parties                             | Non           |
| Conseils de jeu                                           | Non           |
| Changement de couleur joueur                              | Non           |
| Résolution de problèmes                                   | Non           |
| Jeu en réseau                                             | Non           |
| Interface Graphique                                       | Oui (via CLI) |

Difficultés rencontrées
-----------------------

La plus grande diffoculté rencontrée (et non résolue) a été la prise de décision quand à la vctoire d'un joueur par rapport à un autre. Je suis passé par plusieurs méthodes, avant d'arriver à l'arbre de noeuds actuel.

J'avais d'abord commencé par un algorithme permettant de stocker tous les coups joués dans un vecteur, mais j'ai changé de méthode car celle-ci ne conservait ni l'ordre relatif dans lequel les pions avaient étés placés, ni le "chemin" formé par ces pions.

J'avais ensuite pensé à faire un vecteur de listes de paires d'entiers (std::vector < std::list< std::pair< int,int > > >), mais cette méthode était trop lourde au niveau du temps de calcul ET de la mémoire utilisée, et j'ai donc abandonné cette idée.

J'avais ensuite pensé à une solution par Backtracking, comme appris l'année dernière, mais n'étant jamais bon à sa pratique, je n'ai pas réussi à l'implémenter, et donc ai passsé beaucoup trop de temps dessus

La solution qui est présente dans le code (qui est donc incomplète dû majoritairement au manque de temps engendré par ma volonté d'implémenter un algorithme de backtracking pour vérifier la gagne d'un joueur) est donc une analyse à chaque tour des coups joués par les joueurs. La méthode présente ici scanne le plateau, et dès qu'elle trouve un noeud, l'ajoute dans l'arbre et dans le vecteur de pointeurs de noeuds. Ce vecteur est présent pour avoir une fonction de recherche de complexité O(n) et donc linéaire, au lieu des fonctions de recherche récursives bancales présentes auparavant dans la classe arbre. Une fois le noeud ajouté, la fonction est rappellée sur tous les voisins et dès que l'on ne trouve plus de voisins, la fonction retourne une des valeurs de l'énumérateur afin de déterminer quelle forme géométrique le joueur a formé avec ses pions.
