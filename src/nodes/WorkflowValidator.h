#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>

namespace nodes {

struct Node {
    std::string id;
    std::vector<std::string> outputs; // List of target node IDs
};

class WorkflowValidator {
public:
    static bool hasCycle(const std::map<std::string, Node>& nodes) {
        std::set<std::string> visited;
        std::set<std::string> recStack;

        for (auto const& [id, node] : nodes) {
            if (isCyclicUtil(id, nodes, visited, recStack)) {
                return true;
            }
        }
        return false;
    }

private:
    static bool isCyclicUtil(const std::string& id, const std::map<std::string, Node>& nodes,
                             std::set<std::string>& visited, std::set<std::string>& recStack) {
        if (visited.find(id) == visited.end()) {
            visited.insert(id);
            recStack.insert(id);

            auto it = nodes.find(id);
            if (it != nodes.end()) {
                for (const auto& neighbor : it->second.outputs) {
                    if (visited.find(neighbor) == visited.end() && isCyclicUtil(neighbor, nodes, visited, recStack)) {
                        return true;
                    } else if (recStack.find(neighbor) != recStack.end()) {
                        return true;
                    }
                }
            }
        }
        recStack.erase(id);
        return false;
    }
};

}
