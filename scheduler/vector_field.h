#pragma once

template <typename T>
class vector_field
{
public:
    vector_field(vector<T> &vec)
        : pvector_(&vec)
    {

    }
public:
    typedef typename vector<T>::iterator iterator;
    typedef typename vector<T>::const_iterator const_iterator;
    typedef typename vector<T>::reference reference;
    typedef typename vector<T>::const_reference const_reference;
    typedef typename vector<T>::size_type size_type;

public:
    iterator       begin ()       {return pvector_->begin();}
    const_iterator begin () const {return pvector_->begin();}
    iterator       end   ()       {return pvector_->end();}
    const_iterator end   () const {return pvector_->end();}
          
    iterator       rbegin ()       {return pvector_->rbegin();}
    const_iterator rbegin () const {return pvector_->rbegin();}
    iterator       rend   ()       {return pvector_->rend();}
    const_iterator rend   () const {return pvector_->rend();}

    reference       at (size_type n)       {return pvector_->at(n);}
    const_reference at (size_type n) const {return pvector_->at(n);}

    reference       operator[] (size_type n)       {return (*pvector_)[n];}
    const_reference operator[] (size_type n) const {return (*pvector_)[n];}

    reference       front ()       {return pvector_->front();}
    const_reference front () const {return pvector_->front();}
    reference       back  ()       {return pvector_->back();}
    const_reference back  () const {return pvector_->back();}

private:
    vector<T> *pvector_;
};


template <typename T>
class matrix_field
{
public:
    matrix_field(matrix<T> &vec)
        : pmatrix_(&vec)
    {

    }
public:
    typedef typename matrix<T>::reference reference;
    typedef typename matrix<T>::const_reference const_reference;
    typedef typename matrix<T>::size_type size_type;

public:
    const_reference operator () (size_type i, size_type j) const {return (*pmatrix_)(i, j);}
    reference       operator () (size_type i, size_type j)       {return (*pmatrix_)(i, j);}
private:
    matrix<T> *pmatrix_;
};