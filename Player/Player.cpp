#include "Player.h"





void Player::renderBalance(sf::RenderWindow *window){

    return;
}

void Player::initializePlayer(int amount){

    Player::balance = amount;

}

void Player::addToAmount(int add){
    Player::balance += add;
}