#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "TowerSimulator.h"
#include "TowerObserver.h"
#include "Towers.h"
#include "TowerDecorator.h"
#include "ValueModifierDecorator.h"





TowerSimulator::TowerSimulator(vector<Towers*>* mytowers){
    
    cout << "\n Initializing Tower Simulator\n";
    placing = false;
    towers = mytowers;
    
    
}

TowerSimulator::TowerSimulator(){
    cout << "\n Initializing Tower Simulator\n";
    placing = false;
    towers = new vector<Towers*>;
    
    
}


int TowerSimulator::addMap(Map *theMap){
    map = theMap;
    return 0;
}

/*
int TowerSimulator::createWindow(){


    //create render window
    window = sf::RenderWindow(sf::VideoMode({600, 400}), "SFML works!");
   


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            //wait for any user input
            if (event->is<sf::Event::Closed>())
               { window.close();}
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    window.close();
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::U){
                    //level up the tower
                    double balance = 1000;
                    //tower->levelUp(balance);
                    towers[0] = new ValueModifierDecorator("archer", {5,5}, *towers[0], 20, 10, 1, 2, 100);
                    tObserver->update(towers[0]->getLevel(), towers[0]->getBuyingCost(), towers[0]->getRefundValue(), towers[0]->getRange(), towers[0]->getPower(), towers[0]->getRateOfFire(), {5,5}, "value modifier" );
                    cerr << towers[0]->getPower();
                    
                    
                }
                
                    
                
            }
        }

        //update the window
        window.clear();
        renderTowers(window);
        window.display();
    }

    return 0;

}
*/

//Render towers along with tooltip
int TowerSimulator::renderTowers(sf::RenderWindow* window){

    
    if(towers->size() == 0){
        return 0;
    }

     //define the size of the tower
     sf::Vector2f towerRect(20.f, 20.f);
     //create the rectangle shape and colour
     sf::RectangleShape towerShape(towerRect);


    for(auto t: *towers){
    //cerr << "No. of towers: " << towers.size() << "\n";
    //for(int i = 0; i< 1; i++){

    //Towers* t = towers[0];
   
    towerShape.setFillColor(sf::Color::Blue);
    //set the rectangle position
    TowerObserver* tObserver = t->getTowerObserver();
    int posx = tObserver->getPosition().x;
    int posy = tObserver->getPosition().y;
    float shapex = posx * 20.f + 100.f;
    float shapey = posy * 20.f + 100.f;
    towerShape.setPosition(sf::Vector2f(shapex, shapey));

    //draw the tower
    //window->draw(towerShape);

    }
     

    for(auto t: *towers){

    TowerObserver* tObserver = t->getTowerObserver();
        //get mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    int posx = tObserver->getPosition().x;
    int posy = tObserver->getPosition().y;
    float shapex = posx * 20.f + 100.f;
    float shapey = posy * 20.f + 100.f;
    towerShape.setPosition(sf::Vector2f(shapex, shapey));
    
    //if mouse hovering over tower, show tooltip with stats
    sf::Font font("arial.ttf");
    if(towerShape.getGlobalBounds().contains({static_cast<float>(mousePos.x),
        static_cast<float>(mousePos.y)})) {
        string tip = "Type: " + tObserver->getType() 
        + "\nRange: " +  to_string(tObserver->getRange())
        + "\nLevel: " + to_string(tObserver->getLevel())
        + "\nPower: " + to_string(tObserver->getPower());
        sf::Text tooltip(font);
        tooltip.setCharacterSize(16);
        tooltip.setString(sf::String(tip));
        tooltip.setFillColor(sf::Color::White);
        tooltip.setOutlineColor(sf::Color::Black);
        tooltip.setOutlineThickness(2.f);
        tooltip.setPosition({shapex + 30.f, shapey - 20.f});
        window->draw(tooltip);}

    

    }


    return 0;
}

int TowerSimulator::renderPurchaseMenu(sf::RenderWindow* window){
    sf::RectangleShape shape;

    return 0;
}


int TowerSimulator::click(sf::RenderWindow *window){

    //TODO: remove this !!!!!
    placing = true;

    if(placing){
        //get x y coordinates
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        float x = mousePos.x;
        float y = mousePos.y;
        x = (x - 100.0) / 20.0;
        y = (y - 100.0) / 20.0;
        cout << "x position: " << x << endl;
        cout << "y position: " << y << endl;

        int xPos = int(x);
        int yPos = int(y);
        int success = map->setTower(xPos, yPos);
        if(success == 0){
            Towers* mytower = new Towers("archer", {xPos, yPos});
            TowerObserver* myobs = new TowerObserver(*mytower);
            towers->push_back(mytower);
            cout << "Successfully created new tower!" << endl;
        }
        


        //see if it lines up with a available spot


        //place tower
        return 0;
    } else {

        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        float x = mousePos.x;
        float y = mousePos.y;
        x = (x - 100.0) / 20.0;
        y = (y - 100.0) / 20.0;
        cout << "x position: " << x << endl;
        cout << "y position: " << y << endl;

        return 0;

    }
}

void TowerSimulator::shoot(SFMLCritterSimulator *critSim){
    vector<Critter *>  mycritters;
    Critter* critt;

    mycritters = critSim->getCritters();
    for( auto t : *towers){
        critt = t->findTarget(mycritters);
        if(critt != NULL){
            t->shoot(*critt);
        }

    }


   
}


//entry point to simulator
int TowerSimulator::runGame(){

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({600, 400}), "window test!");
    Towers* mytower = new Towers("ballista", {8, 5});
    TowerObserver* myobs = new TowerObserver(*mytower);
    towers->push_back(mytower);
    // run the program as long as the window is open
    while (window->isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window->pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        window->clear();
        renderTowers(window);
        window->display();
    }

    
    



    //createWindow();


    return 0;
}