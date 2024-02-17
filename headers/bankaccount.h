#pragma once

class BankAccount
{
private:
	int money = 0, capacity = 0;

public:
	BankAccount(int cap) : capacity(cap) {}
	void AddMoney(int money)
	{
		this->money = std::min(this->money + money, capacity);
	}
	bool Pay(int price)
	{
		if (price > money)
		{
			return false;
		}
		else
		{
			money -= price;
			return true;
		}
	}
	void DrawOn(SDL_Renderer *rend, SDL_Rect dst, int section, SDL_Color col = SDL_Color{255, 255, 0, 255}) const
	{
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderFillRect(rend, &dst);

		SDL_SetRenderDrawColor(rend, 255, 255, 0, 255);
		SDL_Rect money_rect{dst.x, dst.y, dst.w * money / capacity, dst.h};
		SDL_RenderFillRect(rend, &money_rect);

		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_RenderDrawRect(rend, &dst);
		for (int i = section; i < capacity; i += section)
		{
			SDL_RenderDrawLine(rend, dst.x + dst.w * i / capacity, dst.y, dst.x + dst.w * i / capacity, dst.y + dst.h - 1);
		}
	}
};