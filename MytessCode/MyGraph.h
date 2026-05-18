/*** 
 * @Author: shengli.liu
 * @Date: 2024-06-28 14:26:21
 * @Description: 
 * @
 * @LastEditors: shengli.liu shengli.liu@hongjingdrive.com
 * @LastEditTime: 2024-07-18 11:16:21
 */


#ifndef MYGRAPH_H
#define MYGRAPH_H
#include <climits>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <array>
#include <cassert>
#include <list>
#include <cstdint>

#include "MyList.h"
enum class v_color{White, Gray, Black};
namespace mygraph
{
    
class Vertex{
private:
    std::int32_t index; // somewhere also name
    v_color color;
    
    // std::int32_t time;
public:
    Vertex();
    Vertex(std::int32_t index);
    Vertex(Vertex const &v);

    std::int32_t get_index() const;
    v_color get_color() const;
    // std::int32_t get_time() const;
    void set_index(std::int32_t index);
    void set_color(v_color color);
    // void set_time(std::int32_t time);
    // v_color get_color(std::int32_t index);
};
// namespace LinkTable
// {
class Graph{
private:
    void operator =(const Graph&) {} // Protect assignment
    Graph(const Graph&) {} // Protect copy constructor
public:
    // Default constructor
    Graph() {} // Default constructor
    virtual ~Graph() {} // Base destructor

    // Initialize a graph of n vertices
    virtual void Init(int n) = 0;

    // Return: the number of vertices and edges
    virtual std::int32_t n() = 0;
    virtual std::int32_t e() = 0;
    // Return v’s first neighbor
    virtual Vertex first(Vertex v) = 0;
    // Return v’s next neighbor
    virtual Vertex next(Vertex v, Vertex w) = 0;
    // Set the weight for an edge
    // i, j: The vertices
    // wgt: Edge weight
    virtual void setEdge(Vertex v1, Vertex v2, std::int32_t wght) = 0;
    // Delete an edge
    // i, j: The vertices
    virtual void delEdge(Vertex v1, Vertex v2) = 0;
    // Determine if an edge is in the graph
    // i, j: The vertices
    // Return: true if edge i,j has non-zero weight
    virtual bool isEdge(Vertex i, Vertex j) = 0;
    // Return an edge’s weight
    // i, j: The vertices
    // Return: The weight of edge i,j, or zero
    virtual std::int32_t weight(Vertex v1, Vertex v2) = 0;
    // Get and Set the mark value for a vertex
    // v: The vertex
    // val: The value to set
    virtual std::int32_t getMark(Vertex v) = 0;
    virtual void setMark(Vertex v, std::int32_t val) = 0;
    

};


class Edge {
public:
    Edge(){
        vert.set_index(-1);
        vert.set_color(v_color::White);
        // vert.set_time(0);
        wt = -1;
    };
    Edge(Vertex v, std::int32_t w):vert(v),wt(w) {

    }
    Vertex vertex() const { 
        return vert; 
    }
    std::int32_t weight() const{
        return wt;
    }
    // void set_color(v_color incolor){
    //     color = incolor;
    // }
    // v_color get_color() const {
    //     return color;
    // }
private:
    Vertex vert;//vertiv
    std::int32_t wt;//weight

