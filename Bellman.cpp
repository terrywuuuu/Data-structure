#include <iostream>

using namespace std;

struct Node
{
    int dis;
    int weight[1000] = {0};

    Node() : dis(-100) {};
};

bool Bellman(pair<int, int> *con, Node *gra, int ver, int edge)
{
    for (int i = 1; i <= ver; i++)
    {
        for (int j = 0; j < edge; j++)
        {
            if (gra[con[j].first].dis != -100)
            {
                if (gra[con[j].second].dis == -100)
                {
                    gra[con[j].second].dis = gra[con[j].first].dis + gra[con[j].first].weight[con[j].second];
                }
                else
                {
                    if (gra[con[j].first].dis + gra[con[j].first].weight[con[j].second] < gra[con[j].second].dis)
                    {
                        gra[con[j].second].dis = gra[con[j].first].dis + gra[con[j].first].weight[con[j].second];
                    }
                }
            }
        }
    }

    for (int j = 0; j < edge; j++)
    {
        if (gra[con[j].first].dis != -100)
        {
            if (gra[con[j].second].dis != -100)
            {
                if (gra[con[j].first].dis + gra[con[j].first].weight[con[j].second] < gra[con[j].second].dis)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

int main()
{
    int vertex = 0, edge = 0, sourse = 0;

    cin >> vertex >> edge >> sourse;
    Node *gragh = new Node[vertex + 1];
    pair<int, int> *connect = new pair<int, int>[edge];
    gragh[sourse].dis = 0;

    for (int i = 0; i < edge; i++)
    {
        int start = 0, end = 0, wei = 0;
        cin >> start >> end >> wei;

        connect[i] = {start, end};
        gragh[start].weight[end] = wei;
    }

    if (Bellman(connect, gragh, vertex, edge))
    {
        for (int i = 1; i <= vertex; i++)
        {
            if (gragh[i].dis == -100)
            {
                cout << "INF" << endl;
            }
            else
            {
                cout << gragh[i].dis << endl;
            }
        }
    }
    else
    {
        cout << "Negative cycle detected" << endl;
    }

    delete[] gragh; 
    delete[] connect;  

    return 0;
}