procedure build(p,l,r:longint);//建树
 var m:longint;
 begin
  tree[p].l:=l; tree[p].r:=r;
  if l<>r then begin m:=(l+r) shr 1; build(p shl 1,l,m); build(p shl 1+1,m+1,r); end;
 end;
procedure change(p,l,r,data:longint);//修改
 var m:longint;
 begin
  inc(tree[p].sum,(r-l+1)*data);
  if tree[p].l=tree[p].r then exit;
  m:=(tree[p].l+tree[p].r) shr 1;
  if r<=m then change(p*2,l,r,data)
   else if m+1<=l then change(p*2+1,l,r,data)
   else begin change(p*2,l,m,data); change(p*2+1,m+1,r,data); end;
 end;
function getsum(p,l,r:longint):longint;//求和
 var m:longint;
 begin
  if (tree[p].l=l) and (tree[p].r=r) then exit(tree[p].sum);
  m:=(tree[p].l+tree[p].r) shr 1;
  if r<=m then exit(getsum(p*2,l,r))
   else if m+1<=l then exit(getsum(p*2+1,l,r))
   else exit(getsum(p*2,l,m)+getsum(p*2+1,m+1,r));
 end;