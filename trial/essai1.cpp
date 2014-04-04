#include <iostream>
#include <algorithm>
#include <utility>
#include <map>
#include <cstdlib>
#include <time.h>
#include <set>

using namespace std;

int rep;
int N,M;
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {0, 1, -1, 1, -1, 0, 1, -1};

bool peutPasFaire[1000][2000];
map<pair<int, int>, int> carres;
set<pair<int, int> > reset;
inline bool findBis(pair<int, int> a, int b)
{
    auto it = carres.find(a);
    return (it != carres.end() && it->second == b);
}


int main(void)
{
    char carte[716][1522];
    cin >> N >> M;

    for (int i = 0; i < N; i++)
        cin >> carte[i];


    for (int l = 0; l < N; l++)
        for (int c = 0; c < M; c++)
            if (carte[l][c] == '#')
                carres.insert(make_pair(make_pair(l,c),0));
    bool doAgain = true;

    while (doAgain)
    {
        doAgain = false;
        for (auto it = carres.end(); it != carres.begin(); --it)
        {
            pair<int, int> pos = it->first;
            //cout << "MA POS = " << pos.first << "," << pos.second << endl;
            int size = it->second;

            pair<int, int> vois[8];
            for (int i = 0; i < 8; i++)
            {
                vois[i].first = pos.first+max(1,2*size)*dy[i];
                vois[i].second = pos.second+max(1,2*size)*dx[i];
            }
            bool exists[8] = {false, false, false, false, false, false, false, false};

            int cpt = 0;
            for (int i = 0; i < 8; i++)
            {
                //      cout << "cool pos = " << vois[i].first << "," << vois[i].second << endl;
                if (findBis(make_pair(vois[i].first, vois[i].second), size))
                {
                    cpt++;
                    exists[i] = true;
                }
            }
            //cout << "pos = " << it->first.first << ',' << it->first.second << "==>" << cpt << endl << endl;
            if (exists[0] && exists[1] && exists[2] && exists[3] && exists[4] && exists[5] && exists[6] &&
                    exists[7])
            {
                //cout << "lil" << endl;
                for (int i = 0; i < 8; i++)
                    carres.erase(make_pair(vois[i].first, vois[i].second));
                carres.erase(pos);
                carres.insert(make_pair(pos, max(1,3*size)));
                //             it = carres.begin();
                doAgain = true;
            }

        }
    }

    doAgain = true;
    while (doAgain)
    {
        doAgain = false;
        //for (auto it = carres.begin(); it != carres.end(); ++it)
        for (int lin = 0; lin < N; lin++)
        {
            for (int col = 0; col < M; col++)
            {

                if (peutPasFaire[lin][col])
                {
                    int size  = 0;
                    pair<int, int> vois[8];
                pair<int, int> pos = make_pair(lin, col);
                for (int i = 0; i < 8; i++)
                {
                    vois[i].first = pos.first+max(1,2*size)*dy[i];
                    vois[i].second = pos.second+max(1,2*size)*dx[i];
                }
                for (int i = 0; i < 8; i++)
                        if (vois[i].first >= 0 && vois[i].second >= 0)
                            peutPasFaire[vois[i].first][vois[i].second] = true;
                    
                    continue;
                }
                pair<int, int> pos = make_pair(lin, col);
                //         cout << carres.size()<< endl;
                //cout << "MA POS = " << pos.first << "," << pos.second << endl;
                int size = 0;
                if (size > 0)
                    continue;
                //            cout << "==>" << size << endl;
                pair<int, int> vois[8];
                for (int i = 0; i < 8; i++)
                {
                    vois[i].first = pos.first+max(1,2*size)*dy[i];
                    vois[i].second = pos.second+max(1,2*size)*dx[i];
                }
                bool exists[8] = {false, false, false, false, false, false, false, false};

                int cpt = 0;
                if(findBis(pos, 0))
                    cpt++;
                for (int i = 0; i < 8; i++)
                {
                    if (findBis(make_pair(vois[i].first, vois[i].second), size))
                    {
                        cpt++;
                        exists[i] = true;
                    }
                }
                //            cout << cpt << endl;
                if (9 <= 2*cpt)
                {
                    for (int i = 0; i < 8; i++)
                        if (vois[i].first >= 0 && vois[i].second >= 0)
                            peutPasFaire[vois[i].first][vois[i].second] = true;
                    //       doAgain = true;
                    for (int i = 0; i < 8; i++)
                    {
                        //      cout << "cool pos = " << vois[i].first << "," << vois[i].second << endl;
                        if (exists[i] == false)
                            reset.insert(vois[i]);
                        else
                            carres.erase(vois[i]);
                    }
                    if (findBis(pos, 0))
                        carres.erase(pos);
                    else
                        reset.insert(pos);
                    //                cout << cpt << endl;
                    //              cout << pos.first << "," << pos.second << endl;
                    carres.insert(make_pair(pos, 1));
                    //                cout << "lol" << endl;
                    //it = carres.begin();
                }

            }
            //      cout << "fin" << endl;
        }
    }
    cout << carres.size() << endl;

    vector<pair<pair<int, int>, int> > trucAShuffle;
    copy(carres.begin(), carres.end(), back_inserter(trucAShuffle));
    random_shuffle(trucAShuffle.begin(), trucAShuffle.end());
    for (auto it = trucAShuffle.begin(); it != trucAShuffle.end(); ++it)
    {
        if (it-> second > 1)
            cout << it->second << endl;
        cout << "PAINTSQ " << it->first.first << " " << it->first.second << " " << it->second << '\n';
    }

    for (auto it = reset.begin(); it!= reset.end(); ++it)
        cout << "ERASECELL " << it->first << " " << it->second << endl;

    return 0;
}


