/**/
#include<cstdio>
inline void read(int &a){
	char c=getchar(); bool bl=true;
	for(a=0;c>'9'||c<'0';c=getchar())if(c=='-')bl=false;
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
	if(!bl)a=-a;
}
int T;
int n,m;
int Fa[120],Dist[120];
int Getfa(int u){//带权并查集
	if(Fa[u]==u)return u;
	int fu=Getfa(Fa[u]); Dist[u]+=Dist[Fa[u]]; Fa[u]=fu; return fu;
}
void init(){
	int vi;
	read(n); read(m);
	for(vi=1;vi<=n+1;vi++)Fa[vi]=vi,Dist[vi]=0;
}
int main(){
	int al,i,li,ri,wi,fl,fr; bool bl;
	read(T);
	for(al=1;al<=T;al++){
		init(); bl=1;
		for(i=1;i<=m;i++){
			read(li); read(ri); read(wi);
			fl=Getfa(li); fr=Getfa(ri+1);
			if(fl==fr){
				if(Dist[ri+1]-Dist[li]!=wi)bl&=0;//否则判断是否矛盾
			}else{
				Fa[fr]=fl; Dist[fr]=Dist[li]+wi-Dist[ri+1];//如果之前没有信息，就构造
			}
		}
		if(bl)printf("true\n");else printf("false\n");//输出
	}
}