//Finds All Bridge Edges in Undirected Graph

#include <bits/stdc++.h>

#define icin(x) scanf("%d",&x)
#define VVI vector< vector<int> >
#define pb push_back
#define mp make_pair



using namespace std;

VVI gr;

vector< pair<int,int> > edges;


vector<int> visited,parent,prev;

int n;


int sec=0;

int DFS1(int num)
{
	visited[num] = sec;
	prev[num] = num ;
	sec++;
	
	for(int i=0;i<gr[num].size();i++)
	{
		int x = gr[num][i];
		if(x == parent[num])
		continue;
		else if(visited[x]==0)
		{
			parent[x] = num;
			int can = DFS1(x);
			
			if(prev[x]> visited[num])
			{
				edges.pb(mp(num,x));
			}
			prev[num] = min(can,prev[num]);
		}	
		else 
		{
			if(visited[x]<prev[num])
				prev[num] = visited[x];
		}

	}

	return prev[num];

}


void find_bridges()
{
	sec=1;
	visited.assign(n+1,0);
	parent.assign(n+1,0);
	prev.assign(n+1,0);
	DFS1(1);

}




int main()
{
	int m,q;
	
	icin(n);icin(m);
	icin(q);

	gr.resize(n+1);

	visited.assign(n+1,0);

	for(int i=0;i<m;i++)
	{
		int a,b;
		icin(a);
		icin(b);
		gr[a].pb(b);
		gr[b].pb(a);
	}

	find_bridges();
	cout << "BRIDGES are :" << endl;
	for(int i=0;i<edges.size();i++)
		cout << edges[i].first << " " << edges[i].second << endl;








	return 0;
}