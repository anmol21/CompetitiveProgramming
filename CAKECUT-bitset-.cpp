// Problem Source :https://www.codechef.com/problems/CAKECUT (June 2016 CookOff)
// Ideas Used : Bitset Optimization, XOR for pairity check

#include <bits/stdc++.h>

#define icin(x) scanf("%d",&x)
#define pb push_back
#define LL long long
#define maxn 1509

using namespace std;

char data[maxn][maxn];
int  bxor[maxn][maxn];
bitset<maxn> bs[maxn];

int main()
{
  int n,m;
  icin(n);
  icin(m);
  for(int i=0;i<n;i++)
    scanf("%s",data[i]);

  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
    {
      bxor[i][j] = data[i-1][j-1]-'0';
      bxor[i][j] ^= bxor[i-1][j] ;
      bxor[i][j] ^= bxor[i][j-1];
      bxor[i][j] ^= bxor[i-1][j-1];
      bs[i][j] = bxor[i][j];
    }
  }
  LL ans = 0;
  for(int i=1;i<=n;i++)
  {

    for(int j=0;j<i;j++)
    {
        int a = (bs[i]^bs[j]).count();
        int b = (m+1-a);
        ans += (a*1ll*(a-1))/2;
        ans += (b*1ll*(b-1))/2;
    }
  }
  cout << ans;
  
}
