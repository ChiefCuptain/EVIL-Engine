#include "Assets.h"

namespace assets
{
#pragma region Player Model
    std::vector<nu::Vector2> pointz1{ nu::Vector2{0, 0.5f}, nu::Vector2{-1, 1}, nu::Vector2{-1,-1}, nu::Vector2{0, -0.5f } };
    nu::Mesh mesh1{ pointz1, nu::Color{1.0f, 0.0f, 0.0f} };
    std::vector<nu::Vector2> pointz2{ nu::Vector2{0, 1}, nu::Vector2{2, 0}, nu::Vector2{0,-1}, nu::Vector2{0, 1 } };
    nu::Mesh mesh2{ pointz2, nu::Color{1.0f, 0.57f, 1.0f} };

    nu::Model playerModel{ {mesh1, mesh2} };
#pragma endregion

#pragma region Bullet Model
    std::vector<nu::Vector2> points{ nu::Vector2{ -1, -1 }, nu::Vector2{ 1, 0 }, nu::Vector2{ -1, 1 }, nu::Vector2{ -1, -1 } };
    nu::Mesh bulletMesh{ points,nu::Color{ 1.0f, 1.0f, 0.0f } };
    nu::Model bulletModel{ { bulletMesh } };
#pragma endregion


}