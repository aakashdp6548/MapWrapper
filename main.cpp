#include <iostream>
#include <algorithm>
#include <cassert>
#include <utility>
#include <string>
#include <vector>

#include "map.h"

using namespace std;

int main() {

    Map<string, int> map(Type::Unordered);
    map.insert("aakash", 5);
    map.insert("saad", 3);
    map.insert("andrew", 7);

    map["shariq"] = 4;
    map["zain"] = 10;
    map.erase("aakash");

    for (auto iter : map) {
        std::cout << iter.first << " " << iter.second << std::endl;
    }

    Map<string, int> map2(Type::Ordered);
    map2.insert("aakash", 5);
    map2.insert("saad", 3);
    map2.insert("andrew", 7);
    map2["shariq"] = 4;
    map2["zain"] = 10;

    std::cout << "saad: " << map2["saad"] << std::endl;
    map2.erase("zain");
    std::cout << "zain: " << map2["zain"] << std::endl;

    for (auto iter2 : map2) {
        std::cout << iter2.first << " " << iter2.second << std::endl;
    }

    return 0;

}
