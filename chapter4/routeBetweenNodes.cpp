#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
using namespace std;

struct node
{
	bool visited;
	int name;
	vector<int> neighbours; 

	node(const int& n, const vector<int>& nb): visited(false), name(n), neighbours(nb){}

	void visit()
	{
		visited=true;
	}
};

void graphSummary(const vector<node*>& g)
{
	cout << "======Graph Summary======" << endl;
	for(auto i = 0; i < g.size(); ++i)
	{
		cout 
		<< "node name: " << left << setw(5) << g[i]->name 
		<< "visited: " << left << setw(5) << ((g[i]->visited)?"YES":"NO")
		<< "neighbours: ";
		for(auto item : g[i]->neighbours)
		{
			cout << item << " ";
		}
		cout << endl;
	}
}

vector<node*> createGraph(const vector<vector<bool>>& am)
{
	vector<node*> my_graph;

	int n_node = am.size();
	for(int i = 0; i < n_node; ++i)
	{
		vector<int> cnb;
		for(int j = 0; j < n_node; ++j)
		{
			if(am[i][j])
			{
				cnb.push_back(j);
			}
		}
		my_graph.push_back(new node(i, cnb));
	}

	return my_graph;
}

bool dfs_route(vector<node*>& graph, const int& n1, const int& n2)
{
	// return if there's a route from n1 to n2
	graph[n1]->visit();

	for(auto i = 0; i < graph[n1]->neighbours.size(); ++i)
	{
		if(graph[n1]->neighbours[i] == n2)
		{
			graph[n2]->visit();
			return true;
		}

		if(not graph[graph[n1]->neighbours[i]]->visited)
		{
			graph[graph[n1]->neighbours[i]]->visit();
			return dfs_route(graph, graph[n1]->neighbours[i], n2);
		}
	}

	return false;
}

bool bfs_route(vector<node*>& graph, const int& n1, const int& n2)
{
	if(n1 == n2)
	{
		return true;
	}

	queue<int> todo;
	todo.push(n1);
	graph[n1]->visit();

	while(not todo.empty())
	{
		auto curr_node = todo.front();
		todo.pop();

		for(int i = 0; i < graph[curr_node]->neighbours.size(); ++i)
		{
			if(graph[curr_node]->neighbours[i] == n2)
			{
				graph[n2]->visit();
				return true;
			}

			if(not graph[graph[curr_node]->neighbours[i]]->visited)
			{
				graph[graph[curr_node]->neighbours[i]]->visit();
				todo.push(graph[curr_node]->neighbours[i]);
			}
		}
	}

	return false;
}

int main()
{
	vector<vector<bool>> m=
	{
		{0,1,0,0,1,1},
		{0,0,0,1,1,0},
		{0,1,0,0,0,0},
		{0,0,1,0,1,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
	};

	auto g = createGraph(m);
	auto g2 = createGraph(m);

	cout << dfs_route(g, 0, 3) << endl;

	graphSummary(g);

	cout << bfs_route(g2, 0, 3) << endl;

	graphSummary(g2);

	return 0;
}