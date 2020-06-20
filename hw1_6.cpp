#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#define maxlen 256

class bigInt {
	public:
		bigInt();
		bigInt operator + (bigInt obj);
		bigInt operator - (bigInt obj);
		bigInt operator * (bigInt obj);
		bigInt division (bigInt num);
		bool operator < (bigInt obj);
		void print(bigInt num);
		int arr[maxlen];
		int len;

};

bigInt::bigInt() { //initialization
	len=0;
}

bigInt bigInt::operator + (bigInt obj){
	bigInt ans;
	int maxl=(len<obj.len)? obj.len : len; //maxl for the length of smaller num
	int carry=0;
	int i;
	int total=0;
	for(i=0;i<maxl;i++){
		if(i>=len)
			arr[i]=0;
		if(i>=obj.len)
			obj.arr[i]=0;
		total=arr[i]+obj.arr[i]+carry;
		if(total > 9){
			ans.arr[i]=total-10;
			carry=1;
		}else{
			ans.arr[i]=total;
			carry=0;
		}
	}
	ans.len=i;
	return ans;
}
bigInt bigInt::operator - (bigInt obj){ //assume the result will not be negative
	bigInt ans;
	int i;
	int carry=0;
	int total=0;
	for(i=0;i<len;i++){
		if(i>=obj.len)
			obj.arr[i]=0;
		total = arr[i] - obj.arr[i] + carry;
		if(total<0){
			total+=10;
			carry=-1;
			ans.arr[i]=total;
		}else{
			ans.arr[i]=total;
			carry=0;
		}
	}
	for(i=len-1;i>=0;i--){
		if(ans.arr[i]!=0){
			ans.len=i+1;
			break;
		}
	}
	return ans;
}
bigInt bigInt::operator * (bigInt obj){
	bigInt ans;
	int i,j;
	for(i=0;i<len+obj.len;i++)
		ans.arr[i]=0;
	for(i=0;i<len;i++){
		for(j=0;j<obj.len;j++){
			ans.arr[i+j] += arr[i]*obj.arr[j]; 
		}
	}
	int carry=0;
	for(i=0;i<len+obj.len;i++){
		ans.arr[i]+=carry;
		carry=ans.arr[i]/10;
		ans.arr[i]-=carry*10;
	}
	for(i=len+obj.len-1;i>=0;i--){
		if(ans.arr[i]!=0){
			ans.len=i+1;
			break;
		}
	}
	return ans;
}
bigInt bigInt::division(bigInt num){
	bigInt ans;
	int i;
	int carry=0;
	ans.len=num.len;
	for(i=num.len-1;i>=0;i--){
		ans.arr[i]=0;
		ans.arr[i]+=carry*5;
		carry=num.arr[i]%2;
		ans.arr[i]+=num.arr[i]/2;
	}
	for(i=num.len-1;i>=0;i--){
		if(ans.arr[i]!=0){
			ans.len=i+1;
			break;
		}
	}
	return ans;
}
bool bigInt::operator < (bigInt obj){
	int i;
	if(len < obj.len)
		return true;
	else if(len > obj.len)
		return false;
	else 
		for(i=len-1;i>=0;i--){
			if(arr[i]<obj.arr[i]){
				return true;
				break;
			}else if(arr[i]>obj.arr[i]){
				return false;
				break;
			}else{
				continue;
			}
		}
	return false;
}
void bigInt::print(bigInt num){
	for(int i=num.len-1;i>=0;i--)
		printf("%d",num.arr[i]);
	printf("\n");
}
bigInt gcd_by_binary(bigInt num1, bigInt num2){
	bigInt n,m;
	bigInt ans;
	bigInt two;
	bigInt zero;
	ans.arr[0]=1;
	ans.len=1;
	two.len=1;
	two.arr[0]=2;
	zero.len=1;
	zero.arr[0]=0;
	int i;
	if(num2 < num1){ //num1 > num2
		m.len=num1.len;
		for(i=0;i<num1.len;i++)
			m.arr[i]=num1.arr[i];
		n.len=num2.len;
		for(i=0;i<num2.len;i++)
			n.arr[i]=num2.arr[i];
	}else{
		m.len=num2.len;
		for(i=0;i<num2.len;i++)
			m.arr[i]=num2.arr[i];
		n.len=num1.len;
		for(i=0;i<num1.len;i++)
			n.arr[i]=num1.arr[i];
	}

	while(zero < n && zero < m){
		if(n.arr[0]%2==0 && m.arr[0]%2==0){
			ans = ans * two;
			n = n.division(n);
			m = m.division(m);
		}else if(n.arr[0]%2==0 && m.arr[0]%2!=0){
			n = n.division(n);
		}else if(n.arr[0]%2!=0 && m.arr[0]%2==0){
			m = m.division(m);
		}
		if(m<n){ //swap
			bigInt tmp;
			tmp.len=n.len;
			for(i=0;i<tmp.len;i++)
				tmp.arr[i]=n.arr[i];
			n.len=m.len;
			for(i=0;i<n.len;i++)
				n.arr[i]=m.arr[i];
			m.len=tmp.len;
			for(i=0;i<m.len;i++)
				m.arr[i]=tmp.arr[i];
		}

		m = m - n;
	}
	return n * ans;
}
int main() {
	char in1[maxlen];
	char in2[maxlen];
	scanf("%s %s",in1,in2);
	bigInt num1,num2;
	num1.len=strlen(in1);
	num2.len=strlen(in2);
	int len1 = strlen(in1), len2 = strlen(in2);
	for(int i=0;i<len1;i++)
		num1.arr[i]=(int)(in1[len1-i-1]-'0');
	for(int i=0;i<len2;i++)
		num2.arr[i]=(int)(in2[len2-i-1]-'0');
#ifdef P 
	num1.print(num1);
	printf("num1.len = %d\n",num1.len);
	num2.print(num2);
	printf("num2.len = %d\n",num2.len);
#endif
	bigInt bigIntGCD = gcd_by_binary(num1,num2);
	bigIntGCD.print(bigIntGCD);
}
