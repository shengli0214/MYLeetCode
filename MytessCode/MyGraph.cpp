#include "MyGraph.h"
#include "MyList.h"

mygraph::Vertex::Vertex(){
    index = 0;
    color = v_color::White;
    // time = 0;
}
mygraph::Vertex::Vertex(std::int32_t index){
    index = index;
    color = v_color::White;
    // time = 0;
}
mygraph::Vertex::Vertex(Vertex const & v):index(v.index), color(v.color) {

}
    
std::int32_t mygraph::Vertex::get_index() const {
    return index;
}

v_color mygraph::Vertex::get_color() const {
    return color;
}
// v_color Vertex::get_color(std::int32_t index){

// }

// std::int32_t Vertex::get_time() const {
//     return time;
// }

void mygraph::Vertex::set_index(std::int32_t index) { 
    index = index;
}
void mygraph::Vertex::set_color(v_color color) {
    color = color;
}
// void Vertex::set_time(std::int32_t time) {
//     time = time;
// }


mygraph::Graph1::~Graph1(){
    delete[] mark;
    for (std::int32_t i = 0; i < numVertex; ++i){
        delete[] vertex[i];
    };
}

void mygraph::Graph1::Init(std::int32_t n){
    std::int32_t i;
    numVertex = n;
    numEdge = 0;
    mark = new std::int32_t[n];
    for (i = 0; i < numVertex; ++i){
        mark[i] = UNVISITED; 
    }
    // Create and initialize adjacency lists
    vertex = (List<Edge>**) new List<Edge>*[numVertex];
    for (i = 0; i < numVertex; i++){
        vertex[i] = new LList<Edge>();
    }
}
// Number of vertices
std::int32_t mygraph::Graph1::n(){
    return numVertex;
}

std::int32_t mygraph::Graph1::e(){
    return numEdge;
}

// Return first neighbor of "v"
mygraph::Vertex mygraph::Graph1::first(Vertex v){
    Vertex reValue;
    
    if(vertex[v.get_index()]->length() == 0){
        reValue.set_index(numVertex);
    }else{
        vertex[v.get_index()]->moveToStart();
        Edge it = vertex[v.get_index()]->getValue();
        reValue = it.vertex();
    }
    return reValue;
}

// Get v’s next neighbor after w
mygraph::Vertex mygraph::Graph1::next(Vertex v, Vertex w) {
    Edge it;
    Vertex ReValue(n());
    if (isEdge(v, w)) {
        if ((vertex[v.get_index()]->currPos()+1) < vertex[v.get_index()]->length()) {
            vertex[v.get_index()]->next();
            it = vertex[v.get_index()]->getValue();
        return it.vertex();
        }
    }
    return ReValue; // No neighbor
}
// Set edge (i, j) to "weight"
void mygraph::Graph1::setEdge(Vertex i,Vertex j,std::int32_t weight){
    Assert(weight > 0, "May not set weight to 0");
    Edge currEdge(j, weight);
    if(isEdge(i,j)){
        // Edge already exists in graph
        vertex[i.get_index()]->remove();
        vertex[i.get_index()]->insert((currEdge));
    }else{
        // Keep neighbors sorted by vertex index
        numEdge++;
        for (vertex[i.get_index()]->moveToStart();
        vertex[i.get_index()]->currPos() < vertex[i.get_index()]->length();
        vertex[i.get_index()]->next()) {
            Edge temp = vertex[i.get_index()]->getValue();
                if (temp.vertex().get_index() > j.get_index()) {
                    break;
                }
        }
        vertex[i.get_index()]->insert(currEdge);

    }
}

// Delete edge (i, j)
void mygraph::Graph1::delEdge(Vertex i, Vertex j) { 
    if (isEdge(i,j)) {
        vertex[i.get_index()]->remove();
        numEdge--;
    }
}

