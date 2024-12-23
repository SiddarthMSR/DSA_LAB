#include <bits/stdc++.h>
using namespace std;
#define Cooling Rate 0.999
int T=300;
// test case 1
set <int > X={1,4,5,8,9,12,14,15,18,19,20,21};
vector < set <int > > F={
        {1,18,9,4},
        {4,1,19,8},
        {4,18,1,9,14},
        {8,5,1,18,4},
        {15,19,20,12},
        {14,15,19,5},
        {19,8,21,14},
        {19,12,1,20,5},
        {19,14,1,18,5},
        {20,8,18,5,1,4}
    };
// test case 2
// set<int> X = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

//     vector<set<int>> F = {
//         {1, 2, 3, 4, 5, 6}, 
//         {7, 8, 9, 10, 11}, 
//         {5, 6, 12, 13}, 
//         {10, 14, 15}, 
//         {1, 3, 9, 12, 16}, 
//         {2, 4, 11, 17}, 
//         {13, 14, 18, 19}, 
//         {7, 8, 20}, 
//         {15, 16, 17, 18, 19, 20}
//     };
    // set<int> X = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // vector<set<int>> F = {
    //     {1,2,7,9,10},
    //     {4,5,2,3},
    //     {5,6,7},
    //     {9,10,8},
    //     {1,2,3},
    //     {7,8,4},
    //     {5,6,9,10}
    // };

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
        int rand_value=rand()%F.size();
        flip(&s[rand_value]);
        if(is_valid(s))return s;
        else return Gen_neighbor(s);
    }
    else{
        int rand_value=rand()%F.size();
        for(int i=0;i<s.length();i++){
            if(s[(i+rand_value)%s.length()]=='0')s[(i+rand_value)%s.length()]='1';
            if(is_valid(s))return s;
            else return Gen_neighbor(s);
        }
    }
    return s;//just to avoid warnings
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
string ans_by_SA(){
    srand(time(0));
    string s=Gen_permutation(F.size());
    s=Gen_neighbor(s);
    mini_cost=cost(s);
    string mini_str=s;
    // cout<<s<<endl;
    int markov_chains=5000000;
    while(markov_chains--){
        string new_str;
        new_str=Gen_neighbor(s);
        if(Acceptance(s,new_str))s=new_str;
        if(mini_cost>cost(s))mini_str=s,mini_cost=cost(s);
    }
    return s;
}
//
string Tr;
set <int > Find_max(vector < set <int > > &F,set <int > Ui){

    int card=0;
    int max_ind=0;
    if(F.size()==0)
    return set <int > ();

    set <int > Max_Set;
    int i=0;
    for(auto S:F){
    
        set <int > intersection_Set;
        set_intersection(S.begin(),S.end(),Ui.begin(),Ui.end(),inserter(intersection_Set,intersection_Set.begin()));
        
        if(card<intersection_Set.size())Max_Set=S,card=intersection_Set.size(),max_ind=i;
        i++;
    }
    Tr[max_ind]='1';
    return Max_Set;
}

vector < set <int > >Greedy_algo_for_set_cover(set <int > &X,vector < set <int > > &F){

    vector < set <int > > C;
    vector < set <int > > U;
    U.push_back(X);

    while(U.back().size()){

        set <int > Max_Set=Find_max(F,U.back());
        C.push_back(Max_Set);
        set <int > Next;
        set_difference(U.back().begin(),U.back().end(),Max_Set.begin(),Max_Set.end(),inserter(Next,Next.begin()));
        U.push_back(Next);
    }

    return C;
}
void printset(ofstream &file,set <int > S){
    auto it =S.begin();
    for(int i=0;i<S.size();i++){
        if(i==0)file<<"{"<<*it;
        else file<<","<<*it;
        it++;
    }
    file<<"}";
}
string num_Bin(long long int n,int si){
string t;
for(int i=0;i<si;i++){
    if(n%2==0)t.push_back('0');
    else t.push_back('1');
    n/=2;
}
for(int i=0;i<si/2;i++){
    if(t[i]==t[si-i-1])continue;
    else if(t[i]=='1')t[i]='0',t[si-i-1]='1';
    else t[i]='1',t[si-i-1]='0';
}
return t;
}
void Gen_Set(int n,int maxn){
    X.clear();
    F.clear();
    for(int i=0;i<n;i++){
        X.insert(i+1);
    }
    int a[n+1]={};
    for(int i=1;i<=pow(2,X.size())&&maxn>=0;i++){
        int ch=rand()%2;
        if(ch==1){
            string temp=num_Bin(i,X.size());
            set <int > S;
            for(int j=0;j<temp.size();j++){
                if(temp[j]=='1')S.insert(j+1),
                a[j+1]++;
            }
            F.push_back(S);maxn--;
        }
    }
    set <int > S;
    for(int i=1;i<=n;i++){
        if(a[i]==0)S.insert(i);
    }
    F.push_back(S);
    

}
string BruteForce(){
    string s;
    for(int i=0;i<F.size();i++)s.push_back('1');
    for(long long int i=0;i<pow(2,F.size());i++){
        string temp=num_Bin(i,F.size());
        if(is_valid(temp)){
            if(cost(temp)<cost(s))s=temp;
        }
    }
    return s;
}
int main(){
    Gen_Set(10,10);
    cout<<"Generated"<<endl;
    for(int i=0;i<F.size();i++)Tr.push_back('0');
    ofstream file("TestCases_setcover.txt",ios::trunc);
    clock_t start,end;
    start=clock();
    vector < set <int > > C=Greedy_algo_for_set_cover(X,F);
    end=clock();
    cout<<"finished TR"<<endl;
    file<<endl<<"Test Case:"<<endl;
    file<<"X = ";
    printset(file,X);
    file <<endl;
    auto it1=F.begin();
    file<<"F = ";
    for(int i=0;i<F.size();i++){
        if(i==0)file<<"{ ";
        else file<<","<<endl;
        printset(file,*it1);
        it1++;
    }
    file<<"}"<<endl;
    file<<"For Traditional algo:"<<endl;
    file<<"string:"<<Tr<<endl;
    file<<"Time taken:"<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    start=clock();
    string sa=ans_by_SA();
    end=clock();
    file<<"For SA:"<<endl;
    file<<"String:"<<sa<<endl;
    file<<"Time taken:"<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    start=clock();
    string br=BruteForce();
    end=clock();
    file<<"For BF:"<<endl;
    file<<"String:"<<br<<endl;
    file<<"Time taken:"<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
}