#pragma once
#ifndef TAG_TYPE_H 
#define TAG_TYPE_H 

#include <iostream>
#include <cassert>
#include <concepts>
#include <format>

const int MaxTypeId = 7;
typedef enum {
    NIL = 0,
    INT_VALUE,
    LIST_VALUE,
    TREE_NODE_VALUE,
    TREE_LEAF_VALUE,
    SZIPPER_ROOT_VALUE,
    SZIPPER_NODER_VALUE,
    SZIPPER_NODEL_VALUE = 7
} ValueType;

struct Tagged {
    ValueType tag;
};

void init_tag(Tagged* tag, ValueType vtype);

ValueType get_type(Tagged* val);

#endif