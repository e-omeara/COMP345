#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "TowerSimulator.h"
#include "TowerObserver.h"
#include "Towers.h"
#include "Player.h"
#include "TowerDecorator.h"


using namespace ColorSchemeConstants;





TowerSimulator::TowerSimulator(vector<Towers*>* mytowers){
    
    cout << "\n BAD TOWERSIM INIT\n";
    placing = false;
    towers = mytowers;
    burners = new vector<BurningEffectDecorator*>;
    icers = new vector<SlowingEffectDecorator*>;
    
    
}

TowerSimulator::TowerSimulator(){
    cout << "\n BAD TOWERSIM INIT\n";
    placing = false;
    towers = new vector<Towers*>;
    burners = new vector<BurningEffectDecorator*>;
    icers = new vector<SlowingEffectDecorator*>;
    
    
}

TowerSimulator::TowerSimulator(Player* thePlayer){
    cout << "\n Initializing Tower Simulator\n";
    placing = false;
    towers = new vector<Towers*>;
    burners = new vector<BurningEffectDecorator*>;
    icers = new vector<SlowingEffectDecorator*>;
    player = thePlayer;
    towerSelect = -1;
    
    
}


int TowerSimulator::addMap(Map *theMap){
    map = theMap;
    return 0;
}

//Destructor to delete towers and clear vectors
TowerSimulator::~TowerSimulator(){
    if(towers){
        for(auto t : *towers){
            delete t;
        }
        towers->clear();
        delete towers;
        towers = nullptr;
    }
    if(burners){
        burners->clear();
        delete burners;
        burners = nullptr;
    }
    if(icers){
        icers->clear();
        delete icers;
        icers = nullptr;
    }
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

//Render towers along with tooltips
int TowerSimulator::renderTowers(sf::RenderWindow* window){

    
    if(towers->size() == 0){
        return 0;
    }

     //define the size of the tower
     sf::Vector2f towerRect(20.f, 20.f);
     //create the rectangle shape and colour
     sf::RectangleShape towerShape(towerRect);

     if(towerSelect >= 0){
        int sx = towers->at(towerSelect)->getPosition().x;
        int sy = towers->at(towerSelect)->getPosition().y;
        towerShape.setPosition({float(sx) * 20.f + 100.f, float(sy) * 20.f + 100.f});
        towerShape.setFillColor(sf::Color::Transparent);
        towerShape.setOutlineColor(sf::Color::Black);
        towerShape.setOutlineThickness(2.f);
        window->draw(towerShape);
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
        tooltip.setFillColor(TEXT_COLOR);
        tooltip.setOutlineColor(sf::Color::Black);
        tooltip.setOutlineThickness(2.f);
        tooltip.setPosition({shapex + 30.f, shapey - 20.f});
        window->draw(tooltip);}

        

    

    }

    

    return 0;
}

//render the menu allowing the different towers to be purchased
int TowerSimulator::renderPurchaseMenu(sf::RenderWindow* window){
    sf::RectangleShape button;
    button.setSize({100.f,40.f});
    button.setFillColor(sf::Color::Transparent);
    button.setOutlineColor(ACCENT_COLOR);
    button.setOutlineThickness(1.f);

    sf::Font font("Arial Unicode.ttf");
    sf::Text text(font); 
    text.setCharacterSize(16);
    text.setFillColor(TEXT_COLOR);

    text.setString("Archer\n" + to_string(Towers::archerCost) + " coin");
    if(selected == 'a'){
        button.setFillColor(SECONDARY_COLOR);
    } else {
        button.setFillColor(sf::Color::Transparent);
    }
    button.setPosition({100.f, 50.f});
    text.setPosition({110.f, 50.f});
    window->draw(button);
    window->draw(text);

    text.setString("Ballista\n" + to_string(Towers::ballistaCost) + " coin");
    if(selected == 'b'){
        button.setFillColor(SECONDARY_COLOR);
    } else {
        button.setFillColor(sf::Color::Transparent);
    }
    button.setPosition({200.f, 50.f});
    text.setPosition({210.f, 50.f});
    window->draw(button);
    window->draw(text);

    text.setString("Catapult\n" + to_string(Towers::catapultCost) + " coin");
    if(selected == 'c'){
        button.setFillColor(SECONDARY_COLOR);
    } else {
        button.setFillColor(sf::Color::Transparent);
    }
    button.setPosition({300.f, 50.f});
    text.setPosition({310.f, 50.f});
    window->draw(button);
    window->draw(text);



    if(towerSelect >= 0){
        text.setCharacterSize(14);
        button.setSize({80.f, 40.f});
        

        text.setString("Upgrade!");
        button.setPosition({10.f, 100.f});
        text.setPosition({20.f, 100.f});
        button.setOutlineColor(sf::Color::Blue);
        window->draw(button);
        window->draw(text);


        text.setString("Make Fire");
        button.setPosition({10.f, 150.f});
        text.setPosition({20.f, 150.f});
        button.setOutlineColor(sf::Color::Red);
        window->draw(button);
        window->draw(text);

        text.setString("Make Ice");
        button.setPosition({10.f, 200.f});
        text.setPosition({20.f, 200.f});
        button.setOutlineColor(sf::Color::Cyan);
        window->draw(button);
        window->draw(text);


    }



    return 0;
}

