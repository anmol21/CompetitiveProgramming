#include <bits/stdc++.h>
 
#define icin(x) scanf("%d",&x)
#define VVI  vector< vector<int> >
#define LL long long
#define pb push_back
#define mp make_pair
#define maxn 1000000
#define MAXN 100009
#define MAXL 16
#define inf (int)(1e9 + 7)
#define mod (LL)(1e9 + 7)
#define F first
#define S second
 
using namespace std;
 

vector<int> gr[MAXN] , costs[MAXN] ;

///// DFS_LCA variables
int sec =0;//time variable.
int L[MAXN+9],P[MAXL][MAXN+9],st[MAXN+9],ft[MAXN+9]; // level , parent dp table , start time, finish time.
int cnt[MAXN]; // SUBTREE SIZES; 


vector<int> visited;


// HLD_Variables
int chain_num , chain_head[MAXN] , chain_ind[MAXN] , pos_base[MAXN]; // pos_st is position in segment tree array.
int ptr = 1 , base_ar[MAXN]; // base_ar is the base array for the segment tre. (1 Based Array)



/************************* Segment Tree Functions *************************************************/


LL tree[6*MAXN]; // Segment Tree Array - as we only need max , we don't need to make structure of nodes.

LL combine (LL a,LL b) // Merge Logic
{
	return a+b;   
}

LL build(int from, int to, int index) 
{
	if (from == to) 
	{
    	tree[index] = base_ar[from];
    	return tree[index];
	}

	int mid = (from+to)/2;
	LL l = build(from,mid, (index<<1));
	LL r = build(mid+1,to, (index<<1)+1);

	tree[index] = combine(l,r);
	return tree[index];
}

void modify(int from, int to, int index, int indexMod) 
{
	if (from == to && from == indexMod)
    {
    	tree[index] = base_ar[from];
    	return;
	 }
	int mid = (from+to)/2;
	if (indexMod <= mid)
	{
    	modify(from, mid, (index<<1), indexMod);
	} 
	else 
	{
    	modify(mid+1, to, (index<<1)+1, indexMod);
	}
	tree[index] = combine(tree[index<<1],tree[(index<<1)+1]);
}

LL st_ans(int a,int b,int index, int from, int to) 
{
	if (from == a && to == b) {
    	return tree[index];
	}

	int mid = (from+to)/2;
	if (b <= mid) 
	{
    	return st_ans(a,b,(index<<1), from, mid);
	}
	if (a > mid) 
	{
    	return st_ans(a,b,(index<<1) + 1, mid+1,to);
	}
	LL l = st_ans(a,mid,(index<<1), from, mid);
	LL r = st_ans(mid+1,b,(index<<1) + 1, mid+1,to);
	return combine(l,r);
}

/*************** End of Segment Tree Functions ******************************************************/






/************************** HLD Function **************************************************************/

void HLD(int node,int cost,int prev)
{
	if(chain_head[chain_num]==-1) // If current chain has not been assigned a head, that is it is not started yet.
		chain_head[chain_num]=node;

	chain_ind[node] = chain_num ;// The index of the chain to which this node belongs is the current value of chain_num
	pos_base[node] = ptr;		    // Position of this node in the common segment tree that we are building
	base_ar[ptr] = cost;        // Filling that Position with the value.
	ptr++;

	int spe=-1,cost_spe;        // Now , we proceed to find the special child.

	for(int i=0 ; i<gr[node].size();i++)
	{
		int x = gr[node][i];
		if(x==prev)
			continue;
		if(spe==-1 || cnt[spe]<cnt[x]) // The special child is the one with the greatest subtree size.
		{
			spe = x;
			cost_spe = costs[node][i];
		}
	}

	if(spe!=-1)
		HLD(spe,cost_spe,node); // We include the special child to the current chain first.

	for(int i=0;i<gr[node].size();i++)
	{
		int x = gr[node][i];
		if(x==prev || x==spe)
			continue;
		chain_num++;			// At all other children which are not special , we start a new chain from them.
		int cost = costs[node][i];
		HLD(x,cost,node);
	}

}

