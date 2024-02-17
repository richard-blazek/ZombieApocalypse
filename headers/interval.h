#pragma once

class Interval
{
private:
	int interval, left;

public:
	void Continue()
	{
		if (left > 0)
		{
			--left;
		}
	}
	void Refresh()
	{
		left = interval;
	}
	bool IsElapsed()
	{
		return left == 0;
	}
	bool WasRefreshed()
	{
		return left == interval;
	}
	Interval(int interval) : interval(interval), left(interval - 1) {}
};