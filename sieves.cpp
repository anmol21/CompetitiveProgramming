vector< int >  mu(maxv+9,1);
vector< int > is_prime(maxv+9,0);

// Prime Sieve

void prime_sieve()
{
	is_prime[1]=1;
	for(int i=4;i<=maxv;i+=2)
		is_prime[i]=1;
	for(int i=3;i<maxv;i+=2)
	{
		if(is_prime[i]==0)
		{
			if(i<= sqrt(maxv) + 9)
			{
				for(int j=i*i;j<=maxv;j+=i)
					is_prime[j]=1;
			}
		}
	}
	
}

// Sieve to Calculate the Mobius Function

void mu_sieve()
{
	
	
	for(int i=2;i<=maxv;i++)
	{
		if(is_prime[i]==1)
			continue;
		for(int j=i;j<=maxv;j+=i)
			mu[j] = mu[j]*(-1);
		
		if(i<=sqrt(maxv) + 9)
		{
			for(int j=i*i;j<=maxv;j+=i*i)
				mu[j]=0;
		}

	}
}
