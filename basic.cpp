//#include <iostream>
//#include<list>
////#include<queue>
//#include<vector>
#include"basic.h"
//using namespace std;

// note: delete after using
vector<string>* split(const string& s, const char& delim, vector<string>* tokens )
{
	if (tokens == nullptr)
	{
		tokens = new vector<string>;
	}
	else
	{
		tokens->clear();
	}
	size_t lastPos = s.find_first_not_of(delim, 0);
	size_t pos = s.find(delim, lastPos);
	while (lastPos != string::npos) {
		tokens->emplace_back(s.substr(lastPos, pos - lastPos));
		lastPos = s.find_first_not_of(delim, pos);
		pos = s.find(delim, lastPos);
	}
	return tokens;
}
