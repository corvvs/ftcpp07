#ifndef CPP07_ITER_HPP_
# define CPP07_ITER_HPP_

template <class T, typename Func>
void    iter(T array[], std::size_t n, Func func) {
    if (!func) { return; }
    for (std::size_t i = 0; i < n; i += 1) {
        func(array[i]);
    }
}

#endif
