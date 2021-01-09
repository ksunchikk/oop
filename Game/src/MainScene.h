#pragma once

#include "Enemy.h"
#include <vector>
namespace game{
class MainScene {
    public:
        Castle* castle = nullptr;
        std::vector<Enemy*> enemies;
};
}

