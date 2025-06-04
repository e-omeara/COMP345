

# COMP345: Tower Defense Game

## Overview

Welcome to the COMP345 Tower Defense Game repository! This project is developed for the COMP345 course at Concordia University, focusing on advanced program design using C++. The game implements a tower defense strategy where players place towers to defend against waves of critters. It also integrates key design patterns, such as observer, factory, and decorator.

## Team Members

* **Elizabeth O'Meara** 
* **Vi Kyne**
* **Sang Hyun Hong**
* **MinhThien Tran**

## Project Structure

The project is organized into several modules, each responsible for different aspects of the game:

* **GameEngine**: Manages the game loop, user input, and overall game flow, as well as the main graphics.
* **Map**: Handles the game map, including the layout of paths and placement of towers. Also allows the use to create a new map.
* **MapObjects**: Holds the critters and towers that go in the map. See below
* **Player**: Manages player information, including health and score.
* **Critters**: Defines the enemies that move along the paths, with varying speeds and health.
* **Towers**: Defines the defensive tpwers that attack critters, each with unique abilities.

## Features

* **Dynamic Map Generation**: Create or load maps with different layouts and difficulty levels.
* **Tower Placement and Upgrade**: Strategically place towers to maximize defense against incoming critters, and upgrade them for new abilities.
* **Wave System**: Face multiple waves of critters with increasing difficulty.
* **Resource Management**: Earn resources by defeating critters to purchase and upgrade towers.
* **User Interface**: Graphical mouse-based interface for interaction and control.

## Getting Started

### Prerequisites

Ensure you have the following installed:

* **C++ Compiler**: GCC or MSVC
* **CMake**: For building the project
* **SFML**: For graphical rendering 

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/e-omeara/COMP345.git
   cd COMP345
   ```

2. Build the project using CMake:

   See the howtorun.md for command-line instructions on Windows and Mac

3. Run the game:


### Running the Game

Upon starting, you'll be prompted to:

* Select a map or create a new one and save it for future use.
* Place towers at strategic locations.
* Start the wave of critters and defend your base.
