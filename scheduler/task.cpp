#include "stdafx.h"
#include "task.h"


task::task(size_t n)
    : min_bound_ (new moment[n])
    , max_bound_ (new moment[n])
    , due_       (new moment[n])
    , separation_(new moment[n * n])
    , eweight_   (new moment[n])
    , tweight_   (new moment[n])
    , n_         (n)
{

}

task::task(const task& t)
    : min_bound_ (new moment[t.get_n()])
    , max_bound_ (new moment[t.get_n()])
    , due_       (new moment[t.get_n()])
    , separation_(new moment[t.get_n() * t.get_n()])
    , eweight_   (new moment[t.get_n()])
    , tweight_   (new moment[t.get_n()])
    , n_         (t.get_n())
{

#pragma warning (push)
#pragma warning(disable:4996)

    std::copy(t.min_bound_.get(), t.min_bound_.get() + n_, min_bound_.get());
    std::copy(t.max_bound_.get(), t.max_bound_.get() + n_, max_bound_.get());
    std::copy(t.due_.get(), t.due_.get() + n_, due_.get());
    std::copy(t.separation_.get(), t.separation_.get() + n_ * n_, separation_.get());

    std::copy(t.eweight_.get(), t.eweight_.get() + n_, eweight_.get());
    std::copy(t.tweight_.get(), t.tweight_.get() + n_, tweight_.get());

#pragma warning (pop)


}

cost_t calculate_cost(const task& t, const permutation &p) 
{
    assert(p.size() == t.get_n());

    const vector<moment> &x = generate_times(t, p);
    cost_t cost = 0;
    
    for (size_t i = 0; i < t.get_n(); ++i)
    {
        if (x[i] > t.get_due()[i])
            cost += t.get_tweight()[i] * (x[i] - t.get_due()[i]);
        else
            cost += t.get_eweight()[i] * (t.get_due()[i] - x[i]);
    }

    return cost;
}

bool is_valid(const task& t, const permutation &p) 
{
    assert(p.size() == t.get_n());
    const vector<moment> &x = generate_times(t, p);

    for (size_t i = 0; i < t.get_n(); ++i)
    {
        if (x[i] > t.get_max_bound()[i])
            return false;
    }
    return true;
}

vector<moment> generate_times(const task& t, const permutation &p) 
{
    assert(p.size() == t.get_n());

    vector<moment> x (t.get_n());
    if (t.get_n() == 0)
        return x;

    x[p[0]] = t.get_min_bound()[p[0]];

    for (size_t i = 1; i < t.get_n(); ++i)
    {
        const size_t prev = p[i-1];
        const size_t curr = p[i];
        x[curr] = max(t.get_min_bound()[curr], x[prev] + t.get_separation(prev, curr));
    }

    return x;
}

