#pragma once
#include "Sprite.h"
#include <ctime>
#include <stdlib.h> 
using namespace System::Drawing;
using namespace System;

static class LambdaRunner
{
public:
    static Point AssassinNormalizePoint(int x, int y, float distance) {
        auto getNormalizeAxisPoint = [distance](int value) {return Math::Round(value / distance, MidpointRounding::AwayFromZero); };
        return Point(getNormalizeAxisPoint(x), getNormalizeAxisPoint(y));
    }

    static SpriteDirections AssassinSpriteDirection(Point point) {
        auto getSpriteDirection = [](Point point) {
            if (point.Y != 0) return point.Y > 0 ? SpriteDirections::down : SpriteDirections::up; 
            else return point.X > 0 ? SpriteDirections::right : SpriteDirections::left;
        };
        return getSpriteDirection(point);
    }

    static int MatrixGetNodeValue(int curRow, int curCol, int rows, int cols, float porcentajeLadrillo) {
        auto getNormalizeAxisPoint = [=]() {
            if ((curRow == 0 || curCol == 0 || curRow == rows - 1 || curCol == cols - 1) || (curRow % 2 == 0 && curCol % 2 == 0)) return 2;//Marco al rededor del mapa //Bloques fijos en el interior
            else if ((curRow == 1 && (curCol == 1 || curCol == 2)) || (curCol == 1 && curRow == 2) || (curRow == rows - 2 && (curCol == cols - 3 || curCol == cols - 2)) || (curRow == rows - 3 && curCol == cols - 2)) return 0; //Bloques libres en las esquinas
            else return GetRandomNodeValue(porcentajeLadrillo);
        };
        return getNormalizeAxisPoint();
    }

private:
    static int GetRandomNodeValue(int porcentajeLadrillo) {
        int value = rand() % 100;
        return value >= porcentajeLadrillo ? 0 : 1;

    }
};
