#include <bits/stdc++.h>

#define icin(x) scanf("%d",&x)
#define VVI  vector< vector<int> >
#define LL long long
#define pb push_back
#define mp make_pair
#define maxn 1000000
#define MAXN 1000000
#define MAXL 20
#define inf (int)(1e9)
#define mod (LL)(1e9 + 7)
#define F first
#define S second

using namespace std;


int bit[maxn+9]={0};

int n;
void update(int x,int num)
{
	for(;x<=n; x += x&-x)
	{
		bit[x] += num;
	}
}

int query(int x)
{
	int ret=0;
	for(;x>0;x -=x&-x)
	{
		ret += bit[x];
	}
	return ret;
}




#define PP pair< pair<int,int> , int >

struct mycomp{
	bool operator()(PP p1 , PP p2)
	{
		return p1.F.S < p2.F.S;
	}
};

int main()
{
	int m,d;
	icin(n);
	icin(m);
	icin(d);
	vector<int> ar(n+1);
	vector<int> l(n+1),r(n+1);
	vector<int> idx(n+1);

	for(int i=1;i<=n;i++)
	{
		icin(ar[i]);
		idx[ar[i]]=i;
		l[i] = max(1,ar[i]-d);
		r[i] = min(n,ar[i]+d);
	}

	vector< pair< pair<int,int> , int > > vec;

	for(int i=1;i<=m;i++)
	{
		int L,R;
		icin(L);
		icin(R);
		vec.pb( { {L,R} , i } );
	}

	sort(vec.begin(),vec.end(),mycomp());

	int k=0;

	vector<int> ans(m+1,0);

	for(int i=1;i<=n;i++)
	{
	//	cout << l[i] << " " << r[i];
		int a = l[i];
		int b = r[i];
		for(int j=a;j<=b;j++)
		{
		//	if(idx[j]<i)
		//	cout << "YO";
			update(idx[j],idx[j]<=i);
		}
		for(;k<m && vec[k].F.S==i;k++)
		{
			int p = vec[k].F.F;
			int q = vec[k].F.S;
			int num = vec[k].S;
		
			if(p==1)
				ans[num] = query(q);
			else
				ans[num] = query(q) - query(p-1);

		}

	}

	for(int i=1;i<=m;i++)
		cout << ans[i] << endl;

	return 0;
}

