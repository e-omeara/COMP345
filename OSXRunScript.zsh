#!/bin/zsh


#clang++ -std=c++20 -c MapObjects/Critter/Driver.cpp -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';


clang++ -std=c++20 -c Driver.cpp -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';


clang++ -std=c++20 -c MapObjects/Critter/Critter.cpp -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c MapObjects/Critter/CritterObserver.cpp -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c MapObjects/Critter/SFMLCritterSimulator.cpp -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';

clang++ -std=c++20 -c Map/MapObserver.cpp -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c Map/MapGraphics.cpp -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c Map/Map.cpp -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';


clang++ -std=c++20 -c MapObjects/Tower/Towers.cpp -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';

g++ *.o -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-graphics -lsfml-window -lsfml-system -o myapp;

rm *.o;


#clang++ -std=c++20 Driver.o Towers.o Critter.o MapMaker.o Map.o 

#g++ MapGraphics.o MapObserver.o Map.o -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-graphics -lsfml-window -lsfml-system -o myapp;
