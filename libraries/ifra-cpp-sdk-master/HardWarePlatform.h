 
#include "Client.h"

class HardWarePlatform
{
public:
    // virtual ~HardWarePlatform() {};
    virtual void Connect() = 0;
    virtual Client* GetClient() = 0;
};



