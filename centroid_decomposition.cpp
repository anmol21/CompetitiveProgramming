// Anmol Sood
// Problem Statement : http://codeforces.com/contest/342/problem/E

#include <bits/stdc++.h>

#define icin(x) scanf("%d",&x)
#define VVI  vector< vector<int> >
#define LL long long
#define pb push_back
#define maxn 1000000
#define MAXN 1000000
#define MAXL 20
#define inf (int)(1e9)

using namespace std;


VVI g;

/***************************LCA functions******************************************************/



int sec =0;//time variable.
int L[MAXN+9],P[MAXL][MAXN+9],st[MAXN+9],ft[MAXN+9]; // level , parent dp table , start time, finish time.
vector<int> visited(MAXN+9,0);

void DFS_lca(int num,int par=-1)
{

	//cout << "Here" << " " << num << " " << par <<  endl;
	visited[num]=1;
	L[num] = ((par==-1)? 1 : (L[par] +1));

	sec++;
	st[num]  = sec;

	if(par!=-1)
	P[0][num] = par;
	else P[0][num]=num;

	
	for(int i=1;i<MAXL;i++)
	{
		int x = P[i-1][num];
		if(x<=0)break;

		P[i][num] = P[i-1][x];

	}

	for(auto i:g[num])
	{
		//cout << i << endl;
		int x = i;
		if(visited[x])continue;
		else DFS_lca(x,num);
	}

	ft[num] = ++sec;

}

bool is_ancestor(int u,int a)
{
	if(u==a)
		return true;
	if(st[u] > st[a] && ft[u] < ft[a] )
		return true;
	
	return false;
}

int lca(int p,int q)
{

	int loga, i;
    if (L[p] < L[q]) swap(p,q); // If level of q is greater than p , we swap p with q.
    for (loga = 1; (1 << loga) <= L[p]; loga++);
    loga--;
    for (i = loga; i >= 0; i--)
        if (L[p] - (1 << i) >= L[q]) p = P[i][p]; // We bring p and q to the same level in log(height) time.
    if (p == q) return p;
    for (i = loga; i >= 0; i--)
        if (P[i][p] != -1 && P[i][p] != P[i][q]) p = P[i][p], q = P[i][q];
    return P[0][p];
}

int dist(int u, int v)
{
	int lc=lca(u,v);
	if(u==v)
		return 0;
    return L[u]+L[v]-2*L[lc];
}



/**********************************End of LCA functions*******************/







/****************************Centroid Decomposition Functions**********************************/

int nn=0;

int cnt[maxn+9]; // subtree size count.
int cpar[maxn+9];

void dfsa(int a,int par)
{
	cnt[a]=1;
	nn++;
	for(auto it:g[a])
	{
		if(it !=par)
		{
			dfsa(it,a);
			cnt[a] += cnt[it]; 
		}
	}
}

int find_centroid(int root,int par)
{
	for(auto it:g[root])
	{
		if(it != par)
		{
			if(cnt[it]>nn/2)
				return find_centroid(it,root);
		}
	}
	return root;
}


void decompose(int root,int p)
{
	
	nn=0;
	dfsa(root,root);
	int cen = find_centroid(root,root);
	if(p==-1)p=cen;
	cpar[cen]=p;
	
	for(auto i:g[cen])
	{

	
		for(auto j=g[i].begin();j!=g[i].end();j++)
		{
	
			if(*j==cen)	
			{
				g[i].erase(j);
				break;
			}
		}
		decompose(i,cen);
	}	
	g[cen].clear();

}

/**********************************************************************************/

vector<int> ans(maxn+9,inf);

void update(int node)
{
	int num=node;
	ans[num]=0;
	while(1)
	{
		ans[num] = min(ans[num],ans[node]+dist(num,node));
		
		if(cpar[num]==num)
			break;
		num=cpar[num];
	}
}

int query(int node)
{
	int num=node;
	int cur=inf;
	while(1)
	{
		cur= min(cur,dist(node,num) + ans[num]);
		if(cpar[num]==num)
			break;
		num=cpar[num];
	}
	return cur;
}




int main()
{
	int n;
	icin(n);
	g.resize(n);
	int m;
	icin(m);
	for(int i=0;i<n-1;i++)
	{
		int x,y;
		icin(x);
		icin(y);
		g[x-1].pb(y-1);
		g[y-1].pb(x-1);
	}

	DFS_lca(0);

	decompose(0,-1);
	update(0);
	while(m--)
	{
		int x,y;
		icin(x);
		icin(y);
		if(x==1)
			update(y-1);
		else if(x==2)
		{
			printf("%d\n",query(y-1));
		}
	}

	return 0;
}


