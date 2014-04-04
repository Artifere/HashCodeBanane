#include <iostream>
#include <algorithm>
#include <utility>
#include <map>


using namespace std;

int rep;
int N,M;
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {0, 1, -1, 1, -1, 0, 1, -1};


map<pair<int, int>, int> carres;

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
        for (auto it = carres.begin(); it != carres.end(); ++it)
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
                            it = carres.begin();
              //  doAgain = true;
            }

            /*else if (size > 0 &&exists[0] && exists[2] && exists[4])
            {
                carres.erase(make_pair(vois[0].first, vois[0].second));
                carres.erase(make_pair(vois[2].first, vois[2].second));
                carres.erase(make_pair(vois[2].first, vois[4].second));
                carres.erase(it);
                carres.insert(make_pair(make_pair(pos.first-size, pos.second-size), 2*size+1));
                          it = carres.begin();
                doAgain = true;
            }

            else if (size > 0 && exists[0] && exists[1] && exists[3])
            {
                carres.erase(make_pair(vois[0].first, vois[0].second));
                carres.erase(make_pair(vois[1].first, vois[1].second));
                carres.erase(make_pair(vois[3].first, vois[3].second));
                carres.erase(it);
                carres.insert(make_pair(make_pair(pos.first+size, pos.second-size), 2*size+1));
                        it = carres.begin();
                doAgain = true;
            }

            else if (size > 0 && exists[3] && exists[5] && exists[6])
            {
                carres.erase(make_pair(vois[3].first, vois[3].second));
                carres.erase(make_pair(vois[5].first, vois[5].second));
                carres.erase(make_pair(vois[6].first, vois[6].second));
                carres.erase(it);
                carres.insert(make_pair(make_pair(pos.first+size, pos.second+size), 2*size+1));
                      it = carres.begin();
                doAgain = true;
            }

            else if (size > 0 && exists[4] && exists[7] && exists[5])
            {
                carres.erase(make_pair(vois[4].first, vois[4].second));
                carres.erase(make_pair(vois[7].first, vois[7].second));
                carres.erase(make_pair(vois[5].first, vois[5].second));
                carres.erase(it);
                carres.insert(make_pair(make_pair(pos.first-size, pos.second+size), 2*size+1));
                    it = carres.begin();
                doAgain = true;
            }*/
        }
    }

    cout << carres.size() << endl;
    for (auto it = carres.begin(); it != carres.end(); ++it)
    {
        cout << "PAINTSQ " << it->first.first << " " << it->first.second << " " << it->second << '\n';
    }
    return 0;
}


