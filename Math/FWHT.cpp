
void XOR(vector<ll> &a,bool inv=false){
    int M=a.size();
    for(int len=2,l2=1;len<=M;len<<=1,l2<<=1){
        for(int i=0,inc=M/len;i<M;i+=len){
            for(int j=0,l=0;j<l2;j++,l+=inc){
                ll u=a[i+j],v=a[i+j+l2];
                a[i+j]=(u+v);
                a[i+j+l2]=(u-v);
            }
        }
    }
    if(inv){
        for(auto &x:a)x=x/M;
    }
}
void AND(vector<ll> &a,bool inv=false){
    int M=a.size();
    for(int len=2,l2=1;len<=M;len<<=1,l2<<=1){
        for(int i=0,inc=M/len;i<M;i+=len){
            for(int j=0,l=0;j<l2;j++,l+=inc){
                ll u=a[i+j],v=a[i+j+l2];
                if(inv){
                    a[i+j]=(-u+v);
                    a[i+j+l2]=u;
                }
                else{
                    a[i+j]=v;
                    a[i+j+l2]=(u+v);
                }
            }
        }
    }
}
void OR(vector<ll> &a,bool inv=false){
    int M=a.size();
    for(int len=2,l2=1;len<=M;len<<=1,l2<<=1){
        for(int i=0,inc=M/len;i<M;i+=len){
            for(int j=0,l=0;j<l2;j++,l+=inc){
                ll u=a[i+j],v=a[i+j+l2];
                if(inv){
                    a[i+j]=v;
                    a[i+j+l2]=(u-v);
                }
                else{
                    a[i+j]=(u+v);
                    a[i+j+l2]=u;
                }
            }
        }
    }
}
void multiply(vector<ll> &a,vector<ll> &b,vector<ll> &v1){
    int n=max(a.size(),b.size());
    int M=1;
    while(M<n)M<<=1;
    v1.resize(M);
    vector<ll> v2(M);
    for(int i=0;i<a.size();i++)v1[i]=a[i];
    for(int i=0;i<b.size();i++)v2[i]=b[i];
    XOR(v1);
    XOR(v2);
    for(int i=0;i<M;i++)v1[i]=v1[i]*v2[i];
    XOR(v1,1);
}
