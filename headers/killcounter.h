#pragma once

class KillCounter
{
private:
	TTF_Font *font = TTF_OpenFont("font.ttf", 20);
	int killed = 0, total = 0;

public:
	KillCounter(int total) : total(total) {}

	~KillCounter()
	{
		TTF_CloseFont(font);
	}

	void Increment(int newkilled)
	{
		killed += newkilled;
	}
	bool YouWin()
	{
		return killed == total;
	}
	void DrawOn(SDL_Renderer *rend, SDL_Rect dst) const
	{
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderFillRect(rend, &dst);

		SDL_SetRenderDrawColor(rend, 0, 255, 255, 255);
		SDL_Rect score_rect{dst.x, dst.y, dst.w * killed / total, dst.h};
		SDL_RenderFillRect(rend, &score_rect);

		auto pct_string = std::to_string(killed * 100 / total) + "%";
		auto pct_surface = TTF_RenderText_Blended(font, pct_string.c_str(), SDL_Color{255, 255, 255, 255});
		auto pct_texture = SDL_CreateTextureFromSurface(rend, pct_surface);
		auto pct_dstrect = SDL_Rect{dst.x + (dst.w - pct_surface->w) / 2, 0, pct_surface->w, pct_surface->h};
		SDL_RenderCopy(rend, pct_texture, 0, &pct_dstrect);
		SDL_DestroyTexture(pct_texture);
		SDL_FreeSurface(pct_surface);
	}
};