#include<cstdio>
int T,a,b,c;
inline void read(int &a){
	char c=getchar();
	for(a=0;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar())(a*=10)+=c-'0';
}
inline int gcd(int a,int b){int c=a%b;while(c!=0){a=b;b=c;c=a%b;}return b;}
int main(){
	read(T);
	while(T>0){
		T--;
		read(a); read(b); read(c);
		int gys=gcd(a,b);
		if(c%gys==0){putchar('Y'); putchar('e'); putchar('s'); putchar('\n');}
		else{putchar('N'); putchar('o'); putchar('\n');}
	}
}        