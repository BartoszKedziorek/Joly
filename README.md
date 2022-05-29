# Joly - The game ispired by pacman
This project is about game using graph algorithms. Joly contains three different levels of difficulty which are using three algorithms to determinate paths for the wraiths (Entities that chase player). Joly was made for educational purpose. I wanted to practise my programing skills, learn how to use SDL2 library and also get some knowledge about Algorithms and data structures.

## Technologies
* C++14
* SDL2-2.0.20
* SDL2_image-2.0.5
* Visual Studio Community 2019 - 16.11.13

## Game mechanics
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Joly is the game where player is collecting keys while being chased by ghosts. Those wraits doesn't move randomly. They are using graph algorithms to determinate path to the player. Game contains three different levels of difficulty.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The first one is easy mode. In easy mode path for every ghost is determinate by Roy-Warshall algorithm. Input matrix contains informations about which vertices are connected (are next to each other). For example, if vertice 4. is connected with vertice 12. then martix[4][12] will be filled with 12 and marix[12][4] will store value of 4. In other words, each record represents one vertice x and each cell on index i is filled with value i if vertice x and vertice i are linked. If they're not or column index and row index are equal (cell which tells us about connection of vertex with itself) then this field is assigned with numbger of 1000.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The algorithm is based on relation of transitivity. It iterates over our two-dimensional array looking for vertices that are linked with path. When it finds cell that indicates this situation (has value different than 1000), then it asks if there'is an oportunity to create path to another vertice and under this condition the path is created. All in all, idea behind the algorithm is preety simple: "I can go from **j** to **i** and **i** can also go from **j** to **k**, so **i** know the path between **i** and **k**".
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
Roy-Warshall algorithm gives inforation about how to get to a player. However it doesn't provide the most optimal track.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Then comes the second, medium difficulty. In this scenario game is using Floyd-Warshall for pathfinding. Let's talk about matrices. The first matrix indicates edges between vertices. This time single cell in row x and column y contains length of edge between vertice x and vertice y. Cells with the same index of column and row contains 0 and if there is no edge between vertex x and vertex y, the value will be 1000. Second matrix is filled with 1000 on input. 

This time chasers are given with the shortes path that allows them to catch player. 
