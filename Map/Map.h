
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct coord{
            int x;
            int y;
};

class Map{


    Map(int x, int y);

    void printMap();



    //getter methods
    vector<coord> getPath();

     vector<char> getMap();



    //methods to make the map
    void initiateMaking();

    void setEntrance(int x, int y);

    void laypath(char dir);

    void setExit();



};








/*

MAP CLASS
attrivute: editting
attributes: length & width

2d array all cells - can i put a tower here? pointer to tower cell if there is one or some kinda indication its a path
ep--k----
-p-x-----
-p--h----
-pe------

1d array this is the path
1,1 - 1,2 - 2,2 - etc.

function backspace if we have time

function displaymap

constructor function

function userInput:


function add path tile(direction)
    this must include a validation step to check they don't double back directly where they came from
    would they have to click enter after each tile ?
    

    
function add entrance(x,y)

function add exit(x,y)


function validatePath
    check that path touches exit
    if so, exit the thing
    also check that there is scenery remaining: does 2d array contain -



1d array of critter objects
TO BE DISCUSSED ON MONDAY
should have location attribute - this can be a 
will consume path array to move

function that takes (location x, y of tower, range (square or circle ??))
    return critters in range;




PathCell CLASS:
Awareness of before and next


MAINMENU class

-build a thing
    -choose sizes x width, y height
    -construct map with input sizes
-exit






 */









int main( )
{

}

//Uses cmath:
int roundDub(double number)
{

}
