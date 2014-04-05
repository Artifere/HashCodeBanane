#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


using namespace std;


int nbCar, nbNode, nbArc;
int idDep;
int tpsMax;


int dists[18000], distsInit[18000];



int compAux(int node, int idRec);

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

        inline bool operator < (const s_edge& truc) const
        {
//            cerr << dest << "vs" << truc.dest << endl;
            //return (dists[id] > dists[truc.id]);
            return dists[id]+compAux(dest, 0) > dists[truc.id]+compAux(truc.dest, 0);
        }
};

const int maxRecCompAux = 2;
vector<int> idArcAux(20);



pair<double, double> posNodes[12000];

vector<int> parcoursCar[8];
vector<s_edge> graph[12000], graphTmp[12000];

int prevDistGoCar = 0, prevDistIdGoCar = 17999;
int goCar(int idCar, int node, int tpsLeft, int prevSize)
{
    if (tpsLeft < 0)
    {
        parcoursCar[idCar].pop_back();
        dists[prevDistIdGoCar] = prevDistGoCar;
        return -prevSize;

    }

    sort(graph[node].begin(), graph[node].end());


    int maxi = -1;
 //   int idMax = 0;
    int idArcMax = -1, idDestMax = 0, valTpsMax = 0;
    for (size_t i = 0; i < 1; i++)//graph[node].size(); i++)
    {
        if (dists[graph[node][i].id] > maxi)
        {
            idArcMax = graph[node][i].id;
            idDestMax = graph[node][i].dest;
            valTpsMax = graph[node][i].tps;
            maxi= dists[idArcMax];
//            idMax = i;
        }
    }
    if (idArcMax == -1)
        return 0;
    dists[idArcMax] = 0;
    parcoursCar[idCar].push_back(idDestMax);
    prevDistIdGoCar = idArcMax;
    prevDistGoCar = maxi;
    return maxi + goCar(idCar, idDestMax, tpsLeft - valTpsMax, maxi);

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
        distsInit[i] = size;
        graph[n1].push_back(s_edge(n2, tps, size, i));
        if (bidir == 2)
            graph[n2].push_back(s_edge(n1, tps, size, i));
    }
    
    for (int i = 0; i < nbNode; i++)
        graphTmp[i] = graph[i];
    for (int i = 0; i < nbNode; i++)
        sort(graph[i].begin(), graph[i].end());

    int rep = 0;
    for (int car = 0; car < nbCar; car++)
    {
        prevDistIdGoCar = 17999;
        prevDistGoCar = 0;
        rep+=goCar(car, idDep, tpsMax, 0);
    }

    cout << "8\n";

    for (int iCar = 0; iCar < 8; iCar++)
    {
        cout << parcoursCar[iCar].size()+1 << "\n" << "4516\n";
        for (auto x : parcoursCar[iCar])
            cout << x << endl;
    }
    cerr << rep << endl;


    return 0;
}




int compAux(int nodeA, int idRec)
{
    if (idRec == maxRecCompAux)
        return 0;

    int maxi = -1;
    for (size_t i = 0; i < graphTmp[nodeA].size(); i++)
    {
        int idArc = graphTmp[nodeA][i].id, idDest = graphTmp[nodeA][i].dest;
        int prevDist = dists[idArc];
        dists[idArc] = 0;
        int tmp = prevDist + compAux(idDest, idRec+1);
        dists[idArc] = prevDist;
        maxi = max(tmp, maxi);
        /*if (tmp > maxi)
        {
            idArcMax = graph[node][i].id;
            idDestMax = graph[node][i].dest;
            maxi= dists[idArcMax];
            idMax = i;
        }*/
    }
    return maxi;
} 



