#pragma once
#ifndef TAGED_LIST_H 
#define TAGED_LIST_H

#include <iostream>
#include "TagType.hpp"
#include <variant>
#include <algorithm>
#include <ranges>
#include <vector>


struct List {
    struct Tagged base;
    size_t size;
    Tagged* value;
    List* tail;

    // Iterator implementation
    struct Iterator {
        List* current;

        Iterator() : current(nullptr) {}
        Iterator(List* node) : current(node) {}

        Iterator& operator++() {
            if (current) {
                current = current->tail;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        List* operator*() {
            return current;
        }

        Tagged* operator->() {
            return &current->base;
        }

        bool operator==(const Iterator& other) {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) {
            return !(*this == other);
        }
    };

    // Container methods
    Iterator begin() { return Iterator(this); }
    Iterator end() { return init_list(); }
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

//////////////////////////////////////////////////////////////

using ListElement = std::variant<Tagged**, RecursiveList>;
using RecursiveListContainer = std::vector<ListElement>;
class RecursiveList {
    ValueType type;
    RecursiveListContainer elements;

public:
    ValueType type() {
        return type;
    }
    RecursiveList(ValueType t, RecursiveListContainer init) : elements(init), type(t) {}
    RecursiveList(ValueType t, std::initializer_list<ListElement> init) : elements(init), type(t) {}
    size_t size() {
        return elements.size();
    }
    RecursiveListContainer::iterator begin() {
        return elements.begin();
    }
    RecursiveListContainer::iterator end() {
        return elements.end();
    }
};
void printList(const RecursiveList& list, int indent = 0);
RecursiveList nested(ValueType t, std::initializer_list<ListElement> init) {
    return RecursiveList(t, init);
}

//bool SPLIT(const List* splitted, RecursiveList binders);
//bool SPLIT(const List* splitted, Tagged** binders);

void _unsave_split_step(const List* splitted, Tagged** last);

template <IsTaggedPtrPtr Arg, IsTaggedPtrPtr... Args>
void _unsave_split_step(const List* splitted, Arg first, Args... results)
{
    *first = splitted->value;
    return _unsave_split_step(tail(splitted), results...);
}


bool SPLIT(List& splitted, RecursiveList& binders)
{
    if (splitted.size < binders.size())
        return false;

    auto&& split = splitted.begin();
    auto&& bind = binders.begin();
    while (split != splitted.end() && bind != binders.end()) {
        if (std::holds_alternative<RecursiveList>(*bind)) {
            if (!SPLIT(**split, std::get<RecursiveList>(*bind))) {
                return false;
            }
        }
        else {
            // FIXME: handle
        }

        ++split;
        ++bind;
    }

    return true;
}


#endif