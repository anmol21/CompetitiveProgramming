
#include <bits/stdc++.h>


#define icin(x) scanf("%d",&x)
#define pb push_back
#define PI pair< int,int >

using namespace std;

struct node {
    int val;
};
 
int n;
int q[50003];

node tree[200003];
 
node makeNode(int val) 
{
    node tmp;
    tmp.val = val;
    return tmp;
}
 
node combine (node l, node r) {
    
    return makeNode(l.val + r.val);
}
 
node build(int from, int to, int index) {
    if (from == to) {
        tree[index] = makeNode(q[from]);
        return tree[index];
    }
    int mid = (from+to)/2;
    node l = build(from,mid, (index<<1));
    node r = build(mid+1,to, (index<<1)+1);
 
    tree[index] = combine(l,r);
    return tree[index];
}
 
int ans(int index, int from, int to, int a, int b) {
    if (from == a && to == b) {
        return tree[index].val;
    }
    int mid = (from+to)/2;
    if (b <= mid) {
        return ans((index<<1), from, mid, a, b);
    }
    if (a > mid) {
        return ans((index<<1) + 1, mid+1,to,a,b);
    }
    int l = ans((index<<1), from, mid, a, mid);
    int r = ans((index<<1) + 1, mid+1,to,mid+1,b);
    return l+r;
}
 
void modify(int from, int to, int index, int indexMod) {
    if (from == to && from == indexMod) {
        tree[index] = makeNode(q[from]);
        return;
    }
    int mid = (from+to)/2;
    if (indexMod <= mid) {
        modify(from, mid, (index<<1), indexMod);
    } else {
        modify(mid+1, to, (index<<1)+1, indexMod);
    }
    tree[index] = combine(tree[index<<1],tree[(index<<1)+1]);
}


struct query
{
    int l;
    int r;
    int k;
    int pos;
    int ans;
   
};

struct mycomp
{
    bool operator()(query a, query b)
    {
        return a.k<b.k;
    }

};


pair<int,int> ar[300100];

int myhash[300000];
query store[300000];

int main()
{
    icin(n);
    
    
    for(int i=1;i<=n;i++)
        q[i]=1;

    build(1,n,1);
    //cout << ans(1,1,n,1,n).val;
    

    for(int i=1;i<=n;i++)
    {
         icin(ar[i].first);
         ar[i].second=i;
    }  
 
    
    int Q;
    icin(Q);
    

    
    for(int p=0;p<Q;p++)
    {
        int i,j,k;
        query temp;
        icin(temp.l);icin(temp.r);icin(temp.k);
        temp.pos=p+1;
        store[p]=temp;
    }
    
    sort(store,store+Q,mycomp() );
    sort(ar+1,ar+n+1);
    
    int pos=1;
    
    for(int i=0;i<Q;i++)
    {
       // cout << i << endl ;
        int k = store[i].k;
        while(pos<=n && ar[pos].first<=k)
        {
            q[ar[pos].second]=0;
            modify(1,n,1,ar[pos].second);
            pos++;
        }
        //cout << store[i].l << " " << store[i].r << " " << store[i].k << endl;
        myhash[store[i].pos] = ans(1,1,n,store[i].l,store[i].r);

    }
    //cout << endl;
    for(int i=1;i<=Q;i++)
        printf("%d\n",myhash[i]);




    return 0;
}