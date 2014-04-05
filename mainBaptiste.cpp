#include <stack>
#include <queue>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>

int idQuatre[4] = {0,2,1,3};


using namespace std;
pair<double, double> posNodes[12000];



#define forn(i, n) for (int i = 0; i < (n); ++i)
#define foreach(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)


int nbCar, nbNode, nbArc;
int idDep;
int tpsMax;
//int seuils[8] = {25005, 2317, 2499, 3148, 10458, 5181, 19567, 16095};
//10=>
//int seuils[8] = {1629, 2600, 4259, 2963, 10110, 4846, 8155, 17768};
//11 =>
int seuils[8] = {1614, 10237, 2918, 26303, 3386, 18005, 3761, 329};


//12
//int seuils[8] = {1676,15690,2591,37503,16640,12397,10695,3205};

int dists[18000], distsInit[18000];


double latCentre=posNodes[4516].first;
double longCentre=posNodes[4516].second;



int compAux(int node, int idRec, int tpsMis);
double compAuxRatio(int node, int idRec, int tpsMis);
int idTour = 0;
int idCar2;
int tpsLeft2;
int randTruc;


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
            if (idTour < seuils[idCar2]-20 || randTruc)// || randTruc)
                return (truc.tps > tpsLeft2 || (tps <= tpsLeft2 &&dists[id]+compAux(dest,0, tps) > dists[truc.id]+compAux(truc.dest, 0, truc.tps)));
            else
            {
                return (truc.tps > tpsLeft2 || (tps <= tpsLeft2 &&(double)dists[id]/(double)tps+compAuxRatio(dest, 0, tps) > (double)dists[truc.id]/(double)tps+compAuxRatio(truc.dest, 0, truc.tps)));
            }
        }
};


class Compare
{
public:
    inline bool operator() (s_edge a, s_edge b)
    {
        return a.tps> b.tps;
    }
};


int maxRecCompAux = 11;

vector<int> idArcAux(20);



vector<int> parcoursCar[8];
vector<s_edge> graph[12000];

vector<s_edge> graphTmp[12000];




void dijkstra(vector<int> &prev, vector<int> &disti, int source, int dest) {
    priority_queue<s_edge, vector<s_edge>, Compare> file;
    vector<bool> mark(18000, false);
    prev.assign(18000, -1);
    disti.assign(18000, 1e8);
    file.push(s_edge(source, 0, source, 0));
    while (not file.empty() && mark[dest] == false) {
        s_edge t = file.top(); file.pop();
        if (mark[t.dest]) continue;
        prev[t.dest] = t.dist;
        disti[t.dest] = t.tps; // distiance form source is now correct
        mark[t.dest] = true;
        forn(i, graphTmp[t.dest].size()) {
            s_edge f = graphTmp[t.dest][i];
            f.tps += t.tps;
            f.dist = t.dest;
            if (disti[f.dest] > f.tps) file.push(f);
        }
    }
}




int prevDistGoCar = 0, prevDistIdGoCar = 17999;
int goCar(int idCar, int node, int tpsLeft, int prevSize)
{
    randTruc = rand()%2;
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
    srand(17);
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
    cout << "8\n";
    for (int car = 0; car < nbCar; car++)
    {
        idCar2 = car;
        //        if (car == nbCar-1)
        //            maxRecCompAux = 12;

        if (idCar2 < 5)
        {
            vector<int> previ(18000), disti(180000);
            dijkstra(previ, disti, 4516, idQuatre[idCar2]);

            int cptt = 0;
            int machin = idQuatre[idCar2];
            stack<int> bidule;
            int tpsPris = 0;
            while (machin != 4516)
            {
                int prevMachin = machin;
                bidule.push(machin);
                machin = previ[machin];
                cptt++;
                for (int u = 0; u < graphTmp[machin].size(); u++)
                {
                    if (graphTmp[machin][u].dest == prevMachin)
                    {
                        tpsPris += graphTmp[machin][u].tps;
                        dists[graphTmp[machin][u].id] = 0;
                    }
                }
            }
            bidule.push(4516);

            prevDistIdGoCar = 17999;
            prevDistGoCar = 0;
            rep+=goCar(car, idQuatre[idCar2], tpsMax-tpsPris, 0);

            cout << parcoursCar[idCar2].size()+1+cptt << "\n";
            while (!bidule.empty())
            {
                cout << bidule.top() << '\n';
                bidule.pop();
            }

            for (auto x : parcoursCar[idCar2])
                cout << x << '\n';
            cerr << parcoursCar[idCar2].size() << endl;
        }

        else
        {
            prevDistIdGoCar = 17999;
            prevDistGoCar = 0;
            rep+=goCar(idCar2, idDep, tpsMax, 0);
            cerr << parcoursCar[idCar2].size() << endl;
            cout << parcoursCar[idCar2].size()+1 << "\n" << "4516\n";
            for (auto x : parcoursCar[idCar2])
                cout << x << '\n';
        }



    }


    cerr << rep << endl;


    return 0;
}




int compAux(int nodeA, int idRec, int tpsMis)
{
  
  if (idRec == maxRecCompAux)
        return 0;

    if (idCar2 == 0 && (posNodes[nodeA].first < latCentre || posNodes[nodeA].second < longCentre))
        return 0;
    if (idCar2 == 1 && (posNodes[nodeA].first > latCentre || posNodes[nodeA].second < longCentre))
        return 0;
    if (idCar2 == 2 && (posNodes[nodeA].first < latCentre || posNodes[nodeA].second > longCentre))
        return 0;
    if (idCar2 == 3 && (posNodes[nodeA].first > latCentre || posNodes[nodeA].second > longCentre))      
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
    }
    return maxi;
} 