// is (i,j) an edge?
bool mygraph::Graph1::isEdge(Vertex i, Vertex j){
    Edge it;
    bool ReValue = false;
    // check whole list
    for (vertex[i.get_index()]->moveToStart(); 
    vertex[i.get_index()]->currPos() < vertex[i.get_index()]->length(); 
    vertex[i.get_index()]->next()){
        Edge temp = vertex[i.get_index()]->getValue();

        if (temp.vertex().get_index() == j.get_index()){
            ReValue = true;
        }
    }
    return ReValue;
}

std::int32_t mygraph::Graph1::weight(Vertex i,Vertex j){
    Edge curr;
    std::int32_t ReValue(0);
    if(isEdge(i,j)){
        curr = vertex[i.get_index()]->getValue();
        ReValue = curr.weight();
    }
    return ReValue;
}

std::int32_t mygraph::Graph1::getMark(Vertex v){
    return mark[v.get_index()];
}

void mygraph::Graph1::setMark(Vertex v,std::int32_t val){
    mark[v.get_index()] = val;
}

mygraph::Graphm::Graphm(std::int32_t numVert){
    Init(numVert);
}

mygraph::Graphm::~Graphm(){
    delete[] mark;
    for (std::int32_t i = 0; i < numVertex; i++){
        delete[] matrix[i];
        delete[] matrix;
    }
}

void mygraph::Graphm::Init(std::int32_t n){
    std::int32_t i;
    numVertex = n;
    numEdge = 0;
    mark = new int[n];

    // make matrix
    for (i = 0; i < numVertex;i++){
        mark[i] = UNVISITED;
    }
    matrix = (std::int32_t **) new int *[numVertex];
    for (i = 0; i < numVertex;i++){
        matrix[i] = new int[numVertex];
    }
    //Initialize to 0 weights
    for (i = 0; i < numVertex;i++){
        for (std::int32_t j = 0; j < numVertex;j++){
            matrix[i][j] = 0;
        }
    }
}

std::int32_t mygraph::Graphm::n(){
    return numVertex;
}

std::int32_t mygraph::Graphm::e(){
    return numEdge;
}

mygraph::Vertex mygraph::Graphm::first(Vertex v){
    Vertex reValue;
    reValue.set_index(numVertex);

    for (std::int32_t i = 0; i < numVertex;i++){
        if (matrix[v.get_index()][i] != 0){
            reValue.set_index(i);
            break;
        }
        
    }
    return reValue;
}

// Return v’s next neighbor after w
mygraph::Vertex mygraph::Graphm::next(Vertex v, Vertex w) {
    Vertex reValue(numVertex);
    for(std::int32_t i = w.get_index() + 1; i < numVertex; i++){
        if (matrix[v.get_index()][i] != 0){
            reValue =  i;
            break;
        }
    }
    // Return n if none
    return reValue;
}

// Set edge (v1, v2) to "wt"
void mygraph::Graphm::setEdge(Vertex v1, Vertex v2, std::int32_t wt){
    Assert(wt > 0, "Illegal weight value");
    if (matrix[v1.get_index()][v2.get_index()] == 0){
        numEdge++;
    }
    matrix[v1.get_index()][v2.get_index()] = wt;
}

// Delete edge (v1, v2)
void mygraph::Graphm::delEdge(Vertex v1, Vertex v2) { 
    if (matrix[v1.get_index()][v2.get_index()] != 0){
        numEdge--;
    }
    matrix[v1.get_index()][v2.get_index()] = 0;
}

 // Is (i, j) an edge?
bool mygraph::Graphm::isEdge(Vertex i,Vertex j){
    return matrix[i.get_index()][j.get_index()] != 0;
}

std::int32_t mygraph::Graphm::weight(Vertex v1,Vertex v2){
    return matrix[v1.get_index()][v2.get_index()];
}

std::int32_t mygraph::Graphm::getMark(Vertex v){
    return mark[v.get_index()];
}

void mygraph::Graphm::setMark(Vertex v,std::int32_t val){
    mark[v.get_index()] = val;
}