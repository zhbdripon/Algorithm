#include<bits/stdc++.h>
using namespace std;

void count_sort(vector<int> &p, vector<int> &c){
    int n = p.size();

    vector<int> cnt(n);
    for(int x: c){
        cnt[x]++;
    }

    vector<int> np(n);
    vector<int> pos(n);

    pos[0] = 0;
    for(int i = 1; i < n; i++){
        pos[i] = pos[i-1] + cnt[i-1];
    }

    for(int x:p){
        int i = c[x];
        np[pos[i]++] = x;
    }
    p = np;

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

        for(int i = 0; i < len; i++)    p[i] = (p[i] - cur_pow + len) % len;

        count_sort(p,c);

        vector<int > nc(len);

        nc[p[0]] = 0;

        for(int i = 1; i<len; i++){
            pair<int,int > cur = { c[p[i]], c[(p[i]+cur_pow) % len] };
            pair<int,int > prv = { c[p[i-1]], c[(p[i-1]+cur_pow) % len]};

            if(cur==prv){
                nc[p[i]] = nc[p[i-1]];
            }else{
                nc[p[i]] = nc[p[i-1]] + 1;
            }
        }
        c = nc;
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
