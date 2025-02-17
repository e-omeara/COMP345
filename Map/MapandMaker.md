The Map class stores the data of the map along which the critters will run
It has two main attributes: the map and the path

The map is a 1D vector of chars initialized to the size of the map
The chars represent the data held in each position
Normal dashes represent scenery
N represents the entrance of the path
X represents the exit of the path
P represents path tiles in between

The path is a 1D vector of "coord" structs, which are made up of x and y positions
As the player adds positions to the map, the map class will add coords to the path
Critters use this path to move from the entrance to the exit

The mapmaking set of functions add path tiles to the map
The entrance and exit can be anywhere in the map
We've chosen to allow "bridges", i.e. the path can overlap itself
We don't allow the path to turn back on itself though

The MapMaker file runs a user input cycle that allows the user to choose and entrance,
add path tiles (by choosing the direction to go), and place an exit