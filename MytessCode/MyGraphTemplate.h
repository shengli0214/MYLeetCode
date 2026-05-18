/*** 
 * @Author: shengli.liu
 * @Date: 2024-10-01 16:13:31
 * @Description: 
 * 原文链接：https://blog.csdn.net/ancientmoondjay/article/details/68141946
 * @
 * @LastEditors: shengli0214 shengli_liu14@126.com
 * @LastEditTime: 2025-12-29 15:00:23
 */
#ifndef MYGRAPHTEMPLATE_H
#define MYGRAPHTEMPLATE_H
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <string>
#include <memory>
#include <cstring>
#include <climits>


#include "UnionFind.h"
namespace mygraptemplate{
using namespace std;
    // 边结点类
template <typename T>
class ENode
{
public:
    int vertex; // 边的一端顶点
    int adjVex; // 边的另一端顶点
    T weight;   // 边的权值
    ENode<T> *next;

    ENode() { next = NULL; }
    ENode(int vertex, int adjvertex, T w, ENode<T> *nextArc)
    {
        this->vertex = vertex;
        adjVex = adjvertex;
        weight = w;
        next = nextArc;
    }
    operator T() const { return weight; }

    bool operator<(const ENode<T> &rhs) const
    {
        return this->weight > rhs.weight; // 最小值优先
    }
};

//自定义优先队列less的比较函数
template <typename T>
struct cmp{
    bool operator()(const ENode<T> &a,const ENode<T> &b) const {
        return a.weight > b.weight;
    }
};                      

//图类
template <typename T>
class Graph{
private:
    ENode<T> **enodes;
    int n;                  //顶点个数
    int edges;              //边的个数
    int connectedCount;     //强连通分量个数
    int *id;                //由顶点索引的数组,存放顶点所属的连通分量标识符
    vector<int> *tarjanConnection;    //通过tarjan算法得到的强连通分量
    int connectedCountForTarjan;      //在tarjan算法中使用的强连通分量个数
    bool hasCycle;          //是否有环
    std::stack<int> cycle;  //有向环中的所有顶点（如果存在）
    stack<int> reversePost; //通过DFS得到的所有顶点的逆后序排列
    unionfind::UnionFind *uf; //用于Kruskal算法,用来判断最小生成树森林中是否会构成回路

    void DFS(int v,bool *visited);  //私有DFS,供递归调用
    void BFS(int v,bool *visited);  //私有BFS

    void DFSForCycle(int v,bool *visited,bool *onStack,int *edgeTo);    //用DFS思想来判断环
    void DFSForReversePost(int v,bool *visited);   //用DFS思想来求逆后序序列,用于求拓扑序列或者强连通分量
    void DFSForConnection(int v,bool *visited); //用DFS思想来求强连通分量
    void TarjanForConnection(int u,bool *visited,int *DFN,int *low,stack<int> *tarjanStack,bool *inStack,int &index); //用tarjan算法求强连通分量,其实也是运用了DFS思想

    void ClearCycle();  //清空栈cycle中的记录
    void ClearReversePost();   //清空栈reversePost中的记录
    void CalInDegree(int *inDegree);    //计算所有顶点的入度

    void Prim(int v0,int *nearest, T *lowcost);  //普里姆算法求无向图最小代价生成树,私有,内部调用
    void Kruskal(priority_queue<ENode<T>> &pq); //克鲁斯卡尔算法求无向图最小代价生成树,私有,内部调用
    void Dijkstra(int v0,int  *path, T *curShortLen);    //迪杰斯特拉算法解决单源最短路径问题,私有,内部调用
    int FinMinLen(T *curShortLen,bool *mark);              //Dijkstra算法的辅助函数,用于找出下一条最短路径的终点
public:
    Graph(int mSize);
    ~Graph();
    bool Exist(int u,int v) const;  //边u->v是否存在
    bool Insert(int u,int v,T w);   //插入边u->v
    bool Remove(int u,int v);       //删去边u->v
    Graph<T> Reverse();             //得到反向图
    void DFS();                     //公有接口,深度优先搜索
    void BFS();                     //公有接口,宽度优先搜索

