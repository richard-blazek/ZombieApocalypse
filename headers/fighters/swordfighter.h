#pragma once

class SwordFighter : public TouchFighter, public Person
{
public:
	SwordFighter(SDL_Texture *img, int pos, int speed, bool good, int health, int damage, int interval, int range, bool flying)
		: TouchFighter(damage, interval, range), Person(img, pos, speed, good, health, flying) {}
	virtual void Action() override
	{
		TouchFighter::Action();
		if (MoveAfterAction())
		{
			GoForward();
		}
	}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) override
	{
		Person::DrawOn(rend, dst_pos);
		TouchFighter::DrawOn(rend, dst_pos);
	}
	virtual Fighter *Clone() override
	{
		return new std::remove_reference_t<decltype(*this)>(*this);
	}
};