#pragma once

class DestructibleFighter : public virtual Fighter
{
protected:
	bool flying;
	int health;
	const int maxhealth;
	DestructibleFighter(int health, bool flying) : flying(flying), health(health), maxhealth(health) {}

public:
	virtual void BeAttacked(Fighter &attacker, int damage) noexcept
	{
		if (auto d = dynamic_cast<DestructibleFighter *>(&attacker); !flying || !d || d->IsFlying())
		{
			health = (health <= damage) ? 0 : health - damage;
		}
	}
	virtual void BeHealed(Fighter &, int power) noexcept
	{
		health = (health + power >= maxhealth) ? maxhealth : health + power;
	}
	bool IsFlying() const noexcept
	{
		return flying;
	}
	virtual bool IsAlive() const noexcept override
	{
		return health != 0;
	}
	bool IsHealthy()
	{
		return health == maxhealth;
	}
	void DrawOn(SDL_Renderer *rend, SDL_Point dst_pos)
	{
		SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
		SDL_Rect health_rect{dst_pos.x, flying ? dst_pos.y + Fighter::size.y - 1 : dst_pos.y, Fighter::size.x * health / maxhealth, 1};
		SDL_RenderFillRect(rend, &health_rect);

		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
		SDL_Rect damage_rect{dst_pos.x + Fighter::size.x * health / maxhealth, flying ? dst_pos.y + Fighter::size.y - 1 : dst_pos.y, Fighter::size.x - Fighter::size.x * health / maxhealth, 1};
		SDL_RenderFillRect(rend, &damage_rect);
	}
};