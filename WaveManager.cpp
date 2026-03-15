#include "WaveManager.h"

#include <cstdlib>
#include <utility>
#include <vector>

WaveManager::WaveManager() : wave(1) {}

void WaveManager::SpawnWave(std::vector<Enemy>& enemies, const Border& border)
{
    if (!HasMoreWaves())
    {
        return;
    }

    if (wave % 5 == 0)
    {
        const int bossX = border.GetMinX() + (border.GetMaxX() - border.GetMinX() - 2) / 2;
        enemies.emplace_back(bossX, border.GetMinY(), EnemyType::Boss);
        wave++;
        return;
    }

    constexpr int enemyWidth = 3;
    constexpr int minHorizontalGap = 1;
    constexpr int maxSpawnRows = 3;

    const int minEnemyX = border.GetMinX();
    const int maxEnemyX = border.GetMaxX() - (enemyWidth - 1);
    const int spawnStep = enemyWidth + minHorizontalGap;
    const int availableRows = (std::min)(maxSpawnRows, border.GetMaxY() - border.GetMinY() + 1);

    std::vector<std::pair<int, int>> spawnSlots;
    for (int rowOffset = 0; rowOffset < availableRows; ++rowOffset)
    {
        const int y = border.GetMinY() + rowOffset;
        for (int x = minEnemyX; x <= maxEnemyX; x += spawnStep)
        {
            spawnSlots.emplace_back(x, y);
        }
    }

    const int enemyCount = (std::min)(3 + wave, static_cast<int>(spawnSlots.size()));
    for (int i = 0; i < enemyCount; ++i)
    {
        EnemyType type = EnemyType::Normal;
        const int typeRoll = rand() % 10;
        if (typeRoll < 2)
        {
            type = EnemyType::Fast;
        }
        else if (typeRoll < 4)
        {
            type = EnemyType::Strong;
        }

        const int slotIndex = rand() % spawnSlots.size();
        const std::pair<int, int> slot = spawnSlots[slotIndex];
        spawnSlots.erase(spawnSlots.begin() + slotIndex);
        enemies.emplace_back(slot.first, slot.second, type);
    }

    wave++;
}

bool WaveManager::HasMoreWaves() const
{
    return wave <= maxWaves;
}

int WaveManager::GetWave() const { return wave; }

int WaveManager::GetMaxWaves() const
{
    return maxWaves;
}