    // v_color color = v_color::White;
};

// enum class MarkType:std::int32_t{UNVISITED,VISITED};
// using UNVISITED = std::int32_t
// #define UNVISITED 0
// #define VISITED 1
constexpr std::int32_t UNVISITED{0U};
constexpr std::int32_t VISITED{1U};
class Graph1 : public Graph{
private:
    List<Edge> **vertex;
    std::int32_t numVertex;
    std::int32_t numEdge;
    std::int32_t* mark;
public:
    Graph1(std::int32_t numVert){
        Init(numVert);
    };
    ~Graph1();
    void Init(std::int32_t n);
    std::int32_t n() override;
    std::int32_t e() override;
    Vertex first(Vertex v) override;
    // Return v’s next neighbor
    Vertex next(Vertex v, Vertex w) override;
    // Set the weight for an edge
    // i, j: The vertices
    // wgt: Edge weight
    void setEdge(Vertex v1, Vertex v2, std::int32_t wght) override;
    // Delete an edge
    // i, j: The vertices
    void delEdge(Vertex v1, Vertex v2) override;
    // Determine if an edge is in the graph
    // i, j: The vertices
    // Return: true if edge i,j has non-zero weight
    bool isEdge(Vertex i, Vertex j) override;
    // Return an edge’s weight
    // i, j: The vertices
    // Return: The weight of edge i,j, or zero
    std::int32_t weight(Vertex v1, Vertex v2) override;
    // Get and Set the mark value for a vertex
    // v: The vertex
    // val: The value to set
    std::int32_t getMark(Vertex v) override;
    void setMark(Vertex v, std::int32_t val) override;
    // void setMark(Vertex v,MarkType val);
};

class Graphm : public Graph{
private:
    std::int32_t numVertex;
    std::int32_t numEdge; // Store number of vertices, edges
    std::int32_t **matrix; // Pointer to adjacency matrix
    std::int32_t *mark; // Pointer to mark array
public:
    // Construct
    Graphm(std::int32_t numVert);
     // Destructor
    ~Graphm();
    void Init(std::int32_t n);
    std::int32_t n() override;
    std::int32_t e() override;
    Vertex first(Vertex v) override;
    // Return v’s next neighbor
    Vertex next(Vertex v, Vertex w) override;
    // Set the weight for an edge
    // i, j: The vertices
    // wgt: Edge weight
    void setEdge(Vertex v1, Vertex v2, std::int32_t wght) override;
    // Delete an edge
    // i, j: The vertices
    void delEdge(Vertex v1, Vertex v2) override;
    // Determine if an edge is in the graph
    // i, j: The vertices
    // Return: true if edge i,j has non-zero weight
    bool isEdge(Vertex i, Vertex j) override;
    // Return an edge’s weight
    // i, j: The vertices
    // Return: The weight of edge i,j, or zero
    std::int32_t weight(Vertex v1, Vertex v2) override;
    // Get and Set the mark value for a vertex
    // v: The vertex
    // val: The value to set
    std::int32_t getMark(Vertex v) override;
    void setMark(Vertex v, std::int32_t val) override;
};
} // namespace mygraph

// template<typename W>
// struct Edge{
// public:
//     size_t _destIndex; //Index of the destination vertex in the edge
//     W _weightedValue;  //weighted value
//     struct Edge* _next; 
//     //Edge> _next
//     //Constructed function
//     Edge(size_t _destIndex, W const& _weightedValue)
//     :_destIndex(_destIndex), _weightedValue(_weightedValue),_next(nullptr) {
//     }
// }; //end class edge
// template<class V, class W, W MAX_W = INT_MAX, bool Direction = false>
// class Graph
// {
//     using Edge<W> Edge;
// public:
//     Graph(std::array<V> const &arr, size_t size){//? V* arr or std::array<V>&
//         // Insert Vertex to a one-dimensional array
//         // and Establish a mapping between vertices and subscripts
//         for (size_t i = 0; i < size; ++i){
//             _vertex.emplace(arr.at(i));
//             _valIndexMap(arr.at(i)) = i;
//         };
//         //Initialize the adjacency list
//         _edges.resize(size,nullptr);
//     }
//     size_t GetIndex(V const& val){
//             size_t retVal = -1;
//             auto pos = _valIndexMap.find(val);
//             if (pos != _valIndexMap.end()){
//                 retVal = pos->second;
//             }else{
//                 assert(false);   
//             }
//             return retVal;
//         };
//     void addEdge(V const& src,V const& dst,W const& weight){
//         size_t srci = GetIndex(src);
//         size_t dsti = GetIndex(dst);
//         // construct the relationship from src to dst
//         std::unique_ptr<Edge> edge1 = new Edge(dsti, weight); //why not use intelligence pointer after Edge call
//         // Edge* edge1 = new Edge(dsti, w);
//         edge1->_next = _edges->
//     }
// private:
//     std::vector<V> _vertex;
//     std::unordered_map<V, size_t> _valIndexMap;
//     std::vector<Edge*> _edges;
// };//end Graph
// }// end namespace LinkTable

#endif // MYGRAPH_H