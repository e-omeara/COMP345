Critters have eight attributes, which are their hp, speed, strength, level, reward (when critter is slain), alive (boolean to check its status), positionIndex (to know its coordinates), and path (a vector path for critter movement). There are getters for all the eight attributes.

There are three additional types of critters currently, named FastCritter, TankCritter and BossCritter. These are all derived classes of the Critter class. The characteristics of FastCritter is its speed being twice as fast, TankCritter is more HP, but slower movement, and BossCritter with High HP and High Strength, but will only spawn once per wave.

The implemented functions are:
takeDamage function, where the hp of the critter will be decreased when damage is taken, 
hasReachedEnd function, which is to check if the critter has reached the end of the path, 
stealCoins function, which is to steal x amount of coins from the player (depending on the critter's strength) should the critter reach the end of the path, 
move function, which is to move the critter along the path, 
generateWave function, which is to generate a wave of critters and one boss per wave, 
and moveCritters function, which is to move all the critters, and implement some of the above functions, to ensure players will gain appropriate rewards if critter is slain, or lose coins if critter is alive and reached the end of the path. 

The purpose of the critter test case was to simulate five turns of a wave, by creating different critter types and by creating and giving a vector path to these critters, which will show the critters' types, attributes and their movement in the x,y coordinates (their position) per turn via output (std::cout).
