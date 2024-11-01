#include "./stdc++.h"

using namespace std;

//Solves: https://www.hackerrank.com/challenges/k-factorization/problem

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);



vector<int> kFactorization(int n, vector<int> A) {
    // Sort A to ensure lexicographically smallest order in BFS expansion
    sort(A.begin(), A.end());

    //Determine if it cannot be written as a product of these factors
    vector<int> divisors = A;
    int tempN = n;
    while (!divisors.empty()) {
        if(tempN % divisors.back() == 0) {
            tempN /= divisors.back();
        }else {
            divisors.pop_back();
        }
    }

    if(tempN != 1) {
        return {-1};
    }

    // Queue to perform BFS, storing pairs of (current_value, path_taken)
    queue<pair<int, vector<int>>> q;
    q.push({1, {1}});

    // Set to track visited values for pruning
    unordered_set<int> visited;
    visited.insert(1);

    // BFS to find the shortest lexicographical path
    while (!q.empty()) {
        auto [current_value, path] = q.front();
        q.pop();

        // Check if we've reached the target value
        if (current_value == n) {
            return path;  // Return the shortest lexicographical path
        }

        // Try each factor
        for (int factor : A) {
            int next_value = current_value * factor;

            // Only proceed if next_value is within bounds and unvisited
            if (next_value <= n && !visited.count(next_value)) {
                visited.insert(next_value);

                // Create the new path with next_value added
                vector<int> new_path = path;
                new_path.push_back(next_value);

                // Push the new state into the queue
                q.push({next_value, move(new_path)});
            }
        }
    }

    // If no valid path was found
    return {-1};
}

int main() {
    int n, s, temp;
    vector<int> A;
    cin >> n >> s;
    for(int i = 0; i < s; i++) {
        cin >> temp;
        A.push_back(temp);
    }

    vector<int> min = kFactorization(n, A);

    for(int i = 0; i < min.size(); i++) {
        cout<<min[i]<<" ";
    }

    return 0;
}
