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
            separations_avg += (t.get_sepatation() (i, j) = get_class_wait(classes[i], classes[j]));
             
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

int main(int argc, char* argv[])
{
    const size_t n = 10;
    
    task t = planes_task(10, 100.0f);

    permutation perm(n);
    for (size_t i = 0; i < n; ++i)
        perm[i] = i;

    random_shuffle(perm.begin(), perm.end());

    cout << t.calculate_cost(perm) << endl;

    return 0;
}

