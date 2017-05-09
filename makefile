ARBRE="./o/arbre.o"
NOEUD="./o/noeud.o"
FLAGS="-std=c++11"

havannah: ./o/main.o ./o/plateau.o ./o/player.o ./o/jeu.o ./o/arbre.o ./o/noeud.o
	@echo "c $@ ..."
	@g++ $^ -o $@ $(FLAGS)
./o/main.o: ./cpp/main.cpp
	@echo "c $@ ..."
	@g++ -c $< -o $@ $(FLAGS)
./o/plateau.o: ./cpp/plateau.cpp ./h/plateau.h
	@echo "c $@ ..."
	@g++ -c $< -o $@ $(FLAGS)
./o/player.o: ./cpp/player.cpp ./h/player.h
	@echo "c $@ ..."
	@g++ -c $< -o $@ $(FLAGS)
./o/jeu.o: ./cpp/jeu.cpp ./h/jeu.h
	@echo "c $@ ..."
	@g++ -c $< -o $@ $(FLAGS)
./o/noeud.o: ./cpp/noeud.cpp ./h/noeud.h
	@echo "c $@ ..."
	@g++ -c $< -o $@ $(FLAGS)
./o/arbre.o: ./cpp/arbre.cpp ./h/arbre.h
	@echo "c $@ ..."
	@g++ -c $< -o $@ $(FLAGS)
doc:
	@echo "making the documentation ..."
	@sleep 1
	@cd doc/; doxygen player_doc > debug.txt; cd latex/; make clean;