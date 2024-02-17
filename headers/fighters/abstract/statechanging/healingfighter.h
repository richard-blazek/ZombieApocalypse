#pragma once

class HealingFighter : public virtual Fighter
{
protected:
	int power;
	void Heal(Fighter *ally)
	{
		ally->BeHealed(*this, power);
	}

public:
	HealingFighter(int power) : power(power) {}
};