#pragma once
#include <iostream>
using namespace std;

class Field
{
public:
	string name;
	void* ref;
	char type;
	Field(string name, void* ref, char type = 'f')// just create a field with a ref
	{
		this->name = name;
		this->ref = ref;
		this->type = type;
		this->IsBuiltIn = true;
	}
	Field(string name, string value, char t = 'f');// create a field from a string applay new memory 
	
	~Field()
	{
		if (!IsBuiltIn)
		{
			delete ref;
		}
	}
	string toString();// using os to print value, value only!
	void assign(string s);
	friend ostream& operator<<(ostream& os, Field&);
	friend istream& operator>>(istream& os, Field&);
	//ostream& operator<<(ostream& os)
	//{
	//	os << name << "=" << toString() << endl;
	//	return os;
	//}
	bool operator == (const string& b) const
	{
		return (name == b);
	}
private:
	bool IsBuiltIn;
};

typedef int (*Cmd_fun)(int n, string s[]);
class Cmd {
public:
	string name;
	string doc;
	Cmd_fun ref;
	Cmd(string s, Cmd_fun f, string d="none")
	{
		name = s;
		ref = f;
		doc = d;
	}
	bool operator == (const string& b) const
	{
		return (name == b);
	}
};

class Fun
{
public:
	string name;
	void* ref;
	char type;
	char argn;
	Fun(string name, void* ref , char argn = 0 ,char type='f')// just create a field with a ref
	{
		this->name = name;
		this->ref = ref;
		this->type = type;
		this->argn = argn;
	}
	bool operator == (const string& b) const
	{
		return (name == b);
	}
};


extern void(*lily_out)(string sth);

int lily_in(string *s1);

template<typename T>
void li_out(T);

int public_a_cmd(string name, Cmd_fun fun);
int public_a_field(string name, void* ref, char type = 'f');
int public_a_fun(string name, void* ref, char argn = 0, char type = 'f');

int shell_do_cmd(string& s);

int shell_do_field(string& s);

int shell_do_fun(string& s);

int shell_do_notFound(string& s);

int cmd_whos(int n, string arg[]);
int cmd_help(int n, string arg[]);
