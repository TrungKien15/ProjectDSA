#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename) {
	ifstream ifs(filename);
	if (!ifs.is_open()) {
		cout << "Cannot open the input file"<<endl;
		return {};
	}
	string temp;
	ifs >> temp;
	int a = stoi(temp);
	vector<vector<int>> result;
	while (ifs>>temp) {
		int count = 0;
		vector<int> comp;
		if (temp == "1") {
			count++;
			comp.push_back(0);
		}
		for (int i = 1; i < a ; i++) {
			ifs >> temp;
			if (temp == "1") {
				count++;
				comp.push_back(i);
			}
		}	
		comp.insert(comp.begin(), count);
		result.push_back(comp);
	}
	return result;
}
vector<vector<int>> convertListToMatrix(const string& filename) {
	ifstream ifs(filename);
	if (!ifs.is_open()) {
		cout << "Cannot open the input file" << endl;
		return {};
	}
	vector<vector<int>> result;
	string temp;
	ifs >> temp;
	int a = stoi(temp);
	while (ifs >> temp) {
		int b = stoi(temp);
		vector<int> comp;
		for (int i = 0; i < a; i++) {
			comp.push_back(0);
		}
		for (int i = 0; i < b; i++) {
			ifs >> temp;
			int index = stoi(temp);
			comp[index] = 1;
		}
		result.push_back(comp);
	}
	return result;
}

