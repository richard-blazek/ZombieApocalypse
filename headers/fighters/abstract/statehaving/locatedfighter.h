#pragma once

class LocatedFighter : virtual public Fighter
{
protected:
	int pos, speed;

public:
	LocatedFighter(int pos, int speed) : pos(pos), speed(speed) {}
	int GetPos() const noexcept
	{
		return pos;
	}
	bool GoLeft()
	{
		if (pos != 0)
		{
			pos = (pos <= speed) ? 0 : pos - speed;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool GoRight()
	{
		if (pos != Fighter::lenght - Fighter::size.x)
		{
			pos = (pos + speed >= Fighter::lenght - Fighter::size.x) ? Fighter::lenght - Fighter::size.x : pos + speed;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool GoForward() noexcept
	{
		return IsGood() ? GoRight() : GoLeft();
	}
	bool GoBackwards() noexcept
	{
		return IsGood() ? GoLeft() : GoRight();
	}
};