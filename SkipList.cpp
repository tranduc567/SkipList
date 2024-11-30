#include "SkipList.h"

Node* createNode(int key, int level) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->forward.resize(level, nullptr);
    return newNode;
}

int randomLevel(const SkipList& skipList) {
    int level = 1;
    while (((float)rand() / RAND_MAX) < skipList.probability && level < skipList.maxLevel) {
        ++level;
    }
    return level;
}

void initializeSkipList(SkipList& skipList, int maxLevel, float probability) {
    skipList.maxLevel = maxLevel;
    skipList.probability = probability;
    skipList.currentLevel = 1;
    skipList.head = createNode(std::numeric_limits<int>::lowest(), maxLevel);
}

bool isEmpty(const SkipList& skipList) {
    return skipList.head->forward[0] == nullptr;
}

int size(const SkipList& skipList) {
    int count = 0;
    Node* current = skipList.head->forward[0];
    while (current) {
        ++count;
        current = current->forward[0];
    }
    return count;
}

void insert(SkipList& skipList, int key) {
    std::vector<Node*> update(skipList.maxLevel, nullptr);
    Node* current = skipList.head;

    for (int i = skipList.currentLevel - 1; i >= 0; --i) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    if (!current || current->key != key) {
        int newLevel = randomLevel(skipList);

        if (newLevel > skipList.currentLevel) {
            for (int i = skipList.currentLevel; i < newLevel; ++i) {
                update[i] = skipList.head;
            }
            skipList.currentLevel = newLevel;
        }

        Node* newNode = createNode(key, newLevel);
        for (int i = 0; i < newLevel; ++i) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

void remove(SkipList& skipList, int key) {
    std::vector<Node*> update(skipList.maxLevel, nullptr);
    Node* current = skipList.head;

    for (int i = skipList.currentLevel - 1; i >= 0; --i) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    if (current && current->key == key) {
        for (int i = 0; i < skipList.currentLevel; ++i) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }
        delete current;

        while (skipList.currentLevel > 1 && skipList.head->forward[skipList.currentLevel - 1] == nullptr) {
            --skipList.currentLevel;
        }
    }
}

void build(SkipList& skipList, const std::vector<int>& items) {
    for (const auto& item : items) {
        insert(skipList, item);
    }
}

void clear(SkipList& skipList) {
    Node* current = skipList.head->forward[0];
    while (current) {
        Node* temp = current;
        current = current->forward[0];
        delete temp;
    }
    for (int i = 0; i < skipList.maxLevel; ++i) {
        skipList.head->forward[i] = nullptr;
    }
    skipList.currentLevel = 1;
}

void print(const SkipList& skipList) {
    for (int i = 0; i < skipList.currentLevel; ++i) {
        Node* current = skipList.head->forward[i];
        std::cout << "Level " << i + 1 << ": ";
        while (current) {
            std::cout << current->key << " ";
            current = current->forward[i];
        }
        std::cout << "\n";
    }
}
