#ifndef STDHEADER_H
#define STDHEADER_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <map>
#include <functional>
#include <tuple>
#include <sstream>
#include <regex>
#include <climits>
#include <ctime>

typedef std::map<std::string, std::string> Option;

template<typename _Tp> 
_Tp parseTo(const std::string &str) {
    std::istringstream iss(str);
    _Tp ret;
    iss >> ret;
    return ret;
}

template<typename _Tp>
std::string toString(const _Tp &x) {
    std::ostringstream oss;
    oss << x;
    return oss.str();
}

inline float rand_float() {
    return (float)rand() / (float)RAND_MAX;
}

#define PI M_PI

#endif  // STDHEADER_H
