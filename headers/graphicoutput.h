#pragma once

#include <SDL2/SDL_image.h>

class GraphicOutput
{
private:
	SDL_Window *window;
	SDL_Renderer *rend;
public:
	constexpr static int width = Fighter::lenght, killedPos = 0, killedHeight = 30,
						 bankPos = killedPos + killedHeight, bankHeight = 30,
						 alliesPos = bankPos + bankHeight, alliesHeight = Fighter::size.y,
						 playgroundPos = alliesPos + alliesHeight, playgroundHeight = Fighter::size.y,
						 height = playgroundPos + playgroundHeight;

	GraphicOutput(std::string title, int x, int y, int w, int h)
	{
		window = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);
		rend = SDL_CreateRenderer(window, -1, 0);
	}

	~GraphicOutput()
	{
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(window);
	}

	void Show(const KillCounter &killed, const BankAccount &account, const MercenaryStore &allies, const Playground &playground)
	{
		SDL_SetRenderDrawColor(rend, 255, 255, 160, 255);
		SDL_RenderClear(rend);

		killed.DrawOn(rend, SDL_Rect{0, killedPos, width, killedHeight});
		account.DrawOn(rend, SDL_Rect{0, bankPos, Fighter::lenght, bankHeight}, 500);
		allies.DrawOn(rend, SDL_Point{0, alliesPos});
		playground.DrawOn(rend, SDL_Point{0, playgroundPos});
		SDL_RenderPresent(rend);
	}

	SDL_Texture *LoadImg(std::string s)
	{
		auto surface = IMG_Load(s.c_str());
		auto texture = SDL_CreateTextureFromSurface(rend, surface);
		SDL_FreeSurface(surface);
		return texture;
	}
};