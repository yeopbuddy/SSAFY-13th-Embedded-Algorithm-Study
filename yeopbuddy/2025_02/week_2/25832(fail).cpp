#include <iostream>

#include <algorithm>

#include <map>

#include <vector>
using namespace std;
int main(){
    int node, query;
    cin >> node >> query;
    int oneortwo, node1, node2;
    map<int, vector<int>> graph;
    map<int, int> way;
    for(int i = 1; i <= node; i++){
        graph[i].push_back(i);
        way[i] = i;
    }
    for(int i = 0; i < query; i++){
        cin >> oneortwo;
        if(oneortwo == 1){
            // connect node
            cin >> node1 >> node2;
            if(way[node1] != way[node2]){
                if(graph.find(node1) == graph.end() && graph.find(node2) == graph.end()){
                    for(int j = 0; j < graph[way[node1]].size(); j++){
                        graph[way[node2]].push_back(graph[way[node1]][j]);
                        way[graph[node1][j]] = way[node2];
                    }
                    graph.erase(way[node1]);
                }
                else if(graph.find(node1) == graph.end()){
                    for(int j = 0; j < graph[node2].size(); j++){
                        graph[way[node1]].push_back(graph[node2][j]);
                        way[graph[node2][j]] = way[node1];
                    }
                    graph.erase(node2);
                }
                else if(graph.find(node2) == graph.end()){
                    for(int j = 0; j < graph[node1].size(); j++){
                        graph[way[node2]].push_back(graph[node1][j]);
                        way[graph[node1][j]] = way[node2];
                    }
                    graph.erase(node1);
                }
                else{
                    for(int j = 0; j < graph[node2].size(); j++){
                        graph[node1].push_back(graph[node2][j]);
                        way[graph[node2][j]] = node1;
                    }
                    graph.erase(node2);
                }   
            }
        }
        else{ // calculate and print
            int up = 0;
            int down = 0;
            for(auto j = graph.begin(); j != graph.end(); j++){
                down++;
                up += (j->second.size() * j->second.size());
            }
            int gcd = __gcd(up, down);
            cout << up/gcd << "/" << down/gcd << "\n";
        }
    }
}