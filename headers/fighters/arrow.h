#pragma once

class Arrow final : public RangeFighter, public AttackingFighter, public VisualFighter, public LocatedFighter, public NonNeutralFighter
{
protected:
	bool end = false;

public:
	Arrow(SDL_Texture *img, int pos, int damage, bool good)
		: RangeFighter(0), AttackingFighter(damage), VisualFighter(img), LocatedFighter(pos, 60), NonNeutralFighter(good) {}
	virtual void Action() override
	{
		if (FindEnemies<DestructibleFighter>([&](auto x) { Attack(x); }, true) || AtEnd())
		{
			end = true;
		}
		else
		{
			GoForward();
		}
	}
	virtual bool IsAlive() const noexcept override
	{
		return !end;
	}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) override
	{
		dst_pos.x += pos;
		VisualFighter::DrawOn(rend, dst_pos);
	}
	Fighter *BeShot(Fighter &archer)
	{
		pos = archer.GetPos();
		return Clone();
	}
	virtual Fighter *Clone() override
	{
		return new std::remove_reference_t<decltype(*this)>(*this);
	}
};