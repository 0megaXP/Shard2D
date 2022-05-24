#include <iostream>

#include "src/Framework/Management/Kickstart.h"
#include "src/ApplicationMain.h"

int main()
{
    ApplicationMain* newMain = new ApplicationMain();

    Shard2D::Init(newMain);

    delete newMain;

    std::cout << "Hello World!\n";

    return 0;
}
