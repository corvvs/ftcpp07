#ifndef CPP07_WHATEVER_HPP_
# define CPP07_WHATEVER_HPP_

template<class T>
void    swap(T& a, T& b) {
    // std::cerr << "SWAP";
    T temp(a);
    a = b;
    b = temp;
}

template<class T>
T       min(T& a, T& b) {
    // std::cerr << "MIN";
    return a < b ? a : b;
}

template<class T>
T       max(T& a, T& b) {
    // std::cerr << "MAX";
    return a >= b ? a : b;
}

#endif
