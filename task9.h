#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include"base.h"
class Task9:public Base{
 public:
   Task9();
  ~Task9();
 string occur_minus(string s);
 vector<int>occur(string s, char c);
 vector<int>variables;
 string solve(float a, float b, float c, float d);
 void parsestring(string s);
 void getoutput(string s);
};
