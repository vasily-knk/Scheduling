// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once



#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <boost/scoped_array.hpp>
using boost::scoped_array;

#include <boost/optional.hpp>
using boost::optional;

using std::min;
using std::max;

#include <algorithm>
#include <numeric>

#include <boost/numeric/ublas/matrix.hpp>
using boost::numeric::ublas::matrix;

#include <boost/random.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/variate_generator.hpp>
using boost::mt19937;
using boost::random::uniform_real_distribution;
using boost::random::uniform_int_distribution;
using boost::random::variate_generator;

