#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#define ULL unsigned long long
#define LL long long
using namespace std;
char ch; bool fh;
inline void read(int &a){
	for(fh=0,ch=getchar();ch<'0'||ch>'9';ch=getchar())if(ch=='-')fh=1;
	for(a=0;ch>='0'&&ch<='9';ch=getchar())(a*=10)+=ch-'0'; if(fh)a=-a;
}
int T;
int n,m;
int S[100010];
struct veg{
	int ti,id;
	bool operator <(const veg &a)const{return ti>a.ti;}
};
veg Heap[500010]; int Htop;
int Seg[1<<18]; int zm;
inline void Change(int p,int w){for(p+=zm;p;p>>=1)Seg[p]+=w;}
inline int Getsum(int l,int r){
	int s=0;
	for(l+=zm-1,r+=zm+1;l^r^1;l>>=1,r>>=1){
		if(!(l&1))s+=Seg[l^1]; if(r&1)s+=Seg[r^1];
	}
	return s;
}
int Find(){
	if(!Seg[1])return 0;
	int p;
	for(p=1;p<=zm;)p=p<<1|(!Seg[p<<1]);
	return p-zm;
}
struct linkele{
	int ti,ne;
};
linkele INpot[500010]; int Hea[100010],Tai[100010]; int Itop;
inline void Ins(const veg &a){
	INpot[++Itop].ti=a.ti; INpot[Itop].ne=0;
	if(Hea[a.id])INpot[Tai[a.id]].ne=Itop,Tai[a.id]=Itop;else Hea[a.id]=Tai[a.id]=Itop;
}
inline void Del(int id){
	Hea[id]=INpot[Hea[id]].ne; if(!Hea[id])Tai[id]=0;
}
void init(){
	int vi;
	Htop=0; Itop=0;
	for(vi=zm<<1;vi>=0;vi--)Seg[vi]=0;
	for(vi=1;vi<=n;vi++)Hea[vi]=Tai[vi]=0;
}
void work(){
	int vi,t,op,id,l,r; veg tmp; int innum,ounum;
	read(n); zm=1<<(int)ceil(log2(n+2));
	for(vi=1;vi<=n;vi++)read(S[vi]);
	read(m);
	for(vi=1;vi<=m;vi++){
		read(t); read(op);
		if(op)for(;(Htop)&&(Heap[1].ti<=t);pop_heap(Heap+1,Heap+Htop+1),Htop--)Change(Heap[1].id,1),Del(Heap[1].id);
		if(op&1){
			if(op==1){
				id=Find();
				if(id){
					Change(id,-1); printf("%d\n",id);
				}else printf("Yazid is angry.\n");
			}else{
				read(l); read(r);
				printf("%d\n",Getsum(l,r));
			}
		}else{
			read(id);
			if(op){
				innum=Getsum(id,id); ounum=Hea[id];
				if(!(innum+ounum))printf("YJQQQAQ is angry.\n");
				else if(innum){
					Change(id,-1); printf("Succeeded!\n");
				}else{
					printf("%d\n",INpot[ounum].ti-t);
				}
			}else{
				tmp.id=id; tmp.ti=t+S[id];
				Heap[++Htop]=tmp; push_heap(Heap+1,Heap+Htop+1);
				Ins(tmp);
			}
		}
	}
}
int main(){
	freopen("T.in","r",stdin); freopen("T.out","w",stdout);
	read(T);
	for(;T;T--){
		init();
		work();
	}
}

