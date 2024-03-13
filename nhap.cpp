#include <iostream>
using namespace std;

#define MAX 1001
int map[MAX][MAX];
int safe = 0, unsafe = -1, occopied = 1; // đã chiếm
int kLightDx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int kLightDy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int qDx[] = {1, 1, 1, 0, 0, -1, -1, -1};
int qDy[] = {1, 0, -1, 1, -1, 1, 0, -1};
int n, m, qR[MAX], qC[MAX], kR[MAX], kC[MAX];

int klights(int r, int c)
{
    int cnt = 0;
    for (int i = 0; i < 8; i++)
    {
        int r1 = r + kLightDx[i];
        int c1 = c + kLightDy[i];

        if (r1 < 1 || c1 < 1 || r1 > n || c1 > m)
            continue;
        if (map[r1][c1] == occopied)
            continue;

        if (map[r1][c1] == safe)
        {
            map[r1][c1] = unsafe;
            cnt++;
        }
    }
    return cnt;
}

int queens(int r, int c)
{
    int cnt = 0;
    for (int i = 0; i < 8; i++)
    {
        int r1 = r - qDx[i];
        int c1 = c - qDy[i];
        while (true)
        {
            if (map[r1][c1] == occopied)
            {
                break;
            }
            if (r1 < 1 || c1 < 1 || r1 > n || c1 > m)
                break;
            if (map[r1][c1] == safe)
            {
                map[r1][c1] = unsafe;
                cnt++;
            }
            // tiếp tục hướng hiện tại ví dụ queens đang ở 24 sddi sang 23
            // nếu k là occupied thì đi sang 22 tương tự với 7 hướng
            r1 -= qDx[i];
            c1 -= qDy[i];
        }
    }
    return cnt;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    for (int t = 1;; t++)
    {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;

        int safeSquares = n * m;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                map[i][j] = safe;
            }
        }

        int qNumber;
        cin >> qNumber;

        for (int i = 1; i <= qNumber; i++)
        {
            int r, c; // row, colume
            cin >> r >> c;
            qR[i] = r;
            qC[i] = c;
            map[r][c] = occopied;
        }

        int kNumber;
        cin >> kNumber;

        for (int i = 1; i <= kNumber; i++)
        {
            int r, c;
            cin >> r >> c;
            kR[i] = r;
            kC[i] = c;
            map[r][c] = occopied;
        }

        int pNum;
        cin >> pNum;
        for (int i = 1; i <= pNum; i++)
        {
            int r, c;
            cin >> r >> c;
            map[r][c] = occopied;
        }
        safeSquares -= qNumber + kNumber + pNum;

        for (int i = 1; i <= qNumber; i++)
        {
            int q = queens(qR[i], qC[i]);
            safeSquares -= q;
        }

        for (int i = 1; i <= kNumber; i++)
        {
            int k = klights(kR[i], kC[i]);
            safeSquares -= k;
        }
        cout << "Board " << t << " "
             << "has " << safeSquares << " "
             << "safe squares." << endl;
    }
    return 0;
}