
#include <iostream>
#include <cctype>
#include "MapMaker.h"
using namespace std;

int main(){
     startMapMaker();
     return 1;
}

void startMapMaker(){
     cout << "Welcome to the Map Maker\n";
     Map map = createMap();

     char input;
     editMap(map);
     bool loop = true;
     while(loop){
          cout << "Would you like to return to the main menu or play the map?\n"
               << "Enter m or p: ";
          cin >> input;
          input = tolower(input);
          if(input == 'm'){
               loop = false;
               backToMain();
          }
          if(input == 'p'){
               loop = false;
               startGame();
          }
          if(loop)
               cout << "invalid input";
     }
     
     return;
}

//asks user for map dimensions, creates map object, and sets entrance.
Map createMap(){
     int width, height;

//TODO: add input validation
     cout << "How wide would you like the map to be?\n";
     cin >> width;
     cout << "How tall would you like the map to be?\n";
     cin >> height;
     cout << "The map will be " << width << " cells wide and " << height << " cells tall.\n";
     cout << "Generating map...\n";
     Map map(width, height);

     map.printMap();

     //Origin is top left. Should we change?
     int x,y;
     cout << "Where would you like to place the entrance?\n" << "Enter the x-coordinate: ";
     cin >> x;
     x--;
     cout << "Enter the y-coordinate:";
     cin >> y;
     y--;

     map.setEntrance(x,y);

     return map;
}
//takes user input, calls Map::layMap
//user input also asks if user wants to place exit at current location > calls Map::setExit
//calls Map::printMapMaker() after every edit
void editMap(Map map){
     char input;
     while(input != 'q'){
          map.printMapMaker();
     
          cout << "Select a direction to lay the path.\n"
               << "Type 'u' 'd' 'l' or 'r' to lay a path.\n"
               << "Type 'e' to place the exit at the current position.\n";
          cin >> input;
          input = tolower(input);
          if(input == 'e'){
               cout << "Placing exit at current location\n";
               map.setExit();
               map.printMap();
               break;
          }
          //switch case ensures that the proper input was given. if not u,d,l, or r, is invalid and loops again
          switch (input){
               case 'u':
                    map.laypath('u');
                    break;
               case 'd':
               map.laypath('d');
                    break;
               case 'l':
                    map.laypath('l');
                    break;
               case 'r':
                    map.laypath('r');
                    break;
               case 'q':
                    break;
               default:
                    cout << "invalid input\n";
                    break;
          }
          
     }
     return;
}


//clear and show game placeholder
void startGame(){
     //system("cls");
     cout << "You're playing the game now...";

}
//clear and show place holder for mm
void backToMain(){
     //system("cls");
     cout << "Returning to main menu...";
}
