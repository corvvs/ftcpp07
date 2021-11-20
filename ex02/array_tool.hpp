#ifndef CPP07_ARRAY_TOOL_HPP_
# define CPP07_ARRAY_TOOL_HPP_

#include "Array.hpp"

template <class From, class To>
Array<To>   map(Array<From> from, To (*mapper)(From)) {
    Array<To> mapped(from.size());
    for (unsigned int i = 0; i < from.size(); i += 1) {
        mapped[i] = mapper(from[i]);
    }
    return mapped;
}

template <class From, class To>
Array<To>   map(Array<From> from, To (*mapper)(From&)) {
    Array<To> mapped(from.size());
    for (unsigned int i = 0; i < from.size(); i += 1) {
        mapped[i] = mapper(from[i]);
    }
    return mapped;
}

template <class T, class R>
R   reduce(Array<T> from, R (*reducer)(R, T)) {
    R reduced = R();
    for (unsigned int i = 0; i < from.size(); i += 1) {
        reduced = reducer(reduced, from[i]);
    }
    return reduced;
}

template <class T, class R>
R   reduce(Array<T> from, R (*reducer)(R&, T&)) {
    R reduced = R();
    for (unsigned int i = 0; i < from.size(); i += 1) {
        reduced = reducer(reduced, from[i]);
    }
    return reduced;
}

#endif
