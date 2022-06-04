#include <iostream>
#include "alloc.h"
#include <vector>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <chrono>
#include <type_traits>

const bool DEBUG = false;

void testVector(int cntIter) {

    std::cout << "Vector: ";
    Allocator<int> VectorAlloc(5000000, 30);
    std::vector<int, Allocator<int>> v(VectorAlloc); // VECTOR
    for (int i = 0; i < cntIter; ++i)
        v.push_back(i);
    if (DEBUG) {
        for (auto x: v) {
            std::cout << x << ' ';
        }
    }
    std::cout << std::endl;
}

void testList(int cntIter) {
    std::cout << "List: ";
    Allocator<int> listAlloc(30, 2 * cntIter);
    std::list<int, Allocator<int>> l(listAlloc);  // LIST
    for (int i = 0; i < cntIter; ++i) {
        l.push_back(i);
    }
    if (DEBUG) {
        for (auto x: l) {
            std::cout << x << ' ';
        }
    }
    std::cout << std::endl;
}

void testSet(int cntIter) {
    std::cout << "Set: ";
    Allocator<int> setAlloc(100, cntIter * 2);
    std::set<int, std::less<int>, Allocator<int>> s(setAlloc); // SET
    for (int i = 0; i < cntIter; ++i)
        s.insert(i);
    if (DEBUG) {
        for (auto x: s) {
            std::cout << x << ' ';
        }
    }
    std::cout << std::endl;

    for (int i = 0; i < cntIter / 2; ++i)
        s.erase(i);
    if (DEBUG) {
        for (auto x: s) {
            std::cout << x << ' ';
        }
    }
    std::cout << std::endl;
}

void testUnorderedMap(int cntIter) {
    std::cout << "Unordered map: ";
    Allocator<std::pair<int,int>> unMapAlloc;
    std::unordered_map<int, int, std::hash<int>, std::equal_to<>,
            Allocator<std::pair<int,int>>> un_map(100, unMapAlloc); // HASH_MAP

    un_map.insert({100,1});
    un_map.insert({255 ,1});
    un_map.insert({350,1});
    un_map.insert({1001 ,1});
    un_map.insert({999,1});
    un_map.insert({-999 ,1});
    if (DEBUG) {
        for (auto[key, value]: un_map)
            std::cout << '(' << key << ", " << value << ")" << ' ';
        std::cout << std::endl;
    }
}

void testUnorderedSet(int cntIter) {
    std::cout << "Unordered set: ";
    std::unordered_set<int, std::hash<int>, std::equal_to<>, Allocator<int>> un_set(100); // HASH_SET
    un_set.insert(-1);
    un_set.insert(999);
    un_set.insert(11155);
    un_set.insert(111135);
    if (DEBUG) {
        for (auto x: un_set)
            std::cout << x << ' ';
    }
}

template<typename Container>
void TestPushBack(int cntIter) {
    Container c;
    for (int i = 0; i < cntIter; ++i)
        c.push_back(typename Container::value_type());
}

template<typename Container>
void TestInsert(int cntIter) {
    Container c;
    for (int i = 0; i < cntIter; ++i)
        c.insert(typename Container::value_type());
}

void compareAllocators(void (*f)(int), int cntIter, void (*testStd)(int)) {
    auto begin = std::chrono::steady_clock::now();
    f(cntIter);
    auto end = std::chrono::steady_clock::now();
    std::cout << "time for custom is: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << '\n';

    begin = std::chrono::steady_clock::now();
    testStd(cntIter);
    end = std::chrono::steady_clock::now();
    std::cout << "time for std is: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

int main() {
    compareAllocators(testVector, 1000000, TestPushBack<std::vector<int>>);
    std::cout << '\n';
    compareAllocators(testList, 1000, TestPushBack<std::list<int>>);
    std::cout << '\n';
    testUnorderedSet(10);
    testSet(10);
}