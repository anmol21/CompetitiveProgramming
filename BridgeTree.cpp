//Bridge Edges Bridge Tree DFS BRIDGE TREE BFS LCA

#include <bits/stdc++.h>

#define icin(x) scanf("%d",&x)
#define VVI vector< vector<int> >
#define pb push_back
#define mp make_pair
#define PI pair<int,int>

#define MAXN 1000000
#define MAXM 1000000
#define MAXL 22

using namespace std;


typedef vector<int> VI;

VI gr[MAXN],tree[MAXN];
int U[MAXM],V[MAXM],trev[MAXN];
int is_bridge[MAXM]={0}; // Selecting the subset of bridge edges from edges set.
int tree_comp=1;
int n,m;
queue<int> Q[MAXN];
int comp[MAXN];
int L[MAXN],P[MAXL][MAXN],strt[MAXN],trnd[MAXN];


VI visited;


int sec=0;


int adj_ver(int num,int x)
{
	return U[num]== x? V[num] : U[num];
}

int DFS1(int num,int edge=0) // It is crucial to consider edge.
{
	
	
	visited[num]=sec;
	trev[num]=sec;
	sec++;

	for(int i=0;i<gr[num].size();i++)
	{
		int e = gr[num][i];
		

		int v = adj_ver(e,num);
		//cout << num << " " << v << " " <<  trndl;
		if(!visited[v])
			trev[num] = min(trev[num],DFS1(v,e));
		else if(e!=edge) 
			trev[num]= min(trev[num],visited[v]);
	}
	
	if(trev[num]==visited[num] && edge!=0)
	{
		is_bridge[edge]=1;
	}

	return trev[num];

}


void DFS2(int v)
{
	 int currcmp = tree_comp;
    Q[currcmp].push(v);
    visited[v]=1;
    while(!Q[currcmp].empty())
    {
        int u = Q[currcmp].front();
        comp[u]=currcmp;
        Q[currcmp].pop();
        for(int i=0;i<(int)gr[u].size();i++)
        {
            int e = gr[u][i];
            int w = adj_ver(e,u);
            if(visited[w])continue;
            if(is_bridge[e])
            {
                tree_comp++;
                tree[tree_comp].push_back(currcmp);
                tree[currcmp].push_back(tree_comp);
                DFS2(w);
            }
            else
            {
                Q[currcmp].push(w);
                visited[w]=1;
            }
        }
    }

	//cout << num << " " << "DFS2" <<  trndl;
	
/*	int cur=tree_comp;

	Q[cur].push(num);
	visited[num]=1;

	while(!Q[cur].empty())
	{
		int x = Q[cur].front();
		Q[cur].pop();
	//	cout << x  << "Que" << trndl;
		comp[x]=cur;
		for(int i=0;i<gr[x].size();i++)
		{
			int e = gr[x][i];
			int v = adj_ver(e,x);

			if(visited[v])continue;

			if(is_bridge[e])
			{
				tree_comp++;
				tree[cur].pb(tree_comp);
				tree[tree_comp].pb(cur);
				DFS2(v);
				
			}
			else
			{
				//ot << "out" << trndl;
				visited[v]=1;
				Q[cur].push(v);
			}
		}
	}
*/
	
}



void find_bridges()
{
	sec=1;
	visited.assign(n+1,0);
	DFS1(1);
}

void build_bridgetree()
{
	visited.assign(n+1,0);
	tree_comp=1;
	DFS2(1);
}


void BFS(int a,int num)
{
	queue<int> Q;
	Q.push(a);
	visited[a]=1;
	comp[a]=num;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();

		for(int i=0;i<gr[x].size();i++)
		{
			int e = gr[x][i];
			int w = adj_ver(e,x);
			
			if(is_bridge[e]==1)
				continue;
			else if(visited[w]==0)
			{
				visited[w]=1;
				comp[w]=num;
				Q.push(w);
			}
		}
	}
}

void build_bridgetree2()
{
	visited.assign(n+1,0);
	tree_comp =0;
	for(int i=1;i<=n;i++)
	{
		if(!visited[i])
		{
			tree_comp++;
			BFS(i,tree_comp);
		}
	}
	int count =0;
	for(int i=1;i<=m;i++)
	{

		if(is_bridge[i]==1)
		{
			count++;
			int u = U[i] , v = V[i];
			tree[comp[u]].pb(comp[v]);
			tree[comp[v]].pb(comp[u]);
		}
		else if(comp[U[i]]!=comp[V[i]])
		{
			cout << U[i] << " " << V[i] << " " << comp[U[i]] << " " << comp[V[i]] << endl;
			if(find(gr[U[i]].begin(),gr[U[i]].end(),i)==gr[U[i]].end())
			cout << "PROBLEM" << endl;
			
		}
	}

	/*if(tree_comp!=count+1)
	{
		cout << tree_comp << " " << count << endl;
		assert(tree_comp==count+1);
	}*/

}

