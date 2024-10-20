#include "./stdc++.h"

using namespace std;

//solves: https://www.hackerrank.com/challenges/icecream-parlor/problem?isFullScreen=true

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'icecreamParlor' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER m
 *  2. INTEGER_ARRAY arr
 */

// //given that the array is sorted
// int binarySearch(int key, vector<int> arr){
//     int endPos = (int)arr.size() - 1;
//     int beginPos = 0;
//     int middlePos;
//     while(endPos > beginPos || endPos == beginPos) {
//         //check the middle element
//         middlePos = (endPos + beginPos) / 2;
//         if(key == arr[middlePos]) {
//             return middlePos;
//         }else if(key > arr[middlePos]) {
//             beginPos = beginPos + middlePos;
//         }else {
//             endPos = endPos - middlePos;
//         }
//     }
//     return -1;
// }



vector<int> icecreamParlor(int m, vector<int> arr) {
    vector<int> result;
    vector<int> tempArr;
    int remainder, foundPosition;
    for(int i = 0; i < arr.size(); i++) {
         remainder = m - arr[i];
         tempArr = arr;
         tempArr.erase(tempArr.begin() + i);
         auto it = find(tempArr.begin(), tempArr.end(), remainder);
         if(it != tempArr.end()) {
             foundPosition = it - tempArr.begin() + 1;
             result.push_back(i + 1);
             result.push_back(foundPosition + 1);
             return result;
         }
    }
    result.push_back(-1);
    result.push_back(-1);
    return result;
}

int main()
{

    vector<int> arr = {1, 3, 5, 7, 8, 9};
    cout<<binarySearch(6, arr)<<endl;
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string m_temp;
        getline(cin, m_temp);

        int m = stoi(ltrim(rtrim(m_temp)));

        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        vector<int> result = icecreamParlor(m, arr);

        for (size_t i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}


