//
//  main.cpp
//  BWT
//
//  Created by Xu Ke on 9/28/18.
//  Copyright 2018 Must Studio. All rights reserved.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::rotate;
using std::vector;
using std::sort;
using std::find;

void outputLine(string s, int lineCount, bool extract) {
    cout << lineCount << '\t' << s;
    if (extract)
        cout << " -> " << s.back();
    cout << endl;
}

void outputMatrix(const vector<string>& M, const string& S = "") {
    if (!M.size()) return;
    string labelD(M[0].size(), 'v');
    string labelU(M[0].size(), '^');
    int lineCount = 0;
    for (auto s: M) {
        if (s == S) {
            cout << '\t' << labelD << endl;
            outputLine(s, lineCount, S.size());
            cout << '\t' << labelU << endl;
        } else {
            outputLine(s, lineCount, S.size());
        }
        lineCount += 1;
    }
}

int main(int argc, const char * argv[]) {
    string x;
    if (argc < 2) {
        cout << "Input x: ";
        std::cin >> x;
    } else {
        x = argv[1];
    }
//    string x = argv[1];
    vector<string> A;
    for (int i = 0; i < x.size(); ++i) {
        A.emplace_back(x);
        rotate(x.begin(), x.begin() + 1, x.end());
    }
    cout << "Construct Matrix A:" << endl;
    outputMatrix(A);
    auto B = A;
    sort(B.begin(), B.end());
    cout << "Sort A to construct Matrix B:" << endl;
    outputMatrix(B, x);
    auto L = find(B.begin(), B.end(), x) - B.begin();
    string y;
    // Gets last column.
    for (auto& s:B) {
        y.push_back(s.back());
    }
    cout << "(" << y << ", " << L << ")" << endl;
    return 0;
}
