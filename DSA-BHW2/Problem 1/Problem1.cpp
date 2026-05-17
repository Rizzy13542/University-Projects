#include <iostream>
#include <string>

using namespace std;

const int infinite = 999999;

struct RoadData {
    int time;
    int risk;
    int energy;
};

struct PathResult {
    bool found;
    int time;
    int energy;
    int len;
    int path[100];
};

template<typename TNode, typename TEdge>
class Graph {
public:
    int N;
    char **matrix;
    TNode *nodes;
    TEdge **edges;

    Graph(int size) {
        N = size;
        matrix = new char*[N];
        nodes = new TNode[N];
        edges = new TEdge*[N];
        for (int i = 0; i < N; i++) {
            matrix[i] = new char[N];
            edges[i] = new TEdge[N];
            for (int j = 0; j < N; j++) {
                matrix[i][j] = 0;
            }
        }
    }

    void setNode(int i, TNode info) { 
        nodes[i] = info; 
    }
    
    TNode getNode(int i) { 
        return nodes[i]; 
    }
    
    void addEdge(int i, int j) { 
        matrix[i][j] = 1; 
    }
    
    void setEdge(int i, int j, TEdge info) { 
        edges[i][j] = info; 
    }
    
    TEdge getEdge(int i, int j) { 
        return edges[i][j]; 
    }

    ~Graph() {
        for (int i = 0; i < N; i++) { 
            delete[] matrix[i]; 
            delete[] edges[i]; 
        }
        delete[] matrix; 
        delete[] edges; 
        delete[] nodes;
    }
};

Graph<string, RoadData>* network;
char* visited;

int stations[100], stationCount;
int criticals[100], criticalCount;
string robotStart[100]; 
int robotAutonomy[100]; 
int robotRisk[100]; 
int robotCount;
string queryBase;

int getNodeIndex(string name) {
    for (int i = 0; i < network->N; i++) {
        if (network->getNode(i) == name) {
            return i;
        }
    }
    return -1;
}

void dfsUndirected(int x) {
    visited[x] = 1;
    for (int y = 0; y < network->N; y++) {
        if ((network->matrix[x][y] || network->matrix[y][x]) && !visited[y]) {
            dfsUndirected(y);
        }
    }
}

void dfsDirected(int x) {
    visited[x] = 1;
    for (int y = 0; y < network->N; y++) {
        if (network->matrix[x][y] && !visited[y]) {
            dfsDirected(y);
        }
    }
}

PathResult bestPath;
int currentPath[100];

void findPaths(int u, int target, int maxRisk, int remEnergy, int currTime, int currEnergy, int depth) {
    currentPath[depth] = u;
    if (u == target) {
        bool update = !bestPath.found || currTime < bestPath.time || (currTime == bestPath.time && currEnergy < bestPath.energy);
        if (update) {
            bestPath.found = true;
            bestPath.time = currTime; 
            bestPath.energy = currEnergy; 
            bestPath.len = depth + 1;
            for (int i = 0; i <= depth; i++) {
                bestPath.path[i] = currentPath[i];
            }
        }
        return;
    }
    visited[u] = 1;
    for (int v = 0; v < network->N; v++) {
        if (network->matrix[u][v] && !visited[v]) {
            RoadData edge = network->getEdge(u, v);
            if (edge.risk <= maxRisk) {
                findPaths(v, target, maxRisk, remEnergy - edge.energy, currTime + edge.time, currEnergy + edge.energy, depth + 1);
            }
        }
    }
    visited[u] = 0;
}

PathResult getBestPath(int start, int target, int maxRisk, int autonomy) {
    bestPath.found = false;
    for (int i = 0; i < network->N; i++) {
        visited[i] = 0;
    }
    findPaths(start, target, maxRisk, autonomy, 0, 0, 0);
    return bestPath;
}

