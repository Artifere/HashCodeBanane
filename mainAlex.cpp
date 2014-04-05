#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


using namespace std;


int nbCar, nbNode, nbArc;
int idDep;
int tpsMax;
//int seuils[8] = {25005, 2317, 2499, 3148, 10458, 5181, 19567, 16095};

int seuils[8] = {1629, 2600, 4259, 2963, 10110, 4846, 8155, 17768};

int dists[18000], distsInit[18000];



int compAux(int node, int idRec, int tpsMis);
double compAuxRatio(int node, int idRec, int tpsMis);
int idTour = 0;
int idCar2;
int tpsLeft2;



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
            if (true)//idTour < seuils[idCar2]-3)
                return (truc.tps > tpsLeft2 || (tps <= tpsLeft2 &&dists[id]+compAux(dest,0, tps) > dists[truc.id]+compAux(truc.dest, 0, truc.tps)));
            else
            {
                return (truc.tps > tpsLeft2 || (tps <= tpsLeft2 &&(double)dists[id]/(double)tps+compAuxRatio(dest, 0, tps) > (double)dists[truc.id]/(double)tps+compAuxRatio(truc.dest, 0, truc.tps)));
            }
        }
};

const int maxRecCompAux = 11;
vector<int> idArcAux(20);


pair<double, double> posNodes[12000];

vector<int> parcoursCar[8];
vector<s_edge> graph[12000];

vector<s_edge> graphTmp[12000];

int prevDistGoCar = 0, prevDistIdGoCar = 17999;
int goCar(int idCar, int node, int tpsLeft, int prevSize)
{
    if (tpsLeft < 0)
    {
        parcoursCar[idCar].pop_back();
        dists[prevDistIdGoCar] = prevDistGoCar;
        return -prevSize;

    }
    tpsLeft2 = tpsLeft;
    idTour++;

    sort(graph[node].begin(), graph[node].end());


    int maxi = -1;
    //   int idMax = 0;
    int idArcMax = -1, idDestMax = 0, valTpsMax = 0;
    //    const int nbVois = graph[node].size();
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
    const int total = maxi + goCar(idCar, idDestMax, tpsLeft - valTpsMax, maxi);
    idTour--;
    return total;

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
        idCar2 = car;
        prevDistIdGoCar = 17999;
        prevDistGoCar = 0;
        rep+=goCar(car, idDep, tpsMax, 0);
    }

    cout << "8\n";

    for (int iCar = 0; iCar < 8; iCar++)
    {
        cerr << parcoursCar[iCar].size() << endl;
        cout << parcoursCar[iCar].size()+1 << "\n" << "4516\n";
        for (auto x : parcoursCar[iCar])
          cout << x << '\n';
    }
    cerr << rep << endl;


    return 0;
}




int compAux(int nodeA, int idRec, int tpsMis)
{
    if (idRec == maxRecCompAux)
        return 0;

    int maxi = -1;
    const size_t nbVois = graphTmp[nodeA].size();
    for (size_t i = 0; i < nbVois; i++)
    {
        int curTps = graphTmp[nodeA][i].tps;
        if (tpsMis + curTps > tpsLeft2)
            continue;
        int idArc = graphTmp[nodeA][i].id, idDest = graphTmp[nodeA][i].dest;
        int prevDist = dists[idArc];
        dists[idArc] = 0;
        int tmp = prevDist + compAux(idDest, idRec+1, tpsMis+curTps);
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



double compAuxRatio(int nodeA, int idRec, int tpsMis)
{
    if (idRec == maxRecCompAux)
        return 0;

    int maxi = -1;
    const size_t nbVois = graphTmp[nodeA].size();
    for (size_t i = 0; i < nbVois; i++)
    {
        if (tpsMis + graphTmp[nodeA][i].tps > tpsLeft2)
            continue;
        int idArc = graphTmp[nodeA][i].id, idDest = graphTmp[nodeA][i].dest;
        int prevDist = dists[idArc];
        dists[idArc] = 0;
        int tmp = (double)prevDist/(double)graphTmp[nodeA][i].tps + compAuxRatio(idDest, idRec+1, tpsMis + graphTmp[nodeA][i].tps);
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



