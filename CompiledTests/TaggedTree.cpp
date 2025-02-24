#include "TagedTree.hpp"

Node* init_node(Tagged* value, Tagged* l, Tagged* r, Tagged* recycle_address = NULL) {
    Node* new_node = recycle_address ? (Node*)recycle_address : (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }

    init_tag(&new_node->base, TREE_NODE_VALUE);
    new_node->value = value;
    new_node->left = l;
    new_node->right = r;
    return new_node;
}

Leaf* init_leaf(Tagged* value, Tagged* recycle_address) {
    Leaf* new_node = recycle_address ? (Leaf*)recycle_address : (Leaf*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->value = value;
    return new_node;
}

Root* init_root(Tagged* recycle_address) {
    Root* new_node = recycle_address ? (Root*)recycle_address : (Root*)malloc(sizeof(Root));
    if (new_node == NULL) {
        return NULL;
    }

    init_tag(&new_node->base, SZIPPER_ROOT_VALUE);
    return new_node;
}

NodeL* init_nodel(Tagged* up, Tagged* value, Tagged* right, Tagged* recycle_address) {
    NodeL* new_node = recycle_address ? (NodeL*)recycle_address : (NodeL*)malloc(sizeof(NodeL));
    if (new_node == NULL) {
        return NULL;
    }

    init_tag(&new_node->base, SZIPPER_NODEL_VALUE);
    new_node->up = up;
    new_node->value = value;
    new_node->right = right;
    return new_node;
}

NodeR* init_noder(Tagged* left, Tagged* value, Tagged* up, Tagged* recycle_address) {
    NodeR* new_node = recycle_address ? (NodeR*)recycle_address : (NodeR*)malloc(sizeof(NodeR));
    if (new_node == NULL) {
        return NULL;
    }

    init_tag(&new_node->base, SZIPPER_NODER_VALUE);
    new_node->up = up;
    new_node->value = value;
    new_node->left = left;
    return new_node;
}

Top* init_top(Tagged* left, Tagged* value, Tagged* right, Tagged* recycle_address) {
    Top* new_node = recycle_address ? (Top*)recycle_address : (Top*)malloc(sizeof(NodeL));
    if (new_node == NULL) {
        return NULL;
    }

    init_tag(&new_node->base, SZIPPER_NODEL_VALUE);
    new_node->left = left;
    new_node->value = value;
    new_node->right = right;
    return new_node;
}