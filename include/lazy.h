//
// Created by Nick White on 03/07/2020.
//

#ifndef MATRIX_LAZY_H
#define MATRIX_LAZY_H

#include <functional>
#include <map>

class Lazy {
    std::function<double(double)> func;
    std::map<double, double> cache = {};
public:
    explicit Lazy(std::function<double(double)> f) : func(std::move(f)) {}
    double operator () (double d);
};


#endif //MATRIX_LAZY_H
