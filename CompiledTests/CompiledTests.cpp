// CompiledTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <concepts>
#include <format>
#include "TagType.hpp"
#include "TagedInt.hpp"
#include "TagedList.hpp"
#include "TagedTree.hpp"
#include "TagLogger.hpp"
#include "FipListAlgo.hpp"


// [int, Node]
//List* zlookup(Node* t, int x) {
//    if (t->left == NULL && t->right == NULL) {
//        return cons(init_integer(0), )
//    }
//}

int main()
{
    PREPARE_LISTS();

    printf("TYPES TEST =========================================\n");
    log_tagged((Tagged*)NULL);
    printf("\n");
    auto inner1 = Cons((Tagged*)init_integer(1), (Tagged*)init_integer(2));
    log_tagged(inner1);
    printf("\n");
    auto inner2 = Cons((Tagged*)init_integer(3), (Tagged*)init_integer(4));
    log_tagged(inner2);
    printf("\n");
    auto list = Cons((Tagged*)inner1, (Tagged*)inner2, (Tagged*)init_integer(5));

    printf("Nested List: ");
    log_tagged(list);
    printf("\n");

    Node* new_tree = init_node((Tagged*)init_integer(4),
        (Tagged*)init_node((Tagged*)init_integer(2),
            (Tagged*)init_leaf((Tagged*)init_integer(1)),
            (Tagged*)init_leaf((Tagged*)init_integer(3))
        ),
        (Tagged*)init_leaf((Tagged*)init_integer(5))
    );
    printf("Tree: ");
    log_tagged(new_tree);
    printf("\n");

    printf("PATTERN MATCHING ===================================\n");
    printf("list = ");
    log_tagged(list);
    printf("\n");
    Tagged *a, *b, *c, *d, *xx;
    std::cout << "list -> (d, xx) is " << SPLIT(list, &d, &xx) << std::endl;
    printf("d = ");
    log_tagged(d);
    printf("\n");
    printf("xx = ");
    log_tagged(xx);
    printf("\n");
    std::cout << "list -> (a, b, c) is " << SPLIT(list, &a, &b, &c) << std::endl;
    printf("a = ");
    log_tagged(a);
    printf("\n");
    printf("b = ");
    log_tagged(b);
    printf("\n");
    printf("c = ");
    log_tagged(c);
    printf("\n");
    std::cout << "list -> (a, b, c, d) is " << SPLIT(list, &a, &b, &c, &d) << std::endl;
    printf("list = ");
    log_tagged(list);
    printf("\n\n");

    printf("IN-PLACE LIST REVERSE ==============================\n");
    printf("Will be reversed: ");
    log_tagged(list);
    printf("\nReversed one: ");
    log_tagged(reverse(list));
    printf("\nOriginal list: ");
    log_tagged(list);
    printf("\n");
}