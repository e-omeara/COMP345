
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include "Map.h" 
//#include "MapMaker.h" 
using namespace std;





    
    
        //Constructor takes map width and height as input
        Map::Map(int x, int y){ 
            cout << "You've constructed MAP \n";
            width = x;
            height = y;

            //Set up the class for map making
            isMaking = true;
            prevDir = 'x';

            //create the linear array of the specified size
            map.resize(x*y, '-');

            


        }



        //Print out the map in a 2d output
        void Map::printMap(){

            

            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    cout << map[i*width + j];
                
                }
                cout << "\n";
            }
            
            cout << "\n";


            return;
        }


        // getter method for the critter path
        vector<coord> Map::getPath(){

            return path;
        }

        //getting method for the 1d map array
        vector<char> Map::getMap(){

            return map;
        }

        //get the width of the map
        int Map::getWidth(){
            return width;
        }

        //get the hheight of the map
        int Map::getHeight(){
            return height;
        }


        //To use in the larger game
        void Map::initiateMaking(){
            isMaking = true;
            return;

        }

        //Specifies the entrance, which is the first coord of the path
        void Map::setEntrance(int x, int y){

            if (isMaking == false){
                cout << "you're not making a map!\n";
                return ;
            }

            //Specify where the user is
            makeX = x;
            makeY = y;

            //set first entry in the path vector
            coord start;
            start.x = x;
            start.y = y;
            path.push_back(start);
            //Set entrance coordinate to N for entrance
            map[getPos(x, y)] = 'N';
            //printMap();
            return;

        }

        //Take a char as parameter, adds a 'P' to the map vector as necessary, checks for doubleback
        void Map::laypath(char dir){

            //make sure we're in the mapmaking mode
            if (isMaking == false){
                cout << "you're not making a map!\n";
                return ;
            }

            //take a character as unput
            if(dir == 'u' || dir == 'U'){
                //go up
                //make sure the path doesn't double back
                if(prevDir == 'd' || prevDir == 'D'){
                    
                    cout << "You just came from there!\n\n";
                    return;
                }
                // make sure we don't go off the map
                if(makeY == 0){
                    cout << "You can't go there!\n\n";
                    return;
                }
                //adjsut the player's current position in the map
                makeY--;
                //set the current coord in the map to P for path
                map[getPos(makeX, makeY)] = 'P';
                
            }
            else if(dir == 'd' || dir == 'D'){
                //go down
                if(prevDir == 'u' || prevDir == 'U'){
                    cout << "You just came from there!\n\n";
                    return;
                }
                if(makeY == height - 1){
                    cout << "You can't go there!\n\n";
                    return;
                }
                makeY++;
                map[getPos(makeX, makeY)] = 'P';
            }
            else if(dir == 'l' || dir == 'L'){
                //go left
                if(prevDir == 'r' || prevDir == 'R'){
                    cout << "You just came from there!\n\n";
                    return;
                }
                if(makeX == 0){
                    cout << "You can't go there!\n\n";
                    return;
                }
                makeX--;
                map[getPos(makeX, makeY)] = 'P';
            }
            else if(dir == 'r' || dir == 'R'){
                //go right
                if(prevDir == 'l' || prevDir == 'L'){
                    cout << "You just came from there!\n\n";
                    return;
                }
                if(makeX == width - 1){
                    cout << "You can't go there!\n\n";
                    return;
                }
                makeX++;
                map[getPos(makeX, makeY)] = 'P';
            }

            //update the path vector
            coord pathstep;
            pathstep.x = makeX;
            pathstep.y = makeY;

            //update the previous direction variable, used to prevent doubling back
            prevDir = dir;
            //printMapMaker(); <-- for testing purposes
            return;
        }

        //signals the player is done creating the path
        void Map::setExit(){
            
            //refuses exit if there is no path (i.e. there is only an entrance)
            int cnt = count(map.begin(), map.end(), 'P');
            if(cnt == 0){
                cout << "You haven't made a path!\n";
                return;
            }

            //in the map array, set the exist coord to X for exit
            map[getPos(makeX, makeY)] = 'X';
            cout << "You've finalized the exit!\n";
            //printMap();

            //the map cannot be modified any more
            isMaking = false;

            return;

            

            
        }

  
            //print the map while indicating the current player location with an X
            void Map::printMapMaker(){

            //make a copy of the map vector
            vector<char> mapMaker = map;
            //set the current player position to X
            mapMaker[getPos(makeX,makeY)] = 'X';

            //print it out according to the width and height as a 2d array
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    cout << mapMaker[i*width + j];
                
                }
                cout << "\n";
            }
            
            cout << "\n";


            return;
            }  

            // take the width x and height y positions and turn them into the 1d position along the map vector
            int Map::getPos(int x, int y){
                return (y)*width + x;
            } 







//for testing purposes
int main(){

    Map map(15, 10);
    map.printMap();
    map.setEntrance(3,4);
    map.initiateMaking();
    map.setEntrance(3,4);
    map.laypath('U');
    map.laypath('U');
    map.laypath('d');
    map.laypath('r');
    map.laypath('R');
    map.laypath('d');
    map.laypath('U');
    map.laypath('U');
    map.laypath('d');
    map.laypath('r');
    map.laypath('R');
    map.laypath('U');
    map.laypath('L');
    map.laypath('U');
    map.laypath('d');
    map.laypath('r');
    map.laypath('R');
    map.laypath('r');
    map.laypath('R');
    map.laypath('r');
    map.laypath('R');
    map.laypath('r');
    map.laypath('R');
    map.laypath('R');
    map.laypath('r');
    map.laypath('R');
    map.laypath('d');
    map.laypath('d');
    map.laypath('d');
    map.laypath('d');
    map.laypath('L');
    map.laypath('L');
    map.laypath('L');
    map.laypath('L');
    map.setExit();


    return 0;

};




