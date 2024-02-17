#pragma once

class TouchFighter : public RangeFighter, public AttackingFighter
{
private:
	bool AttackEnemies()
	{
		return FindEnemies<DestructibleFighter>([&](auto x) { Attack(x); }, false);
	}

protected:
	Interval interval;
	bool AttackIfPossible()
	{
		interval.Continue();
		if (interval.IsElapsed())
		{
			if (AttackEnemies())
			{
				interval.Refresh();
				return true;
			}
		}
		return false;
	}
	bool MoveAfterAction()
	{
		return !FindEnemy<DestructibleFighter>() && !AtEnd();
	}

public:
	TouchFighter(int damage, int interval, int range)
		: RangeFighter(range), AttackingFighter(damage), interval(interval) {}
	virtual void Action() override
	{
		AttackIfPossible();
	}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) override
	{
		if (interval.WasRefreshed())
		{
			RangeFighter::DrawOn(rend, dst_pos);
		}
	}
};