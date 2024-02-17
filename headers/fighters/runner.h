#pragma once

class Runner : public AttackingFighter, public Person
{
public:
	Runner(SDL_Texture *img, int pos, int speed, int health, int damage, bool flying)
		: AttackingFighter(damage), Person(img, pos, speed, false, health, flying) {}
	virtual void Action() override
	{
		GoForward();
		if (pos == 0)
		{
			for (size_t i = 0; i < playground.size(); ++i)
			{
				if (auto g = dynamic_cast<Gate *>(playground[i]))
				{
					Attack(g);
				}
			}
		}
	}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) override
	{
		dst_pos.x += pos;
		StoppableFighter::DrawOn(rend, dst_pos);
		VisualFighter::DrawOn(rend, dst_pos);
		DestructibleFighter::DrawOn(rend, dst_pos);
	}
	virtual bool IsAlive() const noexcept override
	{
		return DestructibleFighter::IsAlive();
	}
	virtual Fighter *Clone() override
	{
		return new std::remove_reference_t<decltype(*this)>(*this);
	}
};