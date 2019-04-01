/*
3. Write a C program to find negative cycle in a directed graph. A negative cycle is one in which
the overall sum of the weights in the cycle is negative.
Input Format
● First line contains two integers n, m denoting number of vertices and number of edges
present in a directed graph
● Next m lines contains 3 integers x, y, w denoting there is an directed edge from x to y
having a weight w
Output Format
● Print 1 if there is negative cycle otherwise print -1
Note: - The vertices are labeled from 0 to n-1
Sample Input
5 8
0 1 -1
0 2 4
1 2 3
1 3 2
1 4 2
3 2 5
3 1 1
4 3 -3
Sample Output
-1
*/

#include <stdio.h>
#include <stdlib.h>
FILE *fp;
FILE *fs;
#define INFINITY 99999
//struct for the edges of the graph
struct Edge {
  int u;  //start vertex of the edge
  int v;  //end vertex of the edge
  int w;  //weight of the edge (u,v)
};

//Graph - it consists of edges
struct Graph {
  int V;  //total number of vertices in the graph
  int E;  //total number of edges in the graph
  struct Edge *edge;  //array of edges
};

int bellmanford(struct Graph *g, int source);
//void display(int arr[], int size);

int main(void)
{
	int temp;
	fs=fopen("input.txt","r");
	fp=fopen("output.txt","w");
  //create graph
  struct Graph *g = (struct Graph*)malloc(sizeof(struct Graph));
	fscanf(fs,"%d ",&g->V);
	fscanf(fs,"%d ",&g->E);
  //array of edges for graph
  g->edge = (struct Edge*)malloc(g->E * sizeof(struct Edge));

	int x,y,z;
	for(int i = 0; i < g->E;i++)
	{
		fscanf(fs,"%d %d %d",&x,&y,&z);
		g->edge[i].u = x;
		g->edge[i].v = y;
		g->edge[i].w = z;
	}
	for(int i =0; i < g->V;i++)
	{
			temp = bellmanford(g, i);      //i is the source vertex
			if(temp == 1)
			{
				fprintf(fp,"1\n");
				fclose(fp);
				fclose(fs);
				return 0;
			}
	}
	fprintf(fp,"-1\n");
	fclose(fp);
	fclose(fs);
  return 0;
}

int bellmanford(struct Graph *g, int source) {
  //variables
  int i, j, u, v, w;
  //total vertex in the graph g
  int tV = g->V;
  //total edge in the graph g
  int tE = g->E;
  //distance array
  //size equal to the number of vertices of the graph g
  int d[tV];
  //predecessor array
  //size equal to the number of vertices of the graph g
  int p[tV];
  //step 1: fill the distance array and predecessor array
  for (i = 0; i < tV; i++) {
    d[i] = INFINITY;
    p[i] = 0;
  }
  //mark the source vertex
  d[source] = 0;
  //step 2: relax edges |V| - 1 times
  for(i = 1; i <= tV-1; i++) {
    for(j = 0; j < tE; j++) {
      //get the edge data
      u = g->edge[j].u;
      v = g->edge[j].v;
      w = g->edge[j].w;

      if(d[u] != INFINITY && d[v] > d[u] + w) {
        d[v] = d[u] + w;
        p[v] = u;
      }
    }
  }
  //step 3: detect negative cycle
  //if value changes then we have a negative cycle in the graph
  //and we cannot find the shortest distances
  for(i = 0; i < tE; i++)
	{
    u = g->edge[i].u;
    v = g->edge[i].v;
    w = g->edge[i].w;
    if(d[u] != INFINITY && d[v] > d[u] + w)
			return 1;
		else
			return 0;
	}
/*
  //No negative weight cycle found!
  //print the distance and predecessor array
  printf("Distance array: ");
  display(d, tV);
  printf("Predecessor array: ");
  display(p, tV);                                */
}
/*
void display(int arr[], int size) {
  int i;
  for(i = 0; i < size; i ++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
*/
