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
    INT,
    LIST,
    TREE_NODE,
    TREE_LEAF,
    SZIPPER_ROOT,
    SZIPPER_NODER,
    SZIPPER_NODEL = 7
} ValueType;

struct Tagged {
    ValueType tag;
};

void init_tag(Tagged* tag, ValueType vtype);

ValueType get_type(Tagged* val);

#endif