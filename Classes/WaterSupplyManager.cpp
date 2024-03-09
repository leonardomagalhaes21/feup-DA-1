#include "WaterSupplyManager.h"
#include <iostream>
using namespace std;




// Function to test the given vertex 'w' and visit it if conditions are met
template <class T>
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, int residual) {
// Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
// Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}
// Function to find an augmenting path using Breadth-First Search
template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
// Mark all vertices as not visited
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
// Mark the source vertex as visited and enqueue it
    s->setVisited(true);
    std::queue<Vertex<T> *> q;
    q.push(s);
// BFS to find an augmenting path
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
// Process outgoing edges
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
// Process incoming edges
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
// Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

// Function to find the minimum residual capacity along the augmenting path
template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double f = INF;
// Traverse the augmenting path to find the minimum residual capacity
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
// Return the minimum residual capacity
    return f;
}
// Function to augment flow along the augmenting path with the given flow value
template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, int f) {
// Traverse the augmenting path and update the flow values accordingly
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

// Main function implementing the Edmonds-Karp algorithm
template <class T>
int edmondsKarp(Graph<T> *g, T source, T target) {
// Find source and target vertices in the graph
    Vertex<T>* s = g->findVertex(source);
    Vertex<T>* t = g->findVertex(target);
// Validate source and target vertices
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
// Initialize flow on all edges to 0
    for (auto v : g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
// While there is an augmenting path, augment the flow along the path
    while( findAugmentingPath(g, s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }


    int maxFlow = 0;
    for (auto e : s->getAdj()) {
        maxFlow += e->getFlow();
    }

    return maxFlow;
}

WaterSupplyManager::WaterSupplyManager(const Data& d) {
    reservoirs = d.getReservoirs();
    stations = d.getStations();
    sites = d.getSites();
    graph = d.getGraph();
}

void WaterSupplyManager::maxFlowToCities() {
    Graph<string> temp = graph;
    string superSource = "superSource";
    string superSink = "superSink";

    temp.addVertex(superSource);
    temp.addVertex(superSink);
    for (auto vertex : temp.getVertexSet()){
        if (vertex->getSel() == 1){
            temp.addEdge("superSource", vertex->getCode(), INT_MAX);
        }
        if (vertex->getSel() == 3){
            temp.addEdge(vertex->getCode(), "superSink", INT_MAX);
        }
    }

    int completeMaxFlow = edmondsKarp(&temp,superSource, superSink);
    cout << "The maximum flow of the full network is: " << completeMaxFlow << endl;

    ofstream out("../docs/results/maxFlow.txt");

    for (auto v : temp.getVertexSet()){
        if (v->getSel() == 3){
            int maxFlow = edmondsKarp(&temp, superSource, v->getCode());
            cout << "City: " << v->getCode() << '\t' << "Max Flow: " << maxFlow << endl;
            out <<  "City: " << v->getCode() << '\t' << "Max Flow: " << maxFlow << endl;

            maxFlows[v->getCode()] = maxFlow;
        }
    }

    out.close();
}

void WaterSupplyManager::demandCoverage() {
    ofstream out("../docs/results/demandCoverage.txt");

    for (auto v : graph.getVertexSet()){
        if (v->getSel() == 3){
            int coverage = maxFlows.find(v->getCode())->second;
            double demand = sites.find(v->getCode())->second.getDemand();
            double deficit = demand - coverage;
            if (deficit > 0){
                cout << "City: " << v->getCode() << '\t' << "Deficit: " << deficit << endl;
                out << "City: " << v->getCode() << '\t' << "Deficit: " << deficit << endl;
            }
        }
    }

    out.close();
}

