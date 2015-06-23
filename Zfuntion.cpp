//Computes Z function for a string.
#include <bits/stdc++.h>


using namespace std;


int Z[1000000]={0};

void compute_z(string S)
{
	int L=0,R=0;
	int len = S.length();
	for(int i=1;i<len;i++)
	{
		if(i>R)
		{
			L=R=i;
			while(R<len && S[R-L]==S[R])R++;
			Z[i]=R-L;
			R--;
		}
		else
		{
			int k = i-L;
			if(Z[k] < R-i+1)
				Z[i] = Z[k];
			else
			{
					L=i;
					while(R<len && S[R-L]==S[R])R++;
					Z[i]=R-L;
					R--;		
			}
		}
	}
}





int main()
{
	string S;
	cin >> S;
	compute_z(S);
	for(int i=0;i<S.length();i++)
		cout << Z[i] << " ";
}