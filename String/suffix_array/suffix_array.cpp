#include<bits/stdc++.h>
using namespace std;

// suffix array
// complexity O(nlog^2 n)
vector<int> build_suffix(string str){

    str = str + "$";
    int len = str.size();

    vector<int > p(len),c(len);

    // k = 0
    vector<pair<char,int>> v(len);
    for(int i = 0; i < len; i++)    v[i] = {str[i],i};
    sort(v.begin(),v.end());

    for(int i = 0; i < len; i++)    p[i] = v[i].second;

    c[p[0]] = 0;

    for(int i = 1; i< len; i++){
        int cur = v[i].first;
        int prv = v[i-1].first;
        if(cur == prv)  c[p[i]] = c[p[i-1]];
        else c[p[i]] = c[p[i-1]] + 1;
    }

    // transition
    int k = 0;
    int cur_pow = pow(2,k);
    while(cur_pow < len){
        //k -> k + 1
        vector<pair<pair<int,int>, int>> a(len);
        for(int i = 0; i < len; i++){
            a[i] = {{c[i], c[(i+cur_pow)%len]},i};
        }

        sort(a.begin(),a.end());

        for(int i = 0; i < len; i++)    p[i] = a[i].second;

        c[p[0]] = 0;

        for(int i = 1; i<len; i++){
            auto cur = a[i].first;
            auto prv = a[i-1].first;
            if(cur == prv)  c[p[i]] = c[p[i-1]];
            else c[p[i]] = c[p[i-1]] + 1;
        }
        k++;
        cur_pow = pow(2,k);
    }
    return p;
}

int main(){

    string str;
    cin>>str;

    int len = str.size();

    vector<int> suffixes = build_suffix(str);

    for(int i = 0; i<suffixes.size(); i++){
        cout<<suffixes[i]<<" "<<str.substr(suffixes[i],len-suffixes[i])<<endl;
    }
}
