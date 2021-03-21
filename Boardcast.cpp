#include "Boardcast.h"
//#include<algorithm>
vector<Timer*> timers;
unsigned long int tick_count=0;
int addTimer(Tasks_def todo, unsigned int re)
{
	Timer* t = new Timer(todo, re);
	if (t == nullptr)
		return -1;
	timers.push_back(t);
	return 0;
}
int removeTimer(Tasks_def todo)
{
	int n = timers.size();
	int i;
	for (i = n - 1; i >= 0; i--)
	{
		if (timers[i]->todo == todo)
			break;
	}
	if (i < 0)return -1;
	timers[n - 1] = timers[i];
	timers.pop_back();
	return 0;
}

int lily_tick()
{
	tick_count++;
	int n = timers.size();
	int i;
	for (i = n - 1; i >= 0; i--)
	{
		timers[i]->tick();
	}
	return 0;
}

int set_delay(Tasks_def todo, unsigned int delay)
{
	int n = timers.size();
	int i;
	for (i = n - 1; i >= 0; i--)
	{
		if (timers[i]->todo == todo)
		{
			timers[i]->count = delay;
			return 0;
		}
			
	}
	if (i < 0)return -1;
}
int set_cycle(Tasks_def todo, unsigned int cycle)
{
	int n = timers.size();
	int i;
	for (i = n - 1; i >= 0; i--)
	{
		if (timers[i]->todo == todo)
		{
			timers[i]->set(cycle);
			return 0;
		}

	}
	if (i < 0)return -1;
}
int set_open(Tasks_def todo, bool open)
{
	int n = timers.size();
	int i;
	for (i = n - 1; i >= 0; i--)
	{
		if (timers[i]->todo == todo)
		{
			timers[i]->set(open);
			return 0;
		}

	}
	if (i < 0)return -1;
}