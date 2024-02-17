#pragma once

class Reverser : public ReversingFighter, public Person, public RangeFighter
{
protected:
	Interval interval;
	bool ReverseIfPossible()
	{
		interval.Continue();
		if (interval.IsElapsed())
		{
			if (FindEnemies<NonNeutralFighter>([&](auto x) { Reverse(x); }, true))
			{
				interval.Refresh();
				return true;
			}
			return false;
		}
		return FindEnemy<NonNeutralFighter>();
	}
	bool MoveAfterAction()
	{
		return !FindEnemy<NonNeutralFighter>() && !AtEnd();
	}

public:
	Reverser(SDL_Texture *img, int pos, int speed, bool good, int health, int interval, int range, bool flying)
		: Person(img, pos, speed, good, health, flying), RangeFighter(range), interval(interval) {}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) override
	{
		Person::DrawOn(rend, dst_pos);
		if (interval.WasRefreshed())
		{
			RangeFighter::DrawOn(rend, dst_pos);
		}
	}
	virtual void Action() override
	{
		ReverseIfPossible();
		if (MoveAfterAction())
		{
			GoForward();
		}
	}
	virtual Fighter *Clone() override
	{
		return new std::remove_reference_t<decltype(*this)>(*this);
	}
};