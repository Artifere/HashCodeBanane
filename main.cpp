#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


using namespace std;


int nbCar, nbNode, nbArc;
int idDep;
int tpsMax;

class s_edge
{
    public:
    int dest;
    int tps, dist;

    s_edge(){}
    s_edge(int u, int v, int w)
    {
        dest = u;
        tps = v;
        dist = w;
    }
};

pair<double, double> posNodes[12000];


vector<s_edge> graph[12000];


int main(void)
{
    cin >> nbNode >> nbArc >> tpsMax >> nbCar >> idDep;

    for (int i = 0; i < nbNode; i++)
        cin >> posNodes[i].first >> posNodes[i].second;
    
    for (int i = 0; i < nbArc; i++)
    {
        int n1, n2, bidir, tps, size;
        cin >> n1 >> n2 >> bidir >> tps >> size;

        graph[n1].push_back(s_edge(n2, tps, size));
        if (bidir == 2)
            graph[n2].push_back(s_edge(n1, tps, size));
    }

    return 0;
}
