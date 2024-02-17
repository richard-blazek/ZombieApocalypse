#pragma once

class VisualFighter : public virtual Fighter
{
private:
	SDL_Texture *img;

public:
	VisualFighter(SDL_Texture *img) : img(img) {}

	virtual void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos) override
	{
		SDL_Rect dest{dst_pos.x, dst_pos.y, Fighter::size.x, Fighter::size.y};
		SDL_RenderCopyEx(rend, img, 0, &dest, 0, 0, IsReversed() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	}
	virtual void DrawOn(SDL_Renderer *rend, SDL_Rect dst_rect) override
	{
		SDL_RenderCopy(rend, img, 0, &dst_rect);
	}
};