#include "GameRenderer.h"
#include "MainMenu.h"
#include <iostream>
#include <optional>

using namespace std;
using namespace ColorSchemeConstants;

//helper method
Position coordToPosition2(const coord &c) {
    Position p;
    p.x = c.x;
    p.y = c.y;
    return p;
 }

 //constructor class
GameRenderer::GameRenderer(Player* theplayer, Map* themap,  MapGraphics* themapGraphics, SFMLCritterSimulator* crSim, TowerSimulator* toSim){
    //initialize data
    window = new sf::RenderWindow(sf::VideoMode({600, 400}), "SFML works!");
    player = theplayer;
    map = themap;
    mapGraphics = themapGraphics;
    critSim = crSim;
    myTower =  new Towers("archer", {5, 5});
    tSim = toSim;
}


//
//
//
//
//
//Rendering the main / welcome window
int GameRenderer::mainWindow(){
    
    window->setTitle("Tower Defense: Main Menu");

    sf::Font font("Arial Unicode.ttf");

    MainMenu menu(window, font);
    int menuChoice;

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
                if(keyPressed->scancode == sf::Keyboard::Scancode::Enter || keyPressed->scancode == sf::Keyboard::Scancode::Right){
                    menu.selectMenu();
                }
            }
        }
        //draws entire main menu. 
        menuChoice = menu.draw();
    }
    switch (menuChoice){
        case 0:{//play map
            return menuChoice;
            break;
        }
        case 1:{//Make a Map
            return menuChoice;
            break;
        }
        default:{
            break;
        }
    }
    return -1; // no choice made
}

//
//
//
//
//
void GameRenderer::getParamsWindow(){
    delete window;
    window = new sf::RenderWindow(sf::VideoMode({600, 400}), "Making Map!");
    window->setTitle("Tower Defense: Determine Map Parameters");
    mapGraphics->getParameters(window);
}


//
//
//
//
//
int GameRenderer::loadMapWindow(){
    delete window;
    window = new sf::RenderWindow(sf::VideoMode({600, 400}), "Load a Map");
    window->setTitle("Tower Defense: Load a map");
    
    int selection = -1;
    bool loaded = false;

    vector<string> mapVector = map->getMapList();
    int numberOfMaps = mapVector.size();
    if (numberOfMaps == 0){
        cout << "No maps found !" << endl;
        return 1;
    }

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
                if(keyPressed->scancode == sf::Keyboard::Scancode::Num0)
                    //move down
                    selection = 0;
                if(keyPressed->scancode == sf::Keyboard::Scancode::Num1)
                    //move up
                    
                    selection = 1;
                if(keyPressed->scancode == sf::Keyboard::Scancode::Num2)
                    //move down
                    if(numberOfMaps >= 2){
                        selection = 2;
                    }
                if(keyPressed->scancode == sf::Keyboard::Scancode::Num3)
                    //move down
                    if(numberOfMaps >= 3){
                        selection = 3;
                    }
                if(keyPressed->scancode == sf::Keyboard::Scancode::Num4)
                    //move down
                    if(numberOfMaps >= 4){
                        selection = 4;
                    }
                if(keyPressed->scancode == sf::Keyboard::Scancode::Num5)
                    //move down
                    if(numberOfMaps >= 5){
                        selection = 5;
                    }
                if(keyPressed->scancode == sf::Keyboard::Scancode::Num6){
                    //select map
                    if(numberOfMaps >= 6){
                        selection = 6;
                    }
                }
                if(keyPressed->scancode == sf::Keyboard::Scancode::Enter){
                    //select map
                    if(loaded == true){
                        //send path to critters
                        std::vector<Position> critterPath;
                        for(auto &c : map->getPath())
                            { critterPath.push_back(coordToPosition2(c));}


                        // create critter simulator with map and critter data
                        critSim = new SFMLCritterSimulator(map, critterPath);
                        window->close();
                        return 0;
                    }
                }
                if(keyPressed->scancode == sf::Keyboard::Scancode::Backspace){
                    //select map
                    if(loaded == true){
                        selection = -1;
                        loaded = false;
                    }
                }
            }
        }
        window->clear(BACKGROUND_COLOR);
        if(selection == -1){
            mapGraphics->loadingMap(window, mapVector);
        }else{
            if(loaded == false){
                map->loadMap(mapVector[selection] + ".txt");
                loaded = true;
            }
            mapGraphics->viewMap(window);
        }
        
        window->display();
    }





    return 0;
}

