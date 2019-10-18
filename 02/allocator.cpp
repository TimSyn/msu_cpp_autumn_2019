#include <iostream>
#include <stdlib.h>

#define MEMORY_SIZE 1000

using namespace std;

class LinearAllocator
{
    char *buffer;
    char *esp;
    size_t buffSize;
    size_t allocated_last_time;

public:
    LinearAllocator(size_t maxSize)
    {
        buffSize = maxSize;
        buffer = (char*) malloc(sizeof(char) * maxSize);
        esp = buffer;
        allocated_last_time = 0;
    }

    size_t AllUsedMemory() { return esp - buffer; }
    size_t WasAllocated() { return allocated_last_time; }
    int IsOnTheFirstByte() { return buffer == esp; }
    char* alloc(size_t size)
    {
        if (size == 0) return nullptr;
        char *mem_pointer = esp; 
        if ((size_t)(esp + size - buffer) > buffSize)
            return nullptr;
        else
        {
            esp += size;
            allocated_last_time = size;
            return mem_pointer; 
        }   
    }

    void reset()
    {
        esp = buffer;
        
    }

    ~LinearAllocator()
    {
        delete buffer;
        cout << "Freed Mem\n";
    }
};

size_t make_size_t(char *str_num)
{
    size_t sum = 0;
    
    while (*str_num)
    {
        sum *= 10;
        sum += *str_num - '0';
        str_num += 1;
    }
    return sum;
}

int main(int argc, char **argv)
{
    LinearAllocator linAlloc(make_size_t(argv[1]));
    
    for (int i = 2; i < argc; i++)
    {
        if (argv[i][0] == 'a')
        {
            if (linAlloc.alloc(make_size_t(argv[i] + 1)) != nullptr)
                cout << "Alloc: " << linAlloc.WasAllocated() << " Mem used: " << linAlloc.AllUsedMemory() << endl;
            else
                cout << "Not alloc "<< "Mem used: " << linAlloc.AllUsedMemory() << endl;
        }
        else if (argv[i][0] == 'r' )
        {
            linAlloc.reset();
            cout << "Reset: " << linAlloc.IsOnTheFirstByte() << " Memory used: " << linAlloc.AllUsedMemory()<< endl;
        }   
    }
    return 0;
}
