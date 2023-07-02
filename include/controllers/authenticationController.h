// authentication.h
#include <string>
#include "userController.h"

class Authentication
{
protected:
    bool authenicated = false;
    virtual void registerUser() = 0;
    virtual void loginUser() = 0;

public:
    virtual void authenticate() = 0;
    bool isAuthenticated() { return authenicated; };
};

class CmdAuthentication : public Authentication
{
private:
    UserController *userController;

public:
    CmdAuthentication();
    void registerUser() override;
    void loginUser() override;
    void authenticate() override;
    bool isAuthenticated();
    void showMenu();
};