//
//
//
//
//
//Rendering the mapmaking portion of the game
int GameRenderer::makeMapWindow(){
    delete window;
    int mapheight = map->getHeight();
    int mapwidth = map->getWidth();
    winwidth = static_cast<unsigned int>(max(20*mapwidth + 200, 600));
    winheight = static_cast<unsigned int>(max(20*mapheight + 200, 400));
    window = new sf::RenderWindow(sf::VideoMode({winwidth, winheight}), "Making Map!");
    window->setTitle("Tower Defense: Make Map");

    //render mapMaker graphics
    int success = mapGraphics->mapMaking(window);
    if(success == 1){
        return 1;
    }
    map->printMap();

    //send path to critters
    std::vector<Position> critterPath;
    for(auto &c : map->getPath())
      { critterPath.push_back(coordToPosition2(c));}

    // create critter simulator with map and critter data
    critSim = new SFMLCritterSimulator(map, critterPath);

    return 0;

}

//Initial tower purchase phase before wave 1
void GameRenderer::preWavePhase(){
    bool resume = false;


    pauseTimeInit();
    window->display();
    while(!resume && window->isOpen()){
        while(auto pauseEvent = window->pollEvent()){
            if(auto pauseEvent2=pauseEvent->getIf<sf::Event::KeyPressed>()){
                if(pauseEvent2->code == sf::Keyboard::Key::Enter){
                    resume = true;
                }
            }
               
            if(pauseEvent->is<sf::Event::Closed>()){
                window->close();
                return;
            }else if(pauseEvent->is<sf::Event::MouseButtonPressed>()){
                tSim->click(window);   
            }
        }

    window->clear(BACKGROUND_COLOR);
    //render map
    mapGraphics->renderMap(window);
    //render towers and tower menu
    tSim->renderTowers(window);
    tSim->renderPurchaseMenu(window);
    
    pauseTimeInit();
    //render player balance
    player->renderBalance(window);
    //send click to towerBuy and towerUpgrade
    window->display();        
    }
}

//Runs the main simulation loop (waves, tower)
void GameRenderer::simulateWave(){
    sf::Clock simulationClock;
    sf::Clock towerClock;
    float simulationInterval = 0.5f;
    float elapsedTime = 0.f;
    float shootTime = 0.f;
    bool gameOver = false;
    
    //loop through input logic
    while(window->isOpen()){
        //receive player input
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
               { 
                window->close();
                return;

            } else if(event->is<sf::Event::MouseButtonPressed>()){
                tSim->click(window);           
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    window->close();
                    return;
                }
            }       
        }

        //Update simulation and player's stats before drawing
         elapsedTime = critSim->checkClock(elapsedTime, &simulationClock);
         critSim->updateCritters(elapsedTime);

        // run tower tageting algorithm
         shootTime += towerClock.restart().asSeconds();
         if(shootTime >= simulationInterval){
              cout << "resetting clock!" << endl;
              shootTime = 0.f;
         }
         if(shootTime == 0.f){
              cout << "attempting to shoot critters" << endl;
              tSim->shoot(critSim);
         }

        //Update player's stats based on simulation changes
        if(critSim->coinsRewarded > 0 || critSim->healthLost > 0){
              player->balance += critSim->coinsRewarded;
              player->reduceHealth(critSim->healthLost);
              critSim->coinsRewarded = 0;
              critSim->healthLost = 0;
         }
        
         //Check for game over (when player health <= 0)
        if(player->getHealth() <= 0){
              gameOver = true;
        }

         window->clear(BACKGROUND_COLOR);
         //render map
         mapGraphics->renderMap(window);
         //render towers and tower menu
         tSim->renderTowers(window);
         tSim->renderPurchaseMenu(window);

         //render player balance
         player->renderBalance(window);

         //send click to towerBuy and towerUpgrade
         critSim->drawSimulation(window);

         //If game over, show Game Over screen and prompt restart
         if(gameOver){
              handleGameOver();
              return;
         }

         //If wave is complete and game is not over, pause to allow tower upgrades
         if(critSim->isWaveComplete() && !gameOver){
            if(critSim->getCurrentWave() < critSim->getMaxWave()){
                 pauseTime();
                 window->display();
                 bool resume = false;
                 while(!resume && window->isOpen()){
                      while(auto pauseEvent = window->pollEvent()){
                           if(auto keyEvent = pauseEvent->getIf<sf::Event::KeyPressed>())
                                if(keyEvent->code == sf::Keyboard::Key::Enter)
                                     resume = true;
                           if(pauseEvent->is<sf::Event::Closed>()){
                                window->close();
                                return;
                           } else if(pauseEvent->is<sf::Event::MouseButtonPressed>()){
                                tSim->click(window);
                           }
                      }
                      window->clear(BACKGROUND_COLOR);
                      mapGraphics->renderMap(window);
                      tSim->renderTowers(window);
                      tSim->renderPurchaseMenu(window);
                      pauseTime();
                      player->renderBalance(window);
                      window->display();
                 }
                 critSim->startNextWave();
            } else {
                 //Final wave complete, trigger end game menu
                 endGame();
                 return;
            }
       }
         window->display();
         elapsedTime = 0.f;
    }
}

