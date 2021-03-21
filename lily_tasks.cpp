#include<iostream>
#include<list>
#include<queue>
#include"lily_tasks.h"
#include<Windows.h>
using namespace std;

Tasks_def tasks_[Tasks_LEN];
unsigned int rear,front;

extern CRITICAL_SECTION cs;
void addTask_(Tasks_def task)
{
	EnterCriticalSection(&cs);
	tasks_[rear++] = task;
	if (rear >= Tasks_LEN)
		rear = 0;
	if (rear == front)
	{
		cout << "error tasks poll full";
	}
	LeaveCriticalSection(&cs);
}

void endTask_(Tasks_def task)//trash
{
	int i;
	for (i = front; i != rear;)
	{
		if (tasks_[i] == task)break;
		i++;
		if (i == Tasks_LEN)
			i = 0;
	}
	if (i == rear)return;
	int j = i, next;
	while (j != rear)
	{
		next = j + 1;
		if (next == Tasks_LEN)
			next = 0;
		tasks_[j] = tasks_[next];
		j = next;
	}
}
void endTaskAt_(char index)
{
	int j = index, next;
	while (j != rear)
	{
		next = j + 1;
		if (next == Tasks_LEN)
			next = 0;
		tasks_[j] = tasks_[next];
		j = next;
	}
}
//whether has a task in pool
//return the index of a task, if any
char hadTask_(Tasks_def task)
{
	char b = 0;
	char i;

	for (i = front; i != rear; )
	{
		if (tasks_[i] == task)
		{
			b = i;
			break;
		}

		if (++i == Tasks_LEN)
			i = 0;
	}
	return b;
}

void run_tasks()
{
	int i;
	while (1)
	{
		i = rear;
		while (front != i)
		{

			if (tasks_[front]() == 1)addTask_(tasks_[front]);
			if (++front == Tasks_LEN)
				front = 0;
		}
	}
}

queue<TasksArg_def> fs_arg;
queue<void*> args;
void addTaskArg(TasksArg_def f, void* arg)
{
	fs_arg.push(f);
	args.push(arg);
	if (!hadTask_(delegate_task_for_args))
		addTask_(delegate_task_for_args);
}

int delegate_task_for_args()
{
	static int code;
	TasksArg_def f = fs_arg.front();
	void* a = args.front();

	code = f(a);// 0->end, 1-> again
	if (code <= 0)
	{
		// if return 0, pop
		fs_arg.pop();
		args.pop();
	}
	if (fs_arg.empty())
		return 0;
	return 1;
}

