#include <bits/stdc++.h>

#define icin(x) scanf("%d",&x)
#define LL long long
#define VVI vector< vector<int> >
#define mod 1000000007LL



using namespace std;


VVI iden(int n)
{
	VVI a;
	a.resize(n);
	for(int i=0;i<n;i++)
		a[i].assign(n,0);
	for(int i=0;i<n;i++)
		a[i][i]=1;
	return a;
}

VVI matrixmulti(VVI m1,VVI m2)
{
	VVI m3;
	int a=m1.size(),b=m1[0].size(),c=m2.size(),d=m2[0].size();
	//cout << a << " " <<  b << " " << c << " " << d << " " << endl;
	if(b!=c)
		cout << "CANNOT MULTIPLY" << endl;

	m3.resize(a);
	for(int i=0;i<a;i++)
		m3[i].assign(d,0);

	for(int i=0;i<a;i++)
	{
		for(int j=0;j<d;j++)
		{
			m3[i][j]=0;
			for(int k=0;k<b;k++)
				m3[i][j]= (m3[i][j] + (m1[i][k]*1ll*m2[k][j])%mod)%mod;
		}
	}
	return m3;
}

VVI matrixpower(VVI a,int n)
{
	if(n==0)
		return iden(a.size());
	VVI res=iden(a.size());
	VVI b=a;
	while(n)
	{
		if(n&1)
			res= matrixmulti(res,b);
		
		b = matrixmulti(b,b);
		n>>=1;
	}
	return res;

}

VVI make(int k=3)
{
	VVI res;
	res.resize(k);
	for(int i=0;i<3;i++)
	res[i].assign(3,0);
	res[0][0]=1;res[0][1]=1;res[0][2]=0;
	res[1][0]=0;res[1][1]=1;res[1][2]=1;
	res[2][0]=0;res[2][1]=1;res[2][2]=0;
	return res;
}

VVI makebase(int k=3)
{
	VVI res;
	res.resize(k);
	for(int i=0;i<k;i++)
	{
		res[i].resize(1);
		res[i][0]=0;
	}
	res[1][0]=1;
	return res;
}

void print(VVI a)
{
	cout << endl;
	for(int i=0;i<a.size();i++)
	{
		for(int j=0;j<a[i].size();j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}	

int main()
{
	int C;
	icin(C);
	while(C--)
	{
		int N,M;
		icin(N);
		icin(M);
		if(N==0 && M==0)
		{
			printf("0\n");
			continue;
		}
		VVI T=make(),R=make();
		

		T = matrixpower(T,M);
		VVI A=makebase();
		VVI res = matrixmulti(T,A);
		int ans1 = res[0][0];

		int ans2=0;
		if(N)
		{
		R = matrixpower(R,N-1);
		VVI res2 = matrixmulti(R,A);
		 ans2 = res2[0][0];
		}
		//cout << ans1 << " " << ans2 << endl;
		
		int result= ((ans1-ans2) + mod)%mod;
		//print(T);
		
		printf("%d\n",result);
	}
	return 0;
}
