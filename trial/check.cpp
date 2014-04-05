#include <iostream>
#include <string>


using namespace std;

char carte[716][1523];

int main(void)
{
    cout << "716 1522" << endl;
    int nbTruc;
    cin >> nbTruc;
    for (int i = 0; i < 716; i++)
        for (int j = 0; j < 1522; j++)
            carte[i][j] = '.';

    for (int req = 0; req < nbTruc; req++)
    {
        string requ;
        int row, col, size;

        cin >> requ >> row >> col;
        if (requ == "ERASECELL")
            carte[row][col] = '.';
        else
        {
            cin >> size;
            int debRow = row-size, finRow = row+size;
            int debCol = col-size, finCol = col+size;
            for (int lin = debRow; lin <= finRow; lin++)
            {
                for (int col = debCol; col <= finCol; col++)
                {
                    if (lin < 0 || col < 0 || lin >= 1522 || col >= 1522)
                    {
                        cout << "lol";
                        req = nbTruc;
                        lin = 1e6;
                        col = 1e6;
                    }
                    else
                        carte[lin][col] = '#';
                }
            }
        }
    }

    for (int lin = 0; lin < 716; lin++)
        cout << carte[lin] << endl;

    return 0;
}
