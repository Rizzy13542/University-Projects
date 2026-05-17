#include <cstring>
#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

#define member_size(type, member) (sizeof( ((type *)0)->member ))

struct Knight {
    char name[16];
    int braveryScore;
    char house[16];
    int battlesWon;

    bool operator<=(const Knight& b) const {
        return braveryScore <= b.braveryScore;
    }

    bool operator>(const Knight& b) const {
        return braveryScore > b.braveryScore;
    }

    bool operator==(const Knight& b) const {
        return braveryScore == b.braveryScore;
    }

    bool operator!=(const Knight& b) const {
        return braveryScore != b.braveryScore;
    }
};

void drawTree(BinarySearchTree<Knight>* tree, const char* prefix = "", bool isLeft = true, bool isRoot = true)
{
    char nextPrefix[300];

    if (!tree || !tree->pinfo)
        return;

    if (tree->right_son)
    {
        strcpy(nextPrefix, prefix);

        if (isRoot)
            strcat(nextPrefix, "    ");
        else
        {
            if (isLeft)
                strcat(nextPrefix, "|   ");
            else
                strcat(nextPrefix, "    ");
        }

        drawTree(tree->right_son, nextPrefix, false, false);
    }

    printf("%s", prefix);

    if (!isRoot)
    {
        if (isLeft)
            printf("L--- ");
        else
            printf("R--- ");
    }

    printf("%s(%d, %s, %d)\n", tree->pinfo->name, tree->pinfo->braveryScore, tree->pinfo->house, tree->pinfo->battlesWon);

    if (tree->left_son)
    {
        strcpy(nextPrefix, prefix);

        if (isRoot)
            strcat(nextPrefix, "    ");
        else
        {
            if (isLeft)
                strcat(nextPrefix, "    ");
            else
                strcat(nextPrefix, "|   ");
        }

        drawTree(tree->left_son, nextPrefix, true, false);
    }
}

void printHouse(BinarySearchTree<Knight>* tree, const char house[], bool* found = nullptr)
{
    if (!tree || !tree->pinfo)
        return;

    if (tree->left_son)
        printHouse(tree->left_son, house, found);

    if (strcmp(tree->pinfo->house, house) == 0)
    {
        if (found)
            *found = true;

        printf("%15s | bravery: %3d | battles won: %3d\n", tree->pinfo->name, tree->pinfo->braveryScore, tree->pinfo->battlesWon);
    }

    if (tree->right_son)
        printHouse(tree->right_son, house, found);
}

int getHeight(BinarySearchTree<Knight>* tree, int* leafCount = nullptr, BinarySearchTree<Knight>* leaf_tree = nullptr) {
    if (!tree) return 0;

    int leftHeight = getHeight(tree->left_son, leafCount, leaf_tree);
    int rightHeight = getHeight(tree->right_son, leafCount, leaf_tree);
    if (leftHeight == 0 && rightHeight == 0) {
        if (leafCount) (*leafCount)++;
        if (leaf_tree) leaf_tree->insert(*tree->pinfo);
    }
    if (leftHeight > rightHeight) return leftHeight + 1;
    return rightHeight + 1;
}

bool isBalanced(BinarySearchTree<Knight>* tree)
{
    if (!tree || !tree->pinfo)
        return true;

    int leftHeight = getHeight(tree->left_son);
    int rightHeight = getHeight(tree->right_son);

    if (abs(leftHeight - rightHeight) > 1)
        return false;

    return isBalanced(tree->left_son) && isBalanced(tree->right_son);
}

