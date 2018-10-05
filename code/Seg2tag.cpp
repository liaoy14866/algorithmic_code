struct node{
	int l,r,m;
	int tag[2],maxn;//tag[0]是区间赋值，tag[1]是区间加。维护区间最大值
};
node Seg[410000];
inline void Update(int p,int ifdo,int w){
	if(!ifdo)Seg[p].tag[0]=Seg[p].maxn=w,Seg[p].tag[1]=0;
	else{int v=(Seg[p].tag[0]==0); Seg[p].tag[v]+=w; Seg[p].maxn+=w;}
}
inline void Down(int p,int ifdo){
	if(!Seg[p].tag[ifdo])return;
	Update(p<<1,ifdo,Seg[p].tag[ifdo]); Update(p<<1|1,ifdo,Seg[p].tag[ifdo]);
	Seg[p].tag[ifdo]=0;
}
inline void Pushdown(int p){Down(p,1); Down(p,0);}
inline void Union(int p){
	Seg[p].maxn=std::max(Seg[p<<1].maxn,Seg[p<<1|1].maxn);
}
void SegChange(int p,int ifdo,int l,int r,int w){
	if(Seg[p].l==l&&Seg[p].r==r){Update(p,ifdo,w); return;}
	Pushdown(p);
	if(r<=Seg[p].m)SegChange(p<<1,ifdo,l,r,w);
	else
	if(Seg[p].m+1<=l)SegChange(p<<1|1,ifdo,l,r,w);
	else{SegChange(p<<1,ifdo,l,Seg[p].m,w);SegChange(p<<1|1,ifdo,Seg[p].m+1,r,w);}
	Union(p);
}
int SegGetmax(int p,int l,int r){
	if(Seg[p].l==l&&Seg[p].r==r)return Seg[p].maxn;
	Pushdown(p);
	if(r<=Seg[p].m)return SegGetmax(p<<1,l,r);
	else
	if(Seg[p].m+1<=l)return SegGetmax(p<<1|1,l,r);
	else return std::max(SegGetmax(p<<1,l,Seg[p].m),SegGetmax(p<<1|1,Seg[p].m+1,r));
}
