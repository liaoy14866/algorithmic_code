/*
1.rand[1..x]
2.LCT
3.PluSeg
4.Sieve_Prime
*/
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cstring>
using namespace std;
inline int randint() {
    return rand()*rand();
}
inline int randx(int x) {
    return 1+randint()%x;
}
inline int randlr(int l,int r) {
    return randx(r-l)+l;
}
inline int rand01() {
    return (randx(1e8)+randx(1e8)&1);
}
inline int randleq(int x) {
    //生成接近x但是比小于等于x的正整数
    if(x<=50)
        return x-rand01();
    if(x<=1000)
        return x-randx(10);
    if(x<=1e6)
        return x-randx(100);
    if(x<=1e7)
        return x-randx(1000);
    return x-randx(5e5);
}

const int none=10;

struct LCT {
    struct node {
        int son[2];
        bool Tag;
    };
    int Fa[none+10],Size[none+10];
    node Tree[none+10];
    void Sizeinit() {
        for(int vi=1; vi<=none; vi++)
            Size[vi]=1;
    }
    void Pushdown(int p) {
        if(!Tree[p].Tag)
            return;
        swap(Tree[p].son[0],Tree[p].son[1]);
        Tree[Tree[p].son[0]].Tag^=1;
        Tree[Tree[p].son[1]].Tag^=1;
        Tree[p].Tag=false;
    }
    bool Beroot(int p) {
        return (Tree[Fa[p]].son[0]!=p)&&(Tree[Fa[p]].son[1]!=p);
    }
    void Splay(int p) {
        int f,gf,son;
        f=Fa[p];
        gf=Fa[f];
        Pushdown(f);
        Pushdown(p);
        if(Beroot(p))
            return;
        if(Tree[f].son[0]==p) {
            son=Tree[p].son[1];
            Tree[f].son[0]=son;
            Tree[p].son[1]=f;
        } else if(Tree[f].son[1]==p) {
            son=Tree[p].son[0];
            Tree[f].son[1]=son;
            Tree[p].son[0]=f;
        }
        Fa[f]=p;
        Fa[son]=f;
        Fa[p]=gf;
        if(gf!=0) {
            if(Tree[gf].son[0]==f)
                Tree[gf].son[0]=p;
            else if(Tree[gf].son[1]==f)
                Tree[gf].son[1]=p;
        }
        Size[f]=Size[Tree[f].son[0]]+Size[Tree[f].son[1]]+1;
        Size[p]=Size[Tree[p].son[0]]+Size[Tree[p].son[1]]+1;
    }
    void Access(int x) {
        int t=0;
        while(x!=0) {
            while(!Beroot(x))
                Splay(x);
            Pushdown(x);
            Size[x]+=Size[t]-Size[Tree[x].son[1]];
            Tree[x].son[1]=t;
            t=x;
            x=Fa[x];
        }
    }
    void Make_root(int x) {
        Access(x);
        while(!Beroot(x))
            Splay(x);
        Tree[x].Tag^=1;
    }
    void Link(int x,int y) {
        Make_root(x);
        Fa[x]=y;
    }
    void Cut(int x,int y) {
        Make_root(x);
        Access(y);
        while(!Beroot(x))
            Splay(x);
        Size[x]-=Size[y];
        Tree[x].son[1]=0;
        Fa[y]=0;
    }
    int Find_root(int x) {
        Access(x);
        while(!Beroot(x))
            Splay(x);
        while(Tree[x].son[0]!=0)
            x=Tree[x].son[0];
        return(x);
    }
};
struct PluSeg {
    struct node {
        int l,r,m,son[2];
        long long sum,tag;
    };
    int top,root;
    node Seg[none*3];
    int SegBuild(int l,int r) {
        int now=++top;
        Seg[now].l=l;
        Seg[now].r=r;
        Seg[now].m=(l+r)>>1;
        if(l==r)
            return now;
        Seg[now].son[0]=SegBuild(l,Seg[now].m);
        Seg[now].son[1]=SegBuild(Seg[now].m+1,r);
        return now;
    }
    void Pushdown(int p) {
        if(!Seg[p].tag)
            return;
        for(int vi=0; vi<=1; vi++) {
            int son=Seg[p].son[vi];
            Seg[son].sum+=Seg[p].tag*(Seg[son].r-Seg[son].l+1);
            Seg[son].tag+=Seg[p].tag;
        }
        Seg[p].tag=0;
    }
    void Plus(int p,int l,int r,long long w) {
        if(Seg[p].l==l&&Seg[p].r==r) {
            Seg[p].sum+=w*(Seg[p].r-Seg[p].l+1);
            Seg[p].tag+=w;
            return;
        }
        Pushdown(p);
        if(r<=Seg[p].m)
            Plus(Seg[p].son[0],l,r,w);
        else if(Seg[p].m+1<=l)
            Plus(Seg[p].son[1],l,r,w);
        else {
            Plus(Seg[p].son[0],l,Seg[p].m,w);
            Plus(Seg[p].son[1],Seg[p].m+1,r,w);
        }
        Seg[p].sum=Seg[Seg[p].son[0]].sum+Seg[Seg[p].son[1]].sum;
    }
    long long Getsum(int p,int l,int r) {
        if(Seg[p].l==l&&Seg[p].r==r)
            return Seg[p].sum;
        Pushdown(p);
        if(r<=Seg[p].m)
            return Getsum(Seg[p].son[0],l,r);
        else if(Seg[p].m+1<=l)
            return Getsum(Seg[p].son[1],l,r);
        else
            return Getsum(Seg[p].son[0],l,Seg[p].m)+Getsum(Seg[p].son[1],Seg[p].m+1,r);
    }
};
struct Sieve {
    bool flag[none+10];
    int Prime[none+10];
    int top;
    void Get(int Up) {
        top=0;
        memset(flag,0,sizeof(flag));
        for(int vi=2; vi<=Up; vi++) {
            if(!flag[vi])
                Prime[++top]=vi;
            for(int vj=1; vi*Prime[vj]<=Up; vj++) {
                flag[vi*Prime[vj]]=true;
                if(!(vi%Prime[vj]))
                    break;
            }
        }
    }
    inline void Print() {
        for(int vi=1; vi<=top; vi++)
            printf("%d ",Prime[vi]);
        printf("\n");
        for(int vi=top; vi>=1; vi--)
            printf("%d ",Prime[vi]);
        printf("\n");
    }
    inline void Printmax() {
        printf("%d\n",Prime[top]);
    }
};





