# Joly - the game ispired by Pacman
This project is mostly about graph algorithms and data structures. Joly contains three different levels of difficulty which are using three algorithms to determinate paths for the wraiths (entities that chase a player). Joly was made for my own educational purposes. I wanted to practise my programing skills, learn how to use SDL2 library and gain some knowledge about algorithms and data structures. This game is my first big project and the first one I published on github. While I was writing this code I wasn't thinking about making it public and because of that, the script is written in polish.

## Table of contents
* [Technologies](#tech)
* [Algorithms](#alg)
* [Game setup](#gs)
* [Project setup](#ps)
* [Source](#src)
* [Inspiration](#ins)
* [License](#lic)


<a name="tech"/>
	
## Technologies
* C/C++14
* SDL2-2.0.20
* SDL2_image-2.0.5
* Visual Studio Community 2019 - 16.11.13

![gra](https://user-images.githubusercontent.com/104023013/171622972-bf84c578-ea1a-4a14-afe9-aba1589c238f.jpg)

<a name="alg"/>

## Algorithms
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Joly is a the game where a player collects keys while being chased by ghosts. Those wraits don't move randomly. They use graph algorithms to determinate path between them and the player. The game contains three different levels of difficulty.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The first level is an easy mode. In this mode, path for every ghost is created with the Roy-Warshall algorithm. Input matrix contains information about which vertices are connected (are next to each other). For example, if vertice ***4*** is connected with vertice ***12*** then ***martix[4][12]*** is filled with ***12*** and ***marix[12][4]*** stores value of ***4***. In other words, each record represents one vertice ***x*** and each cell on index ***i*** is filled with value ***i*** whether vertice ***x*** and vertice ***i*** are linked. If they're not connected or column index and row index are equal (the cell which tells us about connection of vertex ***x*** with itself), then this field is assigned with numbger ***1000***.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Roy-Warshall algorithm is based on relation of transitivity. It iterates over two-dimensional array looking for vertices that are linked with the path (while the algorithm is running, cells are being filled with values which indicate that path between vertex ***x*** and vertex ***i***. A similar concept like the one mentioned before, but array also gives information about current found paths). When the algorithm finds a cell that has value different than ***1000***, then it asks if there'is an oportunity to create a path to another vertice and creates it whether the answer is "yes". All in all, an idea behind the algorithm is pretty simple: "I can go from ***j*** to ***i*** and I can go from ***j*** to ***k***, so I know the path between ***i*** and ***k***".
```
void initMatrixRW(int MatrixRW[144][144])
{
for(int i=0;i<144;i++)
	for(int j=0;j<144;j++)
		//connection found
		if (MatrixRW[j][i] != 1000)
		{
			for (int k = 0; k < 144; k++)
			{	//looking to create new paths
				if (MatrixRW[j][k] == 1000 && MatrixRW[i][k]!=1000)
					MatrixRW[j][k] = MatrixRW[j][i];
			}

		}
}
```
The Roy-Warshall's algorithm gives inforation about how to get to the player. However, it doesn't provide the most optimal track.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The second level is medium difficulty. In this scenario game uses Floyd-Warshall algorithm for pathfinding. Let's talk about matrices. In the first matrix data represents edges between vertices. A single cell in row ***x**** and column ***y*** contains length of the edge between vertice ***x*** and vertice ***y***. Cells with same index of column and row contain ***0*** and if there is no edge between vertex ***x*** and vertex ***y***, then value is ***1000***. Second matrix (***MatrixR***) is filled with ***1000*** on an input. This algorithm is pretty similar to the previous one, but this time it asks whether the currently found, shortes path between ***j*** and ***i*** is longer than the path from ***j*** to ***i*** through ***k*** vertex. If it is, then ***MatrixF[j][i]*** is assigned with sum of ***MatrixF[j][k]*** and ***MatrixF[k][i]***. ***MatrixR[j][i]*** is filled with value of ***k***. As the result of algorithm, cell [***j***][***i***] in ***MatrixR*** is filled with number of vertex that we should go through for the shortest path between vertices ***j*** and ***i***.
```
void initMatrixR(int MatrixF[144][144],int MatrixR[144][144])
{
	for (int k = 0; k < 144; k++)
	{
		for (int j = 0; j < 144; j++)
		{
			for (int i = 0; i < 144; i++)
			{	//Is the current shortest path longer than path through k?
				if(MatrixF[j][k]+MatrixF[k][i]<MatrixF[j][i])
				{
					MatrixF[j][i] = MatrixF[j][k] + MatrixF[k][i];
					MatrixR[j][i] = k;
				}
			}	
		}
	}
}
```
This time chasers are given the most optimal path that allows them to catch the player. Reading path is done by the simple recursive function:
```
void path(int i, int j, int MatrixR[144][144])
{
	int k = MatrixR[i][j];
	if (k != 1000)
	{
		path(i, k, MatrixR);
		std::cout << " " << k;
		path(k, j, MatrixR);
	}
}
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The last algorithm (which is called Dijkstra's algorithm) differs from the previous two. Firstly, it calculates paths for only one vertex (***source***). Secondly, algorithm operates on graph represented as vertices dictionary. In this data structure, each list in record number ***i*** contains indexes of vertexes connected with vertice ***i***. It also uses a priority queue in order to make algorithm run with computational complexity of O(***E*** log ***V***) instead of O(***V***<sup>2</sup>), where ***E*** stands for number of edges and ***V*** is number of vertices. The algorithm implementation also uses stack to represent how many vertices haven't beem vistited yet. The last data structure is a table of current best estimates. Each element of this table tells what is the length of the current shortest path between ***source vertex*** and ***mVertex***. It also has information about pre-last vertex of this path (***mVertex*** is last vertice in the path so the pre-last is the one that is located before ***mVertex***). So, the contains structures like this:
```
struct{
int previous;
int length;
int mVertex};
```
Implementation of this algorithm is quie complex, so I'm going to describe idea behind it. The algorithm stars from a source vertex and adds to the priority queue edges that are connected with it and haven't been added before. Then, it takes an edge with the lowest cost (the shortest one) and check whether a sum of ***tableOfCurrentBestEstimates[firstVertexOfEdge].length*** and ***EdgeLength*** is lower than ***tableOfCurrentBestEstimates[secondVertexOfEdge].length***. If condition returned "true" it updates ***tableOfCurrentBestEstimates[secondVertexOfEdge].length*** with ***EdgeLength*** and assign the ***previous*** with ***firstVertexOfEdge*** and ***mVertex*** with ***secondVertexOfEdge***. The algorithm also adds edges connected with ***secondVertexOfEdge*** (just like before). IF this condition hasn't been met, then the next edge from the queue is handled. These operations repeat untill all vertices are visited. Function that reads path might look like this:
```
void pathD(edge TOCBE[], int startVertex, int endVertex)
{
	//TOCBE - table of the current best estimates 
	if (TOCBE[endVertex].mVertex == startVertex) { return; }
	else { pathD(TOCBE, startVertex, TOCBE[endVertex].previous); }
	cout << TOCBE[endVertex].mVertex << " ";
}
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The third level has one more feature that makes it harder than medium-difficulty. In both scenarios ghosts use the shortest paths to catch the player, but only in hard mode second ghost cares about the locationof the first ghost. Paths for ghost number one are calculated normaly, but paths for second wrait are generated on modified vertices dictionary. Before the Dijkstra's Algorithm starts edges that are "blocked" by first ghost are being erased from dictionary. This change makes ghosts cover more corridors.

![desc2 — kopia](https://user-images.githubusercontent.com/104023013/171666697-edb50b70-fd50-4287-8c0d-b48caeaddc5a.jpg)![desc — kopia](https://user-images.githubusercontent.com/104023013/171666711-df996825-4787-4e3a-a5e5-4a4687607d6c.jpg)<br>
*Area marked with red color is not available for second ghost*

<a name="gs"/>

## Game setup
1.Download the project in .zip format<br>
2.Extract the zip file<br>
3.Go to the folder extracted from Joly-master.zip<br>
5.Extract Release.zip<br>
6.Go to the folder extracted from Release.zip<br>
7.Run Joly.exe<br>

**Release verison has been compiled on Windows OS, so game should be run on it. It may take few attempts to run executable file (even 20), but it should start at some point.** If the program has started succesfully you will see this menu:

![menu](https://user-images.githubusercontent.com/104023013/171625290-c77d4e00-706d-4cb0-a302-3117c0911826.jpg)

First button is for easy mode, second one - medium mode and third one - difficult. The fourth button is exit.
**Speed of entites can be changed by modifying value in speed.txt.**

<a name="ps"/>

## Project setup
In order to work on this project you'll need Visual Studio Community 2019 - 16.11.13 or newer (it also works on VSC 2022) and git installed. From your command line:
```
//Chose the destination folder
cd [path to the folder]

//initizlize git
git init

//clone repository
git clone https://github.com/MichaelMuzan/Joly
```
Run "Joly_Soltion.sln" file.

<a name="src"/>

## Sources 
This application is using SDL2-2.0.20 and SDL2_image-2.0.5 libraries, which are pulbished under [gzip licence](https://www.libsdl.org/license.php). Algorithms and data structures implementation is based on the book "Algorytmy, struktury danych i techniki programowania" by Piotr Wróblewski. The author of the game map structure is Igor Poreda.It contains zlib library entirely written by Jean-loup Gailly and Mark Adler. This software also uses:
* IJG code copyright (C) 1991-2016, Thomas G. Lane, Guido Vollbeding
* libwebp-7.dll Copyright (c) 2010, Google Inc. All rights reserved

<a name="ins"/>

## Inspirations
The idea of creating this project came from Carl Birch's channel named "Let's make games" (https://www.youtube.com/c/CarlBirch). As the title says, rules and idea of the game are ispired on "Pac-Man" created by Toru Iwatani.

<a name="lic"/>

## License
Licensed under the [MIT License](https://github.com/MichaelMuzan/Joly/blob/master/LICENSE.txt)
