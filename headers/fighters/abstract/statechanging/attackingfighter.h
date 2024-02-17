#pragma once

class AttackingFighter : public virtual Fighter
{
protected:
	int damage;
	void Attack(DestructibleFighter *enemy)
	{
		enemy->BeAttacked(*this, damage);
	}

public:
	AttackingFighter(int damage) : damage(damage) {}
};