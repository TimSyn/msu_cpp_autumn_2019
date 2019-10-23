#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

size_t length(const char* str)
{
    int i = 0;
    
    while (str[i])
        i++;
    return i;
}

class Exc
{
protected:
    string err_msg;

public:
    Exc() { err_msg = string(); }
    virtual string GetErr() const = 0;
};

class ExcDivideByZero : public Exc
{
public:
    ExcDivideByZero() { err_msg = string("Was attempt to divide by zero"); }
    string GetErr() const
    {
        return err_msg;
    }
};

class ExcWrongLex : public Exc
{
    int exc_lex_name;

public:
    ExcWrongLex(int name)
    {
        exc_lex_name = name;
        if (exc_lex_name != 0)
        {
            err_msg = string("Didn't expected to get \'");
            err_msg.append(1, (char)GetExcLex());
            err_msg.append("\'");
        }
        else
            err_msg = string("Expression was not complete");
    }

    int GetExcLex() const { return exc_lex_name; }

    string GetErr() const
    {
        return err_msg;
    }
};

class Parser
{
    int lex_index;
    //const char curr_lex;
    string my_str;

    void SetCurrLex() 
    {
        //curr_lex = my_str[lex_index];
        while (my_str[lex_index] == ' ')
            lex_index++;
    }
    
    const int GetCurrLex()
    {
        return my_str[lex_index];
    }
    
    void NextLex()
    {
        if (my_str[lex_index] == 0)
        {
            throw ExcWrongLex(GetCurrLex());
        }
        lex_index++;
        while (my_str[lex_index] == ' ')
            lex_index++;
    }
    
    int ExtractNumber()
    {
        int summ = 0;    
        
        while ((GetCurrLex() >= '0') && (GetCurrLex() <= '9'))
        {
            summ *= 10;
            summ += GetCurrLex() - '0';
            NextLex();
        }
        return summ;
    }

    double Factor()
    {
        if ((GetCurrLex() >= '0') && (GetCurrLex() <= '9')) 
            return ExtractNumber();
        if (GetCurrLex() == '-')
        {
            NextLex();
            return -Factor();
        }
        else
            throw ExcWrongLex(GetCurrLex());
    }

    double MoreFactor()
    {
        if (GetCurrLex() == '*')
        {
            NextLex();
            return Factor() * MoreFactor();
        }
        if (GetCurrLex() == '/')
        {
            NextLex();
            double num = Factor();
            if (num == 0)
                throw ExcDivideByZero();
            return 1 / num * MoreFactor();
        }
        return 1;
    }
    
    double MoreTerm()
    {
        if (GetCurrLex() == '+')
        {
            NextLex();
            return Term() + MoreTerm();
        }
        if (GetCurrLex() == '-')
        {
            NextLex();
            int tmp = -Term();
            return tmp + MoreTerm();
        }
        return 0;
    }

    double Term()
    {
        return Factor() * MoreFactor();
    }
    
    double CalcExpr()
    {
        return Term() + MoreTerm();
    }

public:
    Parser(const char *str)
    {
        my_str = string(str);
        lex_index = 0;
        //strcpy(my_str, str);
    }
    
    double Calc()
    {
        SetCurrLex();
        return CalcExpr();
    }

    //~Parser() { delete [] my_str; }
};

int main(int argc, char** argv)
{
    double res = 0;
    
    if (argc != 2)
    {
        cerr << "wrong input" << endl;
        return 1;
    }
    try
    {
         Parser pars(argv[1]);
         res = pars.Calc();
    }
    catch(const Exc &err)
    {
        cout << err.GetErr() <<endl;
        return 1;
    }
    cout << res << endl;
    return 0;
}
