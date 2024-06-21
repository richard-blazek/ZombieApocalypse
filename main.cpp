#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "headers/bankaccount.h"
#include "headers/progress.h"
#include "headers/playground.h"

#include "headers/level.h"
#include "headers/zombiespawner.h"
#include "headers/killcounter.h"
#include "headers/mercenarystore.h"
#include "headers/graphicoutput.h"

Playground Fighter::playground;

void Main()
{
	auto level = Level(std::ifstream("levels.txt"));
	auto progress = level.GetProgressObject();

	auto out = GraphicOutput("Zombie apocalypse", 40, 40, Fighter::lenght, GraphicOutput::height);

	constexpr int zombie_start = Fighter::lenght - Fighter::size.x;

	std::vector<SDL_Texture *> textures;
	textures.push_back(out.LoadImg("img/dog.jpg"));
	textures.push_back(out.LoadImg("img/decelerator.jpg"));
	textures.push_back(out.LoadImg("img/archer.png"));
	textures.push_back(out.LoadImg("img/healer.png"));
	textures.push_back(out.LoadImg("img/cat.jpg"));
	textures.push_back(out.LoadImg("img/knight.png"));
	textures.push_back(out.LoadImg("img/bribegiver.png"));
	textures.push_back(out.LoadImg("img/cart.png"));
	textures.push_back(out.LoadImg("img/shoot.png"));
	textures.push_back(out.LoadImg("img/zombiearcher.png"));
	textures.push_back(out.LoadImg("img/zombiedoctor.jpg"));
	textures.push_back(out.LoadImg("img/icezombie.png"));
	textures.push_back(out.LoadImg("img/zombie.jpg"));
	textures.push_back(out.LoadImg("img/giant.png"));
	textures.push_back(out.LoadImg("img/runner.png"));
	textures.push_back(out.LoadImg("img/zombiebird.png"));
	textures.push_back(out.LoadImg("img/zombiebribegiver.png"));
	textures.push_back(out.LoadImg("img/zombieshoot.png"));
	textures.push_back(out.LoadImg("img/castle.jpg"));
	textures.push_back(out.LoadImg("img/hero.png"));

	std::vector<Fighter *> fighters;
	fighters.push_back(new SwordFighter(textures[0], 0, 10, true, 100, 10, 1, 0, false));
	fighters.push_back(new Decelerator(textures[1], 0, 2, true, 100, 20, SpeedState(SpeedState::Enum::Slow, 50), false));
	fighters.push_back(new Archer(textures[2], 0, 1, true, 100, 10, 150, false, Arrow(textures[8], 0, 5, true)));
	fighters.push_back(new Healer(textures[3], 0, 1, true, 100, 50, 40, 80, false));
	fighters.push_back(new SwordFighter(textures[4], 0, 1, true, 200, 50, 4, 50, false));
	fighters.push_back(new SwordFighter(textures[5], 0, 1, true, 2000, 20, 1, 0, false));
	fighters.push_back(new Reverser(textures[6], 0, 1, true, 100, 100, 100, false));
	fighters.push_back(new Cart(textures[7], 0, 10, true, 500, 200));

	fighters.push_back(new Archer(textures[9], zombie_start, 1, false, 100, 20, 150, false, Arrow(textures[17], 0, 10, false)));
	fighters.push_back(new Healer(textures[10], zombie_start, 1, false, 100, 50, 40, 80, false));
	fighters.push_back(new Decelerator(textures[11], zombie_start, 1, false, 150, 20, SpeedState(SpeedState::Enum::Slow, 100), false));
	fighters.push_back(new SwordFighter(textures[12], zombie_start, 2, false, 100, 10, 1, 0, false));
	fighters.push_back(new SwordFighter(textures[13], zombie_start, 1, false, 500, 350, 60, 20, false));
	fighters.push_back(new Runner(textures[14], zombie_start, 15, 100, 100, false));
	fighters.push_back(new SwordFighter(textures[15], zombie_start, 2, false, 50, 10, 1, 0, true));
	fighters.push_back(new Reverser(textures[16], zombie_start, 1, false, 50, 100, 100, false));

	Fighter::playground.AddFighter(new Gate(textures[18], 1000, 0, true));
	Fighter::playground.AddFighter(new Player(textures[19], 0, 5, 1000, 20, 1, 0, Arrow(textures[8], 0, 10, true), 20, 200));

	auto account = BankAccount(10000);
	auto shop = MercenaryStore(fighters[0]->Clone(), 500, fighters[1]->Clone(), 500, fighters[2]->Clone(), 500, fighters[3]->Clone(), 1500, fighters[4]->Clone(), 2000, fighters[5]->Clone(), 3000, fighters[6]->Clone(), 2000, fighters[7]->Clone(), 2000);
	auto spawner = ZombieSpawner(fighters, level, progress.GetLoops());
	auto counter = KillCounter(spawner.TotalZombies());

	while (!SDL_QuitRequested())
	{
		out.Show(counter, account, shop, Fighter::playground);
		if (counter.YouWin())
		{
			SDL_ShowSimpleMessageBox(0, "Game finished", "You have won!", 0);
			break;
		}
		if (Fighter::playground.Defeat())
		{
			SDL_ShowSimpleMessageBox(0, "Game over", "You have lost!", 0);
			break;
		}
		if (!progress.End())
		{
			Fighter::playground.AddFighters(spawner.AllNew(progress));
		}
		int newkilled = Fighter::playground.Clean();
		counter.Increment(newkilled);
		account.AddMoney(1 + newkilled * 100);

		Fighter::playground.Actions();
		if (auto bought = shop.Purchase(account, SDL_Point{0, GraphicOutput::alliesPos + 30}))
		{
			Fighter::playground.AddFighter(bought);
		}
		progress.Next();
	}

	for (auto f : fighters)
	{
		delete f;
	}
	for (auto texture : textures)
	{
		SDL_DestroyTexture(texture);
	}
}

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	Main();

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	return 0;
}