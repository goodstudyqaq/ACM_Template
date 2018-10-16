int getkey(int *v,int k)
{
       int i,p=0;
       for(i=1; i<k; i++)
              p=((p<<2)+(v[i]>>4))^(v[i]<<10);
       p = p%prime;
       if(p<0)    p=p+prime;
       return p;
}
