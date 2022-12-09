#ifndef GRAPH_H
#define GRAPH_H

#include<map>
#include<set>
#include<vector>

class Graph {
private:
    std::map<unsigned int, std::set<unsigned int>> graph;
    std::set<unsigned int> visitedNodes;
    std::vector<std::set<unsigned int>> sccs;
public:
    void addNode(unsigned int node);
    void addRelation(unsigned int node, unsigned int relationToAdd);
    bool nodeInGraph(unsigned int node);
    Graph* reverse();
    std::set<unsigned int> DFS(unsigned int node1, std::vector<unsigned int>& postOrder);
    void DFSF(std::vector<unsigned int>& postOrder);
    void DFSFscc(std::vector<unsigned int>& postOrder);
    void printAdjacency();
    void printSCCs();
    unsigned int getSCCSize() {
        return sccs.size();
    }
    std::set<unsigned int> getsccs(unsigned int index) {
        return sccs.at(index);
    }
    std::string sccToSring(unsigned int index) {
        std::string output;
        std::set<unsigned int>::iterator it;
        for (it = sccs.at(index).begin(); it != sccs.at(index).end(); it++)
        {
            if (it != sccs.at(index).begin()) {
                output += ",";
            }
            output += "R" + std::to_string(*it);
        }
        return output;
    }
    bool hasSelfLoop(unsigned int index) {
        std::set<unsigned int> currentSCC = sccs.at(index);
        if (currentSCC.size() == 1) {
            unsigned int node = *currentSCC.begin();
            if (graph[node].find(node) == graph[node].end()) {
                return true;
            }
        }
        return false;
    }
};


#endif // GRAPH_H
