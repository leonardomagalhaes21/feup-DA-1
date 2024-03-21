#include "WaterSupplyManager.h"
#include <iostream>

using namespace std;


// Function to test the given vertex 'w' and visit it if conditions are met
template<class T>
void testAndVisit(std::queue<Vertex<T> *> &q, Edge<T> *e, Vertex<T> *w, int residual) {
// Check if the vertex 'w' is not visited and there is residual capacity
    if (!w->isVisited() && residual > 0) {
// Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
template<class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
// Mark all vertices as not visited
    for (auto v: g->getVertexSet()) {
        v->setVisited(false);
    }
// Mark the source vertex as visited and enqueue it
    s->setVisited(true);
    std::queue<Vertex<T> *> q;
    q.push(s);
// BFS to find an augmenting path
    while (!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
// Process outgoing edges
        for (auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
// Process incoming edges
        for (auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
// Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

// Function to find the minimum residual capacity along the augmenting path
template<class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double f = INF;
// Traverse the augmenting path to find the minimum residual capacity
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        } else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
// Return the minimum residual capacity
    return f;
}

// Function to augment flow along the augmenting path with the given flow value
template<class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, int f) {
// Traverse the augmenting path and update the flow values accordingly
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        } else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

// Main function implementing the Edmonds-Karp algorithm
template<class T>
int edmondsKarp(Graph<T> *g, T source, T target) {
// Find source and target vertices in the graph
    Vertex<T> *s = g->findVertex(source);
    Vertex<T> *t = g->findVertex(target);
// Validate source and target vertices
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
// Initialize flow on all edges to 0
    for (auto v: g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
// While there is an augmenting path, augment the flow along the path
    while (findAugmentingPath(g, s, t)) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }


    int maxFlow = 0;
    for (auto e: s->getAdj()) {
        maxFlow += e->getFlow();
    }

    return maxFlow;
}

WaterSupplyManager::WaterSupplyManager(const Data &d) {
    reservoirs = d.getReservoirs();
    stations = d.getStations();
    sites = d.getSites();
    graph = d.getGraph();
}

int WaterSupplyManager::pumpMaxFlow() {
    string superSource = "superSource";
    string superSink = "superSink";

    graph.addVertex(superSource);
    graph.addVertex(superSink);
    for (auto vertex: graph.getVertexSet()) {
        if (vertex->getSel() == 1) {
            int delivery = reservoirs.find(vertex->getCode())->second.getMaxDelivery();
            graph.addEdge("superSource", vertex->getCode(), delivery);
        }
        if (vertex->getSel() == 3) {
            graph.addEdge(vertex->getCode(), "superSink", INT_MAX);
        }
    }

    int maxFlow = edmondsKarp(&graph, superSource, superSink);

    for (auto v: graph.getVertexSet()) {
        for (auto e: v->getAdj()) {
            if (e->getDest()->getSel() == 3) {
                e->getDest()->setFlow(e->getDest()->getFlow() + e->getFlow());
            }
        }
    }

    graph.removeVertex(superSource);
    graph.removeVertex(superSink);

    return maxFlow;
}

void WaterSupplyManager::resetFlow() {
    for (auto v: graph.getVertexSet()) {
        v->setFlow(0);
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
}

void WaterSupplyManager::maxFlowToCities() {
    int maxFlow = pumpMaxFlow();
    cout << "The maximum flow of the full network is: " << maxFlow << endl;

    ofstream out("../docs/results/maxFlow.txt");

    for (auto v: graph.getVertexSet()) {
        if (v->getSel() == 3) {
            cout << "City: " << v->getCode() << '\t' << "Max Flow: " << v->getFlow() << endl;
            out << "City: " << v->getCode() << '\t' << "Max Flow: " << v->getFlow() << endl;

        }
    }

    resetFlow();
    out.close();
}

void WaterSupplyManager::demandCoverage() {
    pumpMaxFlow();
    ofstream out("../docs/results/demandCoverage.txt");


    for (auto v: graph.getVertexSet()) {
        if (v->getSel() == 3) {
            int coverage = v->getFlow();
            double demand = sites.find(v->getCode())->second.getDemand();
            double deficit = demand - coverage;
            if (deficit > 0) {
                cout << "City: " << v->getCode() << '\t' << "Deficit: " << deficit << endl;
                out << "City: " << v->getCode() << '\t' << "Deficit: " << deficit << endl;
            }
        }
    }

    resetFlow();
    out.close();
}

void WaterSupplyManager::evaluateReservoirImpact(string reservoirToRemove) {
    Graph<string> temp = graph;
    Graph<string> temp1 = graph;
    string superSource1 = "superSource";
    string superSink1 = "superSink";

    temp1.addVertex(superSource1);
    temp1.addVertex(superSink1);
    for (auto vertex: temp1.getVertexSet()) {
        if (vertex->getSel() == 1) {
            temp1.addEdge("superSource", vertex->getCode(), INT_MAX);
        }
        if (vertex->getSel() == 3) {
            temp1.addEdge(vertex->getCode(), "superSink", INT_MAX);
        }
    }
    int completeMaxFlowinohio = edmondsKarp(&temp1, superSource1, superSink1);

    // Find the reservoir vertex to remove
    Vertex<string> *reservoir = temp.findVertex(reservoirToRemove);
    if (reservoir == nullptr || reservoir->getSel() != 1) {
        cout << "Reservoir not found" << endl;
        // Reservoir not found, return empty set
        return;
    }

    // Remove outgoing edges from the reservoir
    reservoir->removeOutgoingEdges();

    string superSource = "superSource";
    string superSink = "superSink";

    temp.addVertex(superSource);
    temp.addVertex(superSink);
    for (auto vertex: temp.getVertexSet()) {
        if (vertex->getSel() == 1) {
            temp.addEdge("superSource", vertex->getCode(), INT_MAX);
        }
        if (vertex->getSel() == 3) {
            temp.addEdge(vertex->getCode(), "superSink", INT_MAX);
        }
    }

    int completeMaxFlow = edmondsKarp(&temp, superSource, superSink);
    cout << "The maximum flow of the full network is: " << completeMaxFlow << endl;

    for (auto v: temp.getVertexSet()) {
        for (auto e: v->getAdj()) {
            if (e->getDest()->getSel() == 3) {
                e->getDest()->setFlow(e->getDest()->getFlow() + e->getFlow());
            }
        }
    }

    for (auto v: temp.getVertexSet()) {
        if (v->getSel() == 3) {
            int coverage = v->getFlow();
            double demand = sites.find(v->getCode())->second.getDemand();
            double deficit = demand - coverage;
            if (deficit > 0) {
                cout << "City: " << v->getCode() << '\t' << "Deficit: " << deficit << endl;
            }
        }
    }

    cout << "The difference in total maximum flow of the whole network is: " << completeMaxFlowinohio - completeMaxFlow
         << endl;
}

void WaterSupplyManager::evaluatePumpingImpact(string pumpingToRemove) {
    Graph<string> temp = graph;
    Graph<string> temp1 = graph;
    string superSource1 = "superSource";
    string superSink1 = "superSink";

    temp1.addVertex(superSource1);
    temp1.addVertex(superSink1);
    for (auto vertex: temp1.getVertexSet()) {
        if (vertex->getSel() == 1) {
            temp1.addEdge("superSource", vertex->getCode(), INT_MAX);
        }
        if (vertex->getSel() == 3) {
            temp1.addEdge(vertex->getCode(), "superSink", INT_MAX);
        }
    }
    int completeMaxFlowinohio = edmondsKarp(&temp1, superSource1, superSink1);
    // Find the reservoir vertex to remove
    Vertex<string> *pumpingStation = temp.findVertex(pumpingToRemove);
    if (pumpingStation == nullptr || pumpingStation->getSel() != 2) {
        cout << "Pumping station not found" << endl;
        // Puping station not found, return empty set
        return;
    }

    // Remove outgoing edges from the pumping station
    pumpingStation->removeOutgoingEdges();

    string superSource = "superSource";
    string superSink = "superSink";

    temp.addVertex(superSource);
    temp.addVertex(superSink);
    for (auto vertex: temp.getVertexSet()) {
        if (vertex->getSel() == 1) {
            temp.addEdge("superSource", vertex->getCode(), INT_MAX);
        }
        if (vertex->getSel() == 3) {
            temp.addEdge(vertex->getCode(), "superSink", INT_MAX);
        }
    }

    int completeMaxFlow = edmondsKarp(&temp, superSource, superSink);
    cout << "The maximum flow of the full network is: " << completeMaxFlow << endl;

    for (auto v: temp.getVertexSet()) {
        for (auto e: v->getAdj()) {
            if (e->getDest()->getSel() == 3) {
                e->getDest()->setFlow(e->getDest()->getFlow() + e->getFlow());
            }
        }
    }

    for (auto v: temp.getVertexSet()) {
        if (v->getSel() == 3) {
            int coverage = v->getFlow();
            double demand = sites.find(v->getCode())->second.getDemand();
            double deficit = demand - coverage;
            if (deficit > 0) {
                cout << "City: " << v->getCode() << '\t' << "Deficit: " << deficit << endl;
            }
        }
    }

    cout << "The difference in total maximum flow of the whole network is: " << completeMaxFlowinohio - completeMaxFlow
         << endl;

}

void WaterSupplyManager::evaluateEdgeImpact(const string &source, const string &destination) {
    // Find the vertices corresponding to the edge
    Graph<string> temp = graph;
    Graph<string> temp1 = graph;
    string superSource1 = "superSource";
    string superSink1 = "superSink";

    temp1.addVertex(superSource1);
    temp1.addVertex(superSink1);
    for (auto vertex: temp1.getVertexSet()) {
        if (vertex->getSel() == 1) {
            temp1.addEdge("superSource", vertex->getCode(), INT_MAX);
        }
        if (vertex->getSel() == 3) {
            temp1.addEdge(vertex->getCode(), "superSink", INT_MAX);
        }
    }
    int completeMaxFlowinohio = edmondsKarp(&temp1, superSource1, superSink1);

    Vertex<string> *sourceVertex = temp.findVertex(source);
    Vertex<string> *destinationVertex = temp.findVertex(destination);

    if (sourceVertex == nullptr || destinationVertex == nullptr) {
        // One of the vertices doesn't exist, handle the error as needed
        cout << "One of the vertices doesn't exist" << endl;
        return;
    }
    temp.removeEdge(sourceVertex->getCode(), destinationVertex->getCode());
    // Remove the edge from the source vertex
    sourceVertex->removeEdge(destination);

    string superSource = "superSource";
    string superSink = "superSink";

    temp.addVertex(superSource);
    temp.addVertex(superSink);
    for (auto vertex: temp.getVertexSet()) {
        if (vertex->getSel() == 1) {
            temp.addEdge("superSource", vertex->getCode(), INT_MAX);
        }
        if (vertex->getSel() == 3) {
            temp.addEdge(vertex->getCode(), "superSink", INT_MAX);
        }
    }

    int completeMaxFlow = edmondsKarp(&temp, superSource, superSink);
    cout << "The maximum flow of the full network is: " << completeMaxFlow << endl;

    for (auto v: temp.getVertexSet()) {
        for (auto e: v->getAdj()) {
            if (e->getDest()->getSel() == 3) {
                e->getDest()->setFlow(e->getDest()->getFlow() + e->getFlow());
            }
        }
    }

    for (auto v: temp.getVertexSet()) {
        if (v->getSel() == 3) {
            int coverage = v->getFlow();
            double demand = sites.find(v->getCode())->second.getDemand();
            double deficit = demand - coverage;
            if (deficit > 0) {
                cout << "City: " << v->getCode() << '\t' << "Deficit: " << deficit << endl;
            }
        }
    }

    cout << "The difference in total maximum flow of the whole network is: " << completeMaxFlowinohio - completeMaxFlow
         << endl;
}

