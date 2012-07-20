// scheduler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "task.h"

task planes_task(size_t n, float timespan)
{
    typedef boost::mt19937 gen;
    using boost::random::uniform_real_distribution;
    using boost::random::uniform_int_distribution;
    using boost::variate_generator;

    gen randgen(static_cast<unsigned int>(std::time(0)));
    uniform_real_distribution<float> dates_distr(0, timespan);
    uniform_int_distribution<size_t> types_distr(0, 3);
    
    boost::variate_generator<gen, uniform_real_distribution<float>> dates_gen(randgen, dates_distr);
    boost::variate_generator<gen, uniform_int_distribution<size_t>> types_gen(randgen, types_distr);

    vector<moment> dates(n);
    vector<size_t> types(n);
    matrix<moment> separations(n, n);

    enum types_enum 
    {
        LIGHT = 0, MEDIUM = 1, HEAVY = 2
    };
    
    for (size_t i = 0; i < n; ++i)
    {
        dates[i] = dates_gen();
        types[i] = types_gen();
    }

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (types[i] == LIGHT)
                separations(i, j) = 1;
            else if (types[i] == HEAVY)
                separations(i, j) = 4;
            else 
            {
                if (types[j] == HEAVY)
                    separations(i, j) = 1;
                else 
                    separations(i, j) = 2;
            }
        }
    }



}

int main(int argc, char* argv[])
{

    boost::mt19937 randgen(static_cast<unsigned int>(std::time(0)));
    boost::random::uniform_real_distribution<float> noise(0,10);

    boost::variate_generator<boost::mt19937, 
        boost::random::uniform_real_distribution<float> > nD(randgen, noise);

    for (int i = 0; i < 100; i++)
    {
        const float value = nD();
        cout << value << endl;
    }

    return 0;
}

