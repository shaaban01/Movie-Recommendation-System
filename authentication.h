#include <string>
#include "db.h"

class Authentication
{
protected:
    virtual void registerUser() = 0;
    virtual void loginUser() = 0;

public:
    virtual void authenticate() = 0;
};

class CmdAuthentication : public Authentication
{
private:
    DB db;

public:
    void registerUser() override;
    void loginUser() override;
    void authenticate() override;
    void showMenu();
};
