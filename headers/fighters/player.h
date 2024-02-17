#pragma once

class Player : public TouchFighter, public Shooter, public Person
{
private:
	const Uint8 *kb_state;

public:
	Player(SDL_Texture *img, int pos, int speed, int health, int damage, int interval, int range, Arrow arrow, int shootinterval, int shootrange)
		: TouchFighter(damage, interval, range),
		  Shooter(shootinterval, shootrange, arrow),
		  Person(img, pos, speed, true, health, false),
		  kb_state(SDL_GetKeyboardState(0)) {}

	virtual void BeReversed(Fighter &) override {}
	virtual void Action() override
	{
		if (!IsHealthy())
		{
			++health;
		}
		if (kb_state[SDL_SCANCODE_LEFT] || kb_state[SDL_SCANCODE_RIGHT])
		{
			if (kb_state[SDL_SCANCODE_RIGHT])
			{
				GoRight();
			}
			else
			{
				GoLeft();
			}
			Shooter::interval.Continue();
			TouchFighter::interval.Continue();
		}
		else if (!TouchFighter::AttackIfPossible())
		{
			Shooter::AttackIfPossible();
		}
		else
		{
			Shooter::interval.Continue();
		}
	}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) override
	{
		Person::DrawOn(rend, dst_pos);
		dst_pos.x += pos;
		TouchFighter::DrawOn(rend, dst_pos);
	}
	virtual Fighter *Clone() override
	{
		throw std::logic_error("Player must be unique");
	}
};