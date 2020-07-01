#include<bits/stdc++.h>
using namespace std;

void raddix_sort(vector<pair<pair<int,int>, int>> &v){
    int n = v.size();

    // sort the second element of the pair
    {
        vector<int> cnt(n);
        for(auto p: v){
            cnt[p.first.second]++;
        }

        vector<pair<pair<int,int>, int>> nw(n);
        vector<int> pos(n);

        pos[0] = 0;
        for(int i = 1; i < n; i++){
            pos[i] = pos[i-1] + cnt[i-1];
        }

        for(auto p:v){
            int e = p.first.second;
            nw[pos[e]++] = p;
        }
        v = nw;
    }
    // sort the first element of the pair
    {
        vector<int> cnt(n);
        for(auto p: v){
            cnt[p.first.first]++;
        }

        vector<pair<pair<int,int>, int>> nw(n);
        vector<int> pos(n);

        pos[0] = 0;
        for(int i = 1; i < n; i++){
            pos[i] = pos[i-1] + cnt[i-1];
        }

        for(auto p:v){
            int e = p.first.first;
            nw[pos[e]++] = p;
        }
        v = nw;
    }
}

// suffix array
// complexity O(nlog n)
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

        raddix_sort(a);

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
