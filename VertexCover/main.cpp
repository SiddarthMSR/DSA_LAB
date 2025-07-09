    #include <bits/stdc++.h>
    using namespace std;
    class Graph{
        private:
        int E=0;
        //put in private no one should voluntarily change this
        //if we decrease or increase it means no of edges
        //then you must had removed and edge or an edge;

        public:
        int V=0;
        vector < vector < int > > Edges;
        Graph(){
            clear();
        }
        Graph(int v){
            clear();
            V=v;
            Edges.resize(V);
            
        }
        void SetVertices(int v){
            clear();
            V=v;
            Edges.resize(V);
        }
        void add_edge(int a,int b){
            if(a>=V || b>=V || a<0 || b<0 || a==b ) {
                cout << "Invalid\n";
                exit(1);
            }
            if(find(Edges[a].begin(),Edges[a].end(),b)!=Edges[a].end())return;
            Edges[a].push_back(b);
            Edges[b].push_back(a);
            E++;
        }
        //If you do take_edges it will clear() all the edges;
        void Take_Graph(){Edges.clear();
            int t;
            cout << "Enter the no.of Vertices in the graph." << endl;
            cin>>t;
            SetVertices(t);
            cout << "Enter the no.of Edges." << endl;
            cin >> t;
            for ( int i=0; i < t; i++){
                int a,b;
                cout << "Edge " << i+1 << ":";
                cin >> a >> b;
                add_edge(a,b);
            }
        }
        //We don't need these as far as now;
        // void remove_Edge(int a, int b){
        //     if(a>=V || b>=V || a<0 || b<0 || a==b ) return;
        //     if(E==0)return;
        //      auto it = find( Edges[a].begin(), Edges[a].end(),b);
        //      if(it!=Edges[a].end()){
        //         Edges[a].erase(it);
        //         auto jt = find( Edges[b].begin() , Edges[b].end(),a);
        //         Edges[b].erase(jt);
        //         E--;
        //      }
        // }
        // void remove_Incident_vertex(int a){
        //     if(a>=V || a<0)return ;
        //     E-=Edges[a].size();
        //     int b;
        //     while(!Edges[a].empty()){
        //         b=Edges[a].back();
        //         auto it= find(Edges[b].begin(),Edges[b].end(),a);
        //         Edges[b].erase(it);
        //         Edges[a].pop_back();
        //     }
        // }
        void PrintGraph(){
            cout << "Graph consists of ";
            cout << V << " vertices and ";
            cout << E << " edges\n";
            for(int i=0; i < V ; i++){ 
                for(int j=0; j<Edges[i].size(); j++){
                    if(Edges[i][j]>i){
                        cout << i << ", " << Edges[i][j];
                        cout << endl;
                    }
                }
            }
        }
        void describe(int i){//nonzero for printgraph 0 for only the vertices and edges;   
            cout<<"No.of Vertices = "<<V<<endl;
            cout<<"No.of Edges = "<<E<<endl;
            if(i)PrintGraph();
        }
        //decrease threshold for more edges;
        /*
        *done like Graph G;
        G.FillGraph(5,0.2);
        something like this
        */
        void FillGraph(int size,double threshold=0.5){
            //we can use G.fillgraph(size);
            SetVertices(size);//This will reset the edges;
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0.0, 1.0);
            double x;
            for(int i=0;i<size;i++){
                for(int j=i+1;j<size;j++){
                    x=dis(gen);
                    if(x < threshold)add_edge(i,j);
                }
            }
        }
        //This will convert into a vector pair of edges
        vector < pair < int, int > >ListEdges(){
            vector < pair < int, int > > pair_of_edges;
            for(int i=0;i<V;i++){
                for(int j=0;j<Edges[i].size();j++){
                    if(i<Edges[i][j])pair_of_edges.push_back(make_pair(i,Edges[i][j]));
                }
            }
            return pair_of_edges;
        }
        
        void clear(){
            V=0,E=0;
            Edges.clear();
        }

    };
    class VertexCover{
        private:
        vector < pair < int, int >  > pair_of_edges;
        void remove_incident_edge(vector < pair < int, int> > &EdgePair,int a,int b){
            for(int i=0;i<EdgePair.size();){
                if(a==EdgePair[i].first || a==EdgePair[i].second){
                    swap(EdgePair.back(),EdgePair[i]);
                    EdgePair.pop_back();
                }
                else if(b==EdgePair[i].first || b==EdgePair[i].second){
                    swap(EdgePair.back(),EdgePair[i]);
                    EdgePair.pop_back();
                }
                else i++;
                
            }
        }
        bool accept(set  <int > s){
            for(auto &x:pair_of_edges){
                //one of the vertex of edge should present;
                if(s.find(x.first)==s.end()&&s.find(x.second)==s.end())return false;
            }
            return true;
        }
        vector < int > neighbor(vector < int > &vec){
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0,G.V-1);
            vector < int > w=vec;
            int idx=dis(gen);
            if(w[idx]==1)w[idx]=0;
            else w[idx]=1;
            // cout<<w[idx]<<","<<endl;
            return w;
        }
        set < int > convert_set(vector < int > &vec){
            set < int > s;
            for(int i=0;i<vec.size();i++){
                if(vec[i])s.insert(i);
            }
            return s;
        }
        vector < int > convert_bin(vector < int > w){
            vector < int > bin(G.V,0);
            for(int x : w)bin[x]=1;
            return bin;
        }
        int cost(vector < int > &vec){
            return accumulate(vec.begin(),vec.end(),0);
        }
        public:
        Graph G;
        VertexCover(Graph g){
            G=g;
            pair_of_edges=G.ListEdges();
        }
        
        vector < int > Bruteforce(){
        vector < int > ans;
        if(G.V > 63)
        {
            cout<<"Very Large size.\n";
            return ans;
        }
        int size=G.V;
            
            for(int i=0; i<G.V;i++)ans.push_back(i);
            size_t limit = 1ULL << G.V;
            set < int > s;
            string t;
            for(size_t mask=1;mask<limit;mask++){
                s.clear();
                bitset < 64 > b(mask);
                t=b.to_string().substr(64-G.V);
                for(int i=0;i<G.V;i++){
                    if(t[i]=='1')s.insert(i);
                }
                if(s.size()<ans.size()){
                    if(accept(s)){
                        ans.assign(s.begin(),s.end());
                    }
                }

            }
            return ans;
        }
        vector < int > ApproxAlgo(){
            vector < pair < int, int > > Edges=G.ListEdges();
            set < int > s;
            int idx;
            //using random edge helped to explore better sets
            //but need to do several times manually
            random_device rd;
            mt19937 gen(rd());
            
            while(!Edges.empty()){
                uniform_int_distribution <> dis(0,Edges.size()-1);
                idx=dis(gen);
                // cout<<Edges[idx].first<<" "<<Edges[idx].second<<",";
                s.insert(Edges[idx].first);
                s.insert(Edges[idx].second);
                remove_incident_edge(Edges,Edges[idx].first,Edges[idx].second);
            }
            // cout<<endl;

            vector  < int > ans(s.begin(),s.end());
            return ans;
        }   
        vector < int > Simulated_Annealing(){
            vector < int > best(G.V,1);
            int best_cost = G.V;
            //best indicates the best accepted seen solution;
            int delta;
            int max_iter = pow(10,4);
            double Temp = 1000;
            double Alpha = 0.95;//cooling rate  
            double eps=1e-6;
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0.0,1.0);
            vector < int > curr=best;
            vector < int > next_neighbor;
            int curr_cost=G.V;
            int batches=5;
            //start with several feasible setcovers to find optimal;
            for(int j=0;j<batches;j++){
                    // cout<<"batch "<<j<<endl;
                    Temp=1000;
                    for(int i=0;i<max_iter && Temp>eps;i++){

                    next_neighbor=neighbor(curr);
                    if(!accept(convert_set(next_neighbor)))
                    continue;
                    curr_cost=cost(curr);
                    delta=cost(next_neighbor)-curr_cost;
                    if(delta<0 || exp(-delta/Temp) > dis(gen) ){
                        curr=next_neighbor;
                        curr_cost=cost(curr);
                    }
                    if(best_cost>curr_cost){
                        best=curr;
                        best_cost=curr_cost;
                    }
                    Temp*=Alpha;
                }
                curr=convert_bin(ApproxAlgo());
                curr_cost=cost(curr);
                // for(auto &x:best)cout<<x<<" ";cout<<endl;
                // cout<<best.size()<<endl;
            }
            set < int > best_set=convert_set(best);
            return vector < int > (best_set.begin(),best_set.end());
        }
    };

    int main(){
        //use this way for hardcoding of your graph.
        Graph G(7);
        G.add_edge(0,1);
        G.add_edge(1,2);
        G.add_edge(2,3);
        G.add_edge(2,4);
        G.add_edge(3,4);
        G.add_edge(3,5);
        G.add_edge(4,5);
        cout << "Choose the way you want to give the input.\n";
        cout << "1.Hardcoded\n";
        cout << "2.In the terminal.\n";
        cout << "3.Go with a Random Graph,(Just want to see how this works).\n";
        int choice;
        cout << "Enter the Choice = ";
        cin >> choice;
        if(choice==1);
        else if(choice==2)G.Take_Graph();
        else if(choice==3){
            cout << "Enter the Number of Vertices that graph should have.\n";
            int vertices;
            cin >> vertices;
            if(vertices<1){
                cout << "Invalid.\n";
                return 0;
            }
            double density;
            cout << "Enter the density of Edges should be in (0,1].\n";
            cin >> density;
            if(density>1||density<=0){
                cout<<"Invalid\n";
                return 0;
            }
            G.FillGraph(vertices,density);
            G.PrintGraph();
        }
        VertexCover Vset(G);
        vector < int > OptCover=Vset.Bruteforce();
        vector < int > ApproxCover=Vset.ApproxAlgo();
        vector < int > SACover=Vset.Simulated_Annealing();
        cout << "Optimal Cover " << endl;
        for(auto x : OptCover)cout<<x<<" ";
        cout<<endl;
        cout << "Approximate Cover" << endl;
        for(auto x : ApproxCover)cout<<x<<" ";
        cout<<endl;
        cout << "Simulated Annealing Cover" << endl;
        for(auto x: SACover)cout<<x<<" ";
        
        cout << "\n| Algorithm           | Size of Cover |\n";
        cout << "|---------------------|---------------|\n";
        cout << "| Brute Force         | " << OptCover.size() << "             |\n";
        cout << "| ApproxCover         | " << ApproxCover.size() << "             |\n";
        cout << "| Simulated Annealing | " << SACover.size() << "             |\n";
    }
