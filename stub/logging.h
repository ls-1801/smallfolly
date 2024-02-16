#ifndef LOGGING_H
#define LOGGING_H
#include <cassert>
#include <iostream>

#define DCHECK_LE(a,b) assert(a <= b)
#define DCHECK_LT(a,b) assert(a < b)
#define DCHECK_GE(a,b) assert(a >= b)
#define DCHECK_GT(a,b) assert(a > b)
#define DCHECK_EQ(a,b) assert(a==b)
#define DCHECK(exp) assert(exp)
#define LOG(...) std::cerr

#endif //LOGGING_H
