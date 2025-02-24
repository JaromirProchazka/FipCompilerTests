#pragma once
#ifndef TAGED_LIST_H 
#define TAGED_LIST_H

#include <iostream>
#include "TagType.hpp"


struct List {
    struct Tagged base;
    size_t size;
    Tagged* value;
    List* tail;
};

template<typename T>
concept IsTaggedPtr = std::same_as<T, Tagged*>;
template<typename T>
concept IsTaggedPtrPtr = std::same_as<T, Tagged**>;

void PREPARE_LISTS();
List* init_list();
List* _init_list_node(size_t size, Tagged* value, Tagged* recycle_address = NULL);
List* list_append(Tagged* value, List* tail, Tagged* recycle_address = NULL);

void _cons(List* current, Tagged* last);
template <IsTaggedPtr Arg, IsTaggedPtr... Args>
void _cons(List* current, Arg next, Args... args) {
    List* result = _init_list_node(sizeof...(Args) + 1, next);
    current->tail = result;
    _cons(result, args...);
}
List* Cons(Tagged* next);
template <IsTaggedPtr Arg, IsTaggedPtr... Args>
List* Cons(Arg next, Args... args) {
    List* result = _init_list_node(sizeof...(Args) + 1, next);
    _cons(result, args...);
    return result;
}

List* _cons_ru(List* ru, List* current, Tagged* lats);
template <IsTaggedPtrPtr Arg, IsTaggedPtrPtr... Args >
List* _cons_ru(List* ru, List* current, Arg next, Args... args) {
    return _cons_ru(ru->tail, list_append(next, current, ru), args...);
}
template <IsTaggedPtr... Args>
List* Cons_ru(List* ru, Args... items) {
    assert(ru->size == sizeof...(items));
    return _cons_ru(ru->tail, init_list(), items...);
}

Tagged* head(const List* list);
List* tail(const List* list);

bool is_empty(const List* list);

template <IsTaggedPtrPtr... Args>
bool SPLIT(const List* splitted, Args... results);

void _unsave_split_step(const List* splitted, Tagged** last);

template <IsTaggedPtrPtr Arg, IsTaggedPtrPtr... Args>
void _unsave_split_step(const List* splitted, Arg first, Args... results)
{
    *first = splitted->value;
    return _unsave_split_step(tail(splitted), results...);
}
template <IsTaggedPtrPtr... Args>
bool SPLIT(const List* splitted, Args... results)
{
    if (splitted->size < sizeof...(results))
        return false;
    _unsave_split_step(splitted, results...);
    return true;
}


#endif