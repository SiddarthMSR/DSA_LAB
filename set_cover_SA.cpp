#include <bits/stdc++.h>
using namespace std;
#define T 300
set <int > X={1,2,3,4,5,6,7,8,9,10,11,12};
vector < set <int > > F={
        {1,2,3,4,5,6},
        {5,6,8,9},
        {1,4,7,10},
        {2,5,7,8,11},
        {3,6,9,12},
        {10,11}
    };
int mini_cost=0;
string Gen_permutation(int len){
string s;
for(int i=0;i<len;i++){
if(rand()%2==0)s.push_back('0');
else s.push_back('1');

}
return s;
}
void flip(char *c){
    if(*c=='0')*c='1';
    else *c='0';
}
int cost(string s){int sum=0;
    for(auto x:s)sum+=x-'0';
    return sum;
}
bool is_valid(string s){
set <int > result={};
for(int i=0;i<s.length();i++){
    if(s[i]=='1'){
        set_union(result.begin(),result.end(),F[i].begin(),F[i].end(),inserter(result,result.begin()));
    }
}
set <int > set_diff={};
set_difference(X.begin(),X.end(),result.begin(),result.end(),inserter(set_diff,set_diff.begin()));
if(set_diff.empty())return true;
else return false;
}
string Gen_neighbor(string s){
    if(is_valid(s)){
        int rand_value=rand()%6;
        flip(&s[rand_value]);
        if(is_valid(s))return s;
        else return Gen_neighbor(s);
    }
    else{
        int rand_value=rand()%6;
        for(int i=0;i<s.length();i++){
            if(s[(i+rand_value)%s.length()]=='0')s[(i+rand_value)%s.length()]='1';
            if(is_valid(s))return s;
            else return Gen_neighbor(s);
        }
    }
}
bool Acceptance(string prev_str,string new_str){
    int prev_cost=cost(prev_str),new_cost=cost(new_str);
    if(prev_cost>=new_cost)return true;
    else {
        float rand_value=rand()%(int(pow(10,6)));
        rand_value/=pow(10,6);
        float prob=exp(-1*((float)(new_cost-prev_cost)/T));
        if(rand_value>=prob)return true;
        else return false;
    }
}
int main(){srand(time(0));
    
    string s=Gen_permutation(6);
    s=Gen_neighbor(s);
    mini_cost=cost(s);
    string mini_str=s;
    // cout<<s<<endl;
    int markov_chains=50;
    while(markov_chains--){
        string new_str;
        new_str=Gen_neighbor(s);
        cout<<new_str<<endl;
        cout<<"s= "<<s<<endl;
        cout<<"no.of chains left = "<<markov_chains<<endl;
        if(Acceptance(s,new_str))s=new_str;
        if(mini_cost>cost(s))mini_str=s,mini_cost=cost(s);
    }
    cout<<s<<endl;

}