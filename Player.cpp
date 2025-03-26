#include "Player.h"
#include <iostream>

using namespace std;


Player::Player(int amount, int hp){
    balance = amount;
    health = hp;

}

//Load textures and font.
void Player::loadResource() {
    if(!font.openFromFile("arial.ttf"))
        std::cerr << "Error loading arial.ttf\n";
}

void Player::renderBalance(sf::RenderWindow *window){

    //Use a static font so it's loaded only once
    static sf::Font font;
    static bool loaded = false;
    if (!loaded) {
        if (!font.openFromFile("arial.ttf")) {
            std::cerr << "Error loading font arial.ttf\n";
        }
        loaded = true;
    }

    //Text for coin balance.
    sf::Text coinText(font);
    coinText.setCharacterSize(20);
    coinText.setFillColor(sf::Color::White);
    coinText.setPosition({400.f, 20.f});
    coinText.setString("Coins: " + std::to_string(balance));
    
    //Text for player's health.
    sf::Text healthText(font);
    healthText.setCharacterSize(20);
    healthText.setFillColor(sf::Color::White);
    healthText.setPosition({250.f, 20.f});
    healthText.setString("Health: " + std::to_string(health));
    
    window->draw(coinText);
    window->draw(healthText);
}


void Player::addToAmount(int add){
    balance += add;
}

void Player::reduceHealth(int dmg) {
    health -= dmg;
    if (health < 0)
        health = 0;
}