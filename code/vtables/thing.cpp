#include <stdlib.h>
#include <assert.h>
#include <dlfcn.h>

#include <iostream>
using namespace std;

/**
 * Wrap our rust type in a "pretty" C++ vtable that get's associated
 * at runtime, after we load the library and find out where 
 * the function pointers are
 */
struct DoAThingVtable {
    void(*destructor)(void *self);
    size_t size;
    size_t alignment;

    void(*add)(void *self, int32_t item);
    int32_t(*remove)(void *self);
};

struct BoxDoAThing {
    void *data;
    DoAThingVtable *vtable;
};

int main(void) {
    auto lib = dlopen("doathing.dll", 0);
    auto new_thing = (BoxDoAThing(*)()) dlsym(lib, "new_thing");
    auto free_thing = (void(*)(BoxDoAThing)) dlsym(lib, "free_thing");

    auto thing = new_thing();
    cout << "So far so good!" << endl;

    thing.vtable->add(thing.data, 5);
    thing.vtable->add(thing.data, 6);
    assert(thing.vtable->remove(thing.data) == 6);
    assert(thing.vtable->remove(thing.data) == 5);
    assert(thing.vtable->remove(thing.data) == 0);

    free_thing(thing);
}