
#define Tasks_LEN 12
typedef int(*Tasks_def)(void*);

class Task
{
public:
	Task(Tasks_def);
	Task(Tasks_def, void*);
	void reset(Tasks_def);
	void reset(Tasks_def, void*);
private:
	Tasks_def startAddress;
	void* para;
};


Tasks_def tasks_[Tasks_LEN];
unsigned int hasTask_, rear,front;
void addTask_(Tasks_def task)
{
	tasks_[rear++] = task;
	if (rear >= Tasks_LEN)
		rear = 0;
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
		//delay
	}
}

