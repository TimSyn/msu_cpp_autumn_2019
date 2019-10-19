#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#define ERR_MSG_SIZE 30

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
    const char* err_msg;

public:
    Exc() { err_msg = nullptr; }
    virtual const char* GetErr() const = 0;
};

class ExcDivideByZero : public Exc
{
public:
    ExcDivideByZero() { err_msg = "Was attempt to divide by zero\n"; }
    const char* GetErr() const
    {
        return err_msg;
    }
};

class ExcWrongLex : public Exc
{
    int exc_lex_name;
    char tmp_msg[ERR_MSG_SIZE];

public:
    ExcWrongLex(int name)
    {
        exc_lex_name = name;
        if (exc_lex_name != 0)
        {
            sprintf(tmp_msg, "%s %c %s","Didn't expected to get \'",(char)GetExcLex(),"\'\n");
            err_msg = tmp_msg;
        }
        else
            err_msg = "Expression was not complete\n";
    }

    int GetExcLex() const { return exc_lex_name; }

    const char* GetErr() const
    {
        return err_msg;
    }
};

class Parser
{
    char *curr_lex;

    void SetCurrLex() 
    {
        while (*curr_lex == ' ')
            curr_lex++;
    }
    
    int GetCurrLex()
    {
        return *curr_lex;
    }
    
    void NextLex()
    {
        if (*curr_lex == 0)
        {
            throw ExcWrongLex(GetCurrLex());
        }
        curr_lex = curr_lex + 1;
        while (*curr_lex == ' ')
            curr_lex++;
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
        curr_lex = new char[length(str)];
        strcpy(curr_lex, str);
    }
    
    double Calc()
    {
        SetCurrLex();
        return CalcExpr();
    }
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
        cout << err.GetErr();
        return 1;
    }
    cout << res << endl;
    return 0;
}
