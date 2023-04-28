/*
    Gabriel Rodrigues Malaquias - 758906
    Trabalho 2 de PAA - Descobrir se o menor caminho até o nó 0 passa por tubulaçoes de ventilação.
*/

#include <bits/stdc++.h>
using namespace std;

struct myComp {
    constexpr bool operator()(
        pair<int, float> const& a,
        pair<int, float> const& b)
        const noexcept
    {
        return a.second > b.second;
    }
};


vector<int> dijkstra(int start, vector<float> dist, vector<bool> visited, vector<int> parent, vector<vector<pair<int,float>>> grafo) {
    dist[start] = 0;
    parent[start] = start;
    priority_queue<pair<int,float>, vector<pair<int,float>>, myComp> pq;
    pq.push({start, 0});

    while(!pq.empty()){
        int u = pq.top().first;                                                                    
        pq.pop();
        if(visited[u]) continue;

        visited[u] = true;
        if(u == 0) return parent;

        for(auto i : grafo[u]){
            int v = i.first;
            float cost = i.second;

            if(dist[v] > dist[u] + cost){
                dist[v] = dist[u] + cost;
                pq.push({v, dist[v]});
                parent[v] = u;
            }

            
        }
    }

    return parent;
}

int main(){
    int m, e, vent, c;
    cin >> m >> e >> vent >> c;

    vector<vector<pair<int,float>>> grafo(m);
    vector<vector<int>> grafo_tubos(m);    

    for(int i = 0; i < e; i++){
        int a, b;
        float cost;
        cin >> a >> b >> cost;
        
        grafo[a].push_back(make_pair(b, cost));
        grafo[b].push_back(make_pair(a, cost));
    }
    
    for(int i = 0; i < vent; i++){
        int a, b;
        cin >> a >> b;
        
        bool test = true;
        for(long unsigned int j = 0; j < grafo[a].size(); j++){
            if(grafo[a][j].first == b){
                if(grafo[a][j].second > 1.01){

                    grafo[a].erase(grafo[a].begin() + j);
                    grafo[a].push_back(make_pair(b, 1));

                    for(long unsigned int i = 0; i < grafo[b].size(); i++){
                        if(grafo[b][i].first == a){
                            grafo[b].erase(grafo[b].begin() + i);
                            grafo[b].push_back(make_pair(a, 1));
                        }
                    }

                    grafo_tubos[a].push_back(b);
                    grafo_tubos[b].push_back(a);
                }
                test = false;
            }
        }
        if(test){
            grafo[a].push_back(make_pair(b, 1));
            grafo[b].push_back(make_pair(a, 1));
            grafo_tubos[a].push_back(b);
            grafo_tubos[b].push_back(a);
        }
    }

    for(int i = 0; i < c; i++){
        vector<float> dist(m, FLT_MAX);
        vector<bool> visited(m,false);
        vector<int> parent(m, -1);

        int a; cin >> a;

        vector<int> parent_resp = dijkstra(a, dist, visited, parent, grafo);
        
        bool victory = true;
        int atual = 0;

        while(atual != a){
            for(auto i : grafo_tubos[atual]){
                if(i == parent_resp[atual]){
                    victory = false;
                }
            }

            atual = parent_resp[atual];
        }

        if(victory){
            cout << "victory" << endl;
        }
        else{
            cout << "defeat" << endl;
        }
    }

    return 0;
}
