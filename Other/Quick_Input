// fread读入挂
const int maxn=1e5+5;
namespace IO {
    const int MX = 4e7; //1e7占用内存11000kb
    char buf[MX]; int c, sz;
    void begin() {
        c = 0;
        sz = fread(buf, 1, MX, stdin);
    }
    inline bool read(int &t) {
        while(c < sz && buf[c] != '-' && (buf[c] < '0' || buf[c] > '9')) c++;
        if(c >= sz) return false;
        bool flag = 0; if(buf[c] == '-') flag = 1, c++;
        for(t = 0; c < sz && '0' <= buf[c] && buf[c] <= '9'; c++) t = t * 10 + buf[c] - '0';
        if(flag) t = -t;
        return true;
    }
}

/******************************************/
//读取一行的整数
char s[10];
    fgets(s,10,stdin);
    int v;
    char *p=strtok(s," ");
    while(p)
    {
        sscanf(p,"%d",&v);
        cout<<v<<endl;
        p=strtok(NULL," ");
}
/*****************************************/
char tools[10000];
memset(tools,0,sizeof tools);
cin.getline(tools,10000);
int ulen=0,tool;
while (sscanf(tools+ulen,"%d",&tool)==1)//
{  
    //这一行，进行操作
    if (tool==0) 
        ulen++;
    else {
        while (tool) {
            tool/=10;
            ulen++;
        }
    }
    ulen++;
}
