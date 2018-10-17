function lowbit(x:longint):longint;//树状数组函数
 begin exit(x and (-x)); end;
procedure change(p,data:longint);//单点修改
 begin while p<=n do begin inc(c[p],data); inc(p,lowbit(p)); end; end;
function getsum(p:longint):longint;//统计1到i的和
 begin getsum:=0; while p<>0 do begin inc(getsum,c[p]); dec(p,lowbit(p)); end; end;