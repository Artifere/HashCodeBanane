#include <iostream>


using namespace std;


int nbCar, nbNode, nbArc;
int idDep;
int tpsMax;

pair<double, double> posNodes[100000];


vector<vector<int> > graph;


int main(void)
{
    cin >> nbNode >> nbArc >> tpsMax >> nbCar >> idDep;

    for (int i = 0; i < nbNode; i++)
        cin >> posNodes[i].first >> posNodes[i].second;


    return 0;
}
