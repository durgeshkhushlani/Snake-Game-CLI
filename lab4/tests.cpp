#include "mini_test.h"

#define main snake_original_main
#include "../snake.cpp"
#undef main

TEST_CASE("Regular food gives 10 points") {
    Food food;
    CHECK(food.value() == 10);
}

TEST_CASE("Special food gives 30 points") {
    Food food;
    food.special = true;
    CHECK(food.value() == 30);
}

TEST_CASE("Special food expires after 5 seconds") {
    Food food;
    food.special = true;
    food.spawnTime = clock() - 6 * CLOCKS_PER_SEC;
    CHECK(food.expired() == true);
}

TEST_CASE("Special food does not expire immediately") {
    Food food;
    food.special = true;
    food.spawnTime = clock();
    CHECK(food.expired() == false);
}

TEST_CASE("Snake dies when head enters its own body") {
    Snake snake;
    snake.setDirection(Direction::UP);
    snake.move(true);
    snake.setDirection(Direction::LEFT);
    snake.move(true);
    snake.setDirection(Direction::DOWN);
    bool moved = snake.move(false);
    CHECK(moved == false);
}

TEST_CASE("Obstacle milestone: no obstacles added before score 50") {
    int lastObstacleScore = 0;
    int toAdd = computeObstaclesToAdd(40, lastObstacleScore, Difficulty::EASY);
    CHECK(toAdd == 0);
}

TEST_CASE("Obstacle milestone: crossing score 50 adds obstacles on Easy") {
    int lastObstacleScore = 0;
    int toAdd = computeObstaclesToAdd(50, lastObstacleScore, Difficulty::EASY);
    CHECK(toAdd == 1);
}

TEST_CASE("Obstacle milestone: crossing score 50 adds obstacles on Hard") {
    int lastObstacleScore = 0;
    int toAdd = computeObstaclesToAdd(50, lastObstacleScore, Difficulty::HARD);
    CHECK(toAdd == 3);
}

TEST_CASE("Obstacle milestone: same milestone does not fire twice") {
    int lastObstacleScore = 1; // already at milestone 1 (i.e. already handled score 50-99)
    int toAdd = computeObstaclesToAdd(60, lastObstacleScore, Difficulty::EASY);
    CHECK(toAdd == 0);
}

int main() {
    return g_tests_failed > 0 ? 1 : 0;
}