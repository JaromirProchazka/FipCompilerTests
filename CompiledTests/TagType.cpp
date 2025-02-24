#include "TagType.hpp"

void init_tag(Tagged* tag, ValueType vtype) {
    assert(vtype <= MaxTypeId && vtype >= 0);
    tag->tag = vtype;
}

ValueType get_type(Tagged* val) {
    if (!val) return NIL;
    return val->tag;
}