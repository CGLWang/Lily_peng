#include"lily.h"
#include <iostream>
#include <list>
#include"basic.h"
#include<algorithm>
#include<sstream>
using namespace std;
static stringstream os;
#define sendout lily_out(os.str());os.clear();os.str("")
#define error(s) latest_error = s;lily_out(latest_error)
vector<Field*> li_fields;
vector<Cmd*> li_cmds;
vector<Fun*> li_funs;
void(*lily_out)(string sth);
string latest_error = "";
typedef int(*shell_do)(string&);
vector<string>* input_stream = new vector<string>;
vector<string>& ins = *input_stream;



template<class InputIterator>
InputIterator find_name(InputIterator first, InputIterator last, string name)
{
    for (; first != last; first++) if ((*(*first))==name) break;
    return first;
}


int lily_in(string *si)
{
    string &sl = *si;
    replace(sl.begin(), sl.end(), '=', ' ');
    split(sl,' ',input_stream);
    if (ins.empty())
    {
        return 0;
    }
    static shell_do shell_dos[4] = { shell_do_cmd, shell_do_field, shell_do_fun, shell_do_notFound };
    int i = 0;
    int code;
    for (; i < 4; i++)
    {
        code = shell_dos[i](sl);
        if (code != 0)break;
    }
    if (code < 0)
    {
        os << "error(" << code << ")\n";
    }
    return 0;
}


template<typename T>
inline void li_out(T val)
{
    os.clear();
    os.str("");

    os << val;
    string s = os.str();
    lily_out(s);
    
}


int public_a_cmd(string name, Cmd_fun fun)
{
    Cmd* c = new Cmd(name, fun);
    if (c == nullptr)
    {
        lily_out("public failed, no memory");
        return -1;
    }
    li_cmds.push_back(c);
    return 0;
}

int public_a_field(string name, void* ref, char type)
{
    Field* f = new Field(name, ref,type);
    if (f == nullptr)
    {
        lily_out("public failed, no memory");
        return -1;
    }
    li_fields.push_back(f);
    return 0;
}

int public_a_fun(string name, void* ref, char argn, char type)
{
    Fun* f = new Fun(name, ref,argn, type);
    if (f == nullptr)
    {
        lily_out("public failed, no memory");
        return -1;
    }
    li_funs.push_back(f);
    return 0;
}

int shell_do_cmd(string& s)
{
    int code;
    vector<Cmd*>::iterator iter = find_name(li_cmds.begin(), li_cmds.end(), ins[0]);
    if (iter == li_cmds.end())
        return 0;
    Cmd& c = *(*iter);

    code = c.ref(ins.size(), ins.data());
    if (code < 0)
        return code;
    return 1;
}

int shell_do_field(string& s)
{
    vector<Field*>::iterator iter = find_name(li_fields.begin(), li_fields.end(), ins[0]);
    if (iter == li_fields.end())
        return 0;
    Field& f = *(*iter);
    if (ins.size() <= 1)
    {
        li_out(f);
        lily_out("\n");
        return 1;
    }
    f.assign(ins[1]);
    return 1;
}
int shell_do_fun(string& s)
{
    typedef void(*f0)();
    typedef void(*f1)(float);
    typedef void(*f2)(float, float);
    typedef void(*f3)(float, float,float);
    typedef void(*f4)(float, float, float, float);
    typedef void(*fi1)(int);
    typedef void(*fi2)(int, int);
    typedef void(*fi3)(int, int, int);
    typedef void(*fi4)(int, int, int, int);

    vector<Fun*>::iterator iter = find_name(li_funs.begin(), li_funs.end(), ins[0]);
    if (iter == li_funs.end())
        return 0;
    Fun& f = *(*iter);
    if (f.argn == 0)
    {
        ((f0)(f.ref))();
        return 1;
    }
    int i;
    int n = ins.size() - 1;
    if (f.type == 'f')
    {
        static float fs[4];
        fs[0] = 0.0f;
        for (i = 0; i < f.argn; i++)
        {
            if (i < n)
            {
                os.clear();
                os << ins[i+1];
                os >> fs[i];
                
            }
            else if (i > 0)
            {
                fs[i] = fs[i - 1];
            }
        }

        switch (f.argn)
        {
        case 1:
            ((f1)(f.ref))(fs[0]);
            break;
        case 2:
            ((f2)(f.ref))(fs[0],fs[1]);
            break;
        case 3:
            ((f3)(f.ref))(fs[0], fs[1],fs[2]);
            break;
        case 4:
            ((f4)(f.ref))(fs[0], fs[1], fs[2], fs[3]);
            break;
        default:
            error("error dd");
            break;
        }
    }
    else
    {
		int ds[4];
		ds[0] = 0;
		for (i = 0; i < f.argn; i++)
		{
			if (i < n)
			{
                os.clear();
                os << ins[i + 1];
				os >> ds[i];
			}
			else if (i > 0)
			{
				ds[i] = ds[i - 1];
			}
		}
        switch (f.argn)
        {
        case 1:
            ((fi1)(f.ref))(ds[0]);
            break;
        case 2:
            ((fi2)(f.ref))(ds[0], ds[1]);
            break;
        case 3:
            ((fi3)(f.ref))(ds[0], ds[1], ds[2]);
            break;
        case 4:
            ((fi4)(f.ref))(ds[0], ds[1], ds[2], ds[3]);
            break;
        default:
            error("error ff");
            break;
        }
    }
    os.str("");
    return 1;
}
int shell_do_notFound(string& s)
{
    lily_out("not found\"");
    lily_out(s);
    lily_out("\"\n");
    return 1;
}

