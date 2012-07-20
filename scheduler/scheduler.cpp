// scheduler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "task.h"


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

