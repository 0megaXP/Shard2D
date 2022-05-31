# Shard2D

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/77c77ace295247dba07cf1a9c82ba3b3)](https://www.codacy.com/gh/0megaXP/Shard2D/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=0megaXP/Shard2D&amp;utm_campaign=Badge_Grade)
[![License-MIT](https://img.shields.io/github/license/0megaXP/Shard2D)](https://github.com/0megaXP/Shard2D/blob/main/LICENSE)
![Repo Size](https://img.shields.io/github/repo-size/0megaXP/Shard2D)

Shard2D is an early-stage 2D rendering framework for the creation of 2D games and applications, created in C++ with the support of the SDL2 library. This project was originally created for the purpose of testing and learning, trying to make the development of games with C++ as simple and optimized as possible.

***

## Dependencies

To use Shard2D you need to download and implement the following libraries:

- [SDL2](https://www.libsdl.org/download-2.0.php)<br>
- [SDL_image](https://www.libsdl.org/projects/SDL_image/)<br>
- [SDL_ttf](https://www.libsdl.org/projects/docs/SDL_ttf/SDL_ttf.html)<br>

## Requirements

- Visual Studio 2019 / 2022
- C++ 20

***

## Implementation

- Start by downloading the latest version (or the one you want to use) of the framework from the [release](https://github.com/0megaXP/Shard2D/releases) section. Then implement it as a library inside your Visual Studio project.
- Once you have included the framework, you need to setup it. Shard2D needs a custom main class which must inherit from the IMain interface. Once the class has been created, it will be mandatory to define the 2 pure virtual functions Init() (called at the first frame of the runtime) and Update() (called each frame).

```cpp
#include <ShardKickstart.h>

class TestMain : public Shard2D::IMain
{
private:
	void Init();
	void Update();
};
```

- Once the class has been created, Shard2D must be initialized from main. Create an IMain ptr with the constructor of the custom class previously created and use it as a parameter in the Init() function of Shard2D (also remember to delete it after the Init function).

```cpp
#include <ShardKickstart.h>
#include "TestMain.h"

int main()
{
    Shard2D::IMain* testMain = new TestMain();
    Shard2D::Init(testMain);
    delete(testMain);
}
```

From here the framework will start its loop and you can start developing everything from the new custom class.
