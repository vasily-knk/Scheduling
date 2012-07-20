#pragma once

typedef float moment;
typedef float cost_t;

typedef vector<size_t> permutation;

class task
{
public:
    task(size_t n, 
        const vector<moment> &min_bound,
        const vector<moment> &max_bound,
        const vector<moment> &due,
        const matrix<moment> &separation,
        const vector<cost_t> &eweight,
        const vector<cost_t> &tweight
        );

    bool is_valid(const permutation &p) const;
    cost_t calculate_cost(const permutation &p) const;
    cost_t get_cost(const vector<moment> &x) const;

public:
    const vector<moment> &get_min_bound () const {return min_bound_;}
    const vector<moment> &get_max_bound () const {return max_bound_;}
    const vector<moment> &get_due       () const {return due_;}
    const matrix<moment> &get_sepatation() const {return separation_;}

    const vector<cost_t> &get_eweight   () const {return eweight_;}
    const vector<cost_t> &get_tweight   () const {return tweight_;}

private:
    vector<moment> generate_times(const permutation &p) const;

private:
	const vector<moment> min_bound_;
    const vector<moment> max_bound_;

    const vector<moment> due_;
	const matrix<moment> separation_;

	const vector<cost_t> eweight_;
	const vector<cost_t> tweight_;

    const size_t n_;
};

