#include <iostream>
#include <stdlib.h>
#include "big_numbers.h"

void printBigInt(const BigInt& bi)
{
    if (bi.isNeg())
        std::cout << '-';
    for (long i = bi.realAmOfDig() - 2; i >= 0; i--)
        std::cout << bi.my_number[i];    
}

size_t len(char *str)
{
    size_t counter = 0;
        
    if (str == nullptr)
        return counter;
    while (str[counter] && (str[counter] != '+') && (str[counter] != '-'))
        counter++;

    return counter;
}

size_t count_dig_am(int a)
{
    size_t counter = 0;

    while (a != 0)
    {
        counter++;
        a = a / 10;
    }

    return counter;
}

bool copy_from_to(char *src, char* dst)
{
    if ((src == nullptr) || (dst == nullptr))
        return false;

    size_t src_length = len(src);
    //std::cout << src << " copy_from_to "<< len(src)<< std::endl;
    for (size_t i = 0; i < src_length; i++)
        if ((src[i] != '+') && (src[i] != '-'))
            dst[i] = src[i];
    //std::cout << dst << " copy_from_to "<< len(src)<< std::endl;
        
    return true;    
}

std::ostream& operator<<(std::ostream &os, const BigInt& bi)
{
    if (bi.isNeg()) //&& (bi != 0))
        os << '-';
    for (long i = bi.realAmOfDig() - 2; i >= 0; i--)
        os << bi.my_number[i];    

    return os;
}

void BigInt::incMemForNumb(size_t add_bytes)
{
    char *my_number_new = new char[mem_size + add_bytes]();
    
    copy_from_to(my_number, my_number_new);

    if (isNeg())
        my_number_new[mem_size + add_bytes - 1] = '-';
    else
        my_number_new[mem_size + add_bytes - 1] = '+';

    delete [] my_number;
    my_number = my_number_new;
    mem_size += add_bytes;
}

bool BigInt::fillNumbInMem(int a)
{
    size_t dig_am = count_dig_am(a);

    if (a < 0)
        setSign('-');
    else
        setSign('+');

    if (a == 0)
        dig_am = 1;
    
    size_t i;   
    for (i = 0; i < dig_am; i++)
    {
        my_number[i] = abs(a % 10) + '0';
        a = a / 10;
    }

    i++;
    for (i = i; i < mem_size - 1; i++)
        my_number[i] = 0;
        
    return true;
}

BigInt::BigInt(int a, size_t size)
{
    mem_size = size;
    my_number = new char[mem_size]();
    fillNumbInMem(a);
}

BigInt::BigInt(const BigInt& bi)
{
    char* new_number_bi = new char[bi.mem_size]();

    copy_from_to(bi.my_number, new_number_bi);
    mem_size = bi.mem_size;
    my_number = new_number_bi;
    if (bi.isNeg())
        setSign('-');
    else
        setSign('+');
}

void BigInt::setMyNumber(char *new_number, size_t size)
{
    delete [] my_number;
    my_number = new_number;
    mem_size = size;
}

char sub_2_dig_symb(char a, char b, bool& was_carry)
{
    int res = (a - '0') - (b - '0') - int(was_carry);

    if (res < 0)
    {
        res += 10;
        was_carry = true;
    }
    else
        was_carry = false;
    return res + '0';
}

char sum_2_dig_symb(char a, char b, bool& was_carry)
{
    int res = (a - '0') + (b - '0') + int(was_carry);
    
    was_carry = (res >= 10);
    return res % 10 + '0';
}

bool operator<(const BigInt& a, const BigInt& b)
{
    return !(a > b) && (a != b);
}

bool operator<=(const BigInt& a, const BigInt& b)
{
    return (!(a > b) && (a != b)) || (a == b);
}

bool operator>=(const BigInt& a, const BigInt& b)
{
    return (a > b) || (a == b);
}

bool operator!=(const BigInt& a, const BigInt& b)
{
    return !(a == b);
}

bool operator==(const BigInt& a, const BigInt& b)
{
    if (a.isNeg() != b.isNeg())
        return false;
    
    if (a.realAmOfDig() > b.realAmOfDig())
        return false;

    if (a.realAmOfDig() < b.realAmOfDig())
        return false;
    
    bool equal = true;
    size_t number_size = a.realAmOfDig();

    for(long i = number_size - 2; i >= 0; i--)
        if (a.my_number[i] != b.my_number[i])
        {
            equal = false;
            break;
        }

    return equal;
}

BigInt& BigInt::operator=(const BigInt& b)
{
//    std::cout << b << " operator= "<< b.realAmOfDig() <<std::endl;
    char *new_number = new char[b.realAmOfDig()]();
    
    copy_from_to(b.my_number, new_number);
    delete [] my_number;
    my_number = new_number;

//    std::cout << new_number << " operator= "<<std::endl;
//    std::cout << my_number << " operator= "<<std::endl;
    
    mem_size = b.realAmOfDig();
    if (!b.isNeg())
        setSign('+');
    else
        setSign('-');

//    std::cout << (*this).my_number << " operator= " << std::endl;
    return *this;
}

