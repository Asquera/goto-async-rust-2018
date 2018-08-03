
using namespace std;
#include <iostream>

int main(int argc, char const *argv[])
{
    try
    {
        try
        {
            throw 5;
        }
        catch (const char *e)
        {
            cout << "String exception: " << e << endl;
        }
    }
    catch (int i)
    {
        cout << "Integer exception " << i << endl;
    }

    return 0;
}
