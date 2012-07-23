// scheduler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "task.h"

enum plane_class
{
    LIGHT = 0, MEDIUM = 1, HEAVY = 2
};

float get_class_wait(plane_class i, plane_class j)
{
    if (i == LIGHT)
        return 1;
    else if (i == HEAVY)
        return 4;
    else 
    {
        if (j == HEAVY)
            return 1;
        else 
            return 2;
    }

}

task planes_task(size_t n, float timespan)
{
    typedef mt19937 gen;

    gen randgen(static_cast<unsigned int>(std::time(0)));
    uniform_real_distribution<float> classes_distr(0, 1);
    uniform_real_distribution<float> dates_distr(0, timespan);

    variate_generator<gen, uniform_real_distribution<float>> classes_gen(randgen, classes_distr);
    
    boost::variate_generator<gen, uniform_real_distribution<float>> dates_gen(randgen, dates_distr);


    task t(n);

    vector<plane_class> classes(n);
    for (size_t i = 0; i < n; ++i)
    {
        float p = classes_gen();
        if (p < 0.2)
            classes[i] = LIGHT;
        else if (p > 0.8)
            classes[i] = HEAVY;
        else
            classes[i] = MEDIUM;
    }


    float separations_avg = 0;
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j) 
            separations_avg += (t.get_separation(i, j) = get_class_wait(classes[i], classes[j]));
             
    separations_avg /= (n * n);


    std::generate(t.get_due(), t.get_due() + n, dates_gen);
    std::sort (t.get_due(), t.get_due() + n);
    std::copy (t.get_due(), t.get_due() + n, t.get_min_bound());
    std::fill (t.get_max_bound(), t.get_max_bound() + n, std::numeric_limits<moment>::max());

    for (size_t i = 0; i < n; ++i) 
    {
        t.get_tweight() [i] = t.get_eweight() [i] = classes_gen();
    }

    return t;
}

permutation random_solver(const task &t, const permutation &src, size_t n_iters)
{
    permutation dst (src);
    int counter = 0;
    for (size_t iter = 0; iter < n_iters; ++iter)
    {
        size_t i = rand() % (t.get_n() - 1);
        size_t j = i + 1 + rand() % (t.get_n() - i - 1);

        cost_t before = calculate_cost(t, dst);
        std::swap(dst[i], dst[j]);
        cost_t after = calculate_cost(t, dst);

        if (after >= before)
            std::swap(dst[i], dst[j]);
        else
            ++counter;
    }
    cout << " " << counter << "/" << n_iters << " swaps" << endl;
    return dst;        
}

permutation all_pairs_solver(const task &t, const permutation &src, size_t n_iters)
{
    permutation dst (src);


    for (size_t iter = 0; iter < n_iters; ++iter)
    {
        int counter = 0;
        for (size_t i = 0; i < t.get_n(); ++i)
        {
            for (size_t j = i + 1; j < t.get_n(); ++j)
            {
                cost_t before = calculate_cost(t, dst);
                std::swap(dst[i], dst[j]);
                cost_t after = calculate_cost(t, dst);

                if (after >= before)
                    std::swap(dst[i], dst[j]);
                else
                    ++counter;
            }
        }
        cout << " iter " << iter << ": " << counter << " swaps" << endl;
    }
    return dst;        
}


permutation sliding_window_solver(const task &t, const permutation &src, size_t window_size)
{
    permutation dst (src);
    permutation best (src);
    cost_t best_cost = calculate_cost(t, best);

    size_t last = dst.size() - window_size;

    for (size_t i = 0; i <= last; ++i)
    {
        dst = best;
        
        auto it = dst.begin() + i;
        
        std::sort(it, it + window_size);

        int counter = 0;
        do {
            ++counter;
            cost_t curr_cost = calculate_cost(t, dst);
            if (curr_cost < best_cost)
            {
                //cout << " improvement: " << best_cost << " -> " << curr_cost << endl;
                best = dst;
                best_cost = calculate_cost(t, best);
            }
        } while (std::next_permutation(it, it + window_size));

        cout << " offset " << i << " " << counter << endl;

    }

    return best;
}
std::ostream& operator<< (std::ostream& s, const permutation &p)
{
    for (auto i : p)
        s << i << " ";
    return s;
}



int main(int argc, char* argv[])
{
    srand (static_cast<unsigned int>(std::time(0)));

    const size_t n = 50;
    
    task t = planes_task(n, 50.0f);

    permutation perm(n);
    for (size_t i = 0; i < n; ++i)
        perm[i] = i;

    std::sort (perm.begin(), perm.end(), [&](size_t i, size_t j) -> bool
    {
        return t.get_due()[i] < t.get_due()[j];
    });


    permutation perm1(perm);
    cout << "Original: " << endl;
    cout << perm1 << endl;
    cout << calculate_cost(t, perm1) << endl;

    cout << "Random solver: " << endl;
    perm1 = random_solver(t, perm, 10000);
    cout << perm1 << endl;
    cout << calculate_cost(t, perm1) << endl;

    cout << "All pairs solver: " << endl;
    perm1 = all_pairs_solver(t, perm, 5);
    cout << perm1 << endl;
    cout << calculate_cost(t, perm1) << endl;
    
    cout << "Sliding window solver: " << endl;
    perm1 = sliding_window_solver(t, perm, 10);
    cout << perm1 << endl;
    cout << calculate_cost(t, perm1) << endl;
    return 0;
}



/*int main(int argc, char* argv[])
{
    const size_t n = 4;

    permutation perm(n);
    for (size_t i = 0; i < n; ++i)
        perm[i] = i;

    bool ok = true;
    while (ok)
    {
        cout << perm << endl;
        ok = std::next_permutation(perm.begin(), perm.end());
    }

}*/