void printRange(BinarySearchTree<Knight>* tree, int L, int R, int& total)
{
    if (!tree || !tree->pinfo)
        return;

    if (tree->left_son && tree->pinfo->braveryScore > L)
        printRange(tree->left_son, L, R, total);

    if (tree->pinfo->braveryScore >= L && tree->pinfo->braveryScore <= R)
    {
        if (total < 0) total = 0;
        printf("%15s(%d) | House %15s | %d battles\n", tree->pinfo->name, tree->pinfo->braveryScore, tree->pinfo->house, tree->pinfo->battlesWon);
        total += tree->pinfo->battlesWon;
    }

    if (tree->right_son && tree->pinfo->braveryScore < R)
        printRange(tree->right_son, L, R, total);
}

int countNodes(BinarySearchTree<Knight>* tree)
{
    if (!tree || !tree->pinfo)
        return 0;

    return 1 + countNodes(tree->left_son) + countNodes(tree->right_son);
}

BinarySearchTree<Knight>* kthMostValorous(BinarySearchTree<Knight>* tree, int& k)
{
    if (!tree || !tree->pinfo)
        return nullptr;

    BinarySearchTree<Knight>* result = kthMostValorous(tree->right_son, k);
    if (result) return result;

    k--;
    if (k == 0)
        return tree;

    return kthMostValorous(tree->left_son, k);
}

BinarySearchTree<Knight>* findByName(BinarySearchTree<Knight>* tree, const char name[])
{
    if (!tree || !tree->pinfo)
        return nullptr;

    if (strcmp(tree->pinfo->name, name) == 0)
        return tree;

    BinarySearchTree<Knight>* found = findByName(tree->left_son, name);

    if (found != nullptr)
        return found;

    return findByName(tree->right_son, name);
}

BinarySearchTree<Knight>* findLCA(BinarySearchTree<Knight>* tree, int score1, int score2)
{
    if (!tree || !tree->pinfo)
        return nullptr;

    if (score1 < tree->pinfo->braveryScore && score2 < tree->pinfo->braveryScore)
        return findLCA(tree->left_son, score1, score2);

    if (score1 > tree->pinfo->braveryScore && score2 > tree->pinfo->braveryScore)
        return findLCA(tree->right_son, score1, score2);

    return tree;
}

