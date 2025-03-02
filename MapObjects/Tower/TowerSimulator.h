#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "TowerObserver.h"
#include "Towers.h"

using namespace std;

class TowerSimulator{


    private:
    //attributes
    TowerObserver* tObserver;
    Towers* tower;
    sf::RenderWindow window;



    public:
    //methods
    TowerSimulator(TowerObserver* towerObserver, Towers* tower);

    int runGame();

    int createWindow();

    int renderTowers();

    int updatevisuals();

    




    private:
    //methods
};