    bool HasCycle();                //判断是否有环
    stack<int> GetCycle();          //返回环
    void CalReversePost();          //通过递归调用DFSForReversePost来求得
    void TopoSort();                //拓扑排序
    void TopoSortByDFS();           //用DFS来求拓扑 
    stack<int> GetReversePost();    //返回DFS中顶点的逆后序序列
    void CalculateConnection();     //求图的强连通分量
    int GetConnectedCount();        //得到强连通分量数
    int ConnectionID(int v);        //v所在的强连通分量的标识符(1~connectedCount)
    void ShowConnection();          //打印强连通分量
    void TarjanForConnection();     //用tarjan算法求强连通分量

    void Prim(int v0);              //普里姆算法求无向图最小代价生成树,外部接口
    void Kruskal();                 //克鲁斯卡尔算法求无向图最小代价生成树,外部接口
    void Dijkstra(int v0);          //迪杰斯特拉算法解决单源最短路径问题
    void Floyd();                   //弗洛伊德算法求所有顶点之间的最短路径
    T GetWeight(int u,int v);       //获得边u-v的权值
};

template <typename T>
Graph<T>::Graph(int mSize) {
    n = mSize;
    edges = 0;
    connectedCount = 0;
    hasCycle = false;
    enodes = new ENode<T> *[n];
    id = new int[n];
    for (int i = 0; i < n; ++i) {
        enodes[i] = NULL;
        id[i] = 0;
    }
    uf = new unionfind::UnionFind(n);
}

template <typename T>
Graph<T>::~Graph() {
    ENode<T> *p,*q;
    for (int i = 0; i < n; ++i){
        p = enodes[i];
        while (p) {
            q = p;
            p = p->next;
            delete (q);
        }
    }
    delete[] enodes;
    delete[] id;
    delete uf;
}

//边u->v是否存在
template <typename T>
bool Graph<T>::Exist(int u, int v) const {
    if (u < 0 || v < 0 || u > n - 1 || v > n - 1 || u == v) {
        return false;   //输入参数无效
    }
    ENode<T> *p = enodes[u];
    while (p && p->adjVex != v) {
        p = p->next;
    }
    // if (p) {
    //     return true;
    // } else {
    //     return false;
    // }
    return p != nullptr;
}

//插入边u->v
template <typename T>
bool Graph<T>::Insert(int u, int v, T w) {
    if (u < 0 || v < 0 || u > n - 1 || v > n - 1 || u == v) {
        return false;   //输入参数无效
    }
    if (Exist(u, v)) {
        cout<<"Duplicate"<<endl;
        return false;
    } else {
        //将新边结点插在由指针enodes[u]所指示的单链表最前面
        ENode<T> *p = new ENode<T>(u,v, w, enodes[u]);
        enodes[u] = p;
        edges++;
        return true;
    }
}

template <typename T>
bool Graph<T>::Remove(int u, int v) {
    if (u < 0 || v < 0 || u > n - 1 || v > n - 1 || u == v) {
        return false;   //输入参数无效
    }
    ENode<T> *p = enodes[u];
    ENode<T> *q = NULL;
    while (p && p->adjVex != v) {
        q = p;
        p = p->next;
    }
    if (!p) {
        cout<<"Not exist."<<endl;
        return false;
    }
    if (p == enodes[u]) {
        q = p;
        enodes[u] = p->next;
        delete (q);
        edges--;
    } else {
        q->next = p->next;
        delete (p);
        edges--;
    }
    return true;
}

//得到反向图
template <typename T>
Graph<T> Graph<T>::Reverse() {
    Graph<T> R(n);
    for (int i = 0; i < n; ++i) {
        for (ENode<T> *w = enodes[i]; w; w = w->next) {
            R.Insert(w->adjVex, i, w->weight);
        }
    }
    return R;
}

//私有DFS,供递归调用
template <typename T>
void Graph<T>::DFS(int v, bool *visited) {
    visited[v] = true;
    cout<<v<<" ";
    for (ENode<T> *w = enodes[v]; w; w = w->next) {
        if (!visited[w->adjVex]) {
            DFS(w->adjVex, visited);
        }
    }
}
//公有接口,深度优先搜索
template <typename T>
void Graph<T>::DFS() {
    bool *visited = new bool[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }
    for (int j = 0; j < n; ++j) {
        if (!visited[j]) {
            DFS(j, visited);
        }
    }
    delete[] visited;
}

//私有BFS
template <typename T>
void Graph<T>::BFS(int v, bool *visited) {
    visited[v] = true;
    cout<<v<<" ";
    queue<int> myqueue;
    myqueue.push(v);

    int s;
    while (!myqueue.empty()) {
        s = myqueue.front();
        myqueue.pop();
        for (ENode<T> *w = enodes[s]; w; w = w->next) {
            if (!visited[w->adjVex]) {
                visited[w->adjVex] = true;
                cout<<w->adjVex<<" ";
                myqueue.push(w->adjVex);
            }
        }
    }
}

//公有接口,宽度优先搜索
template <typename T>
void Graph<T>::BFS() {
    bool *visited = new bool[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    for (int j = 0; j < n; ++j) {
        if (!visited[j]) {
            BFS(j, visited);
        }
    }
    delete[] visited;
}

//non-recursion

// template <typename T>
// void DFS2(Graph G, int num){
//     std::stack<int> Stack;
//     visit[num] = 1;
//     Stack.push(num);
//     while (!Stack.empty()){
//         num = Stack.top();
//         Stack.pop();
//         cout << num << " ";
//         for (int i = G.n - 1; i >= 0; i--){
//             if (G.edge[num][i] != 0 && visit[i] == 0){
//                 Stack.push(i);
//                 visit[i] = 1;
//             }
//         }
//     }
//     cout << endl;
// }

//用DFS思想来求逆后序序列,用于求拓扑序列或者强连通分量
template <typename T>
void Graph<T>::DFSForReversePost(int v, bool *visited) {
    visited[v] = true;
    for (ENode<T> *w = enodes[v]; w; w = w->next) {
        if (!visited[w->adjVex]) {
            DFSForReversePost(w->adjVex, visited);
        }
    }
    reversePost.push(v);    //这是和普通的DFS唯一不同的地方！
}

//通过调用DFSForReversePost来求得
template <typename T>
void Graph<T>::CalReversePost() {
    ClearReversePost();
    bool *visited = new bool[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }
    for (int j = 0; j < n; ++j) {
        if (!visited[j]) {
            DFSForReversePost(j, visited);
        }
    }

    delete[] visited;
}

//返回DFS中顶点的逆后序序列
template <typename T>
stack<int> Graph<T>::GetReversePost() {
    //因为栈的特殊性,这里直接返回一个拷贝,以保证源栈不会因为外界操作而改变
    stack<int> tmp(reversePost);

    return tmp;
}

//清空栈reversePost中的记录
template <typename T>
void Graph<T>::ClearReversePost() {
    while (!reversePost.empty()) {
        reversePost.pop();
    }
}

//用DFS思想来判断环
template <typename T>
void Graph<T>::DFSForCycle(int v, bool *visited, bool *onStack, int *edgeTo) {
    onStack[v] = true;
    visited[v] = true;

    for (ENode<T> *w = enodes[v]; w; w = w->next) {
        if (hasCycle) {
            return;
        }else if (!visited[w->adjVex]) {
            edgeTo[w->adjVex] = v;
            DFSForCycle(w->adjVex, visited, onStack, edgeTo);
        } else if (onStack[w->adjVex]) {    //此顶点已经在递归调用的栈上,再次访问说明出现环了
            //用栈cycle将环上的点都保存起来
            for (int i = v; i != w->adjVex; i = edgeTo[i]) {
                cycle.push(i);
            }
            cycle.push(w->adjVex);
            cycle.push(v);
            hasCycle = true;
        }
    }
    onStack[v] = false;     //消除在此递归调用栈上的记录,因为已经递归结束了
}

//判断是否有环
template <typename T>
bool Graph<T>::HasCycle() {
    bool *visited = new bool[n];
    bool *onStack = new bool[n];    //由顶点索引的数组,以标记递归调用栈上的所有顶点
    int *edgeTo = new int[n];       //edgeTo[i]存放指向i的边的点
    ClearCycle();

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        onStack[i] = false;
        edgeTo[i] = -1;
    }

    for (int j = 0; j < n; ++j) {
        if (!visited[j]) {
            DFSForCycle(j, visited, onStack, edgeTo);
        }
    }
    delete[] visited;
    delete[] onStack;
    delete[] edgeTo;
    if (hasCycle) {
        return true;
    } else {
        return false;
    }
}

//返回环
template <typename T>
stack<int> Graph<T>::GetCycle() {
    stack<int> tmp(cycle);
    return tmp;
}

//清空栈cycle中的记录
template <typename T>
void Graph<T>::ClearCycle() {
    while (!cycle.empty()) {
        cycle.pop();
    }
}

//计算所有顶点的入度
template <typename T>
void Graph<T>::CalInDegree(int *inDegree) {
    for (int i = 0; i < n; ++i) {
        for (ENode<T> *w = enodes[i]; w; w = w->next) {
            inDegree[w->adjVex]++;
        }
    }
}

//拓扑排序
template <typename T>
void Graph<T>::TopoSort() {
    if (HasCycle()) {       //存在环,直接返回
        cout<<"Cycle exists."<<endl;
        return;
    }

    int *inDegree = new int[n];
    for (int i = 0; i < n; ++i) {
        inDegree[i] = 0;
    }

    CalInDegree(inDegree);
    queue<int> topoQueue;
    //将入度为0的顶点存入队列
    for (int j = 0; j < n; ++j) {
        if (inDegree[j] == 0) {
            topoQueue.push(j);
        }
    }
    int v;
    int k;
    while (!topoQueue.empty()) {
        v = topoQueue.front();
        topoQueue.pop();

        cout<<v<<" ";
        for (ENode<T> *w = enodes[v]; w; w = w->next) {
            k = w->adjVex;
            inDegree[k]--;  //所有由顶点v指出的邻接点入度-1
            if (0 == inDegree[k]) {     //更新后入度为0,则存进队列
                topoQueue.push(k);
            }
        }
    }
}

//用DFS来求拓扑序列
//一幅有向无环图的拓扑顺序即为DFS中所有顶点的逆后序排列,所以只要求该逆后序排列就好
//如果该图是有环的,就说明拓扑序列不存在,尽管该逆后序排列仍能求出来
template <typename T>
void Graph<T>::TopoSortByDFS() {
    if (HasCycle()) {       //存在环,直接返回
        cout<<"Cycle exists."<<endl;
        return;
    }
    CalReversePost();

}

//用DFS思想来求强连通分量
template <typename T>
void Graph<T>::DFSForConnection(int v, bool *visited) {
    visited[v] = true;
    id[v] = connectedCount;
    for (ENode<T> *w = enodes[v]; w; w = w->next) {
        if (!visited[w->adjVex]) {
            DFSForConnection(w->adjVex, visited);
        }
    }
}

//求图的强连通分量
template <typename T>
void Graph<T>::CalculateConnection() {
    connectedCount = 0;
    bool *visited = new bool[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        id[i] = 0;
    }

    //根据本图的反向图的顶点逆后序序列来进行DFS
    //所有在同一个递归DFS调用中被访问到的顶点都在同一个强连通分量中
    Graph<T> R = this->Reverse();
    R.CalReversePost();
    stack<int> topostack = R.GetReversePost();

    int j;
    while (!topostack.empty()) {
        j = topostack.top();
        topostack.pop();
        if (!visited[j]) {
            connectedCount++;
            DFSForConnection(j, visited);
        }
    }
    delete[] visited;
}

//打印强连通分量
template <typename T>
void Graph<T>::ShowConnection() {
    CalculateConnection();

    set<int> connections[connectedCount];
    for (int i = 0; i < n; ++i) {
        connections[id[i] - 1].insert(i);
    }
    for (int j = 0; j < connectedCount; ++j) {
        cout << "connection " << j + 1 << ":";
        for (set<int>::iterator set_iter = connections[j].begin(); set_iter != connections[j].end(); set_iter++) {
            cout << *set_iter << " ";
        }
        cout << endl;
    }
}

//得到强连通分量数
template <typename T>
int Graph<T>::GetConnectedCount() {
    return connectedCount;
}

//v所在的强连通分量的标识符(1~connectedCount)
template <typename T>
int Graph<T>::ConnectionID(int v) {
    return id[v];
}

//用tarjan算法求强连通分量,其实也是运用了DFS思想
/*
 * visited[u]:顶点u是否被访问过
 * dfn[u]：DFS遍历时顶点u被搜索的次序,也即时间戳
 * low[u]：顶点u能够回溯到的最早位于栈中的顶点
 * tarjanStack：用于存放每次遍历时被搜索到的顶点
 * inStack[u]：u目前是否在栈中,要配合tarjanStack使用
 * index：时间戳,随着访问的结点而递增
 */
template <typename T>
void Graph<T>::TarjanForConnection(int u,bool *visited,int *dfn,int *low,stack<int> *tarjanStack,bool *inStack,int &index) {
    dfn[u] = low[u] = ++index;      //为顶点u设访问时间戳和low初值
    visited[u] = true;              //修改为已访问
    tarjanStack->push(u);           //顶点u入栈
    inStack[u] = true;

    //搜索从顶点u指出的每个顶点
    for (ENode<T> *w = enodes[u]; w; w = w->next) {
        if (!visited[w->adjVex]) {      //顶点v还没被访问过
            TarjanForConnection(w->adjVex, visited, dfn, low, tarjanStack, inStack, index);
            //从上个递归函数返回后就是回溯过程,用u和v即w->adjVex的最小low值来更新low[u]。
            //因为顶点v能够回溯到的已经在栈中的顶点,顶点u也一定能回溯到。
            //因为存在从u到v的直接路径,所以v能够到达的顶点u也一定能够到达。
            low[u] = low[u] < low[w->adjVex] ? low[u] : low[w->adjVex];
        }else if (inStack[w->adjVex]) { //顶点v已经在栈中
            //用u的low值和v的DFN值中最小值来更新low[u]。
            //如果DFN[v]<low[u],则根据low值的定义,即能够回溯到的最早已经在栈中的顶点,所以我们应该用DFN[v]来更新low[u],
            //表示u能和v回溯到相同的最早顶点
            low[u] = low[u] < dfn[w->adjVex] ? low[u] : dfn[w->adjVex];
        }
    }
    //搜索完从顶点u指出的所有顶点后判断该结点的low值和DFN值是否相等。
    //如果相等,则该结点一定是在深度遍历过程中该强连通图中第一个被访问过的顶点,因为它的low值和DFN值最小,不会被该强连通图中其他顶点影响。
    //既然知道了该顶点是该强连通子树里的根,又根据栈的特性,则该顶点相对于同个连通图中其他顶点一定是在栈的最里面,
    //所以能通过不断地弹栈来弹出该连通子树中的所有顶点,直到弹出根结点即该顶点为止。
    if (low[u] == dfn[u]) {
        connectedCountForTarjan++;  //找到一个强连通分量,计数自增
        int x;
        do {
            x = tarjanStack->top();
            tarjanStack->pop();
            inStack[x] = false;     //注意要和tarjanStack配套使用
            tarjanConnection[connectedCountForTarjan - 1].push_back(x);
        } while (x != u);
    } else {
        return;    //不等则返回
    }
}

//用tarjan算法求强连通分量
template <typename T>
void Graph<T>::TarjanForConnection() {
    connectedCountForTarjan = 0;
    bool *visited = new bool[n];
    int *dfn = new int[n];
    int *low = new int[n];
    stack<int> *tarjanStack = new stack<int>;
    bool *inStack = new bool[n];
    int index = 0;

    memset(visited, false, n);
    memset(dfn, 0, n);
    memset(low, 0, n);
    memset(inStack, false, n);

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            TarjanForConnection(i, visited, dfn, low, tarjanStack, inStack, index);
        }
    }

    for (int i = 0; i < connectedCountForTarjan; ++i) {
        cout<<"connection "<<i+1<<" : ";
        for (auto ite:tarjanConnection[i]) {
            cout<<ite<<" ";
        }
        cout<<endl;
    }

    delete[] visited;
    delete[] dfn;
    delete[] low;
    delete tarjanStack;
    delete[] inStack;
}

