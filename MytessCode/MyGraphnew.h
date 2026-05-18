/*** 
 * @Author: shengli.liu
 * @Date: 2024-07-18 11:14:28
 * @Description: 
 * @
 * @LastEditors: shengli.liu shengli.liu@hongjingdrive.com
 * @LastEditTime: 2024-07-25 15:37:07
 */
#ifndef MYGRAPHNEW_H
#define MYGRAPHNEW_H
#include <vector>
#include <list>
#include <iostream>
#include <map>
#include <deque>

namespace mygraphnew{
//A graph is a set of vertices and a collection of edges that each connect a pair of vertices
//By convention, we use the names 0 through V-1 for the vertices in a V-vertex graph.
enum class VerColor : std::int32_t{
    white = 0,
    gray,
    black,
};

struct graphNode{
    char name;
    struct graphNode *pre;
    std::int32_t d; // depth
    VerColor c;     // Node color
    graphNode(char n):name(n),pre(nullptr),c(VerColor::white),d(0){}
};
struct graph{
    std::vector<graphNode *> v;
    std::map<char, std::list<graphNode *>> adj; //adjacent list
};

graph BFS(graph G, graphNode *s);

graph initGraph();
void printPath(graph G, graphNode *s, graphNode *v);

} //end mygraphnew namespace

#endif // MYGRAPHNEW_H