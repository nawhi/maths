//
// Created by Nick White on 03/07/2020.
//

#include "lazy.h"
#include <cmath>
#include <iostream>

double Lazy::operator()(double d) {
    const std::map<double, double>::iterator &it = cache.find(d);
    if (it != cache.end()) {
        std::cout << "cache hit" << std::endl;
        return it->second;
    }
    auto result = func(d);
    cache[d] = result;
    return result;
}