//普里姆算法求无向图最小代价生成树,私有,内部调用
template <typename T>
void Graph<T>::Prim(int v0,int *nearest, T *lowcost) {
    bool *mark = new bool[n];
    for (int i = 0; i < n; ++i) {
        mark[i] = false;
    }
    ENode<T> *p = NULL;
    nearest[v0] = v0;
    lowcost[v0] = 0;
    mark[v0] = true;

    int k = v0;         //最近加入生成树中的顶点

    for (int i = 1; i < n ; ++i) {
        for (p = enodes[k]; p; p = p->next) {   //更新nearest和lowcost
            int j = p->adjVex;
            if (!mark[j] && lowcost[j] > p->weight) {
                nearest[j] = k;
                lowcost[j] = p->weight;
            }
        }
        T min = INT_MAX;
        for (int j = 0; j < n; ++j) {       //找到最小代价的边
            if (!mark[j] && min > lowcost[j]) {
                min = lowcost[j];
                k = j;
            }
        }
        mark[k] = true;
    }
}

//普里姆算法求无向图最小代价生成树,外部接口
template <typename T>
void Graph<T>::Prim(int v0) {
    if (v0 < 0 || v0 > n - 1) {
        cout << "input error!" << endl;
        return;
    }
    int *nearest = new int[n];      //nearest[v]=u,表示离v最近的是u,其中u在最小生成树中,v是待加入的顶点
    T *lowcost = new T[n];          //lowcost[v]=w(u,v),表示离v最近的点u之间的权值

    for (int i = 0; i < n; ++i) {
        nearest[i] = -1;
        lowcost[i] = INT_MAX;
    }

    Prim(v0, nearest, lowcost);
    cout << "(nearest[i],i,lowcost[i]) = ";
    for (int i = 0; i < n; ++i) {
        cout << "(" << nearest[i] << "," << i << "," << lowcost[i] << ")" << " ";
    }
    cout << endl;
    delete[]nearest;
    delete[]lowcost;

}

