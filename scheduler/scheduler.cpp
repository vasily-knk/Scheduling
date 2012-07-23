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

    for (size_t i = 0; i < n; ++i) 
    {
        t.get_due() [i] = t.get_min_bound() [i] = dates_gen();
        t.get_max_bound() [i] = std::numeric_limits<moment>::max();
    }

    for (size_t i = 0; i < n; ++i) 
    {
        t.get_tweight() [i] = t.get_eweight() [i] = 1;
    }

    return t;
}

permutation random_solver(const task &t, const permutation &src, size_t n_iters)
{
    permutation dst (src);
    for (size_t iter = 0; iter < n_iters; ++iter)
    {
        size_t i = rand() % (t.get_n() - 1);
        size_t j = i + 1 + rand() % (t.get_n() - i - 1);

        cost_t before = calculate_cost(t, dst);
        std::swap(dst[i], dst[j]);
        cost_t after = calculate_cost(t, dst);

        if (after >= before)
            std::swap(dst[i], dst[j]);
    }
    return dst;        
}

int main(int argc, char* argv[])
{
    srand (static_cast<unsigned int>(std::time(0)));

    const size_t n = 50;
    
    task t = planes_task(n, 100.0f);

    permutation perm(n);
    for (size_t i = 0; i < n; ++i)
        perm[i] = i;

    std::sort (perm.begin(), perm.end(), [&](size_t i, size_t j) -> bool
    {
        return t.get_due()[i] < t.get_due()[j];
    });


    cout << calculate_cost(t, perm) << endl;
    permutation perm1 = random_solver(t, perm, 10000);
    cout << calculate_cost(t, perm1) << endl;


    return 0;
}

