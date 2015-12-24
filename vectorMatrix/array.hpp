#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>
#include <iostream>

//#define _e_ 0.01 //floating point authorized error for null check

template<size_t size, typename T> class Array
{
public:

    //Constructeurs//

    Array();
    Array(const Array<size,T> &other);
    virtual ~Array();

    //Opérateurs//

    Array& operator=(const Array<size,T> &other);
    T& operator[](unsigned int i);
    const T& operator[](unsigned int i) const;
    bool operator==(const Array<size,T> &other) const;

    //Accesseurs//

    size_t Size() const;

    //Opérations//

    void exchangeWith(Array<size,T> &other);

    //Itérateurs//

    class iterator //credits for iterator example goes to https://gist.github.com/jeetsukumaran/307264
    {
    public:
        typedef iterator self_type;
        typedef T   value_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef int difference_type;

        iterator() {}
        iterator(value_type* ptr) : ptr_(ptr) {}

        inline self_type operator=(self_type other) { ptr_ = other.ptr_; return *this; }
        inline self_type operator++() { self_type i = *this; ptr_++; return i; }
        inline self_type operator++(int unusued) { ptr_++; return *this; }
        inline self_type operator--() { self_type i = *this; ptr_--; return i; }
        inline self_type operator--(int unusued) { ptr_--; return *this; }
        inline value_type& operator*() { return *ptr_; }
        inline value_type* operator->() { return ptr_; }
        inline bool operator==(const self_type& other) { return ptr_ == other.ptr_; }
        inline bool operator!=(const self_type& other) { return ptr_ != other.ptr_; }
    private:
        value_type* ptr_;
    };

    class const_iterator //credits for iterator example goes to https://gist.github.com/jeetsukumaran/307264
    {
    public:
        typedef const_iterator self_type;
        typedef T   value_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef int difference_type;

        const_iterator() {}
        const_iterator(const value_type *ptr) : ptr_(ptr) {}

        inline self_type operator=(self_type other) { ptr_ = other.ptr_; return *this; }
        inline self_type operator++() { self_type i = *this; ptr_++; return i; }
        inline self_type operator++(int unusued) { ptr_++; return *this; }
        inline self_type operator--() { self_type i = *this; ptr_--; return i; }
        inline self_type operator--(int unusued) { ptr_--; return *this; }
        inline const value_type& operator*() { return *ptr_; }
        inline const value_type* operator->() { return ptr_; }
        inline bool operator==(const self_type& other) const { return ptr_ == other.ptr_; }
        inline bool operator!=(const self_type& other) const { return ptr_ != other.ptr_; }
    private:
        const value_type* ptr_;
    };

    iterator begin();
    iterator end();
    iterator last(); ///< returns the pointer of the last value from the array

    const_iterator begin() const;
    const_iterator end() const;
    const_iterator last() const;

protected:

    T m_tab[size];
};

template<size_t size, typename T>
std::ostream& operator<< (std::ostream &stream, const Array<size,T> &array);

//------------------------------------------------
//------------------------------------------------

//====================================================================================================================================
//Constructeurs//

template<size_t size, typename T>
Array<size,T>::Array()
{}

template<size_t size, typename T>
Array<size,T>::Array(const Array<size,T> &other)
{
    typename Array<size,T>::iterator itThis;
    typename Array<size,T>::const_iterator citOther;
    for(itThis=begin(), citOther=other.begin(); itThis!=end() && citOther!=other.end(); ++itThis, ++citOther)
    {
        *itThis=*citOther;
    }
}

//====================================================================================================================================

template<size_t size, typename T>
Array<size,T>::~Array()
{}

//====================================================================================================================================
//Opérateurs//

template<size_t size, typename T>
Array<size,T>& Array<size,T>::operator=(const Array<size, T> &other)
{
    typename Array<size,T>::iterator itThis;
    typename Array<size,T>::const_iterator citOther;
    for(itThis=begin(), citOther=other.begin(); itThis!=end() && citOther!=other.end(); ++itThis, ++citOther)
    {
        *itThis=*citOther;
    }
    return *this;
}

//====================================================================================================================================

template<size_t size, typename T>
T& Array<size,T>::operator[](unsigned int i)
{
    if(i>=size || i<0)
    {
         throw std::out_of_range("argument out of bounds");
    }
    return m_tab[i];
}

template<size_t size, typename T>
const T& Array<size,T>::operator[](unsigned int i) const
{
    if(i>=size || i<0)
    {
         throw std::out_of_range("argument out of bounds");
    }
    return m_tab[i];
}

//====================================================================================================================================

template<size_t size, typename T>
bool Array<size,T>::operator==(const Array<size,T> &other) const
{
    bool ret=true;
    typename Array<size,T>::const_iterator citThis, citOther;
    for(citThis=begin(), citOther=other.begin(); ret && citThis!=end() && citOther!=other.end(); ++citThis, ++citOther)
    {
        if(*citThis!=*citOther)
            ret=false;
    }
    return ret;
}

//====================================================================================================================================
//Accesseurs//

template<size_t size, typename T>
size_t Array<size, T>::Size() const
{
    return size;
}

//====================================================================================================================================
//Opérations//

template<size_t size, typename T>
void Array<size,T>::exchangeWith(Array<size,T> &other)
{
    Array<size,T> copy;
    copy=other;
    for(unsigned int i=0;i<size;i++)
    {
        other[i]=m_tab[i];
        m_tab[i]=copy[i];
    }
}

//====================================================================================================================================
//Itérateurs//

template<size_t size, typename T>
typename Array<size,T>::iterator Array<size,T>::begin()
{
    return iterator(m_tab);
}

template<size_t size, typename T>
typename Array<size,T>::iterator Array<size,T>::end()
{
    return iterator(m_tab + size);
}

template<size_t size, typename T>
typename Array<size,T>::iterator Array<size,T>::last()
{
    return iterator(m_tab + (size-1));
}


//====================================================================================================================================

template<size_t size, typename T>
typename Array<size,T>::const_iterator Array<size,T>::begin() const
{
    return const_iterator(m_tab);
}

template<size_t size, typename T>
typename Array<size,T>::const_iterator Array<size,T>::end() const
{
    return const_iterator(m_tab + size);
}

template<size_t size, typename T>
typename Array<size,T>::const_iterator Array<size,T>::last() const
{
    return const_iterator(m_tab + (size-1));
}

//====================================================================================================================================
//Autres//

template<size_t size, typename T>
std::ostream& operator << (std::ostream &stream, const Array<size,T> &array)
{
    stream << '[';
    typename Array<size,T>::const_iterator cit;
    for(cit=array.begin(); cit!=array.last(); ++cit)
    {
        stream << *cit << ", ";
    }
    stream << *cit << ']';
    return stream;
}


#endif // ARRAY_H
