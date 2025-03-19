Please copy and paste the entire thing into your terminal
Then run ./a.out in terminal


g++ -c Driver.cpp;
g++ -c MapObjects/Towers.cpp;
g++ -c MapObjects/Critter.cpp;
g++ -c Map/MapMaker.cpp;
g++ -c Map/Map.cpp;
g++ Driver.o Towers.o Critter.o MapMaker.o Map.o

If using a mac, copy/paste this:

clang++ -std=c++20 -c Map/MapObserver.cpp -I/opt/homebrew/Cellar/sfml/3.0.0_1/include;
clang++ -std=c++20 -c Map/MapGraphics.cpp -I/opt/homebrew/Cellar/sfml/3.0.0_1/include;
clang++ -std=c++20 -c Map/Map.cpp -I/opt/homebrew/Cellar/sfml/3.0.0_1/include;
g++ Map/MapGraphics.o Map/MapObserver.o Map/Map.o -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-graphics -lsfml-window -lsfml-system -o myapp;
./myapp


/usr/bin/clang++ -std=c++20 -g -c 'Driver.cpp' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include'