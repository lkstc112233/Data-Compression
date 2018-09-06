//
//  main.cpp
//  LempelZivEncoder
//
//  Created by Xu Ke on 2018/9/4.
//  Copyright © 2018 Must Studio. All rights reserved.
//

#include <cmath>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

int logI(int i) {
    return ceil(log2(i));
}

class LZC {
private:
    class Node {
    public:
        unique_ptr<Node> zeroChild;
        unique_ptr<Node> oneChild;
        int id = 0;
        Node(int i) : id(i) {}
    };
    unique_ptr<Node> head;
    const unique_ptr<Node>* current = &head;
    vector<pair<int, bool>> table;
    int finishingId = -1;
public:
    LZC() {
        head = make_unique<Node>(0);
    }
    void bit(bool bitIn) {
        unique_ptr<Node> Node::*childPtr;
        if (bitIn) {
            childPtr = &Node::oneChild;
        } else {
            childPtr = &Node::zeroChild;
        }
        if ((**current).*childPtr) {
            current = &((**current).*childPtr);
        } else {
            table.emplace_back(make_pair((*current)->id, bitIn));
            (**current).*childPtr = make_unique<Node>(table.size());
            current = &head;
        }
    }
    void finishInput() {
        finishingId = (*current)->id;
    }
    int output(ostream& ost) {
        int length = 0;
        int id = 0;
        for (auto& p: table) {
            int size = logI(++id);
            for (int i = size; i > 0; --i) {
                ost << ((p.first & (1 << (i - 1)))?'1':'0');
            }
            ost << (p.second?'1':'0');
            length += size + 1;
        }
        if (finishingId) {
            int size = logI(++id);
            for (int i = size; i > 0; --i) {
                ost << ((finishingId & (1 << (i - 1)))?'1':'0');
            }
            length += size;
        }
        cout << endl;
        return length;
    }
};

int main(int argc, const char * argv[]) {
    char c;
    int inputSize = 0;
    LZC compressor;
    while (std::cin >> c) {
        if (c != '0' && c != '1') {
            break;
        }
        inputSize += 1;
        compressor.bit(c == '1');
    }
    compressor.finishInput();
    int codeLength = compressor.output(cout);
    cout << "CR: " << inputSize << "/\t" << codeLength << "\t= " << (inputSize / double(codeLength)) << endl;
    return 0;
}
