/*
题目大意：给张无向图染色，一个点可以是红色也可以是黑色，也可以不染。不染的要求是存在至少一个红色与一个黑色点与之相连。
解法：
考虑对于size>=2的连通块，我们只需要黑白染色，染到染不动的地方就不染就可以了。
所以就是寻找是否有size=1的连通块。
*/
#include<cstdio>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m;
bool flag[210000];
int main(){
	int i,u,v;
	read(n); read(m);
	for(i=1;i<=m;i++){
		read(u); read(v); flag[u]|=1; flag[v]|=1;
	}
	for(i=1;i<=n;i++)if(!flag[i]){printf("NIE\n");return 0;}
	printf("TAK\n");
}