#include "FipListAlgo.hpp"
#include "TagType.hpp"
#include "TagedList.hpp"

List* reverseAcc(List* xs, List* acc) {
    ValueType type = get_type((Tagged*)xs);

    if (type == NIL) return acc;
    else { //(type != 0)
        Tagged* x = head(xs);
        List* xx = tail(xs);
        //SPLIT(xs, &x, (Tagged**)&xx);

        Tagged* ru = &xs->base;
        return reverseAcc(xx, list_append(x, acc, ru));
    }
}

List* reverse(List* xs) {
    return reverseAcc(xs, init_list());
}