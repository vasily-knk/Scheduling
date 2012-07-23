#pragma once

typedef float moment;
typedef float cost_t;

typedef vector<size_t> permutation;

#include "vector_field.h"

class task
{
public:
    task(size_t n);

    bool is_valid(const permutation &p) const;
    cost_t calculate_cost(const permutation &p) const;
    cost_t get_cost(const vector<moment> &x) const;

public:
    vector_field<moment> get_min_bound  () {return min_bound_;}
    vector_field<moment> get_max_bound  () {return max_bound_;}
    vector_field<moment> get_due        () {return due_;}
    matrix_field<moment> get_sepatation () {return separation_;}

    vector_field<cost_t> get_eweight   () {return eweight_;}
    vector_field<cost_t> get_tweight   () {return tweight_;}

private:
    vector<moment> generate_times(const permutation &p) const;

private:
    vector<moment> min_bound_;
    vector<moment> max_bound_;

    vector<moment> due_;
    matrix<moment> separation_;

    vector<cost_t> eweight_;
    vector<cost_t> tweight_;

    const size_t n_;
};

