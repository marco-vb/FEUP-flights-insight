#include <bits/stdc++.h>
#include "graph.h"

Graph::Graph() {
    n = 0;
    hasDir = false;
}

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, string airline, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    for (Edge &e : nodes[src].adj)
        if (e.dest == dest) {
            e.airlines.insert(airline);
            return;
        }
    nodes[src].adj.push_back({dest, weight, {airline}});
}

// Depth-First Search: example implementation
void Graph::dfs(int v) {
    // show node order
    // cout << v << " ";
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

// Breadth-First Search: example implementation
void Graph::bfs(int v) {
    for (int i=1; i<=n; i++) nodes[i].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        // show node order
        //cout << u << " ";
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}

list<li> Graph::least_flights(int source, int destination) {
    for (int j = 1; j <= n; ++j) {nodes[j].visited = false; nodes[j].distance = -1;}
    vector<vi> previous(n+1, vi());

    queue<int> q;
    q.push(source);
    nodes[source].visited = true;
    nodes[source].distance = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                previous[w].push_back(u);
            } else if (nodes[w].distance == nodes[u].distance + 1) {
                previous[w].push_back(u);
            }
        }
    }

    list<li> paths;
    if (nodes[destination].distance == -1) return paths;

    li path;
    path.push_back(destination);
    paths.push_back(path);
    for (int i = 0; i < nodes[destination].distance; ++i) {
        list<li> new_paths;
        for (const auto& p : paths) {
            for (const auto& node : previous[p.front()]) {
                li new_path = p;
                new_path.push_front(node);
                new_paths.push_back(new_path);
            }
        }
        paths = new_paths;
    }
    return paths;
}

list<li> Graph::least_flights(int src, int dest, set<string> &airlines_to_consider) {
    for (int j = 1; j <= n; ++j) {nodes[j].visited = false; nodes[j].distance = -1;}
    vector<vi> previous(n+1, vi());

    queue<int> q;
    q.push(src);
    nodes[src].visited = true;
    nodes[src].distance = 0;

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& e : nodes[u].adj) {
            set<string> intersection;
            set_intersection(e.airlines.begin(), e.airlines.end(), airlines_to_consider.begin(), airlines_to_consider.end(), inserter(intersection, intersection.begin()));
            if (intersection.empty()) continue;
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                previous[w].push_back(u);
            } else if (nodes[w].distance == nodes[u].distance + 1) {
                previous[w].push_back(u);
            }
        }
    }

    list<li> paths;
    if (nodes[dest].distance == -1) return paths;

    li path;
    path.push_back(dest);
    paths.push_back(path);
    for (int i = 0; i < nodes[dest].distance; ++i) {
        list<li> new_paths;
        for (const auto& p : paths) {
            for (const auto& node : previous[p.front()]) {
                li new_path = p;
                new_path.push_front(node);
                new_paths.push_back(new_path);
            }
        }
        paths = new_paths;
    }
    return paths;
}

list<li> Graph::least_flights(vector<int> sources, vector<int> destinations) {
    for (int j = 1; j <= n; ++j) {nodes[j].visited = false; nodes[j].distance = -1;}
    vector<vi> previous(n+1, vi());

    queue<int> q;
    for(const auto& s : sources) {
        q.push(s);
        nodes[s].visited = true;
        nodes[s].distance = 0;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                previous[w].push_back(u);
            } else if (nodes[w].distance == nodes[u].distance + 1) {
                previous[w].push_back(u);
            }
        }
    }

    li all_min;
    int min_dist = INT_MAX;
    for(int d : destinations) {
        if(nodes[d].distance != -1 && nodes[d].distance < min_dist) {
            min_dist = nodes[d].distance;
        }
    }
    for(int d : destinations) {
        if(nodes[d].distance == min_dist) {
            all_min.push_back(d);
        }
    }

    list<li> paths;
    if(min_dist == INT_MAX) return paths;
    for(int d : all_min) {
        li path;
        path.push_back(d);
        paths.push_back(path);
    }
    for (int i = 0; i < min_dist; ++i) {
        list<li> new_paths;
        for (const auto& p : paths) {
            for (const auto& node : previous[p.front()]) {
                li new_path = p;
                new_path.push_front(node);
                new_paths.push_back(new_path);
            }
        }
        paths = new_paths;
    }
    return paths;
}

