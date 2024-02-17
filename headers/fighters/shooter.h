#pragma once

class Shooter : public RangeFighter
{
private:
	bool AttackEnemies()
	{
		return FindEnemies<DestructibleFighter>([&](auto) { playground.AddFighter(arrow.BeShot(*this)); }, true);
	}

protected:
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
	Interval interval;
	Arrow arrow;

public:
	Shooter(int interval, int range, Arrow arrow)
		: RangeFighter(range), interval(interval), arrow(arrow) {}

	virtual void Action() override
	{
		AttackIfPossible();
	}
};