int Fa[210000];
int Getfa(int x){
	if(!Fa[x]){Fa[x]=x;return x;} if(Fa[x]==x)return x;
	int fu=Getfa(Fa[x]);
	Dist[x]+=Dist[Fa[x]]; Fa[x]=fu; return fu;
}