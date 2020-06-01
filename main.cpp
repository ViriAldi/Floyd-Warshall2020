#include <iostream>
#include <vector>
#include <limits>


std::vector<std::vector<int>> read_graph(){
    std::vector<std::vector<int>> graph;
    int v;
    std::cout << "Enter the number of vertices" << std::endl;
    std::cin >> v;

    for (int row = 0; row < v; row++){
        std::vector<int> r;
        for (int col = 0; col < v; col++){
            r.push_back(-1);
        }
        graph.push_back(r);
    }

    std::cout << "In each line input three space-separate integers: "
                 "first vertex, second vertex, weight of the edge. "
                 "First two integers should be in range [0, number of vertices]"
                 "Third integer should be any number, but too large numbers can"
                 "cause the integer overflow, try to use integers < 10^5"
                 "You can't make self-loops in the graph. Also loop with"
                 "negative length will cause an error. Be careful!"
                 "To exit input -1." << std::endl;

    while (true){
        int first, second, third;
        std::cin >> first;
        if (first == -1) break;
        std::cin >> second >> third;

        if ((first < 0) or (first >= v) or (second < 0) or (second >= v) or (first == second)){
            std::cout << "Wrong input!" << std::endl;
            continue;
        }

        graph[first][second] = third;
        graph[second][first] = third;
    }

    return graph;
}


int main() {
    std::vector<std::vector<int>> graph = read_graph();
    int v = graph.size();

    std::vector<std::vector<int>> matrix;
    for (int row = 0; row < v; row++){
        std::vector<int> r;
        for (int col = 0; col < v; col++){
            if (row == col){
                r.push_back(0);
            } else if (graph[row][col] != -1){
                r.push_back(graph[row][col]);
            } else {
                r.push_back(std::numeric_limits<int>::max() / 2);
            }
        }
        matrix.push_back(r);
    }

    for (int n = 0; n < v; n++){
        for (int row = 0; row < v; row++){
            for (int col = 0; col < v; col++){
                matrix[row][col] = std::min(matrix[row][n] + matrix[n][col], matrix[row][col]);
                matrix[col][row] = matrix[row][col];
            }
        }
    }

    std::cout << "Matrix of distances in graph computed with Floyd-Warshall algorithm" << "\n\n";
    std::cout << "X ";
    for (int n = 0; n < v; n++){
        std::cout << n << " ";
    }
    std::cout << "\n";

    for (int row = 0; row < v; row++){
        std::cout << row << " ";
        for (int col = 0; col < v; col++){
            std::cout << matrix[row][col] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
