struct inf{
	int v,x;
};
int cnt;
inf stk[510000];
inline void Pushin(int x){stk[++top].x=x;}
inline void Pushout(){top--;}
bool Ad[510000],Xd[510000];
int Depth[510000],Size[510000];
void DFS(){
	Pushin(1); Depth[1]=1;
	for(;;){
		if(!Ad[stk[top].x]){Ad[stk[top].x]=1;IN[stk[top].x]=++cnt;Depth[stk[top].x]=Depth[stk[top-1].x]+1;Size[stk[top].x]=1;}
		if(!Xd[stk[top].x]){Xd[stk[top].x]=1;stk[top].v=Tree[stk[top].x];}
		else stk[top].v=Etree[stk[top].v].next;
		if(stk[top].v){
			if(Etree[stk[top].v].x!=Fm[stk[top].x][0]){
				Fm[Etree[stk[top].v].x][0]=stk[top].x;
				Pushin(Etree[stk[top].v].x);
			}
		}else{
			OUT[stk[top].x]=++cnt; Pushout(); if(!top)break; Size[stk[top].x]+=Size[stk[top+1].x];
		}
	}
}