// Lily_peng.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <sstream>
#include<list>
#include<queue>
#include<stack>
#include<Windows.h>
#include<edpwin32.h>
#include<process.h>

#include"lily_tasks.h"
#include"lily.h"
#include"Boardcast.h"
#include"basic.h"
#include <conio.h>


using namespace std;
class Base
{
public:
    string name;
    void* ref;
    Base(string n, void* r=NULL)
    {
        name = n;
        ref = r;
    }
    friend ostream& operator<<(ostream&,const Base&);
    
};
CRITICAL_SECTION cs;
HANDLE sem;

DWORD WINAPI thread1(LPVOID para)
{
    cout << "tick starting...\n";
    while (1)
    {

        Sleep(10);
        if(!hadTask_(lily_tick))
            addTask_(lily_tick);
        else
        {
            cout << "x";
        }
        //cout << "_";
    }
    return 0;
}

DWORD WINAPI thread2(LPVOID para)
{
    cout << "tasks running...\n";
    run_tasks();
    return 0; 
}

void out_from_lily(string s)
{
    cout << s;
}

void f2_test(float a, float b, float c, float d )
{
    cout << "a=" << a << " b=" << b << " c=" << c << " d=" << d << endl;
}
void fi2_test(int a, int b, int c, int d)
{
    cout << "a=" << a << " b=" << b << " c=" << c << " d=" << d << endl;
}
int timer1()
{
    static int c=20,step=-1;
    c += step;
    if (c < 5||c>30)
    {
        step *= -1;
    }
    set_delay(timer1, c);
    cout << "-";
    return 0;
}
int main()
{
    lily_out = out_from_lily;
    InitializeCriticalSection(&cs);
    sem = CreateSemaphore(NULL, 0, 10, NULL);


    HANDLE h1 = CreateThread(NULL, 0, thread1, NULL, 0, 0);
    if (h1 == NULL)
    {
        cout << "error";
        exit(-1);
    }
    HANDLE h2 = CreateThread(NULL, 0, thread2, NULL, 0, 0);
    if (h2 == NULL)
    {
        cout << "error";
        exit(-1);
    }

    float kp = 0;
    int ki=0;
    bool kd=false;

    addTimer(timer1, 20);
    public_a_field("kp", &kp);
    public_a_field("ki", &ki,'d');
    public_a_field("kd", &kd,'b');
    
    public_a_cmd("help", cmd_help);
    public_a_cmd("whos", cmd_whos);
    public_a_cmd("exit", (Cmd_fun)exit);

    public_a_fun("abs", f2_test,4);
    public_a_fun("ab", fi2_test, 4, 'd');
    static int c = 0;
    char cv;
    static char new_one = 1;
    stringstream ss;
    static string s;
    while (1)
    {
        
        if (_kbhit())
        {
            if (new_one)
            {
                cout << ">>";
                new_one = 0;
            }
            cv = _getch();
            
            if (cv == '\b')
            {
                cout << "\b ";
                ss << "\b ";
                continue;
            }
                
            cout << cv;
            if (cv == '\r')
            {
                cv = '\n';
                cout << "\n";
                new_one = 1;
                s = ss.str();
                ss.clear();
                ss.str("");
                addTaskArg((TasksArg_def)lily_in, &s);
                continue;
            }
            ss << cv;
            //lily_in(cv);
        }
    }
    WaitForSingleObject(h1, INFINITE);
    //WaitForSingleObject(h2, INFINITE);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

ostream& operator<<(ostream& os,const Base& ba)
{
    os << ba.name;
    return os;
}

unsigned int lily_millis()
{
    unsigned int a = GetTickCount64();
    return a / 1000;
}

