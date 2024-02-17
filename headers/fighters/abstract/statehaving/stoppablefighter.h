#pragma once

class StoppableFighter : public virtual Fighter
{
protected:
	SpeedState speedstate;

public:
	StoppableFighter() : speedstate() {}
	void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos)
	{
		auto state = speedstate.GetState();
		if (state != SpeedState::Enum::Ok)
		{
			SDL_SetRenderDrawColor(rend, state == SpeedState::Enum::Sleeping ? 255 : 0, 0, 255, 255);
			SDL_Rect rect{dst_pos.x, dst_pos.y, Fighter::size.x, Fighter::size.y};
			SDL_RenderFillRect(rend, &rect);
		}
	}
	void Continue()
	{
		speedstate.Continue();
	}
	SpeedState::Enum GetState()
	{
		return speedstate.GetState();
	}
	virtual void BeDecelerated(Fighter &, SpeedState newstate)
	{
		if (newstate > speedstate)
		{
			speedstate = newstate;
		}
	}
};