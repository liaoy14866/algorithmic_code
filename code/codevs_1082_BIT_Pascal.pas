var
 A,C,T:array[0..200000] of int64;
 n,q,i,ifdo,l,r:longint;
 w:int64;
function lowbit(x:longint):longint;//lowbit函数
procedure Cchange(p:longint;data:int64);//修改C
procedure Tchange(p:longint;data:int64);//修改T
function Cgetsum(p:longint):int64;//求C的前缀和
function Tgetsum(p:longint):int64;//求T的前缀和
begin
 read(n);
 for i:=1 to n do read(A[i]);
 for i:=n downto 1 do dec(A[i],A[i-1]);//M[i]=A[i]-A[i-1]，直接把A换成了M
 for i:=1 to n do begin Cchange(i,A[i]); Tchange(i,A[i]*i); end;//建树
 read(q);
 for i:=1 to q do
 begin
  read(ifdo);
  if ifdo=1 then//修改
  begin 
   read(l,r,w);
   Cchange(l,w); Tchange(l,w*l); Cchange(r+1,-w); Tchange(r+1,-w*(r+1));//注意修改两个数组
  end
   else begin
   read(l,r);
   writeln((r+1)*Cgetsum(r)-(l)*Cgetsum(l-1)+Tgetsum(l-1)-Tgetsum(r));//区间求和
  end;
 end;
end.