bool isDirected(const vector<vector<int>>& adjMatrix) {
	for (int i = 0; i < adjMatrix.size(); i++) {
		for (int j = i+1; j < adjMatrix.size(); j++) {
			if (adjMatrix[i][j] != adjMatrix[j][i]) {
				return true;
			}
		}
	}
	return false ;
}
int countVertices(const vector<vector<int>>& adjMatrix) {
	return adjMatrix.size();
}
int countEdges(const vector<vector<int>>& adjMatrix) {
	int count = 0;
	for (int i = 0; i < adjMatrix.size(); i++) {
		for (int j = 0; j < adjMatrix.size(); j++) {
			if (adjMatrix[i][j] == 1) {
				count++;
			}
		}
	}
	if (isDirected(adjMatrix)) {
		return count;
	}
	else return count / 2;
}
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
	vector<int>result;
	for (int i = 0; i < adjMatrix.size(); i++) {
		bool isolated = true;
		for (int j = 0; j < adjMatrix.size(); j++) {
			if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1) {
				isolated = false;
				break;
			}
		}
		if (isolated) {
			result.push_back(i);
		}
	}
	return result;
}
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
	for (int i = 0; i < adjMatrix.size(); i++) {
		for (int j = i+1; j < adjMatrix.size(); j++) {
			if (adjMatrix[i][j] != 1 || adjMatrix[j][i] != 1) {
				return false;
			}
		}
	}
	return true;
}
bool isBipartite(const std::vector<std::vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1); 
	for (int start = 0; start < n; start++) {
		if (color[start] == -1) { 
			color[start] = 0; 
			vector<int> temp;
			temp.push_back(start);
			while (!temp.empty()) {
				int u = temp.back();
				temp.pop_back();
				for (int v = 0; v < n; v++) {
					if (adjMatrix[u][v] == 1) { 
						if (color[v] == -1) { 
							color[v] = 1 - color[u]; 
							temp.push_back(v);
						}
						else if (color[v] == color[u]) { 
							return false; 
						}
					}
				}
			}
		}
	}
	return true; 
}
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1);
	vector<int> U, V;

	for (int start = 0; start < n; start++) {
		if (color[start] == -1) {
			color[start] = 0;
			vector<int> temp = { start };
			while (!temp.empty()) {
				int u = temp.back(); temp.pop_back();
				for (int v = 0; v < n; v++) {
					if (adjMatrix[u][v]) {
						if (color[v] == -1) {
							color[v] = 1 - color[u];
							temp.push_back(v);
						}
						else if (color[v] == color[u]) {
							return false; 
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		if (color[i] == 0) {
			U.push_back(i);
		}
		else if (color[i] == 1) {
			V.push_back(i);
		}
	}

	for (int u : U) {
		for (int v : V) {
			if (adjMatrix[u][v] != 1 || adjMatrix[v][u] != 1) {
				return false;
			}
		}
	}

	for (int i : U) {
		for (int j : U) {
			if (i != j && adjMatrix[i][j]) {
				return false;
			}
		}
	}

	for (int i : V) {
		for (int j : V) {
			if (i != j && adjMatrix[i][j]) {
				return false;
			}
			return true;
		}
	}
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> undirectedGraph(adjMatrix.size(), vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1) {
				undirectedGraph[i][j] = 1;
				undirectedGraph[j][i] = 1;
			}
		}
	}
	return undirectedGraph;
}
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
	vector<vector<int>> complementGraph(adjMatrix.size(), vector<int>(adjMatrix.size(), 0));
	for (int i = 0; i < adjMatrix.size(); i++) {
		for (int j = 0; j < adjMatrix.size(); j++) {
			if (i != j && adjMatrix[i][j] == 0) {
				complementGraph[i][j] = 1;
			}
		}
	}
	return complementGraph;
}
void dfsEuler(int v, vector<vector<int>>& graph, vector<int>& circuit, bool directed) {
	for (int u = 0; u < graph.size(); ++u) {
		while (graph[v][u] > 0) {
			graph[v][u]--;
			if (!directed) graph[u][v]--;
			dfsEuler(u, graph, circuit, directed);
		}
	}
	circuit.push_back(v);
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> graph = adjMatrix;
	vector<int> degree(n, 0);
	bool directed = isDirected(adjMatrix);


	if (!directed) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				degree[i] += graph[i][j];
			}
			if (degree[i] % 2 != 0) return {};
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			int inDeg = 0, outDeg = 0;
			for (int j = 0; j < n; j++) {
				outDeg += graph[i][j];
				inDeg += graph[j][i];
			}
			if (inDeg != outDeg) return {};
		}
	}

	vector<int> circuit;
	dfsEuler(0, graph, circuit, directed);
	reverse(circuit.begin(), circuit.end());
	return circuit;
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	vector<vector<int>> spanningTree(adjMatrix.size(), vector<int>(adjMatrix.size(), 0));
	vector<bool> visited(adjMatrix.size(), false);
	vector<int> stack;
	stack.push_back(start);
	visited[start] = true;

	while (!stack.empty()) {
		int v = stack.back();
		stack.pop_back();
		for (int u = 0; u < adjMatrix.size(); u++) {
			if (adjMatrix[v][u] == 1 && !visited[u]) {
				spanningTree[v][u] = 1;
				spanningTree[u][v] = 1;
				visited[u] = true;
				stack.push_back(u);
			}
		}
	}
	return spanningTree;
}
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	vector<vector<int>> spanningTree(adjMatrix.size(), vector<int>(adjMatrix.size(), 0));
	vector<bool> visited(adjMatrix.size(), false);
	vector<int> queue;
	queue.push_back(start);
	visited[start] = true;

	while (!queue.empty()) {
		int v = queue.front();
		queue.erase(queue.begin());
		for (int u = 0; u < adjMatrix.size(); u++) {
			if (adjMatrix[v][u] == 1 && !visited[u]) {
				spanningTree[v][u] = 1;
				spanningTree[u][v] = 1;
				visited[u] = true;
				queue.push_back(u);
			}
		}
	}
	return spanningTree;
}
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	vector<int> stack;
	stack.push_back(u);
	visited[u] = true;

	while (!stack.empty()) {
		int current = stack.back();
		stack.pop_back();
		if (current == v) {
			return true;
		}
		for (int i = 0; i < n; i++) {
			if (adjMatrix[current][i] == 1 && !visited[i]) {
				visited[i] = true;
				stack.push_back(i);
			}
		}
	}
	return false;
}
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> dist(n, INT_MAX);
	vector<int> prev(n, -1);
	vector<bool> visited(n, false);
	dist[start] = 0;

	for (int i = 0; i < n; i++) {
		int u = -1;
		for (int j = 0; j < n; j++) {
			if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
				u = j;
			}
		}
		if (dist[u] == INT_MAX) break;
		visited[u] = true;

		for (int v = 0; v < n; v++) {
			if (adjMatrix[u][v] == 1 && !visited[v]) {
				int alt = dist[u] + 1; 
				if (alt < dist[v]) {
					dist[v] = alt;
					prev[v] = u;
				}
			}
		}
	}

	vector<int> result;
	for (int at = end; at != -1; at = prev[at]) {
		result.push_back(at);
	}
	reverse(result.begin(), result.end());
	return result;
}
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> dist(n, INT_MAX);
	vector<int> prev(n, -1);
	dist[start] = 0;

	for (int i = 0; i < n - 1; i++) {
		for (int u = 0; u < n; u++) {
			for (int v = 0; v < n; v++) {
				if (adjMatrix[u][v] == 1) {
					if (dist[u] != INT_MAX && dist[u] + 1 < dist[v]) {
						dist[v] = dist[u] + 1;
						prev[v] = u;
					}
				}
			}
		}
	}
	vector<int> result;
	for (int at = end; at != -1; at = prev[at]) {
		result.push_back(at);
	}
	reverse(result.begin(), result.end());
	return result;
}
