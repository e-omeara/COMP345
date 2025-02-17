Please copy and paste the entire thing into your terminal
Then run ./a.out in terminal


g++ -c Driver.cpp;
g++ -c MapObjects/Towers.cpp;
g++ -c MapObjects/Critter.cpp;
g++ -c Map/MapMaker.cpp;
g++ -c Map/Map.cpp;
g++ Driver.o Towers.o Critter.o MapMaker.o Map.o

If using a mac, copy/paste this:

clang++ -std=c++20 -c Driver.cpp;
clang++ -std=c++20 -c MapObjects/Towers.cpp;
clang++ -std=c++20 -c MapObjects/Critter.cpp;
clang++ -std=c++20 -c Map/MapMaker.cpp;
clang++ -std=c++20 -c Map/Map.cpp;
clang++ -std=c++20 Driver.o Towers.o Critter.o MapMaker.o Map.o