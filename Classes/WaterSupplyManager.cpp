#include "WaterSupplyManager.h"
#include <iostream>

using namespace std;


// Function to test the given vertex 'w' and visit it if conditions are met
template<class T>
void testAndVisit(queue<Vertex<T> *> &q, Edge<T> *e, Vertex<T> *w, int residual) {
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
    queue<Vertex<T> *> q;
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
            f = min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        } else {
            f = min(f, e->getFlow());
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
        throw logic_error("Invalid source and/or target vertex");
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

WaterSupplyManager::WaterSupplyManager() {
    reservoirs = {};
    stations = {};
    sites = {};
    graph = {};
}

int WaterSupplyManager::pumpMaxFlow() {
    string superSource = "superSource";
    string superSink = "superSink";

    graph.addVertex(superSource);
    graph.addVertex(superSink);
    for (auto vertex: graph.getVertexSet()) {
        if (vertex->getSel() == 1) {
            int delivery = reservoirs.find(vertex->getCode())->second.getMaxDelivery();
            graph.addEdge(superSource, vertex->getCode(), delivery);
        }
        if (vertex->getSel() == 3) {
            int demand = sites.find(vertex->getCode())->second.getDemand();
            graph.addEdge(vertex->getCode(), superSink, demand);
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

void WaterSupplyManager::evaluateVertexRemoval(const string &vertex) {
    int completeMaxFlowFirst = pumpMaxFlow();
    vector<pair<string, int>> first;

    for (const auto &v: graph.getVertexSet()) {
        if (v->getSel() == 3) {
            auto p = make_pair(v->getCode(), v->getFlow());
            first.push_back(p);
        }

    }

    Vertex<string> *ver = graph.findVertex(vertex);
    if (ver == nullptr || (ver->getSel() != 1 && ver->getSel() != 2)) {

        cout << "Vertex not found" << endl;
        return;
    }

    resetFlow();

    graph.removeVertex(vertex);

    if (ver->getSel() == 1) {
        reservoirs.erase(vertex);
    } else if (ver->getSel() == 2) {
        stations.erase(vertex);
    } else {
        cout << "Vertex not found!" << endl;
    }

    int completeMaxFlow = pumpMaxFlow();
    cout << "The maximum flow of the full network is: " << completeMaxFlow << endl;
    vector<pair<string, int>> second;

    for (const auto &v: graph.getVertexSet()) {
        if (v->getSel() == 3) {
            auto p = make_pair(v->getCode(), v->getFlow());
            second.push_back(p);
        }

    }

    for (auto v: graph.getVertexSet()) {
        if (v->getSel() == 3) {
            int coverage = v->getFlow();
            double demand = sites.find(v->getCode())->second.getDemand();
            double deficit = demand - coverage;
            if (deficit > 0) {
                cout << "City: " << v->getCode() << '\t' << "Deficit: " << deficit << endl;
            }
        }
    }

    cout << "The difference in total maximum flow of the whole network is: " << completeMaxFlowFirst - completeMaxFlow
         << "\n" << endl;
    if (completeMaxFlowFirst - completeMaxFlow == 0) {
        cout << "No cities were affected" << endl;
    }

    for (const auto &a: second) {
        for (const auto &b: first) {
            if (a.first == b.first) {
                double difference = b.second - a.second;
                if (difference > 0) {
                    cout << "City: " << b.first << " before had " << b.second << endl;
                    cout << "Now has " << a.second << "\n" << endl;
                }
            }
        }
    }

    resetFlow();

}


void WaterSupplyManager::evaluateEdgeRemoval(const string &source, const string &destination) {

    int completeMaxFlowFirst = pumpMaxFlow();
    vector<pair<string, int>> first;

    for (const auto &v: graph.getVertexSet()) {
        if (v->getSel() == 3) {
            auto p = make_pair(v->getCode(), v->getFlow());
            first.push_back(p);
        }
    }

    resetFlow();
    Vertex<string> *sourceVertex = graph.findVertex(source);
    Vertex<string> *destinationVertex = graph.findVertex(destination);

    if (sourceVertex == nullptr || destinationVertex == nullptr) {
        cout << "One of the vertices doesn't exist" << endl;
        return;
    }


    graph.removeEdge(source, destination);
    graph.removeEdge(destination, source);

    int completeMaxFlow = pumpMaxFlow();
    cout << "The maximum flow of the full network is: " << completeMaxFlow << endl;

    vector<pair<string, int>> second;

    for (const auto &v: graph.getVertexSet()) {
        if (v->getSel() == 3) {
            auto p = make_pair(v->getCode(), v->getFlow());
            second.push_back(p);
        }

    }

    for (auto v: graph.getVertexSet()) {
        if (v->getSel() == 3) {
            int coverage = v->getFlow();
            double demand = sites.find(v->getCode())->second.getDemand();
            double deficit = demand - coverage;
            if (deficit > 0) {
                cout << "City: " << v->getCode() << '\t' << "Deficit: " << deficit << endl;
            }
        }
    }

    cout << "The difference in total maximum flow of the whole network is: " << completeMaxFlowFirst - completeMaxFlow
         << "\n" << endl;
    if (completeMaxFlowFirst - completeMaxFlow == 0) {
        cout << "No cities were affected" << endl;
    }

    for (const auto &a: second) {
        for (const auto &b: first) {
            if (a.first == b.first) {
                double difference = b.second - a.second;
                if (difference > 0) {
                    cout << "City: " << b.first << " before had " << b.second << endl;
                    cout << "Now has " << a.second << "\n" << endl;
                }
            }
        }
    }

    resetFlow();

}


void WaterSupplyManager::printCitiesDetails() {
    cout << left << setw(15) << "City"
         << setw(20) << "Name"
         << setw(10) << "Demand"
         << setw(15) << "Population" << endl;

    for (const auto &vertex: graph.getVertexSet()) {
        if (vertex->getSel() == 3) {
            auto city = sites.find(vertex->getCode());
            if (city != sites.end()) {
                cout << left << setw(15) << vertex->getCode()
                     << setw(20) << city->second.getName()
                     << setw(10) << city->second.getDemand()
                     << setw(15) << city->second.getPopulation()
                     << endl;
            }
        }
    }
}

void WaterSupplyManager::printReservoirsDetails() {
    cout << left << setw(15) << "Reservoir"
         << setw(20) << "Name"
         << setw(20) << "Municipality"
         << setw(15) << "Max Delivery" << endl;

    for (const auto &vertex: graph.getVertexSet()) {
        if (vertex->getSel() == 1) {
            auto reservoir = reservoirs.find(vertex->getCode());
            if (reservoir != reservoirs.end()) {
                cout << left << setw(15) << vertex->getCode()
                     << setw(20) << reservoir->second.getName()
                     << setw(20) << reservoir->second.getMunicipality()
                     << setw(15) << reservoir->second.getMaxDelivery()
                     << endl;
            }
        }
    }
}

void WaterSupplyManager::printStationsDetails() {
    for (const auto &vertex: graph.getVertexSet()) {
        if (vertex->getSel() == 2) {
            auto station = stations.find(vertex->getCode());
            if (station != stations.end()) {
                cout << "Pumping Station: " << vertex->getCode() << endl;
            }
        }
    }
}