bool readInput() {
    int N, M;
    if (!(cin >> N >> M)) return false;
    
    network = new Graph<string, RoadData>(N);
    visited = new char[N];

    for (int i = 0; i < N; i++) {
        string name;
        cin >> name;
        network->setNode(i, name);
    }
    for (int i = 0; i < M; i++) {
        string uName, vName; 
        int t, r, e;
        cin >> uName >> vName >> t >> r >> e;
        int u = getNodeIndex(uName);
        int v = getNodeIndex(vName);
        network->addEdge(u, v);
        network->setEdge(u, v, {t, r, e});
    }
    cin >> stationCount;
    for (int i = 0; i < stationCount; i++) {
        string name;
        cin >> name;
        stations[i] = getNodeIndex(name);
    }
    cin >> criticalCount;
    for (int i = 0; i < criticalCount; i++) {
        string name;
        cin >> name;
        criticals[i] = getNodeIndex(name);
    }
    cin >> robotCount;
    for (int i = 0; i < robotCount; i++) {
        cin >> robotStart[i] >> robotAutonomy[i] >> robotRisk[i];
    }
    cin >> queryBase;
    return true;
}

void process() {
    cout << "Most exposed area(s):" << endl << endl;
    int maxIn = -1;
    int inCounts[100] = {0};
    for (int j = 0; j < network->N; j++) {
        for (int i = 0; i < network->N; i++) {
            if (network->matrix[i][j]) {
                inCounts[j]++;
            }
        }
        if (inCounts[j] > maxIn) {
            maxIn = inCounts[j];
        }
    }
    for (int i = 0; i < network->N; i++) {
        if (inCounts[i] == maxIn) {
            cout << network->getNode(i) << " with " << maxIn << " incoming roads" << endl;
        }
    }

    for (int i = 0; i < network->N; i++) {
        visited[i] = 0;
    }
    int comps = 0;
    for (int i = 0; i < network->N; i++) {
        if (!visited[i]) { 
            comps++; 
            dfsUndirected(i); 
        }
    }
    if (comps == 1) {
        cout << "The network is valid when road directions are ignored." << endl << endl;
    }
    
    cout << "Blocked areas:" << endl;
    bool blocked = false;
    for (int i = 0; i < network->N; i++) {
        int in = 0, out = 0;
        for (int j = 0; j < network->N; j++) {
            if (network->matrix[j][i]) in++;
            if (network->matrix[i][j]) out++;
        }
        if (in > 0 && out == 0) {
            cout << network->getNode(i) << " is blocked." << endl;
            blocked = true; 
        }
    }
    if (!blocked) {
        cout << "No blocked areas detected." << endl << endl;
    }
    
    for (int i = 0; i < network->N; i++) {
        visited[i] = 0;
    }
    dfsDirected(getNodeIndex(queryBase));
    bool allReach = true;
    for (int i = 0; i < network->N; i++) {
        if (!visited[i]) {
            if (allReach) {
                cout << "From base " << queryBase << ", following areas cannot be reached: ";
            }
            cout << network->getNode(i) << " ";
            allReach = false;
        }
    }
    if (allReach) {
        cout << "From base " << queryBase << ", all areas are reachable." << endl << endl;
    }
    
    for (int r = 0; r < robotCount; r++) {
        int start = getNodeIndex(robotStart[r]);
        int autoN = robotAutonomy[r];
        int risk = robotRisk[r];

        cout << "Robot " << r + 1 << ":" << endl << endl;
        cout << "Initial position: " << robotStart[r] << endl;
        cout << "Autonomy: " << autoN << endl;
        cout << "Maximum accepted risk: " << risk << endl;

        PathResult bestDirect = {false, infinite, infinite, 0};
        int reachedCrit = -1;

        for (int i = 0; i < criticalCount; i++) {
            PathResult res = getBestPath(start, criticals[i], risk, autoN);
            if (res.found) {
                bool optimize = (res.time < bestDirect.time) || (res.time == bestDirect.time && res.energy < bestDirect.energy);
                if (optimize) {
                    bestDirect = res;
                    reachedCrit = criticals[i];
                }
            }
        }

        if (bestDirect.found) {
            cout << "Optimal direct path to a critical zone:" << endl;
            for (int i = 0; i < bestDirect.len; i++) {
                cout << network->getNode(bestDirect.path[i]) << (i == bestDirect.len - 1 ? "" : " -> ");
            }
            cout << endl;
            cout << "Total travel time: " << bestDirect.time << endl;
            cout << "Energy consumed: " << bestDirect.energy << endl;
            cout << "Critical zone reached: " << network->getNode(reachedCrit) << endl;
        } else {
            cout << "No valid direct path to a critical zone." << endl;
            cout << "No valid solution even with recharge." << endl;
        }
        cout << endl;
    }
}

int main() {
    if (readInput()) {
        process();
    }
    delete network;
    delete[] visited;
    return 0;
}