//
//  main.cpp
//  decoder
//
//  Created by Xu Ke on 2018/9/4.
//  Copyright © 2018 Must Studio. All rights reserved.
//

#include <iostream>
#include <memory>
#include <cmath>
#include <vector>

using namespace std;

int logI(int i) {
    return ceil(log2(i));
}

int main(int argc, const char * argv[]) {
    char c;
    while (std::cin >> c) {
        if (c != '0' && c != '1') {
            break;
        }
    }
    return 0;
}