//克鲁斯卡尔算法求无向图最小代价生成树,私有,内部调用
template <typename T>
void Graph<T>::Kruskal(priority_queue<ENode<T>> &pq) {
    ENode<T> kruskalResult[n - 1];
    ENode<T> x;


    //n个结点只要加入n-1条边就可以
    int k = 0;      //已加入最小生成树中的边数

    //每次从pq中取出具有最小代价的边,并且该边的两端顶点不会都已经在树中了
    while (k < n - 1 && !pq.empty()) {
        x = pq.top();
        pq.pop();
        if (!uf->Connected(x.vertex, x.adjVex)) {  //如果找到的最小边两端点还没在最小树中相连
            kruskalResult[k] = x;
            uf->Union(x.vertex, x.adjVex);        //将两端点在树中相连
            k++;
        }

    }

    cout<<"(u,v,weight) = ";
    for (int j = 0; j < n-1; ++j) {
        cout <<"("<<kruskalResult[j].vertex<<","<<kruskalResult[j].adjVex<<","<<kruskalResult[j].weight<<") ";
    }
    cout << endl;
}

//克鲁斯卡尔算法求无向图最小代价生成树,外部接口
template <typename T>
void Graph<T>::Kruskal() {
    priority_queue<ENode<T>,vector<ENode<T>>> pq;   //最小优先队列

    for (int i = 0; i < n; ++i) {
        for (ENode<T> *w = enodes[i]; w; w = w->next) {
            pq.push(*w);
        }
    }
    Kruskal(pq);
}