int main() {
    auto* tree = new BinarySearchTree<Knight>();
    int n; printf("Enter amount of knights: "); cin >> n;

    if (n <= 0)
    {
        printf("No knights in the registry.\n");
        delete tree;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        Knight temp{};
        cin >> temp.name >> temp.braveryScore >> temp.house >> temp.battlesWon;
        temp.name[sizeof(temp.name)-1] = temp.house[sizeof(temp.house)-1] = '\0';
        tree->insert(temp);
    }

    drawTree(tree);
    printf("\n\nIn-order (Tournament Ranking):\n  "); tree->inOrderTraversal();
    printf("\n\nPre-order (Royal Proclamation):\n  "); tree->preOrderTraversal();
    printf("\n\nPost-order (Tribute Collection):\n  "); tree->postOrderTraversal();

    char inputHouse[member_size(Knight, name)]{}; printf("\n\nEnter a house name: "); cin >> inputHouse; inputHouse[sizeof(inputHouse)-1] = '\0';
    printf("Knights of House %s (ascending bravery):\n", inputHouse);
    bool foundHouse = false;
    printHouse(tree, inputHouse, &foundHouse);
    if (!foundHouse)
        printf("No knights found from House %s.\n", inputHouse);

    auto* selected = tree;
    while (selected->left_son) selected = selected->left_son;
    printf("Newest Recruit (lowest bravery): %15s | bravery: %3d | %15s | %3d battles\n", selected->pinfo->name, selected->pinfo->braveryScore, selected->pinfo->house, selected->pinfo->battlesWon);
    selected = tree;
    while (selected->right_son) selected = selected->right_son;
    printf("Champion of the Realm (highest): %15s | bravery: %3d | %15s | %3d battles\n", selected->pinfo->name, selected->pinfo->braveryScore, selected->pinfo->house, selected->pinfo->battlesWon);

    int leafCount = 0;
    auto* leafTree = new BinarySearchTree<Knight>();
    int treeHeight = getHeight(tree, &leafCount, leafTree);
    printf("\n\nHeight of the Archive: %i\nLeaf nodes (knights with no subordinates): %i\n", treeHeight, leafCount);
    leafTree->inOrderTraversal();
    printf("\nThe Archive is %s.\n\n", isBalanced(tree) ? "balanced" : "unbalanced");
    delete leafTree;

    int rangeLeft, rangeRight;
    printf("\n\nEnter left and right ranges (separated by a space): "); cin >> rangeLeft >> rangeRight;
    if (rangeLeft > rangeRight)
    {
        rangeLeft = rangeLeft + rangeRight;
        rangeRight = rangeLeft - rangeRight;
        rangeLeft = rangeLeft - rangeRight;
    }
    int totalBattles = -1;
    printf("Knights with bravery in [%i, %i]:\n", rangeLeft, rangeRight);
    printRange(tree, rangeLeft, rangeRight, totalBattles);
    if (totalBattles == -1) printf("No knights found!\n\n");
    else printf("\nTotal battles won by knights in range: %i\n", totalBattles);

    int kOrder = 0, nodeCount = countNodes(tree);
    printf("Query Kth most valorous knight: "); cin >> kOrder;
    if (kOrder > nodeCount || kOrder <= 0) printf("Invalid rank. There are only %d knights in the registry.\n\n", nodeCount);
    else {
        int tempK = kOrder;
        auto* kth = kthMostValorous(tree, tempK);
        printf("%d", kOrder);
        if (kOrder % 10 == 1 && kOrder % 100 != 11)
            printf("st");
        else if (kOrder % 10 == 2 && kOrder % 100 != 12)
            printf("nd");
        else if (kOrder % 10 == 3 && kOrder % 100 != 13)
            printf("rd");
        else
            printf("th");

        printf(" most valorous knight: %s | bravery: %d | House %s | %d battles\n\n", kth->pinfo->name, kth->pinfo->braveryScore, kth->pinfo->house, kth->pinfo->battlesWon);
    }
    char nameLCA1[member_size(Knight, name)]{}, nameLCA2[member_size(Knight, name)]{};
    printf("Enter 2 knight names separated by a space to find the LCA of them: "); cin >> nameLCA1 >> nameLCA2;
    nameLCA1[sizeof(nameLCA1)-1] = '\0';
    nameLCA2[sizeof(nameLCA2)-1] = '\0';
    auto* firstKnight = findByName(tree, nameLCA1);
    auto* secondKnight = findByName(tree, nameLCA2);
    if (!firstKnight || !secondKnight) printf("LCA cannot be found because %s.\n", (!firstKnight && !secondKnight) ? "both knights were not found" : (!firstKnight ? "first knight was not found" : "second knight was not found"));
    else {
        BinarySearchTree<Knight>* ancestor = findLCA(tree, firstKnight->pinfo->braveryScore, secondKnight->pinfo->braveryScore);
        printf("LCA of %s and %s:\n %15s | bravery: %d\n", nameLCA1, nameLCA2, ancestor->pinfo->name, ancestor->pinfo->braveryScore);
    }

    printf("Enter knight name to banish: "); cin >> nameLCA1;
    auto* knight = findByName(tree, nameLCA1);
    if (!knight) printf("Knight not found in the Archive!\n");
    else {
        Knight oldInfo = *knight->pinfo;
        bool isLeaf = knight->right_son == knight->left_son;
        tree->removeInfo(*knight->pinfo);
        printf("%s (bravery: %d) has been banished from the Registry.\n", oldInfo.name, oldInfo.braveryScore);
        if (!isLeaf) printf("(Replaced by in-order successor: %s, bravery: %d)\n", knight->pinfo->name, knight->pinfo->braveryScore);
        else printf("(No successor found)\n");
        printf("Registry after banishment (in-order):\n");
        tree->inOrderTraversal();
    }

    delete tree;
}