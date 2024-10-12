#include "../stdc++.h"
using namespace std;

/*
Solves: https://www.hackerrank.com/challenges/crossword-puzzle?isFullScreen=true
*/


map<int, vector< tuple<int, int, char> > > crosswordGaps;

vector<string> tokenizeWords(string words) {
    string delimiter = ";";
    vector<string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = words.find(delimiter)) != std::string::npos) {
        token = words.substr(0, pos);
        tokens.push_back(token);
        words.erase(0, pos + delimiter.length());
    }
    tokens.push_back(words);
    return tokens;
}

void findCrossWordGaps(vector<string> crossword, int minLen) {
    vector< tuple<int, int, char> > temp;
    int length = 0;
    bool startWord = false;
    tuple<int, int, char> wordStartPos;
    //check horizontally
    for(int i = 0; i < crossword.size(); i++) {
        for(int j = 0; j < crossword[i].size(); j++) {
            if(crossword[i][j] == '-' && startWord == false) {
                startWord = true;
                wordStartPos = make_tuple(i, j, 'h');
                ++length;
            }else if(crossword[i][j] == '-' && startWord == true) {
                ++length;
            }

            if(((crossword[i][j] == '+') || (j == crossword[i].size()-1)) && startWord == true) {
                startWord = false;
                if(length >= minLen) {
                    if(crosswordGaps.find(length) != crosswordGaps.end()) {
                        vector< tuple<int, int, char> > temp1 = crosswordGaps[length];
                        temp1.push_back(wordStartPos);
                        crosswordGaps[length] = temp1;
                    }else {
                        temp.push_back(wordStartPos);
                        crosswordGaps.insert({length, temp});
                        temp.clear();
                    }
                }
                length = 0;
            }
        }
    }

    //check vertically
    for(int i = 0; i < crossword.size(); i++) {
        for(int j = 0; j < crossword[i].size(); j++) {
            if(crossword[j][i] == '-' && startWord == false) {
                startWord = true;
                wordStartPos = make_tuple(j, i, 'v');
                ++length;
            }else if(crossword[j][i] == '-' && startWord == true) {
                ++length;
            }

            if(((crossword[j][i] == '+') || (j == crossword[i].size()-1)) && startWord == true) {
                startWord = false;
                if(length >= minLen) {
                    if(crosswordGaps.find(length) != crosswordGaps.end()) {
                        vector< tuple<int, int, char> > temp1 = crosswordGaps[length];
                        temp1.push_back(wordStartPos);
                        crosswordGaps[length] = temp1;
                    }else {
                        temp.push_back(wordStartPos);
                        crosswordGaps.insert({length, temp});
                        temp.clear();
                    }
                }
                length = 0;
            }
        }
    }

}

int shortestWordLength(vector<string> separateWords) {
    int minLen = separateWords[0].length();
    for(int i = 1; i < separateWords.size(); i++) {
        if(separateWords[i].length() < minLen) {
            minLen = separateWords[i].length();
        }
    }
    return minLen;
}

vector<string> recursiveComplete(vector<string> crossWord, vector<string> separateWords) {
    vector<string> previousCrossWord = crossWord;
    vector<string> tmp;
    vector<string> failedAttempt = {"failedAttempt"};
    vector<string> result;
    bool success = true;
    vector< tuple<int, int, char> > possibilities;

    if(separateWords.size() == 0) {
        return crossWord;
    }

    for(int i = 0; i < separateWords.size(); i++) {
        //try to fit the word in any gap possible if they are not taken
        //recursive step
        possibilities = crosswordGaps.at(separateWords[i].length());

        for(int j = 0; j < possibilities.size(); j++) {
            int k = get<0>(possibilities[j]);
            int l = get<1>(possibilities[j]);
            char direction = get<2>(possibilities[j]);
            if(crossWord[k][l] == '-' || crossWord[k][l] == separateWords[i][0]) {
                if(direction == 'h') {
                    for(int m = 0; m < separateWords[i].size(); m++) {
                        if(crossWord[k][l+m] == '-' || crossWord[k][l+m] == separateWords[i][m]) {
                            crossWord[k][l+m] = separateWords[i][m];
                        }else {
                            crossWord = previousCrossWord;
                            success = false;
                            break;
                        }
                    }
                }else {
                    for(int m = 0; m < separateWords[i].size(); m++) {
                        if(crossWord[k+m][l] == '-' || crossWord[k+m][l] == separateWords[i][m]) {
                            crossWord[k+m][l] = separateWords[i][m];
                        }else {
                            crossWord = previousCrossWord;
                            success = false;
                            break;
                        }
                    }

                }
                if(success == true) {
                    tmp = separateWords;
                    tmp.erase(tmp.begin()+i);
                    result = recursiveComplete(crossWord, tmp);
                    if(result[0] == "failedAttempt") {
                        crossWord = previousCrossWord;
                    }else {
                        return result;
                    }
                }

            }
        }
    }
    return failedAttempt;
}

vector<string> crosswordPuzzle(vector<string> crossword, string words) {
    vector<string> separateWords = tokenizeWords(words);
    int minLength = shortestWordLength(separateWords);
    findCrossWordGaps(crossword, minLength);
    vector<string> complete = recursiveComplete(crossword, separateWords);
    for(int i = 0; i < complete.size(); i++) {
        cout<<complete[i]<<endl;
    }
}

int main()
{
    vector<string> crossword;
    string crosswordRow;
    for(int i = 0; i < 10; i++) {
        cin >> crosswordRow;
        crossword.push_back(crosswordRow);
    }
    cin >> crosswordRow;
    crosswordPuzzle(crossword, crosswordRow);


    return 0;
}

