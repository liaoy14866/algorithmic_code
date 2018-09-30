#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,last,top,sum;
int A[110000];
int Ro[1100000];//记录当前颜色在Splay中的根
struct node{
	int p[2],s[2];
}Btr[110000];
int Fa[110000],Size[110000];
/*Splay*/
inline void unite(int p){Size[p]=Size[Btr[p].s[0]]+Size[Btr[p].s[1]]+1;}
void rot(int p){
	int f=Fa[p],gf=Fa[f],v=Btr[f].s[0]!=p,s;
	s=Btr[p].s[v^1]; Btr[p].s[v^1]=f; Btr[f].s[v]=s; Fa[s]=f; Fa[p]=gf; Fa[f]=p; unite(f); unite(p);
	if(gf){v=Btr[gf].s[0]!=f;Btr[gf].s[v]=p;}
}
void Splay(int p){while(Fa[p])rot(p);}
int pre(int p){
	Splay(p); for(p=Btr[p].s[0];Btr[p].s[1];p=Btr[p].s[1]); if(p)Splay(p); return p;
}
int suf(int p){
	Splay(p); for(p=Btr[p].s[1];Btr[p].s[0];p=Btr[p].s[0]); if(p)Splay(p); return p;
}
void delroot(int v){//删除根……写了好长的样子
	int p=Ro[v];
	if(!Btr[p].s[0]){Ro[v]=Btr[p].s[1];Fa[Btr[p].s[1]]=0;return;} if(!Btr[p].s[1]){Ro[v]=Btr[p].s[0];Fa[Btr[p].s[0]]=0;return;}
	while(Btr[Btr[p].s[1]].s[0])rot(Btr[Btr[p].s[1]].s[0]); while(Btr[Btr[p].s[0]].s[1])rot(Btr[Btr[p].s[0]].s[1]);
	Fa[Btr[p].s[0]]=0; Ro[v]=Btr[p].s[0]; Fa[Btr[p].s[1]]=Btr[p].s[0]; Btr[Btr[p].s[0]].s[1]=Btr[p].s[1];
	Size[Btr[p].s[0]]+=Size[Btr[p].s[1]];
}
void ins(int p,int v){
	int u;for(u=(Btr[v].p[0]>Btr[p].p[0]);Btr[p].s[u];p=Btr[p].s[u],u=(Btr[v].p[0]>Btr[p].p[0]))Size[p]++;
	Btr[p].s[u]=v; Size[p]++; Fa[v]=p; Splay(v); 
}
/*启发式合并*/
int pr,pl,rootp;
void ergodic(int p){//遍历节点
	if(Btr[p].s[0])ergodic(Btr[p].s[0]); if(Btr[p].s[1])ergodic(Btr[p].s[1]);
	Btr[p].s[0]=Btr[p].s[1]=Fa[p]=0; Size[p]=1; ins(Ro[rootp],p); Ro[rootp]=p;//清空当前节点信息并插入
	pl=pre(p);if(pl){//尝试与前驱合并
		Ro[rootp]=pl;
		if(Btr[pl].p[1]+1==Btr[p].p[0]){
			Btr[p].p[0]=Btr[pl].p[0]; delroot(rootp); sum--;
		}
	}else Ro[rootp]=p;
	pr=suf(p);if(pr){//尝试与后继合并
		Ro[rootp]=pr;
		if(pr&&Btr[p].p[1]+1==Btr[pr].p[0]){
			Btr[p].p[1]=Btr[pr].p[1]; delroot(rootp); sum--;
		}
	}else Ro[rootp]=p;
}
void Union(int fr,int to){//合并两棵Splay
	if(Size[Ro[fr]]>Size[Ro[to]]){
		rootp=fr; if(Ro[to])ergodic(Ro[to]); Ro[to]=Ro[fr]; Ro[fr]=0;
	}else{
		rootp=to; if(Ro[fr])ergodic(Ro[fr]); Ro[fr]=0;
	}
}
node tmp;
int main(){
	int i,u,v,ifdo;
	read(n); read(m);
	for(i=1;i<=n;i++)read(A[i]);
	for(i=1;i<=n;i++){
		if(A[i]==A[i+1])continue;
		tmp.p[0]=last+1; tmp.p[1]=i; top++; Btr[top]=tmp; Size[top]=1; sum++;
		if(!Ro[A[i]])Ro[A[i]]=top;else ins(Ro[A[i]],top),Ro[A[i]]=top; last=i;//读入并初始化
	}
	for(i=1;i<=m;i++){//回答询问
		read(ifdo);
		if(ifdo==1){
			read(u); read(v); if(u==v)continue; Union(u,v);
		}else printf("%d\n",sum);
	}
}