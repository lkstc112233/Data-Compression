//
//  main.cpp
//  BWT-Reconstruct
//
//  Created by Xu Ke on 9/28/18.
//  Copyright 2018 Must Studio. All rights reserved.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::rotate;
using std::vector;
using std::sort;
using std::find;

void outputMatrix(const vector<string>& M, int L = -1) {
    if (!M.size()) return;
    string labelD(M[0].size(), 'v');
    string labelU(M[0].size(), '^');
    int lineCount = 0;
    for (auto s: M) {
        if (L == lineCount) {
            cout << '\t' << labelD << endl;
            cout << lineCount << '\t' << s << endl;
            cout << '\t' << labelU << endl;
        } else {
            cout << lineCount << '\t' << s << endl;
        }
        lineCount += 1;
    }
}

int main(int argc, const char * argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " *y* L" << endl;
        return -1;
    }
    string y = argv[1];
    int L;
    sscanf(argv[2], "%d", &L);
    
    vector<string> B;
    for (int i = 0; i < y.size(); ++i) {
        B.emplace_back(1, y[i]);
    }
    cout << "Intital B:" << endl;
    outputMatrix(B);
    int iteration = 0;
    while (++iteration < y.size()) {
        sort(B.begin(), B.end());
        for (int i = 0; i < y.size(); ++i) {
            B[i] = y[i] + B[i];
        }
        cout << "Iteration " << iteration << ":" << endl;
        outputMatrix(B);
    }
    sort(B.begin(), B.end());
    cout << "Final Reconstructed Matrix B:" << endl;
    outputMatrix(B, L);
    string x = B[L];
    cout << x << endl;
    return 0;
}
