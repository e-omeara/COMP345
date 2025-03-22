#include "GameRenderer.h"

using namespace std;

//helper method
Position coordToPosition2(const coord &c) {
    Position p;
    p.x = c.x;
    p.y = c.y;
    return p;
 }

 //constructor class
GameRenderer::GameRenderer(Player* theplayer, Map* themap,  MapGraphics* themapGraphics, SFMLCritterSimulator* crSim){
    //initialize data
    window = new sf::RenderWindow(sf::VideoMode({600, 400}), "SFML works!");
    player = theplayer;
    map = themap;
    mapGraphics = themapGraphics;
    critSim = crSim;
    myTower =  new Towers("archer", {5, 5});


}


//Rendering the main / welcome window
void GameRenderer::mainWindow(){
    
    window->setTitle("Tower Defense: Main Menu");

    sf::Font font("Arial Unicode.ttf");
    sf::Text text(font); 
    // set the string to display
    string textstr = "Welcome to Our Tower Defense Game!\n Make Map \n Load Map";
    text.setString(textstr);
    // set the character size
    text.setCharacterSize(24); 
    // set the color
    text.setFillColor(sf::Color::Red);
    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    window->draw(text);

    


    return;
}


//Rendering the mapmaking portion of the game
void GameRenderer::makeMapWindow(){
    window->setTitle("Tower Defense: Make Map");

    //render mapMaker graphics
    mapGraphics->mapMaking(window);
    map->printMap();

    //send path to critters
    std::vector<Position> critterPath;
    for(auto &c : map->getPath())
      { critterPath.push_back(coordToPosition2(c));}


    // create critter simulator with map and critter data
    critSim = new SFMLCritterSimulator(map, critterPath);


    return;
}

//Critter attack phase
void GameRenderer::playTime(){
    //delete window and create a new one
    delete window;
    window = new sf::RenderWindow(sf::VideoMode({600, 400}), "Playtime!");
    window->setTitle("Battle Time !");
    //initialize clock abilities for tower shoot and critter movement
    sf::Clock* simulationClock = new sf::Clock();
    float elapsedTime = 0;

    //critter wave objects
    vector<Critter *>  mycritters;
    Critter* critt;

    
    //loop through input logic
    while(window->isOpen()){
        //receive player input
        while (const std::optional event = window->pollEvent())
        {

            if (event->is<sf::Event::Closed>())
               { 
                
                window->close();
                delete simulationClock;

                return;
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    window->close();
                    delete simulationClock;


                    return;
                }}
            
        }
               

        

    window->clear();
    //render map
    mapGraphics->renderMap(window);
    //render tower menu

    //render player balance
    player->renderBalance(window);
    //send click to towerBuy and towerUpgrade


    //render critters
    elapsedTime = critSim->checkClock(elapsedTime, simulationClock);
    critSim->drawSimulation(window);
    critSim->checkAndLoadNextWave(window);
    mycritters = critSim->getCritters();
    // run tower tageting algorithm
    if(elapsedTime == 0.f){
        critt = myTower->findTarget(mycritters);
        if(critt != NULL){
            myTower->shoot(*critt);
        }
    }
    
    
    
    //display graphics
    window->display();

    



    }

    


    return;
}


//Between waves - tower purchasing phase
void GameRenderer::pauseTime(){
    window->setTitle("Place and upgrade your towers !");

    //render map
    mapGraphics->renderMap(window);
    //render tower menu
    //render player menu
    player->renderBalance(window);
    //send click to towerBuy and towerUpgrade
    //render hoverstats


    return;
}

void GameRenderer::endGame(){
    window->setTitle("Tower Defense: goodbye !");

    //render end game graphics

    //display loss or win

    //display stats


    return;
}

void GameRenderer::startGame(){

    
    
//main menu
 mainWindow();

 //making map menu
 makeMapWindow();

 //tower purchase phase
 

 //critter attack phase
 playTime();

 
 
    

    

}