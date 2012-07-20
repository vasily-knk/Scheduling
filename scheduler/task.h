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

