#ifndef TAGED_TREE_H 
#define TAGED_TREE_H

#include "TagType.hpp"


typedef struct Node {
    struct Tagged base;
    Tagged* value;
    Tagged* left;
    Tagged* right;
} Node;

typedef struct Leaf {
    struct Tagged base;
    Tagged* value;
} Leaf;

typedef struct Root {
    struct Tagged base;
} Root;

typedef struct NodeL {
    struct Tagged base;
    Tagged* up;
    Tagged* value;
    Tagged* right;
} NodeL;

typedef struct NodeR {
    struct Tagged base;
    Tagged* left;
    Tagged* value;
    Tagged* up;
} NodeR;

typedef struct Top {
    struct Tagged base;
    Tagged* left;
    Tagged* value;
    Tagged* right;
} Top;

Node* init_node(Tagged* value, Tagged* l, Tagged* r, Tagged* recycle_address = NULL);
Leaf* init_leaf(Tagged* value, Tagged* recycle_address = NULL);
Root* init_root(Tagged* recycle_address = NULL);
NodeL* init_nodel(Tagged* up, Tagged* value, Tagged* right, Tagged* recycle_address = NULL);
NodeR* init_noder(Tagged* left, Tagged* value, Tagged* up, Tagged* recycle_address = NULL);
Top* init_top(Tagged* left, Tagged* value, Tagged* right, Tagged* recycle_address = NULL);


#endif