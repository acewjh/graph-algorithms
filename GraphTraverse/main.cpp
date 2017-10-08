#include <iostream>

using namespace std;

#define MAXVEXNUM 20

typedef struct vex{
    string name;
}vex, *pvex;

typedef struct graph{
    vex vexs[MAXVEXNUM];
    bool arc[MAXVEXNUM][MAXVEXNUM];
}graph, *pgraph;

typedef struct vexqueue{
    int q[MAXVEXNUM];
    int vexnum = 0;
}vexqueue, *pvq;

typedef struct vexstack{
    int s[MAXVEXNUM];
    int vexnum = 0;
}vexstack, *pvs;

void pushQueue(pvq vq, int v)
{
    vq->q[vq->vexnum] = v;
    vq->vexnum++;
}

int popQueue(pvq vq)
{
    int temp = vq->q[0];
    for(int i = 0; i < vq->vexnum - 1; i++)
        vq->q[i] = vq->q[i + 1];
    vq->vexnum--;
    return temp;
}

void pushStack(pvs vs, int v)
{
    vs->s[vs->vexnum] = v;
    vs->vexnum++;
}

int popStack(pvs vs)
{
    int temp = vs->s[vs->vexnum - 1];
    vs->vexnum--;
    return temp;
}

void BFT(graph g, int vexnum)//广度优先遍历无向连通图
{
    int i;
    bool visited[vexnum];
    vexqueue vq;
    for(i = 0; i < vexnum; i++)//初始化visited
        visited[i] = false;
    pushQueue(&vq, 0);//访问第一个节点
    cout << g.vexs[0].name << " ";
    visited[0] = true;
    while(vq.vexnum > 0)
    {
        i = popQueue(&vq);//出队
        for(int j = 0; j < vexnum; j++)
        {
            if(g.arc[i][j] && !visited[j])//寻找邻接且未访问过的节点j
            {
                pushQueue(&vq, j);//访问j节点
                cout << g.vexs[j].name << " ";
                visited[j] = true;
            }
        }
    }
}

void DFT(graph g, int vexnum)//深度优先遍历无向连通图
{
    int i;
    bool visited[vexnum];
    vexstack vs;
    for(i = 0; i < vexnum; i++)//同上
        visited[i] = false;
    pushStack(&vs, 0);//同上
    cout << g.vexs[0].name << " ";
    visited[0] = true;
    while(vs.vexnum > 0)
    {
        i = vs.s[vs.vexnum - 1];
        int j;
        for(j = 0; j < vexnum; j++)//寻找栈顶节点的未访问子节点
        {
            if(g.arc[i][j] && !visited[j])
            {
                pushStack(&vs, j);//访问j节点
                cout << g.vexs[j].name << " ";
                visited[j] = true;
                break;
            }
        }
        if(j == vexnum)//未找到未访问子节点时将栈顶节点出栈
            popStack(&vs);
    }
}

int main()
{
    graph g;//生成测试连通图
    for(int i = 0; i < 7; i++)
        for(int j = 0; j < 7; j++)
            g.arc[i][j] = false;
    g.arc[0][1] = g.arc[1][0] = g.arc[0][2] = g.arc[2][0] = g.arc[0][3] = g.arc[3][0] = true;
    g.arc[1][4] = g.arc[4][1] = g.arc[2][4] = g.arc[4][2] = true;
    g.arc[3][5] = g.arc[5][3] = true;
    g.arc[4][6] = g.arc[6][4] = g.arc[5][6] = g.arc[6][5] = true;
    g.arc[1][2] = g.arc[2][1] = true;
    g.vexs[0].name = "a";
    g.vexs[1].name = "b";
    g.vexs[2].name = "c";
    g.vexs[3].name = "d";
    g.vexs[4].name = "e";
    g.vexs[5].name = "f";
    g.vexs[6].name = "g";
    cout << "Testing BFT..." << endl;
    BFT(g, 7);
    cout << "\nFinished!" << endl;
    cout << "Testing DFT..." << endl;
    DFT(g, 7);
    cout << "\nFinished!" << endl;
    return 0;
}
