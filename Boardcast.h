#pragma once
#include"lily_tasks.h"
#include<vector>
using namespace std;
class Boardcast
{
public:
	vector< Tasks_def> audio;
	void do_boardcast()
	{
		int i = 0;
		for (; i < audio.size(); i++)
			addTask_(audio[i]);
	}
};

class Timer
{
public:
	Tasks_def todo;
	unsigned int count;
	Timer(Tasks_def td, unsigned int re)
	{
		todo = td;
		reload = re;
		count = reload;
		open = true;
	}
	void tick()
	{
		if (!open)return;
		count--;
		if (count == 0)
		{
			count = reload;
			addTask_(todo);
		}
	}
	void set(bool open=true)
	{
		this->open = open;
	}
	void set(unsigned int cycle)
	{
		this->reload = cycle;
	}
private:
	
	unsigned int reload;
	bool open;
};

int addTimer(Tasks_def, unsigned int);
int removeTimer(Tasks_def);
int lily_tick();
int set_delay(Tasks_def todo, unsigned int delay);
int set_cycle(Tasks_def todo, unsigned int cycle);
int set_open(Tasks_def todo, bool open);