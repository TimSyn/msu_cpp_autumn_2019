#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Exc
{
public:
    virtual void PrintErrMsg() const = 0;
};

class ExcDivideByZero : public Exc
{
public:
    void PrintErrMsg() const
    {
        cout << "Was attempt to divide by zero"<<endl;
    }
};

class ExcStrEnd : public Exc
{
public:
    void PrintErrMsg() const
    {
        cout << "Expression was not completed"<<endl;
    }
};

class ExcWrongLex : public Exc
{
    int exc_lex_name;
    //int is_zero;
    //char *args;

public:
    ExcWrongLex(int name) { exc_lex_name = name; }

    int GetExcLex() const { return exc_lex_name; }
    void PrintErrMsg() const
    {
        cout << "Didn't expected to get \'"<< (char)GetExcLex() << "\'"<<endl;
    }
};

class Parser
{
    static char *curr_lex;

    static void SetCurrLex(char *ptr) 
    {
        curr_lex = ptr;
        while (*curr_lex == ' ')
            curr_lex++;
    }
    
    static int GetCurrLex()
    {
        //if (*curr_lex == 0)
          //  throw ExcStrEnd();
        return *curr_lex;
    }
    
    static void NextLex()
    {
        if (*curr_lex == 0)
        {
            throw ExcStrEnd();
        }
        curr_lex = curr_lex + 1;
        while (*curr_lex == ' ')
            curr_lex++;
    }
    
    static int ExtractNumber()
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

    static double Factor()
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

    static double MoreFactor()
    {
        if (GetCurrLex() == '*')
        {
            NextLex();
            return Factor() * MoreFactor();
        }
        if (GetCurrLex() == '/')
        {
            NextLex();
            int num = Factor();
            if (num == 0)
                throw ExcDivideByZero();
            return 1 / num * MoreFactor();
        }
        return 1;
    }
    
    static double MoreTerm()
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

    static double Term()
    {
        return Factor() * MoreFactor();
    }
    
    static double CalcExpr()
    {
        return Term() + MoreTerm();
    }

public:
    static double Calc(char *expr)
    {
        SetCurrLex(expr);
        return CalcExpr();
    }
};

char* Parser::curr_lex;

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
        res = Parser::Calc(argv[1]);
    }
    catch(const Exc &err)
    {
        err.PrintErrMsg();
        return 1;
    }
    cout << res << endl;
    return 0;
}