//Function to handle game over state and restart
void GameRenderer::handleGameOver(){
    sf::Font font;
    if(!font.openFromFile("arial.ttf"))
         std::cerr << "Error loading font\n";

    //Display Game Over Text
    sf::Text gameOverText(font);
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition({220.f,100.f});
    
    //Set up two menu options: Main Menu and Quit
    sf::Text optionMain(font);
    sf::Text optionQuit(font);
    optionMain.setString("Main Menu");
    optionQuit.setString("Quit");
    optionMain.setCharacterSize(25);
    optionQuit.setCharacterSize(25);
    optionMain.setPosition({220.f, 180.f});
    optionQuit.setPosition({220.f, 220.f});

    //Selected option: 0 for Main Menu, 1 for Quit
    int selectedOption = 0;
    optionMain.setFillColor(ACCENT_COLOR);
    optionQuit.setFillColor(TEXT_COLOR);

    bool menuDone = false;
    while(!menuDone && window->isOpen()){
         while(auto event = window->pollEvent()){
              if(event->is<sf::Event::Closed>()){
                   window->close();
                   menuDone = true;
              }
              else if(auto keyEvent = event->getIf<sf::Event::KeyPressed>()){
                   if(keyEvent->code == sf::Keyboard::Key::Up){
                        selectedOption = (selectedOption == 0) ? 1 : 0;
                   } else if(keyEvent->code == sf::Keyboard::Key::Down){
                        selectedOption = (selectedOption == 1) ? 0 : 1;
                   } else if(keyEvent->code == sf::Keyboard::Key::Enter){
                        menuDone = true;
                   }
              }
         }
         // Update option colors based on selection.
         if(selectedOption == 0){
             optionMain.setFillColor(ACCENT_COLOR);
             optionQuit.setFillColor(TEXT_COLOR);
         } else {
             optionMain.setFillColor(TEXT_COLOR);
             optionQuit.setFillColor(ACCENT_COLOR);
         }
         window->clear(BACKGROUND_COLOR);
         window->draw(gameOverText);
         window->draw(optionMain);
         window->draw(optionQuit);
         window->display();
    }

    if(selectedOption == 0){ // "Main Menu" selected
         // CHANGED: Fully reset game state and go back to main menu.
         player->balance = 100;
         player->health = 100;
         delete map;
         map = new Map(20,20);
         delete critSim;
         critSim = nullptr;
         delete tSim;
         tSim = new TowerSimulator(player);
         delete mapGraphics;
         MapObserver* newObserver = new MapObserver;
         map->getObserver(newObserver);
         mapGraphics = new MapGraphics(newObserver, map);
         startGame();

    } else {
         window->close();
    }
}

//Critter attack phase
void GameRenderer::playTime(){
    //Set window height accordingly
    int mapheight = map->getHeight();
    int mapwidth = map->getWidth();
    winwidth = static_cast<unsigned int>(max(20*mapwidth + 200, 600));
    winheight = static_cast<unsigned int>(max(20*mapheight + 200, 400));

    //delete window and create a new one
    delete window;
    window = new sf::RenderWindow(sf::VideoMode({winwidth, winheight}), "Playtime!");
    window->setTitle("Battle Time !");
    preWavePhase();
    simulateWave();
    }
    
//
//
//
//
//
//Between waves - tower purchasing phase
void GameRenderer::pauseTime(){
    window->setTitle("Place and upgrade your towers !");

    
    //render hoverstats

    
    sf::Font font;
        if(!font.openFromFile("arial.ttf")){
            std::cerr << "Error loading font\n";
        }
             sf::Text continueText(font);
             continueText.setCharacterSize(20);
             continueText.setFillColor(ACCENT_COLOR);
             continueText.setString("Wave Complete! Press Enter to start the next wave!");
             continueText.setPosition({100.f, float(winheight) - 50.f});
             window->draw(continueText);
            

    return;
}

