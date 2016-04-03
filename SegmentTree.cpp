#include <bits/stdc++.h>
#define LL long long
#define icin(x) scanf("%d",&x)

using namespace std;


//////////////////////////////Segment Tree Begins////////////////////////////////////////////////////

// IMPORTANT : KEEP Data vector 1 based.

struct node{
		LL sum;
		LL best;
		LL left;
		LL right;
}; // Node properties

class segment_tree
{

	public:



	static int n; // Size of Segment Tree. i.e range is [1,n]
	vector< node > tree;
	vector< LL >   data;

	
	node make(LL sum, LL best, LL left, LL right) // Make Node Logic   
	{
	    node tmp;
	    tmp.sum = sum;
	    tmp.best = best;
	    tmp.left = left;
	    tmp.right = right;
	    return tmp;
	}

	node combine (node l, node r) // Merge Logic
	 {
	    LL left = l.left;
	    if (l.sum + r.left>left)
	    	 left =l.sum + r.left;
	    LL right = r.right;
	    if (r.sum + l.right > right) 
	    	right = r.sum + l.right;
	    LL best = max(l.right + r.left, max(l.best, r.best));
	    return make(l.sum+r.sum,best, left, right);
	}

	node build(int from=1, int to=n, int index=1) 
	{
    	if (from == to) 
    	{
        	tree[index] = make(data[from], data[from], data[from], data[from]);
        	return tree[index];
    	}
    
    	int mid = (from+to)/2;
    	node l = build(from,mid, (index<<1));
    	node r = build(mid+1,to, (index<<1)+1);
 
    	tree[index] = combine(l,r);
    	return tree[index];
	}

	node ans(int a,int b,int index=1, int from=1, int to=n) 
	{
    	if (from == a && to == b) {
        	return tree[index];
    	}
    
    	int mid = (from+to)/2;
    	if (b <= mid) 
    	{
        	return ans(a,b,(index<<1), from, mid);
    	}
    	if (a > mid) 
    	{
        	return ans(a,b,(index<<1) + 1, mid+1,to);
    	}
    	node l = ans(a,mid,(index<<1), from, mid);
    	node r = ans(mid+1,b,(index<<1) + 1, mid+1,to);
    	return combine(l,r);
	}

	void modify(int from, int to, int index, int indexMod) 
	{
    	if (from == to && from == indexMod)
        {
        	tree[index] = make(data[from], data[from], data[from], data[from]);
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

	void point_update(int idx,LL num)
	{
		data[idx] == num;
		modify(1,n,1,idx);
	}


	segment_tree(int sz,vector< LL > ar) // sz = Size of Segment Tree, ar = Input Data
	{
		n = sz;
		tree.resize(4*n);
		data = ar;
		build();
	}


};











///////////////////////////Segment Tree Ends/////////////////////////////////////////////////////////////








int main()
{
	int N;
	icin(N);
	vector<LL> ar(N+1);
	for(int i=1;i<=N;i++)
	{

		scanf("%lld",&ar[i]);
	}
	segment_tree obj(N,ar);
	int M;
	icin(M);
	while(M--)
	{
		int a,x,y;
		icin(a);
		icin(x);
		icin(y);
		if(a==0)
		{
			obj.point_update(x,y);
		}
		else if(a==1)
		{
			node res =	obj.ans(x,y);
			printf("%lld\n",res.best);
		}
	}


	return 0;
}