string Field::toString()
{
    //static stringstream os;
    os.clear();
    os.str("");
    switch (type)
    {
    case 'f':
        os << *((float*)ref);
        break;
    case 'i':
        os << *((int*)ref);
        break;
    case 'c':
        os << *((char*)ref);
        break;
    case 'b':
        os << *((bool*)ref);
        break;
    default:
        os << "error";
        break;
    }
    return os.str();
}
Field::Field(string name, string value, char t)// create a field from a string applay new memory 
{
    this->name = name;
    type = t;
    os.clear();
    os << value;
    switch (t)
    {
    case 'f':
        ref = new float;
        os >> *((float*)ref);
        break;
    case 'i':
        ref = new int;
        os >> *((int*)ref);
        break;
    case 'c':
        ref = new char;
        os >> *((char*)ref);
        break;
    case 'b':
        ref = new bool;
        os >> *((bool*)ref);
        break;
    default:
        //"error";
        break;
    }
    this->IsBuiltIn = false;
}
void Field::assign(string value)
{
    os.clear();
    os.str("");
    os << value;
    switch (type)
    {
    case 'f':
        //ref = new float;
        os >> *((float*)ref);
        break;
    case 'd':
        //ref = new int;
        os >> *((int*)ref);
        break;
    case 'c':
        //ref = new char;
        os >> *((char*)ref);
        break;
    case 'b':
        //ref = new bool;
        os >> *((bool*)ref);
        break;
    default:
        error("error 0x11");
        break;
    }
}

ostream& operator<<(ostream& os, Field& fed)
{
    os << fed.name << "=";// << fed.toString();
    switch (fed.type)
    {
    case 'f':
        os << *((float*)fed.ref);
        break;
    case 'd':
        os << *((int*)fed.ref);
        break;
    case 'c':
        os << *((char*)fed.ref);
        break;
    case 'b':
        os << *((bool*)fed.ref);
        break;
    default:
        error("error");
    }
    return os;
}

istream& operator>>(istream& os, Field& fed)
{
    switch (fed.type)
    {
    case 'f':
        //ref = new float;
        os >> *((float*)fed.ref);
        break;
    case 'd':
        //ref = new int;
        os >> *((int*)fed.ref);
        break;
    case 'c':
        //ref = new char;
        os >> *((char*)fed.ref);
        break;
    case 'b':
        //ref = new bool;
        os >> *((bool*)fed.ref);
        break;
    default:
        error("error");
        break;
    }
    return os;
}

int cmd_help(int n, string arg[])
{
    vector<Cmd*>::iterator itr = li_cmds.begin();
    for (; itr != li_cmds.end(); itr++)
    {
        os << (*itr)->name <<":"<< (*itr)->doc << endl;
        sendout;
    }
    vector<Fun*>::iterator itr2 = li_funs.begin();
    for (; itr2 != li_funs.end(); itr2++)
    {
        os << (*itr2)->name << ":" << (int)((*itr2)->argn)<<":"<<(*itr2)->type << endl;
        sendout;
    }
    return 0;
}

int cmd_whos(int n, string arg[])
{
    if (n == 1)
    {
        vector<Field*>::iterator itr = li_fields.begin();
        for (; itr != li_fields.end(); itr++)
        {
            os << *(*itr)<<" "<<(*itr)->type << endl;
            sendout;
        }
        return 0;
    }
    int i;
    n--;
    for (i = 0; i < n; i++)
    {
        vector<Field*>::iterator itr = find_name(li_fields.begin(), li_fields.end(), ins[0]);
        if (itr == li_fields.end())
            return -1;
        os << *(*itr) << " " << (*itr)->type << endl;
        sendout;
    }
    return 0;
}