BigInt operator-(const BigInt& a)
{
    BigInt bi = a;

    if (a.isNeg())
        bi.setSign('+');
    else
        bi.setSign('-');

    if (bi.my_number[bi.realAmOfDig() - 2] == '0') //for BigInt a == 0
        bi.setSign('+');

    return bi;
}

BigInt operator-(const BigInt& a, const BigInt& b)
{
    return a + (-b);
}

bool operator>(const BigInt& a, const BigInt& b)
{
    if (a.isNeg() != b.isNeg())
    {
        if (a.isNeg())
            return false;
        else
            return true;
    }

    if (a.realAmOfDig() > b.realAmOfDig())
    {
        if (a.isNeg()) 
            return false;
        else
            return true;
    }

    if (a.realAmOfDig() < b.realAmOfDig())
    {
        if (a.isNeg())
            return true;
        else
            return false;
    }

    bool more = true;
    size_t number_size = a.realAmOfDig() - 1;

    if (!a.isNeg())
    {
        for(long i = number_size - 1; i >= 0; i--)
            if ((a.my_number[i] < b.my_number[i]) && i)
            {
                more = false;
                break;
            }
            else if ((a.my_number[i] <= b.my_number[i]) && (i == 0))
                more = false;
    }
    else
    {
        for(long i = number_size - 1; i >= 0; i--)
            if (a.my_number[i] > b.my_number[i])
            {
                more = false;
                break;
            } 
            else if ((a.my_number[i] >= b.my_number[i]) && (i == 0))
                more = false;
    }
    return more;
}

BigInt sum2BigInt(const BigInt& a, const BigInt& b)
{
    bool was_carry = false;
    BigInt res(0);

    size_t shortest_len, longest_len;
    if (a.realAmOfDig() > b.realAmOfDig())
    {
        longest_len = a.realAmOfDig();
        shortest_len = b.realAmOfDig();
    }
    else
    {
        longest_len = b.realAmOfDig();
        shortest_len = a.realAmOfDig();
    }

    char *new_number = new char[longest_len]();    
    size_t i;

    for (i = 0; i < shortest_len - 1; i++) 
        new_number[i] = sum_2_dig_symb(a.my_number[i], b.my_number[i], was_carry);

    if (a.realAmOfDig() == longest_len)
        for (i = i; i < longest_len - 1; i++)
            new_number[i] = sum_2_dig_symb(a.my_number[i], '0', was_carry);
    else
        for (i = i; i < longest_len - 1; i++)
            new_number[i] = sum_2_dig_symb(b.my_number[i], '0', was_carry);

    if (was_carry)
    {
        longest_len += 1;
        char *new_number_tmp = new char[longest_len]();
        copy_from_to(new_number, new_number_tmp);
        delete [] new_number;
        new_number = new_number_tmp;
        new_number[longest_len - 2] = '1';
    }

    res.setMyNumber(new_number, longest_len);
    if (a.isNeg())
        res.setSign('-');
    else
        res.setSign('+');
    return res;
}

BigInt sub2BigInt(const BigInt& min, const BigInt& sub)
{
    bool was_carry = false;
    BigInt res(0);

    char *new_number = new char[min.realAmOfDig()]();    
    size_t i;
    
    for (i = 0; i < sub.realAmOfDig() - 1; i++) 
        new_number[i] = sub_2_dig_symb(min.my_number[i], sub.my_number[i], was_carry);

    for (i = i; i < min.realAmOfDig() - 1; i++)
        new_number[i] = sub_2_dig_symb(min.my_number[i], '0', was_carry);

    i = min.realAmOfDig() - 2;
    while ((new_number[i] == '0') && i)
    {
        new_number[i] = 0;
        i--;
    }

    res.setMyNumber(new_number, min.realAmOfDig());
    if (min.isNeg() && (res.my_number[res.realAmOfDig() - 2] != '0'))
        res.setSign('-');
    else
        res.setSign('+');
    return res;
}

BigInt operator+(const BigInt& a, const BigInt& b)
{
    if (a.isNeg() == b.isNeg())
        return sum2BigInt(a, b);
    else
    {
        if (a.isNeg())
        {
            if (a.realAmOfDig() > b.realAmOfDig())
                return -sub2BigInt(-a, b);
            else if (b.realAmOfDig() > a.realAmOfDig())
                return sub2BigInt(b, -a);
            else if (-a > b)
                return -sub2BigInt(-a, b);
            else 
                return sub2BigInt(b, -a);
        }        
        else
            if (a.realAmOfDig() > b.realAmOfDig())
                return sub2BigInt(a, -b);
            else if (b.realAmOfDig() > a.realAmOfDig())
                return -sub2BigInt(-b, a);
            else if (a > -b)
                return sub2BigInt(a, -b);
            else 
                return -sub2BigInt(-b, a);
    }
}