void DFS3(int num,int par=-1)
{

	
	visited[num]=1;
	L[num] = ((par==-1)? 1 : (L[par] +1));

	sec++;
	strt[num]  = sec;

	if(par!=-1)
	P[0][num] = par;
	else P[0][num]=num;

	for(int i=1;i<MAXL;i++)
	{
		int x = P[i-1][num];
		if(x<=0)break;

		P[i][num] = P[i-1][x];

	}

	for(int i=0;i<tree[num].size();i++)
	{
		int x = tree[num][i];
		//cout << "X" << x <<trndl;
		if(visited[x])continue;
		else DFS3(x,num);
	}

	trnd[num] = ++sec;

}

bool is_ancestor(int u,int a)
{
	if(u==a)
		return true;
	if(strt[u] > strt[a] && trnd[u] < trnd[a] )
		return true;
	
	return false;
}

int lca(int p,int q)
{

		int loga, i;
    if (L[p] < L[q]) swap(p,q);
    for (loga = 1; (1 << loga) <= L[p]; loga++);loga--;
    for (i = loga; i >= 0; i--)
        if (L[p] - (1 << i) >= L[q]) p = P[i][p];
    if (p == q) return p;
    for (i = loga; i >= 0; i--)
        if (P[i][p] != -1 && P[i][p] != P[i][q]) p = P[i][p], q = P[i][q];
    return P[0][p];
}

int dist(int u, int v, int lca)
{
	if(u==v)
		return 0;
    return L[u]+L[v]-2*L[lca];
}

pair<int,int> common_path(int c,int v,int a,int u)  // c->v and a->u
{
	if(!is_ancestor(a,v))
		return mp(0,0);

	//cout << " " <<  c << "   " << v << " " << a  << " " << u << trndl;
  	int y = lca(a,c);

	if(L[v]>L[u])
	{
		if(is_ancestor(y,v))
			return mp(y,v);
	}
	else
	{
		//cout << "a" << trndl;
	//	cout << u << " " << y;
		if(is_ancestor(y,u))
			return mp(y,u);
	}

	return mp(0,0);

}
int ans(int a,int b,int c,int d)
{
	int u = lca(a,b);
	int v = lca(c,d);
	//cout  <<  c << " " << d << " " << v << trndl;
//	cout <<  a  << " " << u << " " << b  << trndl;
	int ans = dist(c,d,v);
//	cout << ans << trndl;
	pair<int,int> p;
//	cout << v << "VV" << trndl;
	p = common_path(c,v,a,u);
	ans -= dist(p.first,p.second,lca(p.first,p.second));
	p = common_path(c,v,b,u);
	ans -= dist(p.first,p.second,lca(p.first,p.second));
	p = common_path(d,v,a,u);
	ans -= dist(p.first,p.second,lca(p.first,p.second));
	p = common_path(d,v,b,u);
	ans -= dist(p.first,p.second,lca(p.first,p.second));
		//assert(ans>=0);
	return ans;

}

int main()
{		
	int q;
	
	//freopen("input.txt","r",stdin);//freopen("output.txt","w",stdout);
    //freopen("log.txt", "w", stderr);
	//cout << "HELLO";
	icin(n);icin(m);
	icin(q);

	visited.assign(n+1,0);


	for(int i=1;i<=m;i++)
	{
		icin(U[i]);icin(V[i]);				

		gr[U[i]].pb(i);
		gr[V[i]].pb(i);
	}



	

	find_bridges();
	

	visited.assign(n+1,0);
	build_bridgetree2();

	

	//cout << tree_comp  << trndl;
	//cout << "HELLO" << trndl;
	//cout << "HELLO" << trndl;
	visited.assign(n+1,0);

	sec=0;
	DFS3(1); // To calculate L (Level) and P(parent) array for LCP DP < O(nlogn), O(n) >
	// Note that is being done on the bridge Tree of the Graph
	
	//for(int i=1;i<=n;i++)
	//	cout << comp[i] << " ";
		//cout << "HELLO" << trndl;
    while(q--)
    {
    	int a,b,c,d;
    	icin(a);icin(b);icin(c);icin(d);
      	printf("%d\n",ans(comp[a],comp[b],comp[c],comp[d])) ;

    }





	return 0;
}




