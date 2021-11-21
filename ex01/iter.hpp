#ifndef CPP07_ITER_HPP_
# define CPP07_ITER_HPP_

# include <cstdlib>

template <class T>
void    iter(T array[], std::size_t n, void (*func)(T&)) {
    if (!func) { return; }
    for (std::size_t i = 0; i < n; i += 1) {
        func(array[i]);
    }
}

template <class T>
void    iter(T array[], std::size_t n, void (*func)(T)) {
    if (!func) { return; }
    for (std::size_t i = 0; i < n; i += 1) {
        func(array[i]);
    }
}

#endif
