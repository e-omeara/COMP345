#include "GameRenderer.h"
#include "MainMenu.h"

using namespace std;

Position coordToPosition2(const coord &c) {
    Position p;
    p.x = c.x;
    p.y = c.y;
    return p;
 }

GameRenderer::GameRenderer(Player* theplayer, Map* themap,  MapGraphics* themapGraphics, SFMLCritterSimulator* crSim){
    window = new sf::RenderWindow(sf::VideoMode({800, 600}), "SFML works!");
    player = theplayer;
    map = themap;
    mapGraphics = themapGraphics;
    critSim = crSim;
    myTower =  new Towers("archer", {5, 5});


}

void GameRenderer::mainWindow(){
    
    window->setTitle("Tower Defense: Main Menu");

    sf::Font font("Arial Unicode.ttf");

    MainMenu menu(window, font);

    //create the render window
    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {
            //check for key inputs
            if (event->is<sf::Event::Closed>())
                window->close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window->close();
                if(keyPressed->scancode == sf::Keyboard::Scancode::Up)
                    menu.moveUp();
                if(keyPressed->scancode == sf::Keyboard::Scancode::Down)
                    menu.moveDown();
            }
        }
        //draws entire main menu
        menu.draw();
    }

    


    return;
}

void GameRenderer::makeMapWindow(){
    window->setTitle("Tower Defense: Make Map");

    //render mapMaker graphics
    mapGraphics->mapMaking(window);
    map->printMap();

    std::vector<Position> critterPath;
    for(auto &c : map->getPath())
      { critterPath.push_back(coordToPosition2(c));}


    // create critter simulator
    critSim = new SFMLCritterSimulator(map, critterPath);


    return;
}

void GameRenderer::playTime(){
    delete window;
    window = new sf::RenderWindow(sf::VideoMode({600, 400}), "Playtime!");
    window->setTitle("Battle Time !");
    sf::Clock* simulationClock = new sf::Clock();
    float elapsedTime = 0;
    vector<Critter *>  mycritters;
    Critter* critt;
   // Critter* critt;
    
    
    while(window->isOpen()){
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
    //
    if(elapsedTime == 0.f){
        critt = myTower->findTarget(mycritters);
        if(critt != NULL){
            myTower->shoot(*critt);
        }
    }
    
    
    //render hover stats

    window->display();

    



    }

    


    return;
}

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

    
    

 mainWindow();
 //makeMapWindow();
 
 //playTime();

 
 
    

    

}