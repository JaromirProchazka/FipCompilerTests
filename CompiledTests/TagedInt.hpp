#pragma once
#ifndef TAGED_INT_H 
#define TAGED_INT_H

#include "TagType.hpp"


struct Integer {
    struct Tagged base;
    int value;
};

Integer* init_integer(int val, Tagged* recycle_address = NULL) {
    Integer* new_int = recycle_address ? (Integer*)recycle_address : (Integer*)malloc(sizeof(Integer));
    if (new_int == NULL) {
        return NULL;
    }

    init_tag(&new_int->base, INT);
    new_int->value = val;
    return new_int;
}

Tagged* tagged(Integer* integer) {
    return &integer->base;
}

#endif