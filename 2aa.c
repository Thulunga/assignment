/*
2. Given a directed graph G= (V, E), edge weights w e ≥0, source s ∈ V, find the weight of V, find the weight of
shortest path from s to all other vertex.
Input Format
● First line is the number of nodes (V) in a graph. Vertices are labelled from 0 to V-1.
● Second line is the number of edges (E) in a graph.
● Next E lines each line consist of three space separated integers x y z, where x and y
denote the two nodes between which the directed edge exist and z is the weight of the
edge.
● Next line consists of one integer s, where s denotes the source node.
Output Format
● Print the destination node and weight associated with it. If there is no path print “INF”
Sample Input
4
40 1 1
0 3 4
2 1 2
3 2 5
0
Sample Output
0 0
1 1
2 9
3 4
*/

#include<stdio.h>
#include<stdlib.h>

#define INFINITY 9999
#define MAX 1000
FILE *fp;
FILE *fs;

void dijkstra(int G[MAX][MAX],int n,int startnode);
int main()
{
	int G[MAX][MAX],i,j,n,e,x,y,w,s;
	fp = fopen("output.txt","w");
	fs = fopen("input.txt","r");
	fscanf(fs,"%d",&n);
	fscanf(fs,"%d",&e);
	//======================================
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			G[i][j] = 0;
	//======================================
	for(i=0;i<n;i++)
	{
		fscanf(fs,"%d %d %d",&x,&y,&w);
		G[x][y] = w;
	}
	fscanf(fs,"%d",&s );
	dijkstra(G,n,s);
	fclose(fp);
  fclose(fs);
	return 0;
}

void dijkstra(int G[MAX][MAX],int n,int startnode)
{

	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			if(G[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];
	}
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}

	distance[startnode]=0;
	visited[startnode]=1;
	count=1;

	while(count<n-1)
	{
		mindistance=INFINITY;
		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
			//check if a better path exists through nextnode
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
	for(i=0;i<n;i++)
	{
		if(i==startnode)
			fprintf(fp,"%d 0 \n",i );
		else
		{
			if(distance[i]== INFINITY)
				fprintf(fp,"%d INF \n",i);
			else
				fprintf(fp,"%d %d \n",i, distance[i]);
		}
	}
}
