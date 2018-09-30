#include<cstdio>
#include<algorithm>
#include<cmath>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
const int none=300001;
const int Threshold=550;
int n;
struct inf1{
	int time,X;
}O[110000]; int Otop;
struct inf2{
	int time,Y,ans;
	bool done;
}Q[110000]; int Qtop;
int Top[560],Ans[560];
int Fa[360000];
int Getfa(int u){
	int v=u,o; if(Fa[u]==none)return none;
	while(Fa[u]!=u)u=Fa[u];
	while(Fa[v]!=u){
		o=Fa[v]; Fa[v]=u; v=o;
	}
	return u;
}
inline bool Acmp(const inf1 &a,const inf1 &b){
	return a.time>b.time;
}
inline bool Bcmp(const inf2 &a,const inf2 &b){
	return a.time>b.time;
}
int main(){
	int i,j,k,fu,u,Onow; char c;
	read(n); for(i=1;i<=550;i++)Ans[i]=none;
	for(i=1;i<=n;i++){
		for(c=getchar();c!='A'&&c!='B';c=getchar());
		if(c=='A'){Otop++; read(O[Otop].X); O[Otop].time=i;}
		else{
			Qtop++; read(Q[Qtop].Y); Q[Qtop].time=i; 
			if(Q[Qtop].Y<=Threshold){
				Q[Qtop].ans=Ans[Q[Qtop].Y]; Q[Qtop].done=1;
				for(j=Top[Q[Qtop].Y]+1;j<=Otop;j++){u=O[j].X%Q[Qtop].Y; if(u<Q[Qtop].ans)Q[Qtop].ans=u;}
				Ans[Q[Qtop].Y]=Q[Qtop].ans; Top[Q[Qtop].Y]=Otop;
			}
		}
	}
	for(i=1;i<=Otop;i++)Fa[O[i].X]=O[i].X;
	Fa[none]=none;for(i=300000;i>=0;i--)if(!Fa[i])Fa[i]=Fa[i+1];
	Onow=1; std::sort(O+1,O+Otop+1,Acmp); std::sort(Q+1,Q+Qtop+1,Bcmp);
	for(i=1;i<=Qtop;i++){
		if(Q[i].done)continue;
		while(Onow<=Otop&&O[Onow].time>Q[i].time){Fa[O[Onow].X]=Getfa(O[Onow].X+1); Onow++;}
		Q[i].ans=Q[i].Y;
		for(k=0;k*Q[i].Y<=300000;k++){fu=Getfa(k*Q[i].Y); if(fu==none)break; u=fu%Q[i].Y; if(u<Q[i].ans)Q[i].ans=u;}
	}
	for(i=Qtop;i>=1;i--)printf("%d\n",Q[i].ans);
}