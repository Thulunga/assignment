/*
inputs are read from file and output are also printed in the file
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
*/
#include<stdio.h>
#include<string.h>
#define MAX 1000
FILE *fp;
FILE *fs;
FILE *fs1;

typedef struct edge
{
	int u,v,w;
}edge;

typedef struct edgelist
{
	edge data[MAX];
	int n;
}edgelist;

edgelist elist;

int G[MAX][MAX],n;
edgelist spanlist;

void kruskal();
int find(int belongs[],int vertexno);
void union1(int belongs[],int c1,int c2);
void sort();
void print();

int main()
{
	int i,j,total_cost,c,x,y;
  fp = fopen("output.txt","w");
  fs = fopen("input1.txt","r");
  fs1 = fopen("input1.txt","r");

	//printf("\nEnter number of vertices:");

	fscanf(fs,"%d",&n);
  fscanf(fs1,"%d",&n);
  //printf("%d",n);
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
    //printf("%d ",c);
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
/*
	for(i=0;i<n;i++)
  {
		for(j=0;j<n;j++)
			printf("%d ",G[i][j]);
    printf("\n");
  }*/

	kruskal();
  print();
  fclose(fp);
  fclose(fs);
  fclose(fs1);
  return 0;
}

void kruskal()
{
	int belongs[MAX],i,j,cno1,cno2;
	elist.n=0;

	for(i=1;i<n;i++)
		for(j=0;j<i;j++)
		{
			if(G[i][j] > -10001)
			{
				elist.data[elist.n].u=i;
				elist.data[elist.n].v=j;
				elist.data[elist.n].w=G[i][j];
				elist.n++;
			}
		}

	sort();

	for(i=0;i<n;i++)
		belongs[i]=i;

	spanlist.n=0;

	for(i=0;i<elist.n;i++)
	{
		cno1=find(belongs,elist.data[i].u);
		cno2=find(belongs,elist.data[i].v);

		if(cno1!=cno2)
		{
			spanlist.data[spanlist.n]=elist.data[i];
			spanlist.n=spanlist.n+1;
			union1(belongs,cno1,cno2);
		}
	}
}

int find(int belongs[],int vertexno)
{
	return(belongs[vertexno]);
}

void union1(int belongs[],int c1,int c2)
{
	int i;

	for(i=0;i<n;i++)
		if(belongs[i]==c2)
			belongs[i]=c1;
}

void sort()
{
	int i,j;
	edge temp;

	for(i=1;i<elist.n;i++)
		for(j=0;j<elist.n-1;j++)
			if(elist.data[j].w>elist.data[j+1].w)
			{
				temp=elist.data[j];
				elist.data[j]=elist.data[j+1];
				elist.data[j+1]=temp;
			}
}

void print()
{
	int i,cost=0;

	for(i=0;i<spanlist.n;i++)
	{
		//printf("\n%d\t%d\t%d",spanlist.data[i].u,spanlist.data[i].v,spanlist.data[i].w);
		cost=cost+spanlist.data[i].w;
	}
  //printf("\n\nCost of the spanning tree=%d\n",cost);
	fprintf(fp,"%d",cost);
}
