//This is the basic map class
//This holds two main attributes: the map array and the path array
//This also holds the methods for making the map
//And validating the map


#include <iostream>
#include <filesystem>
#include <fstream> 
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

        // takes the x & coords of a tower and 
        //called by TowerSimulator::click
        int Map::changeTargeting(char targType, int xPos, int yPos){
            int index = getPos(xPos, yPos);
            if(map[index] == 'T'){
                //map[index];
                updateObserver("");
                return 0;
            }
            return 1;
        }


        //To use in the larger game
        void Map::initiateMaking(){
            isMaking = true;
            return;

        }


        void Map::resize(int x, int y){
            map.resize(x*y, '-');
            width = x;
            height = y;
            updateObserver("changed map size");
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
            updateObserver("set entrance");
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
                if(map[getPos(makeX, makeY - 1)] == 'N'){
                    cout << "You can't go over the entrance!\n\n";
                    updateObserver("You can't go over the entrance!");
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
                if(map[getPos(makeX, makeY + 1)] == 'N'){
                    cout << "You can't go over the entrance!\n\n";
                    updateObserver("You can't go over the entrance!");
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
                if(map[getPos(makeX - 1, makeY)] == 'N'){
                    cout << "You can't go over the entrance!\n\n";
                    updateObserver("You can't go over the entrance!");
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
                if(map[getPos(makeX + 1, makeY)] == 'N'){
                    cout << "You can't go over the entrance!\n\n";
                    updateObserver("You can't go over the entrance!");
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

            if(x < 0 || x >= width || y<0 || y >= height){
                return 1;
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


            void Map::saveMap(string fileName){

                

                ofstream newFile("saved_maps/" + fileName + ".txt");

                cout << "Saving map data" << endl;
                newFile << width << endl;
                newFile << height << endl;
                for(auto c : path){
                    newFile << c.x << ":" << c.y << endl;
                }



                return;
            }

            


            int Map::loadMap(string fileName){

                ifstream readFile("saved_maps/" + fileName);

                vector<coord> inPath;
                string inWidth;
                string inHeight;
                getline(readFile, inWidth);
                cout << "\n\n\n\nWidth: " << inWidth << endl;
                getline(readFile, inHeight);
                cout << "\nHeight: " << inHeight << endl;
                string pathStep;
                int loadX;
                int loadY;
                while (getline (readFile, pathStep, ':')) {
                    // Output the text from the file
                    loadX = stoi(pathStep);
                    getline (readFile, pathStep);
                    loadY = stoi(pathStep);
                    cout << loadX << endl;
                    cout << loadY << endl;
                    inPath.push_back({loadX, loadY});
                    cout << "\n";
                  }

                  cout << "\n\n\n";

                
                readFile.close();

                if (inPath.size() == 0){
                    cout << "No map in this file!" << endl;
                    return 1;
                }

                width = stoi(inWidth);
                height = stoi(inHeight);
                path = inPath;

                
                map.resize(0);
                map.resize(width*height, '-');
                map[getPos(path[0].x, path[0].y)] = 'N';
                for(int i = 1; i < path.size(); i++){
                    int index = getPos(path[i].x, path[i].y);
                    map[index] = 'P';
                }
                map[getPos(path[path.size()-1].x, path[path.size()-1].y)] = 'X';

                updateObserver("Successfully loaded map");

                cout << "Successfully loaded map" << endl;
                return 0;
            }

            vector<string> Map::getMapList()
            {
                string path = "./saved_maps";
                vector<string> mapList;
                for (const auto & entry : filesystem::directory_iterator(path)){
                    string mapName = entry.path().stem().string();
                    cout << entry.path().stem().string() << std::endl;
                    mapList.push_back(mapName);
                    
                }


                return mapList;
            }

            void Map::updateObserver(string msg){

                if (observer !=nullptr)
                observer->update(height, width, map, path, makeX, makeY, "status", msg);
                //observer->update(msg);
                cout << "\nmsg: " << msg << "\n";

                return;
            }

            // take the width x and height y positions and turn them into the 1d position along the map vector
            int Map::getPos(int x, int y){
                return (y)*width + x;
            } 

            //Removing all towers that are on the map for restart/replay purposes
            void Map::clearTowers() {
                for (size_t i = 0; i < map.size(); i++) {
                    char cell = map[i];
                    //If the cell is not one of the default map markers, clear it
                    if (cell != '-' && cell != 'N' && cell != 'P' && cell != 'X') {
                        map[i] = '-';
                    }
                }
                updateObserver("Cleared towers from map");
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



