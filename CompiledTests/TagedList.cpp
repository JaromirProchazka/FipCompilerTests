#include "TagedList.hpp"


List* EMPTY_LIST;

void PREPARE_LISTS() {
    List* new_node = (List*)malloc(sizeof(List));
    assert(new_node != NULL);
    init_tag(&new_node->base, NIL);
    new_node->size = 0;
    new_node->value = NULL;
    new_node->tail = NULL;

    EMPTY_LIST = new_node;
}

List* _init_list_node(size_t size, Tagged* value, Tagged* recycle_address) {
    List* new_node = recycle_address ? (List*)recycle_address : (List*)malloc(sizeof(List));
    if (new_node == NULL) {
        return NULL;
    }

    init_tag(&new_node->base, LIST);
    new_node->value = value;
    new_node->size = size;
    return new_node;
}

List* list_append(Tagged* value, List* tail, Tagged* recycle_address) {
    size_t new_size = (tail) ? tail->size + 1 : 0;
    List* new_node = _init_list_node(new_size, value, recycle_address);
    new_node->tail = tail;

    return new_node;
}

void _cons(List* current, Tagged* last) {
    List* result = _init_list_node(1, last);
    current->tail = result;
    result->tail = init_list();
}

List* Cons(Tagged* next) {
    List* result = _init_list_node(1, next);
    result->tail = init_list();
    return result;
}

List* _cons_ru(List* ru, List* current, Tagged* lats) {
    return list_append(lats, current, (Tagged*)ru);
}

void _unsave_split_step(const List* splitted, Tagged** last) {
    if (splitted->size == 1) {
        *last = splitted->value;
    }
    else {
        *last = (Tagged*)splitted;
    }
}



Tagged* head(const List* list) {
    return list->value;
}
List* tail(const List* list) {
    return list->tail;
}

List* init_list() {
    return EMPTY_LIST;
}

bool is_empty(const List* list) {
    if (list == NULL || list->size == 0)
        return true;
    return false;
}

void printList(const RecursiveList& list, int indent) {
    std::cout << list.type << "{\n";
    for (const auto& element : list.elements) {
        for (int i = 0; i < indent + 1; ++i) std::cout << "  ";

        if (std::holds_alternative<RecursiveList>(element)) {
            printList(std::get<RecursiveList>(element), indent + 1);
        }
        else {
            std::cout << "&value\n";
        }
    }
    for (int i = 0; i < indent; ++i) std::cout << "  ";
    std::cout << "}\n";
}