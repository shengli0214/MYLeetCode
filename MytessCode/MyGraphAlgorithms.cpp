/*** 
 * @Author: shengli.liu
 * @Date: 2024-07-08 17:46:46
 * @Description: 
 * @
 * @LastEditors: shengli0214 shengli_liu14@126.com
 * @LastEditTime: 2026-03-12 17:42:08
 */
/*** 
 * @Author: shengli.liu
 * @Date: 2024-07-08 17:46:46
 * @Description: 
 * @
 * @LastEditors: shengli.liu shengli.liu@hongjingdrive.com
 * @LastEditTime: 2024-09-30 15:07:22
 */
#include "MyGraphAlgorithms.h"
namespace mygraph{
void MyGraphAlgorithm::graphTraversal(Graph *G){
    std::int32_t v;
    for (v = 0; v < G->n(); v++){
        G -> setMark(v, UNVISITED);
    }
    for (v = 0; v < G->n();v++){
        if(G->getMark(v) == UNVISITED){
           // doTraverse(G, v);
        }
    }
}

void MyGraphAlgorithm::DFS(Graph *G,Vertex v){
    PreVisit(G, v);
    G->setMark(v, VISITED);
    for (Vertex w = G->first(v); w.get_index() < G->n();w = G->next(v,w)){
        if(G->getMark(w) == UNVISITED){
            DFS(G, w);
        }
    }
    PostVisit(G, v);
}

void MyGraphAlgorithm::DFSNonRecur(Graph* G, Vertex v) {
  // std::stack<std::pair<Vertex, std::int32_t> > stk;
  std::stack<Vertex> stk;
  // Vertex w{};
  if (G->getMark(v) == UNVISITED) {
    stk.push(G->first(v));
  }
  while (!stk.empty()) {
    Vertex w{stk.top()};
    stk.pop();
    PreVisit(G, w);
    G->setMark(w, VISITED);
    // Vertex w{G->first(curr_vertex)};
    for (Vertex w = G->first(v); w.get_index() < G->n(); w = G->next(v, w)) {
      if (G->getMark(w) == UNVISITED) {
        stk.push(w);
      }
    }
    PostVisit(G,w);
  }
}

void MyGraphAlgorithm::BFS(Graph *G, Vertex start,std::deque<Vertex> *Q){
    Vertex v;
    Vertex w;
    start.set_color(v_color::White);
    Q->emplace_back(start);
    G->setMark(start, VISITED);
    start.set_color(v_color::Gray);
    while(Q->size() != 0 ){
        v = *(Q->begin());
        // v = Q->front(); return a reference so when the element is deleted ,v is not existed.
        //front() back() and at() all return reference
        Q->pop_front();
        PreVisit(G, v); 
        for (w = G->first(v); w.get_index() < G->n(); w = G->next(v, w)){
            if(G->getMark(w) == UNVISITED){
                w.set_color(v_color::Gray);
                G->setMark(w, VISITED);
                Q->emplace_back(w);
            }
        }
        w.set_color(v_color::Black);
    }
}
} //end namespace mygraph