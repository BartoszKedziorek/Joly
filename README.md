# Joly - The game ispired by pacman
This project is mostly about graph algorithms and data structures. Joly contains three different levels of difficulty which are using three algorithms to determinate paths for the wraiths (Entities that chase player). Joly was made for educational purpose. I wanted to practise my programing skills, learn how to use SDL2 library and also get some knowledge about algorithms and data structures.

## Technologies
* C/C++14
* SDL2-2.0.20
* SDL2_image-2.0.5
* Visual Studio Community 2019 - 16.11.13

## Algorithms
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Joly is a game where player is collecting keys while being chased by ghosts. Those wraits doesn't move randomly. They use graph algorithms to determinate path between them and player. Game contains three different levels of difficulty.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The first one is easy mode. In easy mode path for every ghost is created with Roy-Warshall algorithm. Input matrix contains information about which vertices are connected (are next to each other). For example, if vertice **4** is connected with vertice **12** then martix[4][12] is filled with **12** and marix[12][4] store value of **4**. In other words, each record represents one vertice **x** and each cell on index **i** is filled with value **i** whether vertice **x** and vertice **i** are linked. If they're not or column index and row index are equal (cell which tells us about connection of vertex **x** with itself), then this field is assigned with numbger of **1000**.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Roy-Warshall's algorithm is based on relation of transitivity. It iterates over two-dimensional array looking for vertices that are linked with path (By the time the algorithm is running, cells are beeing filled with values which indicate that path between vertex **x** and vertex **i** exists. Similar concept like before, but array also gives information about current found paths). When it finds cell that indicates this situation (has value different than 1000), then it asks if there'is oportunity to create path to another vertice and creates it whether answer is "yes". All in all, idea behind algorithm is pretty simple: "I can go from **j** to **i** and **i** can also go from **j** to **k**, so **i** know the path between **i** and **k**".
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
The Roy-Warshall's algorithm gives inforation about how to get to player. However, it doesn't provide most optimal track.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Next game mode is medium difficulty. In this scenario game uses Floyd-Warshall's algorithm for pathfinding. Let's talk about matrices. Data in the first matrix (MatrixF) represents edges between vertices. This time single cell in row **x** and column **y** contains length of edge between vertice **x** and vertice **y**. Cells with same index of column and row contain 0 and if there is no edge between vertex **x** and vertex **y**, then value is 1000. Second matrix (MatrixR) is filled with 1000 on input. Algorithm is pretty similar to previous one, but this time it asks whether current found shortes path between **j** and **i** is longer than the path from **j** to **i** through **k** vertex. If it is, then MatrixF[**j**][**i**] is assigned with sum of MatrixF[**j**][**k**] and MatrixF[**k**][**i**]. MatrixR[**j**][**i**] is filled with value of **k**. As the result of algorithm, cell [**j**][**i**] in MatrixR is filled with number of vertex that we should go through for shortest path between vertices **j** and **i**.
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
This time chasers are given with the most optimal path that allows them to catch player. Reading path is done by simple recursive function:
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
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The last algorithm differs from previous two. Firstly, it calculates paths for only one vertex (source).Secondly, algorithm operates on graph represented as vertices dictionary. In this data structure each list in record number **i** contains indexes of vertex conected with vertice **i**. It also uses priority queue in order to make algorithm run with computional complexity of O(**E** log **V**) instead of O(**V**<sup>2</sup>), where **E** stands for number of edges and **V** is number of vertices. Algorithm implementation also uses stack to represent how many vertices haven't beem vistited yet. Last but not least, table of current best estimates. Each element of this table tells what is length of the current shortest path between source vertex and **mVertex**. It also have information about pre-last vertex of this path (**mVertex** is last vertice in the path so the pre-last is the one that is located before **mVertex**). So the table is contain structures like this:
```
struct{
int previous;
int length;
int mVertex};
```
Imlementations of this algorithm is quie complexed, so I'm going to just describe idea behind it. Algorihm stars from source vertex and adds to priority queue edges that are connected with it and haven't been added before. Then it takes edge with the lowest cost (the shortest one) and check whether sum of tableOfCurrentBestEstimates[**firstVertexOfEdge**].length and **EdgeLength** is lower than tableOfCurrentBestEstimates[**secondVertexOfEdge**]. If this conditions returns "true" it updates tableOfCurrentBestEstimates[**secondVertexOfEdge**] with **EdgeLength** and assign **previous** with **firstVertexOfEdge** and mVertex with **secondVertexOfEdge**


/*
Now when we have all data structures that we need, let's talk about how  the Dijkstra's algorithm works. The first step is to iterate over table of current best estimates filling it wth proper data:
```
for (int i=0; i<144; i++)
{
tableOfCurrentBestEstimates[i].previous = -1;
tableOfCurrentBestEstimates[i].length = 1000;
tableOfCurrentBestEstimates[i].mVertex = i;
}
```
Algorithm also need to assign tableOfCurrentBestEstimates[source].length with 0 and put on stack **V** elements (type doesn't matter at this point). Next thing to do is make a loop which will run until stack is empty. In this loop first we need to put all edges that are connected with currentVertex (in the first iteration it should be source vertex) into priority queue. Then algorithm updates table of current best estimates basing on edges in queue and pop one element from the stack. This is the point where next iteration begins. When the loop end, algorithm also finish its action and the table of best estimates (previously: table of current best estimates) is ready to read paths from it. Function that reads path might look like this:*/
```
void pathD(edge paths[], int startVertex, int endVertex)
{
	if (paths[endVertex].mVertex == startVertex) { return; }
	else { pathD(paths, startVertex, paths[endVertex].previous); }
	cout << paths[endVertex].mVertex << " ";
}
```
## Sources 
This application is using SDL2-2.0.20 and SDL2_image-2.0.5 libraries, which are pulbished under gzip licence. Algorithms and data structures' implementation are based on the book "Algorytmy, struktury danych i techniki programowania" by Piotr Wróblewski. The idea of creating this project came from Carl Birch's channel named "Let's make games." (https://www.youtube.com/c/CarlBirch). As the title says, rules and idea of the game are ispired on "Pac-Man" created by Toru Iwatani. The Game map structure Author is Igor Poreda.
