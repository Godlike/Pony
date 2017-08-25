
#include <iostream>
using namespace std;

#include <pony.hpp>
using namespace pony;

int test_address()
{
    Address address;
    return 0;
}

int test_socket()
{
    Socket socket;
    return 0;
}

int tests()
{
    int ret = 0;

    ret = test_address();
    if (ret) return ret;

    ret = test_socket();
    if (ret) return ret;

    return ret;
}

void prologe() {
    cout << "    Pony unit tests, v1.0\n Gl!n, Saint-Petersburg, 2017\n\n...\n";
}

void epiloge(int ret) {
    cout << "\t" << ((ret)? "fail!": "pass.") << "\n\n";
}

int main()
{
    int ret = 0;

    prologe();

    ret = tests();

    epiloge(ret);

    return 0;
}
