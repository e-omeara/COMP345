#include "GameRenderer.h"

using namespace std;



void GameRenderer::initialize(){
    theWindow = new sf::RenderWindow(sf::VideoMode({600, 400}), "SFML works!");

    return;
}

void GameRenderer::mainWindow(){
    theWindow->setTitle("Tower Defense: Main Menu");

    //render main menu


    return;
}

void GameRenderer::makeMapWindow(){
    theWindow->setTitle("Tower Defense: Make Map");

    //render mapMaker graphics


    return;
}

void GameRenderer::playTime(){
    theWindow->setTitle("Battle Time !");

    //render map
    //render tower menu
    //render player balance
    Player::renderBalance(theWindow);
    //send click to towerBuy and towerUpgrade
    //render critters
    //render hover stats


    return;
}

void GameRenderer::pauseTime(){
    theWindow->setTitle("Place and upgrade your towers !");

    //render map
    //render tower menu
    //render player menu
    Player::renderBalance(theWindow);
    //send click to towerBuy and towerUpgrade
    //render hoverstats


    return;
}

void GameRenderer::endGame(){
    theWindow->setTitle("Tower Defense: goodbye !");

    //render end game graphics
    //display loss or win
    //display stats


    return;
}

void main(){

    GameRenderer::initialize();
    Player::initializePlayer(500);
}