//upon clicking the window, check if a tower, placement, or button has been clicked
int TowerSimulator::click(sf::RenderWindow *window){

    //TODO: remove this !!!!!
    //placing = false;

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
            Towers* mytower;
            switch(selected){
                case 'a':
                    mytower = new Towers("archer", {xPos, yPos});
                    player->balance -= Towers::archerCost;
                    break;
                case 'b':
                    mytower = new Towers("ballista", {xPos, yPos});
                    player->balance -= Towers::ballistaCost;
                    break;
                case 'c':
                    mytower = new Towers("catapult", {xPos, yPos});
                    player->balance -= Towers::catapultCost;
                    break;

            }
            TowerObserver* myobs = new TowerObserver(*mytower);
            towers->push_back(mytower);
            cout << "Successfully created new tower!" << endl;
            selected = 'n';
            placing = false;
            return 0;
        } else {
            cout << "You can't place a tower there!";
        }
        


        //place tower
        //return 0;
    } 

        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        float x = mousePos.x;
        float y = mousePos.y;
        cout << "\nx position: " << x << endl;
        cout << "y position: " << y << endl;

        if(y > 50 & y < 80){
            if(x > 100 & x < 200){
                cout << "\nbuy archer" << endl;
                if(player->balance < Towers::archerCost){
                    cout << "\ninsufficient funds" << endl;
                    return 0;
                }
                selected = 'a';
                placing = true;
            } else if(x > 200 & x < 300){
                cout << "\nbuy ballista" << endl;
                if(player->balance < Towers::ballistaCost){
                    cout << "\ninsufficient funds" << endl;
                    return 0;
                }
                selected = 'b';
                placing = true;
            } else if(x > 300 & x < 400){
                cout << "\nbuy catapult" << endl;
                if(player->balance < Towers::catapultCost){
                    cout << "\ninsufficient funds" << endl;
                    return 0;
                }
                selected = 'c';
                placing = true;
            }
        }


        //select a tower
        

        if(towerSelect >= 0){
            cout << "\npressing button?" << endl;
            Towers* toUpgrade = towers->at(towerSelect);
            TowerObserver* upgradeObserver = toUpgrade->getTowerObserver();
            int towerX = towers->at(towerSelect)->getPosition().x;
            int towerY = towers->at(towerSelect)->getPosition().y;
            if(x > 10 & x < 90){
                if(y > 100 & y < 140){
                    cout << "\n click upgrade" << endl;
                    int success = map->upgrade('U', towerX, towerY);
                    if(success == 0){
                        ValueModifierDecorator* newTower = new ValueModifierDecorator(upgradeObserver->getType(), {towerX,towerY}, *toUpgrade, 20, 10, 1, 2, 100);
                        upgradeObserver = new TowerObserver(newTower);
                        towers->erase(towers->begin() + towerSelect);
                        towers->push_back(newTower);
                        //toUpgrade = newTower;
                        //upgradeObserver->update(toUpgrade->getLevel(), toUpgrade->getBuyingCost(), toUpgrade->getRefundValue(), toUpgrade->getRange(), toUpgrade->getPower(), toUpgrade->getRateOfFire(), {towerX,towerY}, "upgraded" );
                    }
                } else if(y > 150 & y < 190){
                    cout << "\n click fire" << endl;
                    int success = map->upgrade('F', towerX, towerY);
                    if(success == 0){
                        BurningEffectDecorator* newTower = new BurningEffectDecorator(upgradeObserver->getType(), {towerX,towerY}, *toUpgrade,0.5, 2);
                        upgradeObserver = new TowerObserver(newTower);
                        towers->erase(towers->begin() + towerSelect);
                        towers->push_back(newTower);
                        burners->push_back(newTower);
                        //upgradeObserver->update(toUpgrade->getLevel(), toUpgrade->getBuyingCost(), toUpgrade->getRefundValue(), toUpgrade->getRange(), toUpgrade->getPower(), toUpgrade->getRateOfFire(), {towerX,towerY}, "fire" );
                    }
                }
                else if(y > 200 & y < 240){
                    cout << "\n click ice" << endl;
                    int success = map->upgrade('I', towerX, towerY);
                    if(success == 0){
                        SlowingEffectDecorator* newTower = new SlowingEffectDecorator(upgradeObserver->getType(), {towerX,towerY}, *toUpgrade,0.5, 2);
                        upgradeObserver = new TowerObserver(newTower);
                        towers->erase(towers->begin() + towerSelect);
                        towers->push_back(newTower);
                        icers->push_back(newTower);
                        //upgradeObserver->update(toUpgrade->getLevel(), toUpgrade->getBuyingCost(), toUpgrade->getRefundValue(), toUpgrade->getRange(), toUpgrade->getPower(), toUpgrade->getRateOfFire(), {towerX,towerY}, "ice" );

                    }
                }
                
            }
        }

        x = (x - 100.0) / 20.0;
        y = (y - 100.0) / 20.0;
        int xPos = int(x);
        int yPos = int(y);


        towerSelect = -1;
        int size = towers->size();
        for(int i = 0; i < size; i++){
            if((towers->at(i)->getPosition().x == xPos) & (towers->at(i)->getPosition().y == yPos)){
                cout << "\nselected tower " << to_string(i) << endl;
                towerSelect = i;

            }

            
        }

        

        

        return 0;

    
}

void TowerSimulator::shoot(SFMLCritterSimulator *critSim){
    vector<Critter *>*  mycritters;
    Critter* critt;

    mycritters = critSim->getCritters();
    for( auto t : *towers){
        critt = t->findTarget(mycritters);
        if(critt != NULL){
            t->shoot(*critt);
        }

    }
    for (auto b : *burners){
        cout << "update burning" << endl;
        //b->updateBurningEffects();
    }
    for (auto i: *icers){
        cout << "update slowing" << endl;
        //i->updateSlowingEffects();
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