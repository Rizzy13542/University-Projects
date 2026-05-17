# Big Homework 2

## Problem 1

### Used headers

- ##### No used headers, I used the cpp file from the lap to modify the already existent graph code.

### Notes
The navigation utilizes an extended custom Graph implementation made with an adjacency matrix representation. Nodes represent city areas (identified by string labels), and edges hold specific weight data for robot navigation.

The system evaluates routes using an optimized DFS backtracking strategy to locate ideal path.

Each road edge stores:
```cpp
int time;    // Travel time required
int risk;    // Risk/danger factor score
int energy;  // Battery consumption requirement
```

### Methods
```cpp
int getNodeIndex(string name); // Maps alphanumeric location names to internal graph matrix indexes
void dfsUndirected(int x);     // Disregards edge orientation to assess network-wide connectivity status
void dfsDirected(int x);       // Traverses specific directions to verify complete zone reachability
void findPaths(int u, int target, int maxRisk, int remEnergy, int currTime, int currEnergy, int depth); // Recursively maps paths satisfying risk limitations
PathResult getBestPath(int start, int target, int maxRisk, int autonomy); // Controls structure resets and initializes optimal route scanning
```

## Problem 2 - The Royal Chronicle of POLITEHNICA

### Used headers

- ##### BinarySearchTree.h

### Notes

The `BinarySearchTree.h` file is based on the BST used in the lab.
It was modified a bit so that it can print `Knight` values properly during the three traversals.

The BST is ordered by the `braveryScore` field.
Each node stores:

```cpp
char name[16];
int braveryScore;
char house[16];
int battlesWon;
```

### Methods

```cpp
void drawTree(BinarySearchTree<Knight>* tree, const char* prefix, bool isLeft, bool isRoot); // draws the BST sideways in the console
void printHouse(BinarySearchTree<Knight>* tree, const char house[], bool* found); // prints all knights from a house in ascending bravery order
int getHeight(BinarySearchTree<Knight>* tree, int* leafCount, BinarySearchTree<Knight>* leaf_tree); // computes the height and can also count/save leaf nodes
bool isBalanced(BinarySearchTree<Knight>* tree); // checks if the BST is height-balanced
void printRange(BinarySearchTree<Knight>* tree, int L, int R, int& total); // prints knights with bravery score in [L, R] and computes total battles
int countNodes(BinarySearchTree<Knight>* tree); // counts all knights in the registry
BinarySearchTree<Knight>* kthMostValorous(BinarySearchTree<Knight>* tree, int& k); // finds the k-th highest bravery score
BinarySearchTree<Knight>* findByName(BinarySearchTree<Knight>* tree, const char name[]); // searches a knight by name
BinarySearchTree<Knight>* findLCA(BinarySearchTree<Knight>* tree, int score1, int score2); // finds the lowest common ancestor based on bravery scores
```

### Modified BST header methods

```cpp
void inOrderTraversal(); // prints the knights in ascending bravery order
void preOrderTraversal(); // prints the knights in pre-order
void postOrderTraversal(); // prints the knights in post-order
```

### Features

- inserts all knights into the BST in input order
- draws the resulting BST in the console
- displays the three required traversals:
  - in-order
  - pre-order
  - post-order
- searches and displays all knights from a given house
- displays the knight with the lowest bravery score
- displays the knight with the highest bravery score
- computes the height of the BST
- counts and displays leaf nodes
- checks if the BST is balanced
- displays all knights in a bravery interval `[L, R]`
- computes the total number of battles won by knights in the interval
- finds the k-th most valorous knight
- finds the LCA of two knights by name
- removes a knight from the registry by name
- displays the BST in-order after deletion

### Handled cases

- house does not exist
- left range being higher than right range
- range contains no knights
- invalid k for k-th most valorous knight
- one or both LCA knights are missing
- banished knight does not exist
- empty/null subtrees during recursive operations

### Usage

Input format:

```txt
N
name1 braveryScore1 house1 battlesWon
name2 braveryScore2 house2 battlesWon
...
nameN braveryScoreN houseN battlesWon
houseQuery
L R
K
nameLCA1 nameLCA2
banishName
```

Example:

```txt
Enter amount of knights: 10 Arthur 50 Pendragon 30 Lancelot 30 Lionel 45 Gawain 70 Pendragon 22 Percival 20 Fisher 15 Tristan 40 Cornwall 28 Galahad 60 Lionel 38 Bedivere 80 Pendragon 19 Bors 25 Lionel 12 Gareth 55 Pendragon 17 Lamorak 35 Cornwall 33
        R--- Bedivere(80, Pendragon, 19)
    R--- Gawain(70, Pendragon, 22)
    |   L--- Galahad(60, Lionel, 38)
    |       L--- Gareth(55, Pendragon, 17)
Arthur(50, Pendragon, 30)
    |   R--- Tristan(40, Cornwall, 28)
    |   |   L--- Lamorak(35, Cornwall, 33)
    L--- Lancelot(30, Lionel, 45)
        |   R--- Bors(25, Lionel, 12)
        L--- Percival(20, Fisher, 15)


In-order (Tournament Ranking):
  Percival(20) Bors(25) Lancelot(30) Lamorak(35) Tristan(40) Arthur(50) Gareth(55) Galahad(60) Gawain(70) Bedivere(80)

Pre-order (Royal Proclamation):
  Arthur(50) Lancelot(30) Percival(20) Bors(25) Tristan(40) Lamorak(35) Gawain(70) Galahad(60) Gareth(55) Bedivere(80)

Post-order (Tribute Collection):
  Bors(25) Percival(20) Lamorak(35) Tristan(40) Lancelot(30) Gareth(55) Galahad(60) Bedivere(80) Gawain(70) Arthur(50)

Enter a house name: Pendragon
Knights of House Pendragon (ascending bravery):
         Arthur | bravery:  50 | battles won:  30
         Gareth | bravery:  55 | battles won:  17
         Gawain | bravery:  70 | battles won:  22
       Bedivere | bravery:  80 | battles won:  19
Newest Recruit (lowest bravery):        Percival | bravery:  20 |          Fisher |  15 battles
Champion of the Realm (highest):        Bedivere | bravery:  80 |       Pendragon |  19 battles


Height of the Archive: 4
Leaf nodes (knights with no subordinates): 4
Bors(25) Lamorak(35) Gareth(55) Bedivere(80)
The Archive is balanced.



Enter left and right ranges (separated by a space): 60 25
Knights with bravery in [25, 60]:
           Bors(25) | House          Lionel | 12 battles
       Lancelot(30) | House          Lionel | 45 battles
        Lamorak(35) | House        Cornwall | 33 battles
        Tristan(40) | House        Cornwall | 28 battles
         Arthur(50) | House       Pendragon | 30 battles
         Gareth(55) | House       Pendragon | 17 battles
        Galahad(60) | House          Lionel | 38 battles

Total battles won by knights in range: 203
Query Kth most valorous knight: 3
3rd most valorous knight: Galahad | bravery: 60 | House Lionel | 38 battles

Enter 2 knight names separated by a space to find the LCA of them: Bors Lamorak
LCA of Bors and Lamorak:
        Lancelot | bravery: 30
Enter knight name to banish: Tristan
Tristan (bravery: 40) has been banished from the Registry.
(Replaced by in-order successor: Lamorak, bravery: 35)
Registry after banishment (in-order):
Percival(20) Bors(25) Lancelot(30) Lamorak(35) Arthur(50) Gareth(55) Galahad(60) Gawain(70) Bedivere(80)
```

The program first builds the BST, then prints the tree and the requested information for every task.