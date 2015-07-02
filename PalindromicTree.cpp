// Simple implementation of Palindromic Tree
#include <bits/stdc++.h>

#define MAXN 100100

using namespace std;


struct ptree_node
{
int edge[26];
int length;
int sufflink;
};

ptree_node tree[MAXN];
int num=0;
int suff=0;  // Number of Processed tree nodes.
int len=0;
string S;

bool insert_ptree(int pos)
{
	int curlen =0;
	int cur=suff;
	int let = S[pos] - 'a';
	
	while(true)
	{
		curlen = tree[cur].length;
		if(pos-1-curlen>=0 && S[pos]==S[pos-1-curlen])
		break;
		cur = tree[cur].sufflink;
	}
	if(tree[cur].edge[let])
	{
		suff=tree[cur].edge[let];
		return false;
	}
	num++;
	suff=num;
	tree[cur].edge[let]=num;
	tree[num].length = tree[cur].length + 2;
	if(tree[num].length==1)
	{
		tree[num].sufflink = 2;
		return true;
	}
	
	while(1)
	{
		cur  = tree[cur].sufflink;
		curlen =tree[cur].length;
		if(pos-1-curlen>=0 && S[pos-1-curlen]==S[pos])
		{
			tree[num].sufflink = tree[cur].edge[let];
			break;
		}
	}
	
	
	return true;
	
}


void init_ptree()
{
	num=2;suff=2;
	tree[1].length=-1;tree[1].sufflink=1;
	tree[2].length=0;tree[2].sufflink=1;
}


int main()
{
	
	cin >> S;
	init_ptree();
	len = S.length();
	for(int i=0;i<len;i++)
	{
		 insert_ptree(i);
	}
	//for(int i=1;i<=num;i++)
	//	cout << tree[i].sufflink << " ";
	
	return 0;
}
