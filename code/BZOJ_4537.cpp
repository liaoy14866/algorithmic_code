#include<cstdio>
#include<cmath>
#include<algorithm>
int n,m,q,Threshold,Num;
struct inf{
	int u,v,a,b,p;
}E[110000],Q[51000];
inline bool Acmp(const inf &a,const inf &b){
	return a.a==b.a?a.b<b.b:a.a<b.a;
}
inline bool Bcmp(const inf &a,const inf &b){
	return a.b<b.b;
}
inf Before[110000],Betmp[110000];
void Merge(int l,int m,int r){
	/*把Before[l,m]与E[m+1,r]并入到Before[l,r]*/
	/*i=1时l=1,m=-Threshold,r=0*/
	/*i=2时l=1,m=0,r=Threshold*/
	if(m==-Threshold)return;
	int st;
	int sl=l,sr=m+1; st=l;
	while(st<=r)
	if((sr>r)||(sl<=m&&Before[sl].b<E[sr].b)){
		Betmp[st]=Before[sl]; sl++; st++;
	}else{
		Betmp[st]=E[sr]; sr++; st++;
	}
	for(st=l;st<=r;st++)Before[st]=Betmp[st];
}
int Fa[51000],Size[51000],maxa[51000],maxb[51000];
int Getfa(int x){
	for(;Fa[x]!=x;x=Fa[x]); return x;
}
struct influ{
	int x,fory,nowy,fora,nowa,forb,nowb;
	//表示把x的父亲从fory变为了nowy，把y的祖先的maxa从fora变为了nowa，把y的祖先的maxb从forb变为了nowb（联通块最大值） 
}C[110000];
void push(int order,const inf &a){
	//如果order为0表示这条边的操作是不用撤销的，否则order记录的是加入的E[k]中的k 
	int fu,fv;
	fu=Getfa(a.u); fv=Getfa(a.v);
	if(Size[fu]>Size[fv])std::swap(fu,fv);
	if(order){
		C[order].x=fu; C[order].fory=Fa[C[order].x]; C[order].nowy=fv; C[order].fora=maxa[fv]; C[order].forb=maxb[fv];
	}
	Fa[fu]=fv; if(fu!=fv)Size[fv]+=Size[fu]; maxa[fv]=std::max(maxa[fu],maxa[fv]); maxb[fv]=std::max(maxb[fu],maxb[fv]);
	maxa[fv]=std::max(maxa[fv],a.a); maxb[fv]=std::max(maxb[fv],a.b);
	if(order){
		C[order].nowa=maxa[fv]; C[order].nowb=maxb[fv];
	}
}
void cancel(int order){
	if(C[order].x==-1)return;
	Fa[C[order].x]=C[order].fory; if(C[order].fory!=C[order].nowy)Size[C[order].nowy]-=Size[C[order].x];
	maxa[C[order].nowy]=C[order].fora; maxb[C[order].nowy]=C[order].forb;
}
bool Query(const inf &a){
	int fu=Getfa(a.u),fv=Getfa(a.v); if(fu!=fv)return 0;
	return (maxa[fu]==a.a&&maxb[fu]==a.b);
}
void back(const inf &a){
	maxa[a.u]=maxa[a.v]=maxb[a.u]=maxb[a.v]=0; Fa[a.u]=a.u; Fa[a.v]=a.v; Size[a.u]=Size[a.v]=1;
}
int last;
bool Ans[51000];
int main(){
	int i,j,k,tl,tr,maxan,now,upedges,upblock;
	scanf("%d%d",&n,&m);  Threshold=ceil(sqrt((double)m*(log2(m)+1)/2)); Num=m/Threshold; if(Num*Threshold<m)Num++;
	for(i=1;i<=n;i++)Fa[i]=i,Size[i]=1,maxa[i]=-1,maxb[i]=-1;
	for(i=1;i<=m;i++)scanf("%d%d%d%d",&E[i].u,&E[i].v,&E[i].a,&E[i].b);
	scanf("%d",&q);
	for(i=1;i<=q;i++)scanf("%d%d%d%d",&Q[i].u,&Q[i].v,&Q[i].a,&Q[i].b),Q[i].p=i;
	std::sort(E+1,E+m+1,Acmp); std::sort(Q+1,Q+q+1,Acmp);
	for(i=1;i<=Num;i++){
		tl=(i-2)*Threshold+1; tr=(i-1)*Threshold; if(tl>=1)std::sort(E+tl,E+tr+1,Bcmp);
		Merge(1,tl-1,tr); upedges=tr;
		/*把1到i-1这个块的所有的边按照b排序，放在Before里面，upedges记录这些边的右边界，upedges=(i-1)*Threshold*/
		tl=(i-1)*Threshold+1; tr=i*Threshold; if(tr>m)tr=m; maxan=E[tr].a; upblock=tr;
		for(j=last+1;Q[j].a<maxan&&j<=q;j++); j--; if(j==last&&i!=Num)continue;
		tl=last+1; tr=j; if(i==Num)tr=q; last=tr;
		std::sort(Q+tl,Q+tr+1,Bcmp);
		/*Q[tl,tr]即为a严格小于第i块的a的最大值的询问，按照b排序，已经更新完了last，upblock记录当前块的右边界*/
		now=1;
		for(j=tl;j<=tr;j++){
			while(Before[now].b<=Q[j].b&&now<=upedges)
			push(0,Before[now]),now++;
			for(k=upedges+1;k<=upblock;k++)if(E[k].a<=Q[j].a&&E[k].b<=Q[j].b)push(k,E[k]);
			Ans[Q[j].p]=Query(Q[j]);
			for(k=upblock;k>=upedges+1;k--)if(E[k].a<=Q[j].a&&E[k].b<=Q[j].b)cancel(k);
		}
		for(k=1;k<=now;k++)back(Before[k]);
	}
	for(i=1;i<=q;i++)if(Ans[i])printf("Yes\n");else printf("No\n");
}