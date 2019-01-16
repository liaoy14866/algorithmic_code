#include<cstdio>
#include<algorithm>
using namespace std;
char ch; bool fl;
inline void read(int &a){
    fl=1;
    for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')fl=0;
    for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
    if(!fl)a=-a;
}
int n,m,qtop,otop,dtop,itop;
unsigned int Ans[50010];
struct que{
    int l,r,k,num,tim;
}Q[50010],tmpQ[50010];
inline bool Ccmp(const que &a,const que &b){
    return a.tim<b.tim;
}
/*原询问*/
struct ope{
    int l,r,c,rank,tim;
    bool operator <(const ope &a)const{
        return c<a.c;
    }
}O[50010],tmpO[50010];
inline bool Acmp(const ope &a,const ope &b){
    return a.c<b.c;
}
inline bool Bcmp(const ope &a,const ope &b){
    return a.tim<b.tim;
}
/*原操作*/
int D[50010],I[50010];
/*D没什么用，I是去重以后的插入的数字的数组*/
struct node{
    unsigned int l,r,m,sum,tag;
}Seg[50010*4];
void Segunite(unsigned int p){
    Seg[p].sum=Seg[p<<1].sum+Seg[p<<1|1].sum+(Seg[p].r-Seg[p].l+1)*Seg[p].tag;
}
void SegChange(unsigned int p,unsigned int l,unsigned int r,unsigned int w){
    if(Seg[p].l==l&&Seg[p].r==r){
        Seg[p].tag+=w; Seg[p].sum+=w*(r-l+1); return;
    }
    if(r<=Seg[p].m)SegChange(p<<1,l,r,w);
    else
    if(Seg[p].m+1<=l)SegChange(p<<1|1,l,r,w);
    else
    SegChange(p<<1,l,Seg[p].m,w),SegChange(p<<1|1,Seg[p].m+1,r,w);
    Segunite(p);
}
unsigned int SegGetsum(unsigned int p,unsigned int l,unsigned int r){
    if(Seg[p].l==l&&Seg[p].r==r)return Seg[p].sum;
    unsigned int sum=(r-l+1)*Seg[p].tag;
    if(r<=Seg[p].m)sum+=SegGetsum(p<<1,l,r);
    else
    if(Seg[p].m+1<=l)sum+=SegGetsum(p<<1|1,l,r);
    else
    sum+=SegGetsum(p<<1,l,Seg[p].m)+SegGetsum(p<<1|1,Seg[p].m+1,r);
    return sum;
}
void Segbuild(unsigned int p,unsigned int l,unsigned int r){
    Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1;
    if(l==r)return;
    Segbuild(p<<1,l,Seg[p].m); Segbuild(p<<1|1,Seg[p].m+1,r);
}
void Div(unsigned int quel,unsigned int quer,unsigned int ansl,unsigned int ansr){
    unsigned int vi;
    if(quel>quer)return;
    if(ansl==ansr){
        for(vi=quel;vi<=quer;vi++)Ans[Q[vi].num]=ansl;
        return;
    }
    unsigned int ansmid=((ansl+ansr)>>1)+1,vj;	ope tmp={0,0,0,0,0};
    tmp.c=I[ansmid]; unsigned int opel=lower_bound(O+1,O+otop+1,tmp)->rank;
    tmp.c=I[ansr]; unsigned int oper=upper_bound(O+1,O+otop+1,tmp)->rank-1;
    unsigned int ql=quel-1,qr=quer+1,qtmp;
    for(vi=opel;vi<=oper;vi++)tmpO[vi]=O[vi]; sort(tmpO+opel,tmpO+oper+1,Bcmp);
    for(vi=quel;vi<=quer;vi++)tmpQ[vi]=Q[vi]; sort(tmpQ+quel,tmpQ+quer+1,Ccmp);
    for(vj=opel,vi=quel;vi<=quer;vi++){
        while(vj<=oper&&tmpO[vj].tim<tmpQ[vi].tim){
            SegChange(1,tmpO[vj].l,tmpO[vj].r,1); vj++;
        }
        qtmp=SegGetsum(1,tmpQ[vi].l,tmpQ[vi].r);
        if(qtmp<tmpQ[vi].k){
            tmpQ[vi].k-=qtmp; Q[++ql]=tmpQ[vi];
        }else Q[--qr]=tmpQ[vi];
    }
    for(vj--;vj>=opel;vj--)SegChange(1,tmpO[vj].l,tmpO[vj].r,-1);
    Div(quel,ql,ansl,ansmid-1);
    Div(qr,quer,ansmid,ansr);
}
int main(){
    int i,opt;
    read(n); read(m);
    for(i=1;i<=m;i++){
        read(opt);
        if(opt==1){
            otop++; read(O[otop].l); read(O[otop].r); read(O[otop].c); O[otop].tim=i; D[++dtop]=O[otop].c;
        }else{
            qtop++; read(Q[qtop].l); read(Q[qtop].r); read(Q[qtop].k); Q[qtop].tim=i; Q[qtop].num=qtop;
        }
    }
    sort(D+1,D+dtop+1);
    for(i=1;i<=dtop;i++){
        if(D[i]==D[i+1]&&i!=dtop)continue;
        I[++itop]=D[i];
    }
    sort(O+1,O+otop+1,Acmp); otop++; O[otop].c=(1LL<<31)-1;
    for(i=1;i<=otop;i++)O[i].rank=i;
    Segbuild(1,1,n);
    Div(1,qtop,1,itop);
    for(i=1;i<=qtop;i++)printf("%d\n",I[Ans[i]]);
}
