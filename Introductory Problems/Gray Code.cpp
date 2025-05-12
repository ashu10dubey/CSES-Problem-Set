#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios:: sync_with_stdio(0); cin.tie(0); cout.tie(0)

int main(){
    FAST_IO;
    int n;
    cin>>n;
    int total=1<<n;
    for(int i=0;i<total;++i){
        int gray=i^(i>>1);
        cout<<bitset<16>(gray).to_string().substr(16-n)<< "\n";
    }
    
    return 0;
}