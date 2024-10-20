#include "./stdc++.h"
using namespace std;

//Solves: https://www.hackerrank.com/challenges/knightl-on-chessboard/problem?isFullScreen=true

int nextStep(vector<int> startingPosition, vector<vector<int>> directions, int boardSize) {
    // Queue stores: {currentPosition, numberOfMoves}
    queue<pair<vector<int>, int>> q;
    q.push({startingPosition, 0});

    // Use a visited matrix to avoid revisiting nodes
    vector<vector<bool>> visited(boardSize, vector<bool>(boardSize, false));
    visited[startingPosition[0]][startingPosition[1]] = true;

    while (!q.empty()) {
        auto [currentPosition, moves] = q.front();
        q.pop();

        // If we reach the bottom-right corner, return the number of moves
        if (currentPosition[0] == boardSize - 1 && currentPosition[1] == boardSize - 1) {
            return moves;
        }

        // Explore all possible directions
        for (const auto& dir : directions) {
            int newX = currentPosition[0] + dir[0];
            int newY = currentPosition[1] + dir[1];

            // Check if the new position is within bounds and not visited
            if (newX >= 0 && newY >= 0 && newX < boardSize && newY < boardSize && !visited[newX][newY]) {
                visited[newX][newY] = true; // Mark as visited
                q.push({{newX, newY}, moves + 1});
            }
        }
    }

    // If we exhaust all possibilities without reaching the goal, return -1
    return -1;
}


int main() {

    //board size;

    int m;
    cin >> m;
    vector<int> startingPosition;
    startingPosition.push_back(0);
    startingPosition.push_back(0);

    //generate directions
    for(int i = 1; i < m; i++) {
        for(int j = 1; j < m; j++) {
            vector<vector<int>> directions = {{i, j}, {i, -j}, {-i, j}, {-i, -j}, {j, i}, {j, -i}, {-j, i}, {-j, -i}};
            cout<<nextStep(startingPosition, directions, m) << " ";
        }
        cout<<endl;
    }


    return 0;
}
