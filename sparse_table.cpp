// Note - O indexed Sparse Table.


#include  <bits/stdc++.h>

#define icin(x) scanf("%d",&x)
#define MAXN 100010
#define MAXL 20

using namespace std;

int st[MAXN][20],ar[MAXN];


int N;


void pre()
{
	for(int i=0;i<N;i++)
		st[i][0] = ar[i];
	for(int j=1;j<MAXL;j++)
	{
		for(int i=0;i<N;i++)
		{
			if(i+(1<<j)-1<N)
				st[i][j] = min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
		cout << endl;
	}




}



int query(int i,int j)
{
	int len = j-i+1;
	
	int stg=0;
	
	do
	{
		stg++;
	}
	while((1<<stg)<=len);

	stg--;	

	
	

	return min(st[i][stg],st[j-(1<<stg)+1][stg]);

	
}



int main()
{
	
	icin(N);
	for(int i=0;i<N;i++)
	{
		icin(ar[i]);
	}
	pre();
	int Q;
	icin(Q);
	while(Q--)
	{
		int i,j;
		icin(i);icin(j);
		printf("%d",query(i,j));
	}


	return 0;
}