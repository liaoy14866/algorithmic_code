#include<cstdio>
#include<algorithm>
#include<vector>
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
int BIT[100010];
inline void Change(int p,int w){for(;p<=n;p+=p&-p)BIT[p]+=w;}
inline int Getsum(int p){int s=0; for(;p;p-=p&-p)s+=BIT[p]; return s;}
int Find(){
    int p=n+1,vi,q;
    for(vi=n;vi;vi-=vi&-vi)if(BIT[vi])p=vi;
    if(p==n+1)return 0;
    for(vi=(p&-p)>>1,q=p-(p&-p);vi;vi>>=1)if(!BIT[q|vi])q|=vi;
    return q+1;
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
    for(vi=1;vi<=n;vi++)BIT[vi]=Hea[vi]=Tai[vi]=0;
}
void work(){
    int vi,t,op,id,l,r; veg tmp; int innum,ounum;
    read(n);
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
                //树状数组上二分 
            }else{
                read(l); read(r);
                printf("%d\n",Getsum(r)-Getsum(l-1));
            }
        }else{
            read(id);
            if(op){
                innum=Getsum(id)-Getsum(id-1); ounum=Hea[id];
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
    read(T);
    for(;T;T--){
        init();
        work();
    }
}
