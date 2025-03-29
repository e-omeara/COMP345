//This is the basic map class
//This holds two main attributes: the map array and the path array
//This also holds the methods for making the map
//And validating the map


#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include "Map.h" 

using namespace std;





    
    
        //Constructor takes map width and height as input
        Map::Map(int x, int y){ 
            
            width = x;
            height = y;
            cout << "You've constructed MAP with height " << height << " \n";


            //Set up the class for map making
            isMaking = true;
            prevDir = 'x';
            makeX = 0;
            makeY = 0;
            coord orig;
            orig.x = 0;
            orig.y = 0;
            path.resize(1, orig);

            //create the linear array of the specified size
            map.resize(x*y, '-');
            cout << "done making map\n";

            


        }

        Map::Map(){
            this->width = 20;
            this->height = 20;
            isMaking = true;
            prevDir = 'x';
            map.resize(this->height * this->width, '-');
            return;
        }

        void Map::getObserver(MapObserver* plugin){
            observer = plugin;
            cout << "ready for game?";
            updateObserver("ready for game");
            cout << "ready for game";
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


        string Map::stringMap(){

            string strmap;
            int count = 0;

            //cout << height << width;

            

            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    //strmap.push_back('i');
                    strmap.push_back( map[i*width + j]);
                    count++;
                
                }
                
                strmap.append("\n");
            }
            
            //cout << strmap << "\n";


            return strmap;
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

        int Map::upgrade(char type, int xPos, int yPos){
            int index = getPos(xPos, yPos);
            if(map[index] == 'T'){
                map[index] = toupper(type);
                updateObserver("upgraded tower");
                return 0;
            }
            return 1;
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
            
            path[0].x = x;
            path[0].y = y;
            cout << path[0].x << "position" << path[0].y;
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
                    updateObserver("You just came from there!");
                    cout << "You just came from there!\n\n";
                    return;
                }
                // make sure we don't go off the map
                if(makeY == 0){
                    cout << "You can't go there!\n\n";
                    updateObserver("You can't go there!");
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
                    updateObserver("You just came from there!");
                    return;
                }
                if(makeY == height - 1){
                    cout << "You can't go there!\n\n";
                    updateObserver("You can't go there!");
                    return;
                }
                makeY++;
                map[getPos(makeX, makeY)] = 'P';
            }
            else if(dir == 'l' || dir == 'L'){
                //go left
                if(prevDir == 'r' || prevDir == 'R'){
                    cout << "You just came from there!\n\n";
                    updateObserver("You just came from there!");
                    return;
                }
                if(makeX == 0){
                    cout << "You can't go there!\n\n";
                    updateObserver("You can't go there!");
                    return;
                }
                makeX--;
                map[getPos(makeX, makeY)] = 'P';
            }
            else if(dir == 'r' || dir == 'R'){
                //go right
                if(prevDir == 'l' || prevDir == 'L'){
                    cout << "You just came from there!\n\n";
                    updateObserver("You just came from there!");
                    return;
                }
                if(makeX == width - 1){
                    cout << "You can't go there!\n\n";
                    updateObserver("You can't go there!");
                    return;
                }
                makeX++;
                map[getPos(makeX, makeY)] = 'P';
            }

            //update the path vector
            coord pathstep;
            pathstep.x = makeX;
            pathstep.y = makeY;
            path.push_back(pathstep); // Add the new coordinates to the path

            //update the previous direction variable, used to prevent doubling back
            prevDir = dir;
            updateObserver("use the arrows keys to create the map, \n press e to create the exit");
            //printMapMaker(); <-- for testing purposes
            return;
        }

        //signals the player is done creating the path
        int Map::setExit(){
            
            //refuses exit if there is no path (i.e. there is only an entrance)
            int cnt = count(map.begin(), map.end(), 'P');
            if(cnt == 0){
                cout << "You haven't made a path!\n";
                return 1;
            }

            //in the map array, set the exist coord to X for exit
            map[getPos(makeX, makeY)] = 'X';
            updateObserver("Place a tower");
            cout << "You've finalized the exit!\n";
            //printMap();

            //the map cannot be modified any more
            isMaking = false;

            //Update the path
            coord pathstep;
            pathstep.x = makeX;
            pathstep.y = makeY;
            path.push_back(pathstep);

            return 0;

            

            
        }

        int Map::setTower(int x, int y){

            if(x > width || y > width){
                return 0;
            }

            int pos = getPos(x, y);
            if(map[pos] == '-'){
                map[pos] = 'T';
                cout << pos << endl;
                updateObserver("placed tower");
                printMap();

                return 0;
            } else {
                return 1;
            }


                
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


            void Map::updateObserver(string msg){

                observer->update(height, width, map, path, makeX, makeY, "status", msg);
                //observer->update(msg);
                cout << "\nmsg: " << msg << "\n";

                return;
            }

            // take the width x and height y positions and turn them into the 1d position along the map vector
            int Map::getPos(int x, int y){
                return (y)*width + x;
            } 







//for testing purposes
/*
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
*/



