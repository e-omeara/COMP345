Please copy and paste the entire thing into your terminal
Then run ./a.out in terminal


g++ -c Driver.cpp;
g++ -c MapObjects/Towers.cpp;
g++ -c MapObjects/Critter.cpp;
g++ -c Map/MapMaker.cpp;
g++ -c Map/Map.cpp;
g++ Driver.o Towers.o Critter.o MapMaker.o Map.o