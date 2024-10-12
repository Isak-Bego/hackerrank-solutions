#include <iostream>
using namespace std;

//Solves: https://www.hackerrank.com/challenges/the-power-sum?isFullScreen=true

int ctr = 0;

void proccessRemainder(vector<int> possibilities, int previousRemainder, int N){
    vector<int> tempVector;
    for(int i = 0; i < possibilities.size(); i++){
        int remainder = previousRemainder - pow(possibilities[i], N);
        if(remainder == 0 || remainder < 0){
            if(remainder == 0) {
                ++ctr;
            }
            return;
        }

        for(int j = i+1; j < possibilities.size(); j++) {
            tempVector.push_back(possibilities[j]);
        }

        proccessRemainder(tempVector, remainder, N);
        tempVector.clear();
    }
}

int powerSum(int X, int N) {
    vector<int> possibilities;
    int capBase = floor(pow(X, (double)1/N));
    for(int i = 1; i <= capBase; i++) {
        possibilities.push_back(i);
    }
    proccessRemainder(possibilities, X, N);
    return ctr;
}

int main() {
    int X, N;
    cin >> X >> N;
    cout<<powerSum(X, N);
    return 0;
}
