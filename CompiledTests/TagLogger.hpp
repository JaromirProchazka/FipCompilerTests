#pragma once
#ifndef TAG_LOGGER_H 
#define TAG_LOGGER_H

#include <iostream>
#include <cassert>
#include <concepts>
#include <format>
#include "TagType.hpp"
#include "TagedInt.hpp"
#include "TagedList.hpp"
#include "TagedTree.hpp"


void log_tagged(Tagged* val);
void log_tagged(void* val);

void print_int(Integer* val) {
    printf("%d", val->value);
}

void print_list(List* list) {
    printf("[");
    while (!is_empty(list)) {
        log_tagged(head(list));

        list = tail(list);
        if (!is_empty(list)) {
            printf(", ");
        }
    }
    printf("]");
}

void print_tabs(int count) {
    for (int i = 0; i < count; i++) {
        printf("\t");
    }
}

void print_tree_level(Tagged* tree, int level) {
    ValueType type = get_type(tree);
    if (type == TREE_NODE) {
        Node* node = (Node*)tree;
        print_tabs(level);
        log_tagged(node->value);
        printf("\n");
        if (node->left) print_tree_level(node->left, level + 1);
        if (node->right) print_tree_level(node->right, level + 1);
    }
    if (type == TREE_LEAF) {
        Leaf* leaf = (Leaf*)tree;
        print_tabs(level);
        log_tagged(leaf->value);
        printf("\n");
    }
}

void print_tree(Tagged* tree) {
    print_tree_level(tree, 0);
}

void log_tagged(Tagged* val) {
    if (val == NULL) {
        printf("NIL");
        return;
    }
    ValueType tag = get_type((Tagged*)val);

    switch (tag)
    {
    case NIL:
        printf("NIL");
        return;
    case LIST:
        print_list((List*)val);
        break;
    case INT:
        print_int((Integer*)val);
        break;
    case TREE_NODE:
        print_tree(val);
        break;
    default:
        assert(false);
    }
}

void log_tagged(void* val) {
    log_tagged((Tagged*)val);
}

#endif