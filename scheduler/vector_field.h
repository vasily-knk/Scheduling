#pragma once

template <typename T>
class vector_field
{
public:
    vector_field(vector<T> &vec)
        : vector_(vec)
    {

    }
public:
    typedef typename vector<T>::iterator iterator;
    typedef typename vector<T>::const_iterator const_iterator;
    typedef typename vector<T>::reference reference;
    typedef typename vector<T>::const_reference const_reference;
    typedef typename vector<T>::size_type size_type;

public:
    iterator       begin ()       {return vector_.begin();}
    const_iterator begin () const {return vector_.begin();}
    iterator       end   ()       {return vector_.end();}
    const_iterator end   () const {return vector_.end();}
          
    iterator       rbegin ()       {return vector_.rbegin();}
    const_iterator rbegin () const {return vector_.rbegin();}
    iterator       rend   ()       {return vector_.rend();}
    const_iterator rend   () const {return vector_.rend();}

    reference       at (size_type n)       {return vector_.at(n);}
    const_reference at (size_type n) const {return vector_.at(n);}

    reference       operator[] (size_type n)       {return vector_.operator[](n);}
    const_reference operator[] (size_type n) const {return vector_.operator[](n);}

    reference       front ()       {return vector_.front();}
    const_reference front () const {return vector_.front();}
    reference       back  ()       {return vector_.back();}
    const_reference back  () const {return vector_.back();}

private:
    vector<T> vector_;
};


template <typename T>
class matrix_field
{
public:
    matrix_field(matrix<T> &vec)
        : matrix_(vec)
    {

    }
public:
    typedef typename matrix<T>::reference reference;
    typedef typename matrix<T>::const_reference const_reference;
    typedef typename matrix<T>::size_type size_type;

public:
    const_reference operator () (size_type i, size_type j) const {return matrix_.operator()(i, j);}
    reference       operator () (size_type i, size_type j)       {return matrix_.operator()(i, j);}
private:
    matrix<T> matrix_;
};