

#include <iostream>
#include "page_alloc.cpp"

int main() {
    auto* bud = new BudLocator();

    bud->to_string();
    void* p1, * p2, * p3, * p4;
    p1 = bud->my_alloc(255);
    p2 = bud->my_alloc(255);
    p3 = bud->my_alloc(255);
    p4 = bud->my_alloc(255);


    bud->free(p3);
    bud->free(p1);
    bud->to_string();
    bud->free(p2);
    bud->free(p4);

    bud->to_string();

    p1 = bud->my_alloc(1);
    p2 = bud->my_alloc(1);
    p3 = bud->my_alloc(1);
    p4 = bud->my_alloc(1);

    bud->free(p3);
    bud->free(p1);
    bud->to_string();
    bud->free(p2);
    bud->free(p4);

    bud->to_string();

    return 0;
}