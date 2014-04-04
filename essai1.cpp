#include <iostream>
#include <algorithm>


using namespace std;

int rep;
int N,M;
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {0, 1, -1, 1, -1, 0, 1, -1};


int main(void)
{
    char map[716][1522];
    cin >> N >> M;

    for (int i = 0; i < N; i++)
        cin >> map[i];


    map<pair<int, int>, int> carres;
    for (int l = 0; l < N; l++)
        for (int c = 0; c < M; c++)
            if (map[i][j] == '#')
                carres.insert(make_pair(l,c),1);

    bool aFusionne = true;
    while (aFusionne)
    {
        aFusionne = false;
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            pair<int, int> pos = it->first;
            int size = it->second;

            pair<int, int> vois[8];
            for (int i = 0; i < 8; i++)
            {
                vois[i].first = pos.first+2*size*dy[i];
                vois[i].second = pos.first+2*size*dx[i];
            