//Dijkstra算法的辅助函数,用于找出下一条最短路径的终点
template <typename T>
int Graph<T>::FinMinLen(T *curShortLen,bool *mark) {
    int minIndex = -1;
    T minLen = INT_MAX;

    for (int i = 1; i < n; ++i) {
        if (!mark[i] && minLen > curShortLen[i]) {
            minIndex = i;
            minLen = curShortLen[i];
        }
    }

    return minIndex;
}

//迪杰斯特拉算法解决单源最短路径问题,私有,内部调用
template <typename T>
void Graph<T>::Dijkstra(int v0, int *path, T *curShortLen) {
    bool *mark = new bool[n];        //mark[i]表示顶点i是否已加入单源最短路径里
    for (int i = 0; i < n; ++i) {
        mark[i] = false;
    }


    mark[v0] = true;
    path[v0] = -1;
    curShortLen[v0] = 0;

    int k = v0;                     //最近加入单源最短路径中的顶点
    int nextK = -1;                 //即将加入单源最短路径中的顶点
    ENode<T> *p;
    int count = 0;                  //用来计数单源最短路径上有多少条边

    for (int i = 1; i < n; ++i) {   //循环n-1次,将其他顶点都加入单源最短路径中
        for (p = enodes[k]; p; p = p->next) {
            int j = p->adjVex;
            if (!mark[j] && curShortLen[j] > curShortLen[k] + p->weight) {
                curShortLen[j] = curShortLen[k] + p->weight;    //保证curShortLen[j] = min{curShortLen[j],curShortLen[k]+p->weight}
            }
        }
        nextK = FinMinLen(curShortLen, mark);   //找到下一条最短路径的终点
        if (-1 == nextK) {                      //返回-1,说明从v0出发的单源最短路径已经都找到了
            break;
        } else {
            mark[nextK] = true;                     //加入最短路径中
            path[nextK] = k;                        //记录终点信息,方便回溯
            k = nextK;                              //k指向最近加入的顶点
            count++;                                //路径上的边数加1
        }
    }

    //输出最短路径结果
    cout<<"shortest path:"<<endl;
    int lastVer;    //最短路径中的上个顶点
    stack<int> tmp; //用栈来逆序储存最短路径上的顶点
    for (int i = 1; i <= count; ++i) {
        cout<<curShortLen[k]<<" : ";

        tmp.push(k);
        lastVer = path[k];
        while (lastVer != v0) {
            tmp.push(lastVer);
            lastVer = path[lastVer];
        }
        tmp.push(v0);

        cout<<tmp.top();
        tmp.pop();
        while (!tmp.empty()) {
            cout<<"->"<<tmp.top();
            tmp.pop();
        }
        cout<<endl;

        k = path[k];    //将k置为最短路径上在该点之前的那个顶点
    }
}

