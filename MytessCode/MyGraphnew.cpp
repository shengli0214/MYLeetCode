/*** 
 * @Author: shengli.liu && shengli_liu14@126.com
 * @Date: 2025-02-17 22:49:13
 * @LastEditors: shengli0214 shengli_liu14@126.com
 * @LastEditTime: 2026-01-09 15:41:46
 * @FilePath: \MytessCode\MyGraphnew.cpp
 * @Description: 
 * @
 * @Copyright (c) 2026 by shengli.liu, All Rights Reserved. 
 */

#include "MyGraphnew.h"
namespace mygraphnew{

graph BFS(graph G, graphNode *s)
{
    s->c = VerColor::gray;
    s->d = 0;

    std::deque<graphNode*> q; // Create an deque
    q.push_back(s);
    while (!q.empty()){
        /* code */
        graphNode *cur = q.front();
        q.pop_front();
        char n = cur->name;
        for(graphNode* u : G.adj[n]){
            if(u->c == VerColor::white){
                u->c = VerColor::gray;
                u->d = cur->d + 1;
                u->pre = cur;
                q.push_back(u);
            }
            
        }
        cur->c = VerColor::black;
    }
    return G;
}
graph initGraph(){
    graph G;
    G.v = {new graphNode('r'),new graphNode('v'),new graphNode('s'),new graphNode('w'),
        new graphNode('t'),new graphNode('x'),new graphNode('u'),new graphNode('y') };
    //初始化邻接链表 G.adj  map r -> list 
    G.adj['r'] = {G.v[1],G.v[2]};
    G.adj['s'] = {G.v[3],G.v[0]};
    G.adj['w'] = {G.v[2],G.v[4],G.v[5]};
    G.adj['t'] = {G.v[5],G.v[3],G.v[6]};
    G.adj['x'] = {G.v[4],G.v[3],G.v[6],G.v[7]};
    G.adj['u'] = {G.v[4],G.v[5],G.v[7]};
    G.adj['y'] = {G.v[5],G.v[6]};
    G.adj['v'] = {G.v[0]};
    return G;                          
}

void printPath(graph G, graphNode *s, graphNode *v) {
    if (s == v) {
        std::cout << s->name;
    }
    else if (v->pre == NULL) {
        std::cout << "no path!";
    }
    else {
        printPath(G, s, v->pre);
        std::cout << v->name;
    }
}
} // end namespace mygraphnew 