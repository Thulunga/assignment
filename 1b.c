/*

1. Write programs that compute the minimum spanning tree of a connected undirected graph
using the following algorithms:
a. Kruskal’s algorithm
b. Prim’s algorithm
Input format:
● The first line of the input contains a positive integer n, the number of vertices in the graph,
in the range 1 to 1000.
● The subsequent n lines contain the labels of the nodes adjacent to the respective nodes,
sorted in ascending order from left to right.
● The subsequent n lines contain the weights of the edges corresponding to the adjacency list.
The edge weights are real numbers in the range [-10000, 10000]. Further, no two edges have
the same weight.
Output format:
● Print the sum of the edge weights of the minimum spanning tree as the output.
Sample Input ( Same for 1a and 1b )
12
8 9
2 3 4
1 3 5 6
1 2 4
1 3 5 7 8 9
2 4 6
2 5 7 10 11
4 6 80 4 7 9
0 4 8
6 11
6 10
27 41
10 11 17
10 7 33 44
11 7 26
17 26 5 8 15 16
33 5 21
44 21 31 18 29
8 31 20
27 15 20 13
41 16 13
18 23
29 23
Sample Output
164
Note: Submit Kruskal’s algorithm(1a) and Prim’s algorithm(1b) as separate programs.

*/
#include<stdio.h>
#include<stdlib.h>
#define infinity 99999
#define MAX 1000
FILE *fp;
FILE *fs;
FILE *fs1;

int G[MAX][MAX],spanning[MAX][MAX],n;

int prims();

int main()
{
  int i,j,total_cost,c,x,y;
  fp = fopen("output.txt","w");
  fs = fopen("input1.txt","r");
  fs1 = fopen("input1.txt","r");


	fscanf(fs,"%d",&n);
  fscanf(fs1,"%d",&n);
  int arr[n];
  for(i=0;i<n;i++)
  {
    c = 0;
    while(1)
    {
      fscanf(fs1,"%d",&j);
      c++;
      if(getc(fs1)=='\n')
        break;
    }
    arr[i] = c;
  }
  //======================================
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      G[i][j] = -10005;
  //======================================
  for(i=0;i<n;i++)
  {
    for(j=0;j<arr[i];j++)
    {
      fscanf(fs,"%d",&x);
      fscanf(fs1,"%d",&y);
      G[i][x] = y;
    }
  }

	total_cost=prims();

	fprintf(fp,"%d",total_cost);
  fclose(fp);
  fclose(fs);
  fclose(fs1);
	return 0;
}

int prims()
{
	int cost[MAX][MAX];
	int u,v,min_distance,distance[MAX],from[MAX];
	int visited[MAX],no_of_edges,i,min_cost,j;

	//create cost[][] matrix,spanning[][]
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(G[i][j] < -10000||G[i][j] >  10000)
				cost[i][j]=infinity;
			else
				cost[i][j]=G[i][j];
				spanning[i][j]=0;
		}

	//initialise visited[],distance[] and from[]
	distance[0]=0;
	visited[0]=1;

	for(i=1;i<n;i++)
	{
		distance[i]=cost[0][i];
		from[i]=0;
		visited[i]=0;
	}

	min_cost=0;		//cost of spanning tree
	no_of_edges=n-1;		//no. of edges to be added

	while(no_of_edges>0)
	{
		//find the vertex at minimum distance from the tree
		min_distance=infinity;
		for(i=1;i<n;i++)
			if(visited[i]==0&&distance[i]<min_distance)
			{
				v=i;
				min_distance=distance[i];
			}

		u=from[v];

		//insert the edge in spanning tree
		spanning[u][v]=distance[v];
		spanning[v][u]=distance[v];
		no_of_edges--;
		visited[v]=1;

		//updated the distance[] array
		for(i=1;i<n;i++)
			if(visited[i]==0&&cost[i][v]<distance[i])
			{
				distance[i]=cost[i][v];
				from[i]=v;
			}

		min_cost=min_cost+cost[u][v];
	}

	return(min_cost);
}
