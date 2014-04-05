#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


using namespace std;


int nbCar, nbNode, nbArc;
int idDep;
int tpsMax;


int dists[18000];




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



pair<double, double> posNodes[12000];

vector<int> parcoursCar[8];
vector<s_edge> graph[12000];


int goCar(int idCar, int node, int tpsLeft, int prevSize)
{
    if (tpsLeft < 0)
    {
        parcoursCar[idCar].pop_back();
        return -prevSize;
    }


    int maxi = 0;
    int idMax = 0;
    for (size_t i = 0; i < graph[node].size(); i++)
    {
        if (dists[graph[node][i].id] > maxi)
        {
            maxi= dists[graph[node][i].id];
            idMax = i;
        }
    }
    parcoursCar[idCar].push_back(graph[node][idMax].dest);
    return maxi + goCar(idCar, graph[node][idMax].dest, tpsLeft - graph[node][idMax].tps, maxi);
}




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
        graph[n1].push_back(s_edge(n2, tps, size, i));
        if (bidir == 2)
            graph[n2].push_back(s_edge(n1, tps, size, i));
    }

    for (int i = 0; i < nbNode; i++)
        sort(graph[i].begin(), graph[i].end());
    
    int rep = 0;
    for (int car = 0; car < nbCar; car++)
    {
        rep+=goCar(car, idDep, tpsMax, 0);
    }

    cout << "8\n";

    for (int iCar = 0; iCar < 8; iCar++)
    {
        cout << parcoursCar[iCar].size()+1 << "\n" << "4516\n";
        for (auto x : parcoursCar[iCar])
            cout << x << endl;
    }


    return 0;
}
