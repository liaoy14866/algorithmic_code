inline int Getfa(int u){
	if(!Fa[u]){Fa[u]=u;val[u]=1;return u;}
	for(;u!=Fa[u];u=Fa[u]);
	return u;
}

inline void unite(int u,int v){
	int fu=Getfa(u),fv=Getfa(v); if(val[fu]>val[fv])swap(fu,fv);
	if(fu!=fv)Fa[fu]=fv,val[fv]=max(val[fv],val[fu]+1);
}