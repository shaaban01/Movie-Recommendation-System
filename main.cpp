#include <iostream>
#include "authentication.h"

int main()
{

    Authentication *auth = new CmdAuthentication();
    auth->authenticate();
    delete auth;
    return 0;
}
