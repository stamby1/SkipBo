CC = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -O -g
GPROF = -pg
GCOV = -fprofile-arcs -ftest-coverage

bin: skipbo

test: pileTest playersTest gameTest
	echo "Running tests..."
	./pileTest
	./playersTest
	./gameTest
# recompiles tests with gcov on and reports the lines not tested                              

testgcov:
	make clean
	make CXXFLAGS="$(CXXFLAGS) $(GCOV)" test
	gcov *.cpp
	-@grep -n "#####" *.cpp.gcov

pileTest: pileTest.cpp buildingPile.cpp Card.cpp Pile.cpp drawDeck.cpp Hand.cpp Stock.cpp
	$(CC) $(CXXFLAGS) pileTest.cpp buildingPile.cpp Card.cpp Pile.cpp drawDeck.cpp Hand.cpp Stock.cpp Players.cpp Computer.cpp Game.cpp Human.cpp -o pileTest

playersTest: playersTest.cpp buildingPile.cpp Card.cpp Pile.cpp drawDeck.cpp Hand.cpp Stock.cpp Players.cpp Computer.cpp Game.cpp Human.cpp
	$(CC) $(CXXFLAGS) playersTest.cpp buildingPile.cpp Card.cpp Pile.cpp drawDeck.cpp Hand.cpp Stock.cpp Players.cpp Computer.cpp Game.cpp Human.cpp -o playersTest

gameTest: gameTest.cpp buildingPile.cpp Card.cpp Pile.cpp drawDeck.cpp Hand.cpp Stock.cpp Players.cpp Computer.cpp Game.cpp Human.cpp
	$(CC) $(CXXFLAGS) gameTest.cpp buildingPile.cpp Card.cpp Pile.cpp drawDeck.cpp Hand.cpp Stock.cpp Players.cpp Computer.cpp Game.cpp Human.cpp -o gameTest

skipbo: SkipBoMain.cpp buildingPile.cpp Card.cpp Pile.cpp drawDeck.cpp Hand.cpp Stock.cpp Players.cpp Computer.cpp Game.cpp Human.cpp
	$(CC) $(CXXFLAGS) SkipBoMain.cpp buildingPile.cpp Card.cpp Pile.cpp drawDeck.cpp Hand.cpp Stock.cpp Players.cpp Computer.cpp Game.cpp Human.cpp -o skipbo



clean:
	rm -f a.out *~ *.o *.gcov *.gcda *.gcno gmon.out pileTest playersTest gameTest skipbo
