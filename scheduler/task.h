#pragma once

typedef float moment;
typedef float cost_t;

typedef vector<size_t> permutation;

//#include "vector_field.h"

class task
{
public:
    task(size_t n);
    task(const task& t);

public:
    moment* get_min_bound  () const {return min_bound_.get();}
    moment* get_max_bound  () const {return max_bound_.get();}
    moment* get_due        () const {return due_.get();}
    moment* get_sepatation () const {return separation_.get();}

    cost_t* get_eweight   () const {return eweight_.get();}
    cost_t* get_tweight   () const {return tweight_.get();}

    moment &get_separation (size_t i, size_t j) const {return separation_[i * n_ + j];}

    size_t get_n() const {return n_;}

private:
    scoped_array<moment> min_bound_;
    scoped_array<moment> max_bound_;

    scoped_array<moment> due_;
    scoped_array<moment> separation_;

    scoped_array<cost_t> eweight_;
    scoped_array<cost_t> tweight_;

    const size_t n_;
};


bool is_valid(const task& t, const permutation &p) ;
cost_t calculate_cost(const task& t, const permutation &p) ;
cost_t get_cost(const task& t, const vector<moment> &x) ;
vector<moment> generate_times(const task& t, const permutation &p) ;
