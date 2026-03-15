#pragma once
#include <vector>
#include "Enemy.h"
#include "Border.h"

class WaveManager
{
private:
    int wave;
    static constexpr int maxWaves = 5;

public:
    WaveManager();

    void SpawnWave(std::vector<Enemy>& enemies, const Border& border);
    bool HasMoreWaves() const;

    int GetWave() const;
    int GetMaxWaves() const;
};