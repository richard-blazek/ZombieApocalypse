#pragma once

class SpeedState
{
public:
	enum class Enum
	{
		Ok = 0,
		Slow = 1,
		Sleeping = 2
	};

private:
	Enum state = Enum::Ok;
	int time = 0;

public:
	constexpr SpeedState() = default;
	constexpr SpeedState(Enum state, int time) : state(state), time(time) {}
	bool operator<(SpeedState second)
	{
		return state < second.state || (state == second.state && time < second.time);
	}
	bool operator>(SpeedState second)
	{
		return state > second.state || (state == second.state && time > second.time);
	}
	void Sleep(int newtime)
	{
		*this = SpeedState(Enum::Sleeping, newtime);
	}
	void Slow(int newtime)
	{
		*this = SpeedState(Enum::Slow, newtime);
	}
	Enum GetState()
	{
		return state;
	}
	void Continue()
	{
		if (time != 0)
		{
			--time;
		}
		if (time == 0)
		{
			state = Enum::Ok;
		}
	}
};