list<li> Graph::least_flights(vector<int> sources, vector<int> dest, set<string> &airlines_to_consider) {
    for (int j = 1; j <= n; ++j) {nodes[j].visited = false; nodes[j].distance = -1;}
    vector<vi> previous(n+1, vi());

    queue<int> q;
    for(const auto& s : sources) {
        q.push(s);
        nodes[s].visited = true;
        nodes[s].distance = 0;
    }

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& e : nodes[u].adj) {
            set<string> intersection;
            set_intersection(e.airlines.begin(), e.airlines.end(), airlines_to_consider.begin(), airlines_to_consider.end(), inserter(intersection, intersection.begin()));
            if (intersection.empty()) continue;
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                previous[w].push_back(u);
            } else if (nodes[w].distance == nodes[u].distance + 1) {
                previous[w].push_back(u);
            }
        }
    }

    li all_min;
    int min_dist = INT_MAX;
    for(int d : dest) {
        if(nodes[d].distance != -1 && nodes[d].distance < min_dist) {
            min_dist = nodes[d].distance;
        }
    }
    for(int d : dest) {
        if(nodes[d].distance == min_dist) {
            all_min.push_back(d);
        }
    }

    list<li> paths;
    if(min_dist == INT_MAX) return paths;
    for(int d : all_min) {
        li path;
        path.push_back(d);
        paths.push_back(path);
    }
    for (int i = 0; i < min_dist; ++i) {
        list<li> new_paths;
        for (const auto& p : paths) {
            for (const auto& node : previous[p.front()]) {
                li new_path = p;
                new_path.push_front(node);
                new_paths.push_back(new_path);
            }
        }
        paths = new_paths;
    }
    return paths;
}

int Graph::getOutDegree(int i) {
    return nodes[i].adj.size();
}

int Graph::getAirlinesNumber(int i) {
    set<string> airlines;
    for (const auto& e : nodes[i].adj)
        for (const auto& a : e.airlines)
            airlines.insert(a);

    return airlines.size();
}

int Graph::getDestinationsNumber(int i) {
    set<int> destinations;
    for (const auto& e : nodes[i].adj)
        destinations.insert(e.dest);

    return destinations.size();
}

int Graph::getDestinationsCountries(int i, unordered_map<int, Airport> &airports) {
    set<string> countries;
    for (const auto& e : nodes[i].adj)
        countries.insert(airports.at(e.dest).getCountry());

    return countries.size();
}

set<int> Graph::getDestinations(int src, int r) {
    set<int> destinations;
    for (int j = 1; j <= n; ++j) {nodes[j].visited = false; nodes[j].distance = -1;}
    queue<int> q;
    q.push(src);
    nodes[src].visited = true;
    nodes[src].distance = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                if (nodes[w].distance <= r) {
                    q.push(w);
                    destinations.insert(w);
                }
            }
        }
    }

    return destinations;
}

vector<Graph::Node> Graph::getNodes() const {
    return nodes;
}

int Graph::getNumEdges() {
    int num_edges = 0;
    for (int i = 1; i <= n; ++i)
        num_edges += (int) nodes[i].adj.size();

    return num_edges;
}

int Graph::getCompanies() {
    set<string> companies;
    for (int i = 1; i <= n; ++i)
        for (const auto& e : nodes[i].adj)
            for (const auto& c : e.airlines)
                companies.insert(c);

    return (int) companies.size();
}

