#include "SkipList.h"

int main() {
     srand(time(nullptr)); // Seed for random number generator

    SkipList skipList;
    initializeSkipList(skipList, 6, 0.5);

    std::cout << "Inserting elements: 3, 6, 7, 9, 12, 19\n";
    insert(skipList, 3);
    insert(skipList, 6);
    insert(skipList, 7);
    insert(skipList, 9);
    insert(skipList, 12);
    insert(skipList, 19);
    print(skipList);

    std::cout << "\nNumber of elements: " << size(skipList) << "\n";

    std::cout << "\nRemoving element: 7\n";
    remove(skipList, 7);
    print(skipList);

    std::cout << "\nBuilding Skip List from vector {1, 4, 8, 10}:\n";
    clear(skipList);
    build(skipList, {1, 4, 8, 10});
    print(skipList);

    std::cout << "\nClearing all elements.\n";
    clear(skipList);
    std::cout << "Skip List is empty: " << (isEmpty(skipList) ? "Yes" : "No") << "\n";

    return 0;
}