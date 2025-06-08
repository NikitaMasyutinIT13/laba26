
#include <string>
#include <vector>
#include <stdexcept>

class Graph {
private:
    std::vector<std::vector<bool>> adjMatrix;
    int vertexCount;
    int edgeCount;

    void calculateEdges();
    void validateGraph() const;

public:
    Graph(const std::string& filename);
    void writeIncidenceMatrix(const std::string& filename) const;
};

