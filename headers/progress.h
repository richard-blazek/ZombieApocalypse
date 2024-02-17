#pragma once

class Progress
{
private:
	int i=0;
	int loops, sleeptime;
public:
	Progress(int loops, int sleeptime):loops(loops), sleeptime(sleeptime){}
	int GetLoops()const noexcept
	{
		return loops;
	}
	void Next()noexcept
	{
		++i;
		SDL_Delay(sleeptime);
	}
	bool End()const noexcept
	{
		return i>=loops;
	}
	operator int()const noexcept
	{
		return i;
	}
};