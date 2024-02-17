#pragma once

class Decelerator : public DeceleratingFighter, public Person, public RangeFighter
{
protected:
	bool lastaction = false;
	bool DecelerateIfPossible()
	{
		return FindEnemies<StoppableFighter>([&](auto f) { Decelerate(f); }, false);
	}

public:
	Decelerator(SDL_Texture *img, int pos, int speed, bool good, int health, int range, SpeedState state, bool flying)
		: DeceleratingFighter(state), Person(img, pos, speed, good, health, flying), RangeFighter(range) {}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) override
	{
		Person::DrawOn(rend, dst_pos);
		if (lastaction)
		{
			RangeFighter::DrawOn(rend, dst_pos);
			lastaction = false;
		}
	}
	virtual void Action() override
	{
		if (DecelerateIfPossible())
		{
			lastaction = true;
		}
		else
		{
			GoForward();
		}
	}
	virtual Fighter *Clone() override
	{
		return new std::remove_reference_t<decltype(*this)>(*this);
	}
};