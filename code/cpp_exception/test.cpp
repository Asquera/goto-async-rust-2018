#include "native/handle.c"
#include <iostream>

extern "C" void meh(unsigned int);

using std::cout;
using std::endl;

void foo()
{
    try
    {
        meh(42, "Not a question!");
    }
    catch (exception_t x)
    {
        cout << "Code: " << x.value << " message: " << x.message << " ... " << endl;
    }
}

int main(int argc, char *argv[])
{
    foo();
    return 0;
}
