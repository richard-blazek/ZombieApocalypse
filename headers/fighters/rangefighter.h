#pragma once

class RangeFighter : public virtual Fighter
{
protected:
	int range;
	bool Touch(Fighter *creature)
	{
		if (IsGood())
			return GetPos() - size.x <= creature->GetPos() && GetPos() + range >= creature->GetPos() - size.x;
		else
			return GetPos() + size.x >= creature->GetPos() && GetPos() - range <= creature->GetPos() + size.x;
	}
	bool AtEnd()
	{
		if (IsGood())
			return GetPos() + size.x + size.x + range >= lenght;
		else
			return GetPos() - size.x - range <= 0;
	}
	template <typename T, typename Fn>
	bool FindEnemies(Fn callback, bool one)
	{
		bool action = false;
		for (size_t i = 0; i < playground.size(); ++i)
		{
			if (auto o = dynamic_cast<T *>(playground[i]); o && o->IsGood() != IsGood() && Touch(o))
			{
				callback(o);
				action = true;
				if (one)
				{
					break;
				}
			}
		}
		return action;
	}
	template <typename T>
	bool FindEnemy()
	{
		return FindEnemies<T>([](auto) {}, true);
	}

public:
	RangeFighter(int range)
		: range(range) {}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) override
	{
		SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
		SDL_Rect rect{GetPos() + dst_pos.x + (IsGood() ? size.x : -range), dst_pos.y + size.y / 2 - 1, range, 2};
		SDL_RenderFillRect(rend, &rect);
	}
};