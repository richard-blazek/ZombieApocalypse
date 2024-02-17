#pragma once

class ZombieSpawner
{
private:
	Level level;
	std::vector<Fighter *> fighters;
	int zombiecount;

public:
	ZombieSpawner(std::vector<Fighter *> fighters, Level level, int loops)
		: level(level), fighters(fighters), zombiecount(level.TotalZombies(loops)) {}
	std::vector<Fighter *> AllNew(int loop)
	{
		std::vector<Fighter *> created;
		for (auto index : level.AllNew(loop))
		{
			created.push_back(fighters[index]->Clone());
		}
		return created;
	}
	int TotalZombies() const noexcept
	{
		return zombiecount;
	}
};