int Graph::getDiameter() {
    int diameter = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {nodes[j].visited = false; nodes[j].distance = -1;}
        queue<int> q;
        q.push(i);
        nodes[i].visited = true;
        nodes[i].distance = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (const auto& e : nodes[u].adj) {
                int w = e.dest;
                if (!nodes[w].visited) {
                    q.push(w);
                    nodes[w].visited = true;
                    nodes[w].distance = nodes[u].distance + 1;
                    diameter = max(diameter, nodes[w].distance);
                }
            }
        }
    }

    return diameter;
}

//TODO
vector<pii> Graph::getTopAirports(int i) {
    vector<pii> airports(n);
    for (int v = 1; v <= n; v++) {
        airports[v-1] = make_pair(v, getDestinationsNumber(v));
    }
    sort(airports.begin(), airports.end(), [](const pii& a, const pii& b) {return a.second > b.second;});

    return vector<pii>(airports.begin(), airports.begin() + i);
}

set<int> Graph::articulationPointsDFS(int v, int index, vector<int>& num, vector<int>& low, unordered_set<int>& s, bool first){
    nodes[v].visited = true;
    num[v] = index;
    low[v] = index;
    index++;
    set<int> ap;
    bool is_ap = false;
    s.insert(v);
    int n_adj = 0;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited) {
            n_adj++;
            ap = articulationPointsDFS(w, index, num, low, s);
            low[v] = min(low[v], low[w]);
            if(low[w] >= num[v]) {
                is_ap = true;
                ap.insert(v);
            }
        }
        if(is_ap && first && n_adj <= 1)
            ap.erase(v);
        else if (s.find(w) != s.end())
            low[v] = min(low[v], num[w]);
    }
    s.erase(v);
    return ap;
}
set<int> Graph::getArticulationPoints() {
    set<int> articulationPoints;
    vector<int> low(n+1);
    vector<int> num(n+1);
    unordered_set<int> s;
    for(int i = 1; i <= n; i++)
        nodes[i].visited = false;
    for(int i = 1; i <= n; i++)
        if(!nodes[i].visited){
            set<int> temp = articulationPointsDFS(i, 0, num, low, s, true);
            for(int t : temp) articulationPoints.insert(t);
        }
    return articulationPoints;
}

set<int> Graph::articulationPointsDFS(int v, int index, vector<int>& num, vector<int>& low, unordered_set<int>& s, set<string> &airlines_to_consider, bool first){
    nodes[v].visited = true;
    num[v] = index;
    low[v] = index;
    index++;
    set<int> ap;
    bool is_ap = false;
    s.insert(v);
    int n_adj = 0;
    for (auto e : nodes[v].adj) {
        set<string> intersection;
        set_intersection(e.airlines.begin(), e.airlines.end(), airlines_to_consider.begin(), airlines_to_consider.end(), inserter(intersection, intersection.begin()));
        if (intersection.empty()) continue;

        int w = e.dest;
        if (!nodes[w].visited) {
            n_adj++;
            ap = articulationPointsDFS(w, index, num, low, s, airlines_to_consider);
            low[v] = min(low[v], low[w]);
            if(low[w] >= num[v]) {
                is_ap = true;
                ap.insert(v);
            }
        }
        if(is_ap && first && n_adj <= 1)
            ap.erase(v);
        else if (s.find(w) != s.end())
            low[v] = min(low[v], num[w]);
    }
    s.erase(v);
    return ap;
}
set<int> Graph::getArticulationPoints(set<string> &airlines_to_consider) {
    set<int> articulationPoints;
    vector<int> low(n+1);
    vector<int> num(n+1);
    unordered_set<int> s;
    for(int i = 1; i <= n; i++)
        nodes[i].visited = false;
    for(int i = 1; i <= n; i++)
        if(!nodes[i].visited){
            set<int> temp = articulationPointsDFS(i, 0, num, low, s, airlines_to_consider, true);
            for(int t : temp) articulationPoints.insert(t);
        }
    return articulationPoints;
}

