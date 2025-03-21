#include "Player.h"
#include <iostream>

using namespace std;


Player::Player(int amount, int hp){
    int balance = amount;
    int health = hp;

}


void Player::renderBalance(sf::RenderWindow *window){

   // cout << "rendering player balance";
    return;
}



void Player::addToAmount(int add){
    balance += add;
}