int n,q;
void work() {
    n=randleq(2000);
    q=randleq(2000);
    printf("%d %d\n",n,q);
    for(int i=1; i<=n; i++)
        printf("%d ",randx(1e9));
    printf("\n");
    int Num = n;
    int opt,p,x;
    for(int i=1; i<=q; i++) {
        opt = randx(4);
        if((Num<=2) && (opt%2==0))
            opt--;
        if(opt <= 2) {
            //p是头或尾
            opt = opt & 1;
            opt++;
            if(opt == 1) {
                p = rand01();
                if(p==1)
                    p=Num;
                x = randx(1e9);
                Num++;
                printf("%d %d %d\n",opt,p,x);
            } else {
                p = rand01();
                if(p==0)
                    p=Num;
                printf("%d %d\n",opt,p);
                Num--;
            }
        } else {
            //p任意
            opt = opt & 1;
            opt++;
            if(opt == 1) {
                p = randx(Num+1) - 1;
                x = randx(1e9);
                Num++;
                printf("%d %d %d\n",opt,p,x);
            } else {
                p = randx(Num);
                printf("%d %d\n",opt,p);
                Num--;
            }
        }
    }

}























































int main() {
    freopen("Link.in","w",stdout);
    srand((unsigned)time(NULL));
    work();
}
