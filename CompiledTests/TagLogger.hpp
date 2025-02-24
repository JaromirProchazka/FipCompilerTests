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

void print_tree_level(Node* tree, int level) {
    print_tabs(level);
    log_tagged(tree->value);
    printf("\n");
    if (tree->left) print_tree_level((Node*)tree->left, level + 1);
    if (tree->right) print_tree_level((Node*)tree->right, level + 1);
}

void print_tree(Node* tree) {
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
    case LIST_VALUE:
        print_list((List*)val);
        break;
    case INT_VALUE:
        print_int((Integer*)val);
        break;
    case TREE_NODE_VALUE:
        print_tree((Node*)val);
        break;
    default:
        assert(false);
    }
}

void log_tagged(void* val) {
    log_tagged((Tagged*)val);
}

#endif