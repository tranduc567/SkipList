#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits> 

struct Node {
    int key;
    std::vector<Node*> forward;
};

struct SkipList {
    int maxLevel;
    float probability;
    int currentLevel;
    Node* head;
};

Node* createNode(int key, int level);
void initializeSkipList(SkipList& skipList, int maxLevel, float probability);
bool isEmpty(const SkipList& skipList);
int size(const SkipList& skipList);
void insert(SkipList& skipList, int key);
void remove(SkipList& skipList, int key);
void build(SkipList& skipList, const std::vector<int>& items);
void clear(SkipList& skipList);
void print(const SkipList& skipList);

#endif // SKIPLIST_H
