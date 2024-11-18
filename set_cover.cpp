#include <bits/stdc++.h>
using namespace std;

set <int > Find_max(vector < set <int > > &F,set <int > Ui){

    int card=0;

    if(F.size()==0)
    return set <int > ();

    set <int > Max_Set;
    
    for(auto S:F){
    
        set <int > intersection_Set;
        set_intersection(S.begin(),S.end(),Ui.begin(),Ui.end(),inserter(intersection_Set,intersection_Set.begin()));
        
        if(card<=intersection_Set.size())Max_Set=S,card=intersection_Set.size();
    }
    
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

int main(){

    set <int > X={1,2,3,4,5,6,7,8,9,10,11,12};

    vector < set <int > > F={
        {1,2,3,4,5,6},
        {5,6,8,9},
        {1,4,7,10},
        {2,5,7,8,11},
        {3,6,9,12},
        {10,11}
    };

    vector < set < int > > C=Greedy_algo_for_set_cover(X,F);

    int i=0;

    for(auto S:C){
        cout<<"Set "<<i++<<":\n";
        for(auto ele:S)cout<<ele<<" ";
        cout<<endl;
    }
}