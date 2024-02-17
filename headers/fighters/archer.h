#pragma once

class Archer : public Shooter, public Person
{
public:
	Archer(SDL_Texture *img, int pos, int speed, bool good, int health, int interval, int range, bool flying, Arrow arrow)
		: Shooter(interval, range, arrow), Person(img, pos, speed, good, health, flying) {}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) override
	{
		Person::DrawOn(rend, dst_pos);
	}
	virtual void Action() override
	{
		Shooter::Action();
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