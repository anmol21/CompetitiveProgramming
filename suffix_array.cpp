#include <bits/stdc++.h>

#define LL long long



using namespace std;


#define MAXN 100000
#define MAXLG 18





// Very short N(logN)^2 implementation of Suffix Array
struct suffix_struct
{
	int rank[2];
	int pos;
}obj[MAXN];

bool suffix_cmp(suffix_struct a,suffix_struct b)
{
	return a.rank[0]==b.rank[0]?(a.rank[1]<b.rank[1]):(a.rank[0]<b.rank[0]);
}

int P[MAXLG][MAXN]; // P is the Array where P[i] denotes the sorted array after i iterations, comparing first 2^i letters of suffixes
int lcp[MAXN]; //lcp[i] is lcp of ith and i+1^th suffix , -1 if undefined.
// Understand what P[i][j] gives i.e at i^th stage of the process , the sorted index of the j^th suffix . 0^th suffix is the entire string and so on
// Objects[i]
int stg=0;
int len;
void build_suffixarray(string S) // Assuming S is lower string English characters.
{
	len = S.length();
	
	for(int i=0;i<len;i++)
		P[0][i] = S[i] -'a';
	int cnt=0;
	for(stg=1,cnt=1;(cnt>>1)<len;stg++,cnt <<=1)
	{
		//cout << stg << endl;
		for(int i=0;i<len;i++)
		{
			obj[i].rank[0] = P[stg-1][i];
			obj[i].rank[1] = (i+cnt<len)?P[stg-1][i+cnt]:-1;
			obj[i].pos = i;
		}	
		sort(obj,obj+len,suffix_cmp);
		for(int i=0;i<len;i++)
		{
			if( i>0 && obj[i].rank[0]==obj[i-1].rank[0] && obj[i].rank[1]==obj[i-1].rank[1]) 
				P[stg][obj[i].pos] = P[stg][obj[i-1].pos]; // We give the same index as the previous one as we haven't been able to differentiate in the current sorting stage.
			else
				P[stg][obj[i].pos] = i; // We give a different index.

		}

	}
	cout << "RETURNED " << endl;
}



int get_lcp(int x,int y) // LCP of x^th suffix and y^th suffix in O(logn)
{
	int ans=0;
	if(x==y)
		return len - x;
	for(int i=stg-1;i>=0 && x<len && y<len;i--)
	{
		if(P[i][x]==P[i][y])
		{
			ans += 1<<i;
			x   += 1<<i;
			y   += 1<<i;
		}
	}
	return ans;
}

void build_lcparray()
{
	memset(lcp,-1,sizeof(lcp));
	for(int i=0;i<len-1;i++)
	{
		lcp[i] = get_lcp(obj[i].pos,obj[i+1].pos); 
	}
}





int main()
{
	string S;
	cin >> S;
	build_suffixarray(S);
	build_lcparray();
	cout << stg << endl;
	for(int j=0;j<S.length();j++)
	{
		cout << S.substr(obj[j].pos,S.length()-obj[j].pos) << " ";
	}
	cout << endl;
	for(int i=0;i<len;i++)
	cout << lcp[i] << " ";
	cout << endl;

	
	return 0;
}
