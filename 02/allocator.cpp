#include <iostream>
#include <cstdlib>

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
        if (maxSize == 0)        
        {
            buffer = nullptr;
            esp = nullptr;
            buffSize = 0;
        }
        else
        {  
            buffSize = maxSize;
            buffer = (char*) malloc(sizeof(char) * maxSize);
//          for (size_t i = 0; i < maxSize; i++)
//                buffer[i] = 0;
            esp = buffer;
            allocated_last_time = 0;
        }
    }

    size_t AllUsedMemory() { return esp - buffer; }

    size_t WasAllocated() { return allocated_last_time; }

    int IsOnTheFirstByte() { return buffer == esp; }

    char* alloc(size_t size)
    {
        if ((size == 0) or (buffer == nullptr)) return nullptr;
        char *mem_pointer = esp; 
        if ((size_t)(esp + size - buffer) > buffSize)
            return nullptr;
        else
        {
            esp += size;
            allocated_last_time = size;
//            for (size_t i = 0; i < size; i++)
//                mem_pointer[i] = i % 10 + '0';
            return mem_pointer; 
        }   
    }

    void reset()
    {
        esp = buffer;
//        for (size_t i =0; i< buffSize; i++) buffer[i] = 0;
    }

    ~LinearAllocator() { free(buffer); }
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
    if (argc == 1) 
        return 1;
    LinearAllocator linAlloc(strtoul(argv[1], NULL, 10));
    
    for (int i = 2; i < argc; i++)
    {
       if (argv[i][0] == 'a')
        {
            if (linAlloc.alloc(strtoul(argv[i] + 1, nullptr, 10)) != nullptr)
                cout << "Alloc: " << linAlloc.WasAllocated() << " Mem used: " << linAlloc.AllUsedMemory() << endl;
            else
                cout << "Not alloc " << "Mem used: " << linAlloc.AllUsedMemory() << endl;
        }
        else if (argv[i][0] == 'r' )
        {
            linAlloc.reset();
            cout << "Reset: " << linAlloc.IsOnTheFirstByte() << " Memory used: " << linAlloc.AllUsedMemory()<< endl;
        }   
    }
    return 0;
}
