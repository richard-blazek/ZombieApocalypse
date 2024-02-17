#pragma once

class Cart : public RangeFighter, public AttackingFighter, public VisualFighter, public LocatedFighter, public NonNeutralFighter
{
private:
	int range;
	bool end = false;

public:
	Cart(SDL_Texture *img, int pos, int speed, bool good, int damage, int range)
		: RangeFighter(0), AttackingFighter(damage), VisualFighter(img), LocatedFighter(pos, speed), NonNeutralFighter(good), range(range) {}
	virtual void Action() override
	{
		GoForward();
		for (size_t i = 0; i < playground.size(); ++i)
		{
			if (auto d = dynamic_cast<DestructibleFighter *>(playground[i]); d && d->IsGood() != IsGood() && Touch(d))
			{
				end = true;
			}
		}
	}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos)
	{
		dst_pos.x += pos;
		if (end)
		{
			SDL_SetRenderDrawColor(rend, 255, 128, 0, 255);
			SDL_Rect rect{dst_pos.x, dst_pos.y, range, size.y};
			SDL_RenderFillRect(rend, &rect);
		}
		else
		{
			VisualFighter::DrawOn(rend, dst_pos);
		}
	}
	virtual bool IsAlive() const noexcept override
	{
		return !end;
	}
	~Cart()
	{
		RangeFighter::range = range;
		for (size_t i = 0; i < playground.size(); ++i)
		{
			if (auto d = dynamic_cast<DestructibleFighter*>(playground[i]); d && d->IsGood() != IsGood() && Touch(d))
			{
				Attack(d);
			}
		}
	}
	virtual Fighter *Clone() override
	{
		return new std::remove_reference_t<decltype(*this)>(*this);
	}
};