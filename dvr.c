#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
struct Link{
int host,dest,wt;
};
struct Network{
int h;
int l;
struct Link* link;
};
int main()
{
	int H,L,s;
	int dist[10];
	printf("enter the total number of Hops\n");
	scanf("%d",&H);
	printf("Enter the total number oof links\n");
	scanf("%d",&L);
	printf("enter the souce node\n");
	scanf("%d",&s);
	struct Network* n=(struct Network*)malloc(sizeof(struct Network));
	n->h=H;
	n->l=L;
	n->link=(struct Link*)malloc(L*sizeof(struct Link));
	for(int i=0;i<L;i++)
	{
		printf("enter the hop,dest,wt of link %d\n",i);
		scanf("%d",&n->link[i].host);
		scanf("%d",&n->link[i].dest);
		scanf("%d",&n->link[i].wt);
	}
	for(int i=0;i<H;i++)
	{
		dist[i]=INT_MAX;
	}dist[s]=0;
	for(int i=1;i<H;i++)
	{
		for(int j=0;j<L;j++)
		{
			int u=n->link[j].host;
			int v=n->link[j].dest;
			int wt=n->link[j].wt;
			if(dist[u]+wt<dist[v])
			{
				dist[v]=dist[u]+wt;
			}
		}
	}
	for(int j=0;j>L;j++)
		{
			int u=n->link[j].host;
			int v=n->link[j].dest;
			int wt=n->link[j].wt;
			if(dist[u]+wt<dist[v])
			{
				printf("nefative edge cycle present\n");
			}
		}
	printf("NODE\tDistance from root node\n");
	for(int i=0;i<H;i++)
	{
		printf("%d\t\t%d\n",i,dist[i]);
	}
}
