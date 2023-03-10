/*
Đếm số lượng khớp và cầu trên đồ thị vô hướng.

Độ phức tạp

O(n+m)
*/

#include <stdio.h>

#include <algorithm>

#include <iostream>

#include <vector>

using namespace std;

const int N = 100005;

int n, m;

vector<int> a[N];

int CriticalEdge = 0;

bool CriticalNode[N];

int Num[N], Low[N], Time = 0;

void visit(int u, int p) {

    int NumChild = 0;

    Low[u] = Num[u] = ++Time;

    for (int v : a[u])

        if (v != p) {

            if (Num[v] != 0)

                Low[u] = min(Low[u], Num[v]);

            else {

                visit(v, u);

                NumChild++;

                Low[u] = min(Low[u], Low[v]);

                if (Low[v] >= Num[v])

                    CriticalEdge++;

                if (u == p) {

                    if (NumChild >= 2)

                        CriticalNode[u] = true;

                } else {

                    if (Low[v] >= Num[u])

                        CriticalNode[u] = true;

                }

            }

        }

}

int main() {

    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {

        int x, y;

        scanf("%d%d", &x, &y);

        a[x].push_back(y);

        a[y].push_back(x);

    }

    for (int i = 1; i <= n; i++)

        if (!Num[i]) visit(i, i);

    int Count = 0;

    for (int i = 1; i <= n; i++)

        if (CriticalNode[i]) Count++;

    printf("%d %d\n", Count, CriticalEdge);

}