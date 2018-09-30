#include<cstdio>
#include<algorithm>
using namespace std;
char ch; bool f;
inline void read(unsigned int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
unsigned int n;
unsigned int B1[60010],B2[60010];
unsigned int A[100010];
long long ans;
int main(){
	unsigned int i,j,k;
	read(n);
	for(i=1;i<=n;i++)read(A[i]);
	for(i=1;i<=n;i++)B2[A[i]]++;
	for(i=1;i<=n;i++){
		B2[A[i]]--;
		for(j=1,k=(A[i]<<1)-1;k>=14;){
			ans+=B1[j]*B2[k]+B1[j+1]*B2[k-1]+B1[j+2]*B2[k-2]+B1[j+3]*B2[k-3]+
			B1[j+4]*B2[k-4]+B1[j+5]*B2[k-5]+B1[j+6]*B2[k-6]+B1[j+7]*B2[k-7]+
			B1[j+8]*B2[k-8]+B1[j+9]*B2[k-9]+B1[j+10]*B2[k-10]+B1[j+11]*B2[k-11]+
			B1[j+12]*B2[k-12]+B1[j+13]*B2[k-13];
			j+=14; k-=14;
		}
		for(;k>=1;){
			ans+=B1[j]*B2[k];
			j++; k--;
		}
		B1[A[i]]++;
	}
	printf("%lld\n",ans);
}