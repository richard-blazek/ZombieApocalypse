#pragma once

class Person : public DestructibleFighter, public StoppableFighter, public VisualFighter, public NonNeutralFighter, public LocatedFighter
{
public:
	Person(SDL_Texture *img, int pos, int speed, bool good, int health, bool flying)
		: DestructibleFighter(health, flying), VisualFighter(img), NonNeutralFighter(good), LocatedFighter(pos, speed) {}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) override
	{
		dst_pos.x += GetPos();
		StoppableFighter::DrawOn(rend, dst_pos);
		DestructibleFighter::DrawOn(rend, dst_pos);
		VisualFighter::DrawOn(rend, dst_pos);
	}
};