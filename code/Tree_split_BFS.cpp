int PIH[100010],Depth[100010],Fa[100010],Wson[100010],Size[100010],Top[100010];
int hi,ti;
int Arr[100010],stk[100010],Fin[100010]; int stktop;
void BFS1(){
	hi=0; ti=1; Arr[1]=1; Depth[1]=1; int v,p,sum,maxn; bool leaf;
	while(hi!=ti){
		hi++; leaf=1; Fin[Fa[Arr[hi]]]++; Size[Arr[hi]]=1;
		for(v=Arrmap[Arr[hi]];v;v=Arre[v].ne)if(Arre[v].x!=Fa[Arr[hi]]){
			ti++; Arr[ti]=Arre[v].x; leaf=0;
			Depth[Arr[ti]]=Depth[Arr[hi]]+1; Fa[Arr[ti]]=Arr[hi];
		}
		if(leaf)stk[++stktop]=Arr[hi]; 
	}
	Fin[0]=0;
	while(stk[stktop]){
		p=stk[stktop--]; Size[Fa[p]]+=Size[p]; Fin[Fa[p]]--; if(!Fin[Fa[p]])stk[++stktop]=Fa[p]; maxn=0;
		for(v=Arrmap[p];v;v=Arre[v].ne)if(Arre[v].x!=Fa[p]&&maxn<Size[Arre[v].x]){
			maxn=Size[Arre[v].x]; Wson[p]=Arre[v].x;
		}
	}
	hi=0; ti=1; Arr[1]=1; Top[1]=1;
	while(hi!=ti){
		hi++; PIH[Arr[hi]]++; sum=0;
		if(Wson[Arr[hi]]){
			Top[Wson[Arr[hi]]]=Top[Arr[hi]]; Arr[++ti]=Wson[Arr[hi]]; PIH[Wson[Arr[hi]]]+=PIH[Arr[hi]]+sum; sum+=Size[Wson[Arr[hi]]];
		}
		for(v=Arrmap[Arr[hi]];v;v=Arre[v].ne)if(Arre[v].x!=Fa[Arr[hi]]&&Arre[v].x!=Wson[Arr[hi]]){
			Top[Arre[v].x]=Arre[v].x; Arr[++ti]=Arre[v].x; PIH[Arre[v].x]+=PIH[Arr[hi]]+sum; sum+=Size[Arre[v].x];
		}
	}
}