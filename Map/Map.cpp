
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include "Map.h" 
//#include "MapMaker.h" 
using namespace std;

/*
struct coord{
            int x;
            int y;
};
*/



    
    

        Map::Map(int x, int y){ //constructor
            cout << "You've constructed MAP \n";
            width = x;
            height = y;
            isMaking = false;
            prevDir = 'x';

            map.resize(x*y, '-');

            


        }




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



        vector<coord> Map::getPath(){

            return path;
        }

        vector<char> Map::getMap(){

            return map;
        }



        void Map::initiateMaking(){
            isMaking = true;


        }


        void Map::setEntrance(int x, int y){

            if (isMaking == false){
                cout << "you're not making a map!\n";
                return ;
            }

            makeX = x;
            makeY = y;
            map[getPos(x, y)] = 'N';
            printMap();
            return;

        }

        void Map::laypath(char dir){

            if (isMaking == false){
                cout << "you're not making a map!\n";
                return ;
            }

            if(dir == 'u' || dir == 'U'){
                //go up
                if(prevDir == 'd' || prevDir == 'D'){
                    cout << "You just came from there!\n\n";
                    return;
                }
                if(makeY == 0){
                    cout << "You can't go there!\n\n";
                    return;
                }
                makeY--;
                map[getPos(makeX, makeY)] = 'P';
                
            }
            else if(dir == 'd' || dir == 'D'){
                //go up
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
                //go up
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
                //go up
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

            prevDir = dir;
            printMapMaker();
            return;
        }

        void Map::setExit(){
            map[getPos(makeX, makeY)] = 'X';
            cout << "You've finalized the exit!\n";
            printMap();
            return;
        }

  

            void Map::printMapMaker(){

            vector<char> mapMaker = map;
            mapMaker[getPos(makeX,makeY)] = 'X';

            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    cout << mapMaker[i*width + j];
                
                }
                cout << "\n";
            }
            
            cout << "\n";


            return;
            }  

            int Map::getPos(int x, int y){
                return (y)*width + x;
            } 








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



//attributes
//length
//width
//map 2d array of chars
//array of struct path with atributes int x int y
//critter 1d array of Critter objects


//map constructor with size
//


//MAIN FUNCS

//display()
//
//return string object



//HELPER FUNCS





