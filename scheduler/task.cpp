#include "stdafx.h"
#include "task.h"


task::task(size_t n)
    : min_bound_ (n, 0)
    , max_bound_ (n, 0)
    , due_       (n, 0)
    , separation_(n, n, 0)
    , eweight_   (n, 0)
    , tweight_   (n, 0)
    , n_         (n)
{

}

cost_t task::calculate_cost(const permutation &p) const
{
    const vector<moment> &x = generate_times(p);
    cost_t cost = 0;
    
    for (size_t i = 0; i < n_; ++i)
    {
        if (x[i] > due_[i])
            cost += tweight_[i] * (x[i] - due_[i]);
        else
            cost += eweight_[i] * (due_[i] - x[i]);
    }

    return cost;
}

bool task::is_valid(const permutation &p) const
{
    const vector<moment> &x = generate_times(p);

    for (size_t i = 0; i < n_; ++i)
    {
        if (x[i] > max_bound_[i])
            return false;
    }
    return true;
}

vector<moment> task::generate_times(const permutation &p) const
{
    assert(p.size() == n_);

    vector<moment> x (n_);
    if (n_ == 0)
        return x;

    x[p[0]] = min_bound_[p[0]];

    for (size_t i = 1; i < n_; ++i)
    {
        const size_t prev = p[i-1];
        const size_t curr = p[i];
        x[curr] = max(min_bound_[curr], x[prev] + separation_(prev, curr));
    }

    return x;
}

