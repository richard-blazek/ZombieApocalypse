#pragma once

class Fighter;

class Playground
{
private:
	std::vector<Fighter *> fighters;
	bool active = true;

public:
	Playground() : fighters() {}
	~Playground();

	void AddFighter(Fighter *fighter)
	{
		fighters.push_back(fighter);
	}
	void AddFighters(std::vector<Fighter *> fighters)
	{
		for (auto fighter : fighters)
		{
			AddFighter(fighter);
		}
	}
	int Clean();
	void DrawOn(SDL_Renderer *rend, SDL_Point pos) const;
	void Actions();
	size_t size() const noexcept
	{
		return fighters.size();
	}
	Fighter *operator[](size_t i) const
	{
		return fighters[i];
	}
	template<typename T>
	bool Has()
	{
		for (size_t i = 0; i < fighters.size(); ++i)
		{
			if (dynamic_cast<T *>(fighters[i]))
			{
				return true;
			}
		}
		return false;
	}
	bool Defeat();
};

#include "speedstate.h"
#include "interval.h"
#include "fighters.h"

Playground::~Playground()
{
	for (size_t i = 0; i < fighters.size(); ++i)
	{
		delete fighters[i];
	}
}

int Playground::Clean()
{
	int money = 0;
	for (size_t i = 0; i < fighters.size(); ++i)
	{
		if (!fighters[i]->IsAlive())
		{
			if (auto d = dynamic_cast<DestructibleFighter*>(fighters[i]); d && !d->IsGood() && !d->IsReversed())
			{
				++money;
			}
			delete fighters[i];
			fighters.erase(fighters.begin() + i);
			--i;
		}
	}
	return money;
}
void Playground::Actions()
{
	active = !active;
	for (size_t i = 0; i < fighters.size(); ++i)
	{
		if (auto x = dynamic_cast<StoppableFighter *>(fighters[i]))
		{
			x->Continue();
			if (x->GetState() != SpeedState::Enum::Sleeping && (x->GetState() != SpeedState::Enum::Slow || active))
			{
				x->Action();
			}
		}
		else
		{
			fighters[i]->Action();
		}
	}
}
void Playground::DrawOn(SDL_Renderer *rend, SDL_Point pos) const
{
	for (size_t i = 0; i < fighters.size(); ++i)
	{
		fighters[i]->DrawOn(rend, pos);
	}
}
bool Playground::Defeat()
{
	return !Has<Player>() || !Has<Gate>();
}