/******* END OF HLD FUNCTION*******************************************/


/***************************LCA functions******************************************************/

// Graph Name : gr
// Also counts subtree sizes


void DFS_lca(int num,int par=-1)
{

	//cout << "Here" << " " << num << " " << par <<  endl;
	visited[num]=1;
	cnt[num] = 1;

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

	for(int  i=0;i<gr[num].size();i++)
	{
		//cout << i << endl;
		int x = gr[num][i];

		if(visited[x])continue;
		else 
		{
			DFS_lca(x,num);
			cnt[num] += cnt[x];	
		}	
	}

	ft[num] = ++sec;

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



LL query_up(int u,int v) // v is an ancestor of u , so we are going up the tree from u to v.
{
	if(u==v)
		return 0;
	int uchain, vchain = chain_ind[v];
	LL ans=0;
	while(1)
	{
		uchain = chain_ind[u];
		if(uchain==vchain) // Both u and v now belong to the same chain.
		{
			if(u==v) // As we have come up to v already.
				break;
			LL res = st_ans(pos_base[v]+1,pos_base[u],1,1,ptr-1); // NOTE : We are going upto v only , the edge connceted to v is not included. 
																   // 1 is the starting index.Segment tree is from 1 to ptr. 
									
			ans +=res;
			break; // As we are done.
		}
		LL res = st_ans(pos_base[chain_head[uchain]],pos_base[u],1,1,ptr-1);
		
		ans += res;
		u = chain_head[uchain];
		u = P[0][u];
	}
	return ans;
}

void query(int u,int v)
{
	/*
	 * We have a query from u to v, we break it into two queries, u to LCA(u,v) and LCA(u,v) to v
	 */
	 int x = lca(u,v);

	 LL ans1 = query_up(u,x);
	 LL ans2 = query_up(v,x);
	 //cout << ans1 << " " << ans2 << endl;
	 LL ans = ans1 + ans2;
	 printf("%lld \n",ans);

}

int par(int u,int k)
{
	int ans=u;

	int gen=0;
	while(k>0)
	{
		int x = k%2;
		k/=2;
		if(x==1)
		  ans = P[gen][ans];
			gen++;
	}
	return ans;
}


void query2(int a,int b,int k)
{
	int p = lca(a,b);
	int dis = dist(a,b);
	int d1 = dist(a,p);
	int ans=-1;
	if(d1>=k)
	{
		ans = par(a,k);
	}
	else
	{
		int d2 = dis - k;
		ans = par(b,d2);
	}
	printf("%d\n",ans);
}


int main()
{
	int t;
	icin(t);
	while(t--)
	{
		int n;
		icin(n);
		for(int i=0;i<=n;i++)
		{
			gr[i].clear();
			costs[i].clear();
			chain_head[i]=-1;
 			chain_ind[i]=-1;
 			cnt[i]=0;

			for(int j=0;j<MAXL;j++)
 			P[j][i]=0;
		}
		visited.assign(n+1,0);
		for(int i=1;i<n;i++)
		{
			int x,y,z;
			icin(x);
			icin(y);
			icin(z);
			gr[x].pb(y);
			costs[x].pb(z);
			gr[y].pb(x);
			costs[y].pb(z);
		}
		sec=0;
		ptr=1;

		
		DFS_lca(1,-1); // Rooting the tree at 1.
 		// End of LCA DFS , also counts subtree sizes , levels , parents.


 		chain_num=0;
 		HLD(1,0,-1);
 		// End of HLD Routine calls.

 		build(1,ptr-1,1);
 	// Building Segment Tree

 		while(1)
 	{	
 		char word[20];
 		scanf("%s",word);
 		if(word[0]=='D' && word[1]=='O')
 			break;

 		if(word[0]=='D' && word[1]=='I')
 		{
 			int a,b;
 			icin(a);
 			icin(b);
 			query(a,b);
 		}
 		else
 		{
 			int a,b,k;
 			icin(a);
 			icin(b);
 			icin(k);
 			query2(a,b,k-1);
 		}


 	}



	}	
	return 0;
}
