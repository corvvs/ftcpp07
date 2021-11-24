#ifndef CPP07_WHATEVER_HPP_
# define CPP07_WHATEVER_HPP_

template<class T>
void        swap(T& a, T& b) {
    T temp(a);
    a = b;
    b = temp;
}

template<class T>
const T&    min(const T& a, const T& b) {
    return a < b ? a : b;
}

template<class T>
const T&    max(const T& a, const T& b) {
    return a > b ? a : b;
}

#endif
