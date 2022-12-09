#include "Graph.h"

#include <set>
#include <iostream>

void Graph::addNode(unsigned int node) {
    graph[node] = std::set<unsigned int>();
}

void Graph::addRelation(unsigned int node, unsigned int relationToAdd) {
    graph[node].insert(relationToAdd);
}

bool Graph::nodeInGraph(unsigned int node) {
    return graph.count(node);
}

void Graph::printAdjacency() {
    std::map<unsigned int, std::set<unsigned int>>::iterator it;

    for (it = graph.begin(); it != graph.end(); it++)
    {
        std::cout << "R" << it->first << ":";

        std::set<unsigned int>::iterator it2;
        for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            if (it2 != it->second.begin()) {
                std::cout << ",";
            }
            std::cout << "R" << *it2;
        }
        std::cout << std::endl;
    }
}

Graph *Graph::reverse() {
    Graph* reverseGraph = new Graph();

    std::map<unsigned int, std::set<unsigned int>>::iterator it;

    for (it = graph.begin(); it != graph.end(); it++)
    {
        std::set<unsigned int>::iterator it2;
        for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            if (nodeInGraph(*it2)) {
                reverseGraph->addRelation(*it2, it->first);
            } else {
                reverseGraph->addNode(*it2);
                reverseGraph->addRelation(*it2, it->first);
            }
        }
    }

    return reverseGraph;
}

std::set<unsigned int> Graph::DFS(unsigned int node1, std::vector<unsigned int>& postOrder) {
    std::set<unsigned int> output;
    visitedNodes.insert(node1);
    std::set<unsigned int>::iterator it2;
    for (it2 = graph[node1].begin(); it2 != graph[node1].end(); it2++)
    {
        if (visitedNodes.find(*it2) == visitedNodes.end()) {
            std::set<unsigned int> result = this->DFS(*it2, postOrder);
            output.insert(result.begin(), result.end());
        }
    }
    postOrder.push_back(node1);
    output.insert(node1);
    return output;
}

void Graph::DFSF(std::vector<unsigned int> &postOrder) {
    std::map<unsigned int, std::set<unsigned int>>::iterator it;
    visitedNodes.clear();
    for (it = graph.begin(); it != graph.end(); it++)
    {
        if (visitedNodes.find(it->first) == visitedNodes.end()) {
            this->DFS(it->first, postOrder);
        }
    }
}

void Graph::DFSFscc(std::vector<unsigned int>& postOrder) {
    visitedNodes.clear();
    std::vector<unsigned int> empty;
    for (unsigned int i = 0; i < postOrder.size(); i++) {
        if (visitedNodes.find(postOrder.at(i)) == visitedNodes.end()) {
            sccs.push_back(this->DFS(postOrder.at(i), empty));
        }
    }
}

void Graph::printSCCs() {
    for (unsigned int i = 0; i < sccs.size(); i++) {
        std::set<unsigned int>::iterator it;
        for (it = sccs.at(i).begin(); it != sccs.at(i).end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}
