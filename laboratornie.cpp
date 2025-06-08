#include "header.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
//проверки
Graph::Graph(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        throw runtime_error("Не удалось открыть файл");
    }

    // Чтение количества вершин
    string line;
    if (!getline(inFile, line)) {
        throw runtime_error("Файл пуст");
    }

    istringstream iss(line);
    if (!(iss >> vertexCount) || vertexCount <= 0) {
        throw runtime_error("Некорректное количество вершин");
    }

    adjMatrix.resize(vertexCount, vector<bool>(vertexCount, false));

    // Чтение матрицы
    for (int i = 0; i < vertexCount; i++) {
        if (!getline(inFile, line)) {
            throw runtime_error("Недостаточно строк в матрице");
        }

        istringstream rowIss(line);
        for (int j = 0; j < vertexCount; j++) {
            int value;
            if (!(rowIss >> value)) {
                throw runtime_error("Некорректный элемент матрицы");
            }
            adjMatrix[i][j] = (value != 0);
        }

        if (adjMatrix[i][i] != 0) {
            throw runtime_error("Найден элемент на диагонали");
        }
    }

    // Проверка симметричности матрицы
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < i; j++) {
            if (adjMatrix[i][j] != adjMatrix[j][i]) {
                throw runtime_error("Матрица не смежна");
            }
        }
    }

    calculateEdges();
}
//подсчет вершин
void Graph::calculateEdges() {
    edgeCount = 0;
    for (int i = 0; i < vertexCount; i++) {
        for (int j = i + 1; j < vertexCount; j++) {
            if (adjMatrix[i][j]) {
                edgeCount++;
            }
        }
    }
}
//запись матрицы инцидентности
void Graph::writeIncidenceMatrix(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("Не удалось создать выходной файл");
    }

    outFile << vertexCount << " " << edgeCount << endl;

    vector<vector<int>> incMatrix(vertexCount, vector<int>(edgeCount, 0));

    int currentEdge = 0;
    for (int i = 0; i < vertexCount; i++) {
        for (int j = i + 1; j < vertexCount; j++) {
            if (adjMatrix[i][j]) {
                incMatrix[i][currentEdge] = 1;
                incMatrix[j][currentEdge] = 1;
                currentEdge++;
            }
        }
    }

    for (const auto& row : incMatrix) {
        for (size_t j = 0; j < row.size(); j++) {
            outFile << row[j];
            if (j != row.size() - 1) outFile << " ";
        }
        outFile << endl;
    }
}