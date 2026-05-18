#include "UnionFind.h"
namespace unionfind{

UnionFind::UnionFind(int N):count(N) {
    id = new int[N];
    sz = new int[N];
    for (int i = 0; i < N; ++i) {
        id[i] = i;
    }
    for (int j = 0; j < N; ++j) {
        sz[j] = 1;
    }
}

UnionFind::~UnionFind() {
    delete[] id;
    delete[] sz;
}

//找p所在连通分量的根
int UnionFind::Find(int p) {
    while (p != id[p]) {
        p = id[p];
    }
    return p;
}

//p和q是否在同一个连通分量里
bool UnionFind::Connected(int p, int q) {
    int pRoot = Find(p);
    int qRoot = Find(q);
    if (pRoot == qRoot) {
        return true;
    } else {
        return false;
    }
}

//返回连通分量
int UnionFind::GetCount() {
    return count;
}

//将p和q连接起来
void UnionFind::Union(int p, int q) {
    int pRoot = Find(p);
    int qRoot = Find(q);

    if (pRoot == qRoot) {   //已经在同个连通分量里,直接返回
        return;
    } else {                //将元素较少的连通分量连接到元素较多的连通分量上
        if (sz[pRoot] < sz[qRoot]) {
            id[pRoot] = qRoot;
            sz[qRoot] += sz[pRoot];
        } else {
            id[qRoot] = pRoot;
            sz[pRoot] += sz[qRoot];
        }
        count--;            //现有连通分量个数减1
    }
}


}; //end namespace unionfind