//
//
//
//
//
//Initial tower purchasing phase, before wave 1 starts
void GameRenderer::pauseTimeInit(){
    window->setTitle("Place and upgrade your towers !");

    //render map
    //send click to towerBuy and towerUpgrade
    //render hoverstats

    
    sf::Font font;
        if(!font.openFromFile("arial.ttf")){
            std::cerr << "Error loading font\n";
        }
             sf::Text continueText(font);
             continueText.setCharacterSize(20);
             continueText.setFillColor(sf::Color::White);
             continueText.setString("Press Enter to Start the Wave after Purchasing Towers!");
             continueText.setPosition({75.f, float(winheight) - 50.f});
             window->draw(continueText);
             

    return;
}


//endGame Menu, After final wave completion
//
//
//
//
//

void GameRenderer::endGame(){
    window->setTitle("Tower Defense: Game Completed!");
    sf::Font font;
    if (!font.openFromFile("arial.ttf"))
        std::cerr << "Error loading font\n";

    //Display the congratulatory heading and stats
    sf::Text heading(font);
    heading.setString("Congrats! You beat the game!");
    heading.setCharacterSize(30);
    heading.setFillColor(sf::Color::Red);
    heading.setPosition({100.f, 50.f});

    std::string statsStr = "Stats:\n"
                           "Fast Critters Killed: " + std::to_string(critSim->fastKilled) + "\n" +
                           "Tank Critters Killed: " + std::to_string(critSim->tankKilled) + "\n" +
                           "Boss Critters Killed: " + std::to_string(critSim->bossKilled) + "\n" +
                           "Total Coins Earned: " + std::to_string(critSim->totalCoinsEarned);
    sf::Text statsText(font);
    statsText.setString(statsStr);
    statsText.setCharacterSize(20);
    statsText.setFillColor(sf::Color::White);
    statsText.setPosition({100.f, 110.f});

    //Set up two menu options: Main Menu and Quit
    sf::Text optionMain(font);
    sf::Text optionQuit(font);
    optionMain.setString("Main Menu");
    optionQuit.setString("Quit");
    optionMain.setCharacterSize(25);
    optionQuit.setCharacterSize(25);
    optionMain.setPosition({100.f, 250.f});
    optionQuit.setPosition({100.f, 290.f});

    int selectedOption = 0; //0 = Main Menu, 1 = Quit.
    optionMain.setFillColor(ACCENT_COLOR);
    optionQuit.setFillColor(TEXT_COLOR);

    bool menuDone = false;
    while(!menuDone && window->isOpen()){
         while(auto event = window->pollEvent()){
              if(event->is<sf::Event::Closed>()){
                   window->close();
                   menuDone = true;
              }
              else if(auto keyEvent = event->getIf<sf::Event::KeyPressed>()){
                   if(keyEvent->code == sf::Keyboard::Key::Up){
                        selectedOption = (selectedOption == 0) ? 1 : 0;
                   } else if(keyEvent->code == sf::Keyboard::Key::Down){
                        selectedOption = (selectedOption == 1) ? 0 : 1;
                   } else if(keyEvent->code == sf::Keyboard::Key::Enter){
                        menuDone = true;
                   }
              }
         }
         if(selectedOption == 0){
             optionMain.setFillColor(ACCENT_COLOR);
             optionQuit.setFillColor(TEXT_COLOR);
         } else {
             optionMain.setFillColor(TEXT_COLOR);
             optionQuit.setFillColor(ACCENT_COLOR);
         }
         window->clear(BACKGROUND_COLOR);
         window->draw(heading);
         window->draw(statsText);
         window->draw(optionMain);
         window->draw(optionQuit);
         window->display();
    }

    //To Main Menu, Replaying the Game
    if(selectedOption == 0){
         player->balance = 100;
         player->health = 100;

         //Delete current map, critter simulator, tower simulator, and map graphics
         delete map;
         map = new Map(20,20);
         delete critSim;
         critSim = nullptr;
         delete tSim;
         tSim = new TowerSimulator(player);
         delete mapGraphics;
         MapObserver* newObserver = new MapObserver;
         map->getObserver(newObserver);
         mapGraphics = new MapGraphics(newObserver, map);
         startGame();
    } else {
         window->close();
    }
}


//
//
//
//
//
void GameRenderer::startGame(){
   
//main menu
 int choice = mainWindow();
 

if(choice == 1){
    //make map option
    getParamsWindow();
    makeMapWindow();
} else if (choice == 0){
    loadMapWindow();
    cerr << "done loading the map!" << endl;
    //load map option

}

 //tower purchase phase
 tSim->addMap(map);
 
 //critter attack phase
 playTime();
}