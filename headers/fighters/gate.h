#pragma once

class Gate : public DestructibleFighter, public VisualFighter, public LocatedFighter, public NonNeutralFighter
{
public:
	Gate(SDL_Texture *img, int health, int pos, bool good)
		: DestructibleFighter(health, false), VisualFighter(img), LocatedFighter(pos, 0), NonNeutralFighter(good) {}
	virtual void Action() override
	{
		reversed = false;
	}
	void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos)
	{
		dst_pos.x += pos;
		VisualFighter::DrawOn(rend, dst_pos);
		DestructibleFighter::DrawOn(rend, dst_pos);
	}
	virtual Fighter *Clone() override
	{
		return new std::remove_reference_t<decltype(*this)>(*this);
	}
};