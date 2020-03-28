#include"task9.h"
#include<sstream>
Task9::Task9(){}
Task9::~Task9(){}
vector<int> Task9::occur(string s, char c)
{
    vector<int> indices;

    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == c)
            indices.push_back(i);
    }
    return indices;
}
string Task9::occur_minus(string s) //x-a=x-b, a-x=b-x, -x=cx-d,
{
    vector<int> m;
    vector<int> e = occur(s,'=');
    string s2 = "+";
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == '-' && i != 0 && i != e[0] + 1)
            m.push_back(i);
    }
    if(m.size() == 1)
        s.insert(m[0], s2);

    else if(m.size() == 2)
    {
        s.insert(m[0], s2);
        s.insert(m[1] + 1, s2);
    }
    return s;
}
void Task9::parsestring(string s)
{
  //  vector<string> f;
    int a,b,c,d;
    vector<int> mod = occur(s, '|');
    //cout << mod[1] << endl;
    s.erase(0,1);
    s.erase(mod[0] - 1, 1);
    s.erase(mod[1] -2, 1);
    s.erase(s.length() - 1, 1);
    s = occur_minus(s);
    vector<int> plus = occur(s,'+');
    vector<int> eq = occur(s, '=');
    if(plus.size() == 1 && plus[0] < eq[0]) // ax+b=cx, bl+ax=c, d =0
    {
            if(s[plus[0] - 1] == 'x' || s[plus[0] + 1] == 'x') //x+b=cx, b+x=cx
            {
                a = 1;
            }

            else if(s[plus[0] - 2] == '-') //-x+b=cx
                a = -1;

            else // ax+b=cx
            {
                if(s[plus[0] - 1] == 'x')
                    a = stoi(s.substr(0,plus[0] - 1));
                else
                    a = stoi(s.substr(plus[0] + 1, eq[0] - plus[0] -2));
                //b = stoi(s.substr(plus[0] + 1, eq[0] - plus[0] - 1));
            }

            if(s[plus[0] - 1] != 'x')
                b = stoi(s.substr(0, plus[0]));
            else
                b = stoi(s.substr(plus[0] + 1, eq[0] - plus[0] - 1));

            if(s[eq[0] + 1] == 'x')
                c = 1;
            else if(s[eq[0] + 1] == '-')
                c = -1;
            else
                c = stoi(s.substr(eq[0] + 1, s.length() - eq[0] - 2));
            d = 0;

    }

    else if(plus.size() == 1 && plus[0] > eq[0]) // ax=cx+d, ax=d+cx, b =0
    {
        {
            if(s[eq[0] + 1] == 'x' || s[plus[0] + 1] == 'x') //ax=x+d , ax= d+x
            {
                c = 1;
            }

            else if(s[plus[0] - 2] == '-' || s.substr(plus[0] + 1, 2) == "-x") //ax=-x+d, ax= d+-x
                c = -1;

            else // ax=cx+d, ax=d+cx
            {
                if(s[plus[0] - 1] == 'x')
                {
                  //  cout << true << endl;
                    c = stoi(s.substr(eq[0] + 1,plus[0] - eq[0] - 2));
                }
                else
                    c = stoi(s.substr(plus[0] + 1, s.length() - plus[0] - 2));
                    //cout << c;

            }
            if(s[plus[0] - 1] == 'x')
                d = stoi(s.substr(plus[0] + 1, s.length() - plus[0] - 1));
            else
                d = stoi(s.substr(eq[0] + 1, plus[0] - eq[0] - 1));


            if(s[0] == 'x')
                a = 1;
            else if(s[0] == '-')
                a = -1;
            else
                a = stoi(s.substr(0, eq[0] - 1));
            b = 0;


        }
    }

    else if(plus.size() == 0) // ax=cx
    {

        if(eq[0] - 1 == 0) //x=(+,-)x
        {
            //cout << "true1" << endl;
            a = 1;
            if(s[eq[0] + 1] == 'x')
                c = 1;
            else if(s[eq[0] + 1] == '-')
                c = -1;
            else
                c = stoi(s.substr(eq[0] + 1, s.length() - eq[0] - 1));

        }

        else if(eq[0] - 2 == '-') // -x=(+,-)x
        {
            //cout << "true2" << endl;
            a = -1;
            if(s[eq[0] + 1] == 'x')
                c = 1;
            else if(s[eq[0] + 1] == '-')
                c = -1;
            else
                c = stoi(s.substr(eq[0] + 1, s.length() - eq[0] - 1));

        }

        else if(s[eq[0] + 1] == 'x') // ax=x
        {
            //cout << "true3" << endl;
            c = 1;

            if(s[eq[0] - 1] == 'x')
                a = 1;
            else if(s[eq[0] - 2] == '-')
                a = -1;
            else
                a = stoi(s.substr(0, eq[0] - 1));
        }

        else if(s[eq[0] + 1] == '-' && s[eq[0] + 2] == 'x') // ax=-x
        {
            //cout << "true4" << endl;
            c = -1;

            if(s[eq[0] - 1] == 0)
                a = 1;
            else if(s[eq[0] - 2] == '-')
                a = -1;
            else
            {
                a = stoi(s.substr(0, eq[0] - 1));
                //cout << a << endl;
            }
        }
        else
        {
            //cout << "true5" << endl;
            a = stoi(s.substr(0, eq[0] - 1));
            //cout << a << endl;
            c = stoi(s.substr(eq[0] + 1, s.length() - eq[0] - 2));
            //cout << c << endl;
        }

        b = 0;
        d = 0;
    }

    else if(plus.size() == 2) //ax+b=cx+d
    {
        //cout << true << " ";
        if(s[plus[0] - 1] == 'x') //x+b=cx+d
        {
            if(plus[0] - 1 == 0)
                a = 1;
            else if(s[plus[0] - 2] == '-')
                a = -1;
            else
                a = stoi(s.substr(0, plus[0] - 1));

            if(s[s.length() - 1] == 'x') // b + ax = d + cx
            {
                if (s.substr(s.length() - 2, 2) == "-x")
                    c = -1;
                else if(s[plus[1] + 1] == 'x'){
                    //scout << true << endl;
                    c = 1;
                }
                else
                {
                    c = stoi(s.substr(plus[1] + 1, s.length() - plus[1] - 2));
                }

                d = stoi(s.substr(eq[0] + 1, plus[1] - eq[0] - 1));

            }
            else
            {

                if(s[eq[0] + 1] == 'x') //x+b=x+d
                    c = 1;
                else if(s[eq[0] + 1] == '-' && s[eq[0] + 2] == 'x') // x+b=-x+d
                    c = -1;
                else  //x+b = cx+d
                    c = stoi(s.substr(eq[0] + 1, plus[1] - eq[0] - 1));

                d = stoi(s.substr(plus[1] + 1, s.length() - plus[1] - 1));
            }

            b = stoi(s.substr(plus[0] + 1, eq[0] - plus[0] - 1));
            //d = stoi(s.substr(plus[1] + 1, s.length() - plus[1] - 1));

        }

        else if(s[plus[0] - 2] == '-')
        {
            a = -1;
            if(s[s.length() - 1] == 'x') // b + ax = d + cx
            {
                if (s.substr(s.length() - 2, 2) == "-x")
                    c = -1;
                else if(s[plus[1] + 1] == 'x'){
                    //scout << true << endl;
                    c = 1;
                }
                else
                {
                    c = stoi(s.substr(plus[1] + 1, s.length() - plus[1] - 2));
                }

                d = stoi(s.substr(eq[0] + 1, plus[1] - eq[0] - 1));

            }
            else
            {
                if(s[eq[0] + 1] == 'x') //-x+b=x+d
                    c = 1;
                else if(s[eq[0] + 1] == '-' && s[eq[0] + 2] == 'x') // -x+b=-x+d
                    c = -1;
                else  //-x+b = cx+d
                    c = stoi(s.substr(eq[0] + 1, plus[1] - eq[0] - 1));


                d = stoi(s.substr(plus[1] + 1, s.length() - plus[1] - 1));
            }
             b = stoi(s.substr(plus[0] + 1, eq[0] - plus[0] - 1));

        }

        else if(s[eq[0] + 1] == 'x')
        {
             c = 1;
            if(s[eq[0] - 1] == 'x') // b+ax
            {
                //cout << "trueal" << endl;
                b = stoi(s.substr(0, plus[0]));
                if(s.substr(plus[0] + 1, 2) == "-x")
                {
                    //cout << true << endl;
                    a = -1;
                }
                else if(s.substr(plus[0] + 1, 1) == "x")
                {
                    //cout << "true1" << endl;
                    a = 1;
                }
                else
                    a = stoi(s.substr(plus[0] + 1, eq[0] - plus[0] - 2));
            }

            else
            {
                if(plus[0] - 1 == 0) //x+b=x+d
                    a = 1;
                else if(s[plus[0] - 2] == '-') // -x+b=x+d
                    a = -1;
                else  //ax+b = x+d
                    a = stoi(s.substr(0, plus[0] - 1));

                b = stoi(s.substr(plus[0] + 1, eq[0] - plus[0] - 1));
            }


            d = stoi(s.substr(plus[1] + 1, s.length() - plus[1] - 1));
        }

        else if(s.substr(eq[0] + 1, 2) == "-x")
        {
             c = -1;
            if(s[eq[0] - 1] == 'x') // b+ax
            {
                //cout << "trueal" << endl;
                b = stoi(s.substr(0, plus[0]));
                if(s.substr(plus[0] + 1, 2) == "-x")
                {
                    //cout << true << endl;
                    a = -1;
                }
                else if(s.substr(plus[0] + 1, 1) == "x")
                {
                    //cout << "true1" << endl;
                    a = 1;
                }
                else
                    a = stoi(s.substr(plus[0] + 1, eq[0] - plus[0] - 2));
            }
            else
            {

                if(plus[0] - 1 == 0) //x+b=-x+d
                    a = 1;
                else if(s[plus[0] - 2] == '-') // -x+b=-x+d
                    a = -1;
                else  //ax+b = -x+d
                    a = stoi(s.substr(0, plus[0] - 1));

                b = stoi(s.substr(plus[0] + 1, eq[0] - plus[0] - 1));
            }

            d = stoi(s.substr(plus[1] + 1, s.length() - plus[1] - 1));

        }

        else if(s[eq[0] - 1] == 'x') // b+ax
        {
            //cout << "trueal" << endl;
            b = stoi(s.substr(0, plus[0]));
            if(s.substr(plus[0] + 1, 2) == "-x")
            {
                //cout << true << endl;
                a = -1;
            }
            else if(s.substr(plus[0] + 1, 1) == "x")
            {
                //cout << "true1" << endl;
                a = 1;
            }
            else
                a = stoi(s.substr(plus[0] + 1, eq[0] - plus[0] - 2));

            if(s[s.length() - 1] == 'x') // b + ax = d + cx
            {
                if (s.substr(s.length() - 2, 2) == "-x")
                    c = -1;
                else if(s[plus[1] + 1] == 'x'){
                    //scout << true << endl;
                    c = 1;
                }
                else
                {
                    c = stoi(s.substr(plus[1] + 1, s.length() - plus[1] - 2));
                }

                d = stoi(s.substr(eq[0] + 1, plus[1] - eq[0] - 1));

            }

            else // b+ax=cx+d
            {
                if (s.substr(eq[0] + 1, 2) == "-x")
                    c = -1;
                else if(s[eq[0] + 1] == 'x')
                {
                    //cout << "treaw" << endl;
                    c = 1;
                }
                else
                {
                    c = stoi(s.substr(eq[0] + 1, plus[1] - eq[0] - 2));
                }

                d = stoi(s.substr(plus[1] + 1, s.length() - plus[1] - 1));
            }


        }

    }
     variables.push_back(a);
     variables.push_back(b);
     variables.push_back(c);
     variables.push_back(d);
  //   cout << a << " "<< b << " " << c << " " << d <<  endl;
}
string Task9::solve(float a, float b, float c, float d)
{
        float x;
        string ans;
        if(a==c && b==d)
        {
            ans = "Infinite Solutions";
        }
        else if(a==c)
        {
            ans = "Wrong Equation: No Solution";
        }
        else
        {
            if(d==b)
             x=0;
            else
             x = (d-b)/(a-c);
             ans = to_string(x);
        }
        return ans;
}
void Task9::getoutput(string s)
{
  parsestring(s);
  string s1 = solve(variables[0],variables[1],variables[2],variables[3]);
  string s2 = solve(-variables[0],-variables[1],variables[2],variables[3]);
//  cout<<s1<<" "<<s2<<endl;
  float x1;
  float x2;
  stringstream a(s1);
  stringstream b(s2);
  float c;
  float d;
  string check1 = "Infinite Solutions";
  string check2 = "Wrong Equation: No Solution";
    if((s1.compare(check1) != 0 && s1.compare(check2) != 0) && (s2.compare(check1) != 0 &&    s2.compare(check2) != 0))
   {
     //cout<<"hi";
    stringstream a(s1);
    stringstream b(s2);
    a>>x1;
    b>>x2;
   //cout<<x1<<" "<<x2<<endl;
  //  if((variables[0]*x1+variables[1]>0 && variables[2]*x1+variables[3]>0) || (variables[0]*x1+variables[1]<0 && variables[2]*x1+variables[3]<0))
   if(x1>x2)
   {
    c=x2;
    d=x1;
  }
  else
  {
    c=x1;
    d=x2;
  }
  bool cval;
  bool dval;
   if(abs(variables[0]*c+variables[1])==variables[2]*c+variables[3])
    cval=true;
   else
    cval=false;
  if(abs(variables[0]*d+variables[1])==variables[2]*d+variables[3])
     dval=true;
  else
     dval=false;
  //  else if((variables[0]*x1+variables[1]>0 && variables[2]*x1+variables[3]<0))
  //  if((-variables[0]*x2-variables[1]>0 && variables[2]*x2+variables[3]>0) || (-variables[0]*x2-variables[1]<0 && variables[2]*x2+variables[3]<0))
//   if(abs(variables[0]*x2+variables[1])=variables[2]*x2+variables[3])
//    d=x2;


    if(cval == true && dval==true)
          cout<<"x="<<setprecision(4)<<c<<";"<<"x="<<setprecision(4)<<d<<endl;
    else if(cval == false && dval==true)
          cout<<"x="<<setprecision(4)<<d<<";invalid:x="<<setprecision(4)<<c<<endl;
    else if(cval == true && dval==false)
          cout<<"x="<<setprecision(4)<<c<<";"<<"invalid:x="<<setprecision(4)<<d<<endl;
    else if(cval == false && dval==false)
          cout<<"invalid:x="<<setprecision(4)<<c<<";"<<"invalid:x="<<setprecision(4)<<d<<endl;
  }
 else
  {
    cout<<s1<<";"<<s2<<endl;
  }
}

int main()
{
 	string s = "\"|3x-2|=3x+1\"";
 	Task9 t;
 	t.getoutput(s);
	return 0;
}
