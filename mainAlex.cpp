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
    int id;

    s_edge(){}
    s_edge(int u, int v, int w, int z)
    {
        dest = u;
        tps = v;
        dist = w;
        id = z;
    }

    bool operator < (const s_edge& truc) const
    {
        return (dists[id] > dists[truc.id]);
    }
};


int dists[18000];

pair<double, double> posNodes[12000];

vector<int> parcoursCar[8];
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
        dists[i] = size;
        graph[n1].push_back(s_edge(n2, tps, size));
        if (bidir == 2)
            graph[n2].push_back(s_edge(n1, tps, size));
    }

    for (int i = 0; i < nbNode; i++)
        sort(graph[i].begin(), graph[i].end());
    

    for (int car = 0; car < nbCar; car++)
    {
        goCar(car, 0, tpsMax);

    return 0;
}
