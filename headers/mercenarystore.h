#pragma once

class MercenaryStore
{
private:
	std::vector<Fighter *> mercenaries;
	std::vector<int> prices;

	void AddMercenary(Fighter *fighter, int price)
	{
		mercenaries.push_back(fighter);
		prices.push_back(price);
	}

	template<typename... Types>
	void AddMercenary(Fighter *fighter, int price, Types... rest)
	{
		AddMercenary(fighter, price);
		AddMercenary(rest...);
	}

public:
	template<typename... Types>
	MercenaryStore(Types... mercenaries)
	{
		AddMercenary(mercenaries...);
	}
	~MercenaryStore()
	{
		for (auto m : mercenaries)
		{
			delete m;
		}
	}
	Fighter *Purchase(BankAccount& account, SDL_Point pos)
	{
		static bool pressed = false;
		int mouse_x = 0, mouse_y = 0;
		if (SDL_GetMouseState(&mouse_x, &mouse_y) & SDL_BUTTON_LEFT)
		{
			if (!pressed)
			{
				pressed = true;
				if (pos.y <= mouse_y && mouse_y <= pos.y + Fighter::size.y && pos.x <= mouse_x && mouse_x <= pos.x + Fighter::size.x * mercenaries.size())
				{
					int i = mouse_x / Fighter::size.x;
					if (account.Pay(prices[i]))
					{
						return mercenaries[i]->Clone();
					}
				}
			}
		}
		else
		{
			pressed = false;
		}
		return nullptr;
	}
	void DrawOn(SDL_Renderer *rend, SDL_Point dst) const
	{
		SDL_Rect rect{dst.x, dst.y, Fighter::size.x, Fighter::size.y};
		for (auto mercenary : mercenaries)
		{
			mercenary->DrawOn(rend, rect);
			rect.x += rect.w;
		}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderDrawLine(rend, 0, dst.y + Fighter::size.y - 1, Fighter::lenght, dst.y + Fighter::size.y - 1);
	}
};