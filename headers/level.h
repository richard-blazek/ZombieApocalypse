#pragma once

#include <vector>

class Level
{
public:
	class Rule
	{
	private:
		int divisor;
		int modus;
		size_t index;

	public:
		Rule(int divisor = 1, int modus = 0, size_t index = 0)
			: divisor(divisor), modus(modus), index(index) {}
		bool IsTrue(int value) const
		{
			return value % divisor == modus;
		}
		size_t GetIndex() const
		{
			return index;
		}
		int TrueCount(int loops) const
		{
			return (loops - modus) / divisor + 1;
		}
		friend std::istream &operator>>(std::istream &in, Rule &rule)
		{
			in >> rule.divisor >> rule.modus >> rule.index;
			return in;
		}
	};

private:
	std::vector<Rule> rules;
	int loops, sleeptime;

public:
	Progress GetProgressObject() const
	{
		return Progress(loops, sleeptime);
	}
	std::vector<size_t> AllNew(int value) const
	{
		std::vector<size_t> result;
		for (auto rule : rules)
		{
			if (rule.IsTrue(value))
			{
				result.push_back(rule.GetIndex());
			}
		}
		return result;
	}
	int TotalZombies(int loops) const
	{
		int zombies = 0;
		for (auto rule : rules)
		{
			zombies += rule.TrueCount(loops);
		}
		return zombies;
	}
	Level(std::istream &&in)
	{
		in >> loops >> sleeptime;
		while (in)
		{
			rules.resize(rules.size() + 1);
			in >> rules.back();
		}
		rules.pop_back();
	}
};