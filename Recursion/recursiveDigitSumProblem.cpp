#include "../stdc++.h";
using namespace std;

//Solves: https://www.hackerrank.com/challenges/recursive-digit-sum?isFullScreen=true

string findSuperDigit(string n){
    long long int sum = 0;

    if(n.length() == 1){
        return n;
    }

    for(int i = 0; i < n.length(); i++){
        sum += n[i] - '0';
    }

    return findSuperDigit(to_string(sum));
}

void superDigit(string n, int k) {
    long long sum = 0;
    for(int i = 0; i < n.length(); i++) {
        sum += n[i] - '0';
    }
    sum = sum*k;
    cout<<stoi(findSuperDigit(to_string(sum)))<<endl;
}

int main() {
    superDigit("6523", 100000);
    return 0;
}