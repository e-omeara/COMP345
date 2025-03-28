#!/bin/zsh


#clang++ -std=c++20 -c MapObjects/Critter/Driver.cpp -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';


clang++ -std=c++20 -c Driver.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';

clang++ -std=c++20 -c MapObjects/Critter/Critter.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c MapObjects/Critter/CritterObserver.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c MapObjects/Critter/SFMLCritterSimulator.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c MapObjects/Critter/CritterFactory.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';

clang++ -std=c++20 -c MapObjects/TowerDecorator/BurningEffectDecorator.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c MapObjects/TowerDecorator/SlowingEffectDecorator.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c MapObjects/TowerDecorator/TowerDecorator.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c MapObjects/TowerDecorator/ValueModifierDecorator.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';

clang++ -std=c++20 -c Map/MapObserver.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c Map/MapGraphics.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c Map/Map.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';

clang++ -std=c++20 -c MapObjects/Tower/Towers.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c MapObjects/Tower/TowerObserver.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c MapObjects/Tower/TowerSimulator.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';

clang++ -std=c++20 -c Player/Player.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c -g GameEngine/GameRenderer.cpp -I 'MapObjects/TowerDecorator' -I 'GameEngine/' -I 'Player/' -I 'Map/' -I 'MapObjects/Tower/' -I 'MapObjects/Critter/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';

clang++ -std=c++20 -c GameEngine/ColorSchemeConstants.cpp -I 'GameEngine/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';
clang++ -std=c++20 -c -g GameEngine/MainMenu.cpp -I 'GameEngine/' -I '/opt/homebrew/Cellar/sfml/3.0.0_1/include';

g++ *.o -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-graphics -lsfml-window -lsfml-system -o myapp;

rm *.o;


#clang++ -std=c++20 Driver.o Towers.o Critter.o MapMaker.o Map.o 

#g++ MapGraphics.o MapObserver.o Map.o -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-graphics -lsfml-window -lsfml-system -o myapp;
