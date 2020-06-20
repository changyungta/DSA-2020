#include <stdio.h>
int times[4];

int gcdbydef(int a, int b)
{
	int min = (a<b)? a : b;
	int i;
	int gcd;
	for(i=1;i<=min;i++){
		if(a%i==0 && b%i==0)
			gcd = i;
	}
	times[0]=i-1;
	return gcd;
}
int gcdbyrev(int a, int b)
{
	int min = (a<b)? a : b;
	int i;
	int gcd;
	for(i=min;i>=1;i--){
		if(a%i==0 && b%i==0){
			gcd = i;
			break;
		}
	}
	times[1]=min-i+1;
	return gcd;
}
int gcdbybin(int a, int b)
{
	int n = (a>b)? b : a;
	int m = (a>b)? a : b;
	int ans=1;
	int cnt=0;
	while(n != 0 &&  m!= 0)
	{
		if(n%2 == 0 && m%2==0)
		{
			ans *= 2;
			n = n/2;
			m = m/2;
		}
		else if(n%2 == 0 && m%2 != 0)
			n = n/2;
		else if(n%2 != 0 && m%2 == 0)
			m = m/2;
		if(n > m){
			int tmp;
			tmp = n;
			n = m;
			m = tmp;
		}
		m = m-n;
		cnt++;
	}
	times[2]=cnt;
	return n * ans;
}
int gcdbyeuc(int a, int b)
{
	int n = (a>b)? b : a;
	int m = (a>b)? a : b;
	int tmp;
	int cnt=0;
	while(m%n != 0)
	{
		tmp = n;
		n = m%n;
		m = tmp;
		cnt++;
	}
	times[3]=cnt;
	return n;
}
int main(void)
{
	int a,b;
	int cnt;
	while(1)
	{
		scanf("%d",&a);
		if(a==0)
			break;
		scanf("%d",&b);
		int gcd_by_def=gcdbydef(a,b);
		printf("Case (%d, %d): GCD-By-Def = %d, taking %d iterations\n",a,b,gcd_by_def,times[0]);
		int gcd_by_rev=gcdbyrev(a,b);
		printf("Case (%d, %d): GCD-By-Reverse-Search = %d, taking %d iterations\n",a,b,gcd_by_rev,times[1]);
		int gcd_by_bin=gcdbybin(a,b);
		printf("Case (%d, %d): GCD-By-Binary = %d, taking %d iterations\n",a,b,gcd_by_bin,times[2]);
		int gcd_by_euc=gcdbyeuc(a,b);
		printf("Case (%d, %d): GCD-By-Euclid = %d, taking %d iterations\n",a,b,gcd_by_euc,times[3]);

	}
}
