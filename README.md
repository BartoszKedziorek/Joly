# Joly - The game ispired by pacman
This project is about game using graph algorithms. Joly contains three different levels of difficulty which are using three algorithms to determinate paths for the wraiths (Entities that chase player). Joly was made for educational purpose. I wanted to practise my programing skills, learn how to use SDL2 library and also get some knowledge about Algorithms and data structures.

## Technologies
* C++14
* SDL2-2.0.20
* SDL2_image-2.0.5
* Visual Studio Community 2019 - 16.11.13

## Game mechanics
Joly is the game where player is collecting keys while being chased by ghosts. Those wraits doesn't move randomly. They are using graph algorithms to determinate path to the player. Game contains three different levels of difficulty. The first one is easy mode. In easy mode path for every ghost is determinate by Roy-Warshall algorithm. This algorith gives inforation about how to get to a player. However it doesn't provide the most optimal track. Then comes the second, medium difficulty. In this scenario game is using Floyd-Warshall for pathfinding. This time chasers are given with the shortes path that allows them to catch player. Both algorithms iitialize NxN martices before the game start and have computional complexity O(n^3). The third algorith (one that is used in difficult mode) 
