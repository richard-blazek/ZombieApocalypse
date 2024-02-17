#pragma once

class Healer : public Person, public HealingFighter
{
protected:
	bool Touch(Fighter *creature)
	{
		if (IsGood())
		{
			return GetPos() <= creature->GetPos() + size.x && GetPos() + size.x + range >= creature->GetPos();
		}
		else
		{
			return GetPos() >= creature->GetPos() - size.x && GetPos() - size.x - range <= creature->GetPos();
		}
	}
	DestructibleFighter *CanHeal(Playground &playground)
	{
		for (size_t i = 0; i < playground.size(); ++i)
		{
			if (auto d = dynamic_cast<DestructibleFighter *>(playground[i]); d && d->IsGood() == IsGood() && Touch(d) && !d->IsHealthy())
			{
				return d;
			}
		}
		return nullptr;
	}
	bool HealIfPossible(Playground &playground)
	{
		interval.Continue();
		auto healable = CanHeal(playground);
		if (interval.IsElapsed() && healable)
		{
			Heal(healable);
			interval.Refresh();
			return true;
		}
		return healable != nullptr;
	}
	bool MoveAfterAction(Playground &playground)
	{
		return !CanHeal(playground);
	}
	Interval interval;
	int range;

public:
	Healer(SDL_Texture *img, int pos, int speed, bool good, int health, int power, int interval, int range, bool flying)
		: Person(img, pos, speed, good, health, flying), HealingFighter(power), interval(interval), range(range) {}
	virtual void Action() override
	{
		if (!HealIfPossible(playground))
		{
			GoForward();
		}
	}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) override
	{
		Person::DrawOn(rend, dst_pos);
	}
	virtual Fighter *Clone() override
	{
		return new std::remove_reference_t<decltype(*this)>(*this);
	}
};