//迪杰斯特拉算法解决单源最短路径问题
template <typename T>
void Graph<T>::Dijkstra(int v0) {
    if (v0 < 0 || v0 > n - 1) {
        cout << "input error!" << endl;
        return;
    }
    T *curShortLen = new T[n];          //curShortLen[i]存放从源点v0到i的当前最短路径的长度
    int *path = new int[n];             //path[i]给出从v0到顶点i的最短路径上,位于顶点i前面的那个顶点

    for (int i = 0; i < n; ++i) {
        curShortLen[i] = INT_MAX;
        path[i] = -1;
    }

    Dijkstra(v0, path, curShortLen);
}

//获得边u-v的权值
template <typename T>
T Graph<T>::GetWeight(int u,int v) {
    if (u == v) {
        return 0;
    }
    ENode<T> *p = enodes[u];
    while (p != NULL && p->adjVex != v) {
        p = p->next;

    }

    if (p) {
        return p->weight;
    } else {
//        cout<<"edge "<<u<<"----"<<v<<" is not connected"<<endl;
        return INT_MAX;
    }
}


//弗洛伊德算法求所有顶点之间的最短路径
template <typename T>
void Graph<T>::Floyd() {
    int path[n][n];    //n*n矩阵,path[i][j]表示从顶点i到j的最短路径上,顶点j的前一个顶点
    T d[n][n];         //d[i][j]存放从顶点i到顶点j的当前最短路径的长度
    int i, j, k;

    //初始化矩阵
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            d[i][j] = GetWeight(i, j);
            if (i != j && d[i][j] < INT_MAX) {
                path[i][j] = i;
            } else {
                path[i][j] = -1;
            }
        }
    }

    for (k = 0; k < n; k++) {       //n次更新矩阵
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (d[i][k] + d[k][j] < d[i][j]) {  //加入顶点k之后更新矩阵
                    d[i][j] = d[i][k] + d[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }

    //输出所有顶点之间的最短路径结果
    cout<<"shortest path between two vertex:"<<endl;
    stack<int> tmp; //用栈来逆序储存最短路径上的顶点
    int m;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            cout << "from " << i << " to " << j << " : ";

            if (path[i][j] == -1) {     //表示不可达
                cout << "not connected" << endl;
            } else {
                tmp.push(j);
                m = path[i][j];
                while (m != -1) {    //在最短路径上进行反向回溯
                    tmp.push(m);
                    m = path[i][m];
                }
                cout << tmp.top();
                tmp.pop();
                while (!tmp.empty()) {
                    cout << "->" << tmp.top();
                    tmp.pop();
                }
                cout << endl;
            }

        }
    }
}


}// end namespace mygraptemplate

#endif // MYGRAPHTEMPLATE_H