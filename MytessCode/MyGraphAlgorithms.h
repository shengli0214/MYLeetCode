/*** 
 * @Author: shengli.liu
 * @Date: 2024-07-08 17:47:04
 * @Description: 
 * @
 * @LastEditors: shengli.liu shengli.liu@hongjingdrive.com
 * @LastEditTime: 2024-07-18 14:36:37
 */
#ifndef MYGRAPHALGORITHMS_H
#define MYGRAPHALGORITHMS_H

#include "MyGraph.h"
#include <deque>
#include <stack>
namespace mygraph{
class MyGraphAlgorithm{
public:
    MyGraphAlgorithm() = default;
    void graphTraversal(Graph *G);
    void DFS(Graph *G, Vertex v);
    void DFSNonRecur(Graph *G,Vertex v);
    void PreVisit(Graph *G, Vertex v) {
        //PreVisit Could add some attribute value on vertex or 
        //something else like this
    };
    void PostVisit(Graph *G, Vertex v) {

    }
    void BFS(Graph *G, Vertex start, std::deque<Vertex> *Q);
};
// Depth-First Search
} // end namespace mygraph
#endif // MYGRAPHALGORITHMS_H
