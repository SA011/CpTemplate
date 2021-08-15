mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


//inverse (Linear)
inv[1]=1;
for(int i=2;i<asz;i++)inv[i]=(mod-(mod/i)*inv[mod%i]%mod)%mod;
