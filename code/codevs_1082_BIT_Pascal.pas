var
 A,C,T:array[0..200000] of int64;
 n,q,i,ifdo,l,r:longint;
 w:int64;
function lowbit(x:longint):longint;//lowbit����
procedure Cchange(p:longint;data:int64);//�޸�C
procedure Tchange(p:longint;data:int64);//�޸�T
function Cgetsum(p:longint):int64;//��C��ǰ׺��
function Tgetsum(p:longint):int64;//��T��ǰ׺��
begin
 read(n);
 for i:=1 to n do read(A[i]);
 for i:=n downto 1 do dec(A[i],A[i-1]);//M[i]=A[i]-A[i-1]��ֱ�Ӱ�A������M
 for i:=1 to n do begin Cchange(i,A[i]); Tchange(i,A[i]*i); end;//����
 read(q);
 for i:=1 to q do
 begin
  read(ifdo);
  if ifdo=1 then//�޸�
  begin 
   read(l,r,w);
   Cchange(l,w); Tchange(l,w*l); Cchange(r+1,-w); Tchange(r+1,-w*(r+1));//ע���޸���������
  end
   else begin
   read(l,r);
   writeln((r+1)*Cgetsum(r)-(l)*Cgetsum(l-1)+Tgetsum(l-1)-Tgetsum(r));//�������
  end;
 end;
end.