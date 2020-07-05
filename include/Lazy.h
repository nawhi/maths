//
// Created by Nick White on 03/07/2020.
//

#ifndef MATRIX_LAZY_H
#define MATRIX_LAZY_H

#include <functional>
#include <map>
#include <iostream>

template<typename T, typename U = T>
class Lazy {
    std::function<T(U)> func;
    std::map<T, U> cache = {};
public:
    explicit Lazy(std::function<T(U)> f) : func(std::move(f)) {}

    U operator()(T t) {
        const auto &hit = cache.find(t);
        if (hit != cache.end()) {
            return hit->second;
        }
        auto result = func(t);
        cache[t] = result;
        return result;
    }
};


#endif //MATRIX_LAZY_H
