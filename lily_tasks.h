#pragma once
#define Tasks_LEN 16
typedef int(*Tasks_def)();
typedef int(*TasksArg_def)(void*);

extern Tasks_def tasks_[];

void addTask_(Tasks_def task);
void endTask_(Tasks_def task);
char hadTask_(Tasks_def task);
void endTaskAt_(char index);
void run_tasks();

void addTaskArg(TasksArg_def f, void* arg);

int delegate_task_for_args();
