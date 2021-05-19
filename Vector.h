#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <iostream>
#include <stdexcept>

using namespace std;
template <typename T>
class Vector
{
private:
    size_t vectorSize;
    size_t vectorCapacity;
    T* container;

public:
    Vector()
    {
        vectorSize = 0;
        vectorCapacity = 1;
        container = new T[vectorCapacity];
    }
    Vector(const Vector& other)
    {
        vectorSize = 0;
        vectorCapacity = 1;
        container = new T[vectorCapacity];
        for(size_t i(0); i < other.size(); ++i)
            push_back(other[i]);
    }
    Vector& operator = (const Vector& other)
    {
        vectorSize = 0;
        vectorCapacity = 1;
        container = new T[vectorCapacity];
        for (size_t i(0); i < other.size(); ++i)
            push_back(other[i]);
        return *this;
    }

    size_t size()const;
    size_t capacity();
    void push_back(const T& element);
    void pop_back();
    void insert(size_t position,const T& element);
    void erase(size_t position);
    void clear();
    void resize();
    const T& at(size_t position);
    T& operator[](size_t idx);

    ~Vector()
    {
        clear();
    }
};

template <typename T>
size_t Vector<T>::size() const
{
    return vectorSize;
}

template <typename T>
size_t Vector<T>::capacity()
{
    return vectorCapacity;
}

template<typename T>
void Vector<T>::resize()
{
    T* temp=new T[vectorCapacity*2];
    temp=container;
    delete container;
    vectorCapacity*=2;
    container=temp;
}

template <typename T>
void Vector<T>::push_back(const T& element)
{
    if(vectorSize==vectorCapacity)
        resize();
    container[vectorSize] = element;
    ++vectorSize;
}

template <typename T>
void Vector<T>::pop_back()
{
    if(vectorSize==0)
        throw range_error("Trying pop_back() on empty vector");
    --vectorSize;
}

template <typename T>
void Vector<T>::insert(size_t position, const T& element)
{
    if((position>vectorSize)||(position<0))
        throw range_error("Trying insert() in non valid position ");
    if(position==vectorSize)
        push_back(element);
    else
    {
        if(vectorSize==vectorCapacity)
            resize();
        for(size_t i(vectorSize);i>position;i--)
            container[i]=container[i-1];
        container[position]=element;
        ++vectorSize;
    }
}

template <typename T>
void Vector<T>::erase(size_t position)
{
    if((position>vectorSize)||(position<0))
        throw range_error("Trying erase() in non valid position ");
    if(vectorSize == 0)
        throw range_error("Trying erase() on empty vector");
    if(position == vectorSize)
        pop_back();
    else
    {
        for(size_t i(position);i<vectorSize-1;i++)
            container[i]=container[i+1];
        --vectorSize;
    }
}

template <typename T>
void Vector<T>::clear()
{
    delete container;
    vectorSize = 0;
    container = new T[vectorCapacity];
}

template <typename T>
const T& Vector<T>::at(size_t position)
{
    if((position>=vectorSize)||(position<0))
        throw range_error("Trying at() in non valid position ");
    return container[position];
}

template <typename T>
T& Vector<T>::operator [](size_t idx)
{
    if((idx>=vectorSize)||(idx<0))
        throw range_error("Trying [] in non valid position ");
    return container[idx];
}

#endif // VECTOR_H_INCLUDED
