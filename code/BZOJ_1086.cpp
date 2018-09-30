#include<cstdio>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,Threshold,cnt;
struct graph{
	int top;
	struct rec{
		int x,next;
	}e[2100];
	int F[1100];
	void ins(int f,int s){
		top++; e[top].x=s; e[top].next=F[f]; F[f]=top;
	}
}G;
int stktop;
int root[1100],belong[1100],stk[1100];
void DFS(int f,int x){//正统树分块
	int v,bottom=stktop;
	for(v=G.F[x];v;v=G.e[v].next){
		if(G.e[v].x!=f){
			DFS(x,G.e[v].x);
			if(stktop-bottom>=Threshold){
				root[++cnt]=x;
				while(stktop!=bottom){
					belong[stk[stktop--]]=cnt;
				}
			}
		}
	}
	stk[++stktop]=x;
}
int main(){
	int i,u,v;
	read(n); read(Threshold);
	for(i=1;i<=n-1;i++){
		read(u); read(v); G.ins(u,v); G.ins(v,u);
	}
	DFS(0,1);
	while(stktop){
		belong[stk[stktop--]]=cnt;
	}
	printf("%d\n",cnt);
	for(i=1;i<=n;i++)printf("%d%c",belong[i],i==n?'\n':' ');
	for(i=1;i<=cnt;i++)printf("%d%c",root[i],i==n?'\n':' ');//输出
}