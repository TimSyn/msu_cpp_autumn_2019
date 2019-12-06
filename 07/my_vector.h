#include <iostream>
#include <stdlib.h>

template <class T>
class Allocator
{
    /*using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using size_type = std::size_t;

    size_type size;
    pointer mem_pointer;*/

public:
    T* allocate(size_t n) { return (T*) malloc(n * sizeof(T)); }
    void deallocate(T* p, size_t n) { if (p && (n > 0)) free(p); }
    void destroy(T* p) { if (p) p->~T(); } 
    void construct(T* p, const T& tmp = T()) { new(p) T(tmp); }
    void construct(T* p, T&& t) { new(p) T(std::move(t)); }
};

template <class T>//check limits
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
    T* ptr_;

public:
    explicit Iterator(T* ptr) : ptr_(ptr) {}

    bool operator==(const Iterator<T> &other) const 
        { return ptr_ == other.ptr_; }
    bool operator!=(const Iterator<T> &other) const
        { return !(*this == other); }
    bool operator>(const Iterator<T> &other) const
        { return ptr_ > other.ptr_; }
    bool operator<(const Iterator<T> &other) const
        { return ptr_ < other.ptr_; }
    bool operator<=(const Iterator<T> &other) const
        { return ptr_ <= other.ptr_; }
    bool operator>=(const Iterator<T> &other) const
        { return ptr_ >= other.ptr_; }

    T* address() const { return ptr_; }
    T& operator*() const { return *ptr_; }

    Iterator<T>& operator++() { ptr_++; return *this; }
    Iterator<T> operator++(int) { Iterator<T> tmp = *this; ptr_++; return tmp; }

    Iterator<T>& operator--() { ptr_--; return *this; }
    Iterator<T> operator--(int) { Iterator<T> tmp = *this; ptr_--; return tmp; }

    Iterator<T> operator+(const Iterator<T> &other) const
        { return Iterator<T>(ptr_ + other.ptr_); }
    Iterator<T> operator-(const Iterator<T> &other) const
        { return Iterator<T>(ptr_ - other.ptr_); }

    T& operator[](size_t n) const { return *(ptr_ + n); }
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator = Iterator<T>;

private:
    Alloc alloc_;
    T* memory = nullptr;
    size_t size, capacity;
    
public:
    Vector() : size(0), capacity(0) 
        {}
    ~Vector();

    iterator begin() { return iterator(memory); }
    iterator rbegin() { return iterator(memory + size); }

    iterator end() { return iterator(memory + size); }
    iterator rend() {return iterator(memory); }

    size_t vec_size() { return size; }
    size_t vec_capacity() { return capacity; }

    void push_back(const T& elem);
    void push_back(T&& elem);
    T* pop_back();
    bool empty() { return size == 0; }
    void clear();
    void resize(const size_t new_size, const T& value = T());
    void reserve(size_t new_cap);

    const T& operator[](size_t index) const;
    T& operator[](size_t index);
};

template<class T, class Alloc>
T& Vector<T, Alloc>::operator[](size_t index)
{
    if (index < size)
        return *(memory + index);
    else
        throw std::runtime_error("err");
}

template<class T, class Alloc>
const T& Vector<T, Alloc>::operator[](size_t index) const
{
    if (index < size)
        return *(memory + index);
    else
        throw std::runtime_error("err");
}

template<class T, class Alloc>
void Vector<T, Alloc>::reserve(size_t new_cap)
{
    if (new_cap > capacity)
    {
        size_t i = 2;
        while (new_cap > capacity * i)
            i++;

        capacity *= i;
        T* new_memory = alloc_.allocate(capacity);

        i = 0;
        for (iterator it = begin(); it != end(); it++)
        {
            alloc_.construct(new_memory + i, *it);
            i++;
        }

        alloc_.deallocate(memory, size);
        memory = new_memory;
    }
}

template<class T, class Alloc>
void Vector<T, Alloc>::resize(const size_t new_size, const T& value)
{
    if (new_size > size)
    {
        if (new_size > capacity)
        {
            capacity *= 2;
            T* new_memory = alloc_.allocate(capacity);
            
            size_t i = 0;
            for (iterator it = begin(); it != end(); it++)
            {
                alloc_.construct(new_memory + i, std::move(*it));
                i++;
            }
            //for (size_t i = size; i < new_size; i++)
              //  alloc_.construct(*(new_memory + i), value);
            
            alloc_.deallocate(memory, size);
            memory = new_memory;
        }
        
        for (size_t i = size; i < new_size; i++)
            alloc_.construct(memory + i, value);    
    }
    else
    {
        for (size_t i = new_size; i < size; i++)
            alloc_.destroy(memory + i);
    }
    
    size = new_size;    
}

template<class T, class Alloc>
void Vector<T, Alloc>::clear()
{
    for (iterator it = begin(); it != end(); it++)
        alloc_.destroy(it.address());

    size = 0;
}

template<class T, class Alloc>
Vector<T, Alloc>::~Vector()
{
    if (memory)
    {
        for (iterator it = begin(); it != end(); it++)
            alloc_.destroy(it.address());

        alloc_.deallocate(memory, size);
    }
}

template<class T, class Alloc>
T* Vector<T, Alloc>::pop_back()
{
    if (size)
    {
        size--;
        T* tmp = new T(std::move(*(memory + size)));
        return tmp;
    }      
    else
        return nullptr;
}

template<class T, class Alloc>
void Vector<T, Alloc>::push_back(T&& elem)
{
    if (!(size < capacity) && memory)
    {
        capacity *= 2;
        T* new_memory = alloc_.allocate(capacity);
            
        size_t i = 0;
        for (iterator it = begin(); it != end(); it++)
        {
            alloc_.construct(new_memory + i, std::move(*it));
            i++;
                //*(new_memory + i) = *it;
                //alloc_.destroy(memory + i);
        }

        alloc_.deallocate(memory, size);
        memory = new_memory;
    }

    if (!memory)
    {
        capacity = 2;
        memory = alloc_.allocate(capacity);
    }

    alloc_.construct(memory + size, std::move(elem));
    //*(memory + size) = elem;
    size++;
    
}

template<class T, class Alloc>
void Vector<T, Alloc>::push_back(const T& elem)
{
    if (!(size < capacity) && memory)
    {
        capacity *= 2;
        T* new_memory = alloc_.allocate(capacity);
        
        size_t i = 0;
        for (iterator it = begin(); it != end(); it++)
        {
            alloc_.construct(new_memory + i, *it);
            //*(new_memory + i) = *it;
            alloc_.destroy(memory + i);
            i++;
        }

        alloc_.deallocate(memory, size);
        memory = new_memory;
    }

    if (!memory)
    {
        capacity = 2;
        memory = alloc_.allocate(capacity);
    }

    alloc_.construct(memory + size, elem);
    //*(memory + size) = elem;
    size++;
}
