#pragma once

class Fighter
{
public:
	virtual void BeAttacked(Fighter &attacker, int damage) {}
	virtual void BeHealed(Fighter &healer, int power) {}
	virtual void BeReversed(Fighter &reverser) {}
	virtual void BeDecelerated(Fighter &decelerator, SpeedState newstate) {}
	constexpr static SDL_Point size{80, 80};
	constexpr static int lenght = 16 * size.x;
	static Playground playground;
	virtual ~Fighter() {}
	virtual bool IsAlive() const noexcept = 0;
	virtual int GetPos() const noexcept = 0;
	virtual bool IsGood() const noexcept = 0;
	virtual bool IsReversed() const noexcept = 0;
	virtual Fighter *Clone() = 0;
	virtual void Action() = 0;
	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) {}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Rect dst_rect) {}
};