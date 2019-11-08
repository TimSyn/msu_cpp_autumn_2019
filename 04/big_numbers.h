#pragma once

size_t len(char *str);

size_t count_dig_am(int a);

bool copy_from_to(char *src, char* dst);

char sub_2_dig_symb(char a, char b, bool& was_carry);

char sum_2_dig_symb(char a, char b, bool& was_carry);

class BigInt                            //123 in mem will be like [3,2,1,sign,byte(0),byte(0),...]
{
    char *my_number;
    size_t mem_size;
   
public:                                
 
    bool isNeg() const { return my_number[mem_size - 1] == '-'; }

    void setSign(char sign) { my_number[mem_size - 1] = sign; }
   
    size_t realAmOfDig() const { return len(my_number) + 1; }
    
    void setMyNumber(char *new_number, size_t size);
 
    void incMemForNumb(size_t add_bytes = 1);

    bool fillNumbInMem(int a);

    friend BigInt sum2BigInt(const BigInt& a, const BigInt& b);

    friend BigInt sub2BigInt(const BigInt& min, const BigInt& sub);

    friend BigInt operator+(const BigInt& a, const BigInt& b);
    
    friend BigInt operator-(const BigInt& a, const BigInt& b);

    friend BigInt operator-(const BigInt& a);

    BigInt& operator=(const BigInt& b);
    
    friend bool operator>(const BigInt& a, const BigInt& b);

    friend bool operator<(const BigInt& a, const BigInt& b);

    friend bool operator>=(const BigInt& a, const BigInt& b);

    friend bool operator<=(const BigInt& a, const BigInt& b);

    friend bool operator==(const BigInt& a, const BigInt& b);

    friend bool operator!=(const BigInt& a, const BigInt& b);

    friend std::ostream& operator<<(std::ostream &os, const BigInt& bi);

    friend void printBigInt(const BigInt& bi);

    BigInt(int a = 0, size_t size = 11);
   
    BigInt(const BigInt& bi);

    ~BigInt() { delete [] my_number; } 
};
