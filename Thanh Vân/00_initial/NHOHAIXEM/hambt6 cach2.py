from math import*
def nguyento(n):
    if n<2:
        return False
    for i in range(2,isqrt(n)+1):
        if n%i==0:
            return False
    return True
#main
n=int(input("hay nhap n "))
d=0
for i in range(1,n//2+1):
  if n%i==0 and nguyento(i):
    d+=1
print(d)
