//================================================================================
// this file has been auto-generated, do not modify its contents!
// date: 2023-08-01 16:03:54.596340
// git hash: 0cf26708f3b17b2f74940e5806bad2aeaae4c076
//================================================================================

#ifndef KERNEL_FLOAT_MACROS_H
#define KERNEL_FLOAT_MACROS_H

#ifdef __CUDACC__
#define KERNEL_FLOAT_CUDA (1)

#ifdef __CUDA_ARCH__
#define KERNEL_FLOAT_INLINE    __forceinline__ __device__
#define KERNEL_FLOAT_IS_DEVICE (1)
#define KERNEL_FLOAT_IS_HOST   (0)
#define KERNEL_FLOAT_CUDA_ARCH (__CUDA_ARCH__)
#else
#define KERNEL_FLOAT_INLINE    __forceinline__ __host__
#define KERNEL_FLOAT_IS_DEVICE (0)
#define KERNEL_FLOAT_IS_HOST   (1)
#define KERNEL_FLOAT_CUDA_ARCH (0)
#endif
#else
#define KERNEL_FLOAT_INLINE    inline
#define KERNEL_FLOAT_CUDA      (0)
#define KERNEL_FLOAT_IS_HOST   (1)
#define KERNEL_FLOAT_IS_DEVICE (0)
#define KERNEL_FLOAT_CUDA_ARCH (0)
#endif

#ifndef KERNEL_FLOAT_FP16_AVAILABLE
#define KERNEL_FLOAT_FP16_AVAILABLE (1)
#endif

#ifndef KERNEL_FLOAT_BF16_AVAILABLE
#define KERNEL_FLOAT_BF16_AVAILABLE (1)
#endif

#ifndef KERNEL_FLOAT_FP8_AVAILABLE
#define KERNEL_FLOAT_FP8_AVAILABLE (0)
#endif

#define KERNEL_FLOAT_ASSERT(expr) \
    do {                          \
    } while (0)
#define KERNEL_FLOAT_UNREACHABLE __builtin_unreachable()

#endif  //KERNEL_FLOAT_MACROS_H
#ifndef KERNEL_FLOAT_CORE_H
#define KERNEL_FLOAT_CORE_H



namespace kernel_float {

template<size_t... Is>
struct index_sequence {
    static constexpr size_t size = sizeof...(Is);
};

namespace detail {
template<size_t N>
struct make_index_sequence_helper {};

// Benchmarks show that it is much faster to predefine all possible index sequences instead of doing something
// recursive with variadic templates.
#define KERNEL_FLOAT_INDEX_SEQ(N, ...)            \
    template<>                                    \
    struct make_index_sequence_helper<N> {        \
        using type = index_sequence<__VA_ARGS__>; \
    };

KERNEL_FLOAT_INDEX_SEQ(0)
KERNEL_FLOAT_INDEX_SEQ(1, 0)
KERNEL_FLOAT_INDEX_SEQ(2, 0, 1)
KERNEL_FLOAT_INDEX_SEQ(3, 0, 1, 2)
KERNEL_FLOAT_INDEX_SEQ(4, 0, 1, 2, 3)
KERNEL_FLOAT_INDEX_SEQ(5, 0, 1, 2, 3, 4)
KERNEL_FLOAT_INDEX_SEQ(6, 0, 1, 2, 3, 4, 5)
KERNEL_FLOAT_INDEX_SEQ(7, 0, 1, 2, 3, 4, 5, 6)
KERNEL_FLOAT_INDEX_SEQ(8, 0, 1, 2, 3, 4, 5, 6, 7)
KERNEL_FLOAT_INDEX_SEQ(9, 0, 1, 2, 3, 4, 5, 6, 7, 8)
KERNEL_FLOAT_INDEX_SEQ(10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
KERNEL_FLOAT_INDEX_SEQ(11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
KERNEL_FLOAT_INDEX_SEQ(12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11)
KERNEL_FLOAT_INDEX_SEQ(13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12)
KERNEL_FLOAT_INDEX_SEQ(14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13)
KERNEL_FLOAT_INDEX_SEQ(15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14)
KERNEL_FLOAT_INDEX_SEQ(16, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)
KERNEL_FLOAT_INDEX_SEQ(17, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)

}  // namespace detail

template<size_t N>
using make_index_sequence = typename detail::make_index_sequence_helper<N>::type;

namespace detail {
template<typename T>
struct decay_helper {
    using type = T;
};

template<typename T>
struct decay_helper<const T> {
    using type = T;
};

template<typename T>
struct decay_helper<const T&> {
    using type = T;
};

template<typename T>
struct decay_helper<T&> {
    using type = T;
};

template<typename T>
struct decay_helper<T&&> {
    using type = T;
};
}  // namespace detail

template<typename T>
using decay_t = typename detail::decay_helper<T>::type;

template<typename A, typename B>
struct promote_type;

template<typename T>
struct promote_type<T, T> {
    using type = T;
};

#define KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, U) \
    template<>                                  \
    struct promote_type<T, U> {                 \
        using type = T;                         \
    };                                          \
    template<>                                  \
    struct promote_type<U, T> {                 \
        using type = T;                         \
    };

// T + bool becomes T
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(char, bool)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(signed char, bool)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(signed short, bool)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(signed int, bool)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(signed long, bool)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(signed long long, bool)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(unsigned char, bool)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(unsigned short, bool)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(unsigned int, bool)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(unsigned long, bool)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(unsigned long long, bool)

KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(double, float)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(long double, float)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(long double, double)

#define KERNEL_FLOAT_DEFINE_PROMOTED_FLOAT(T)                \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, char)               \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, signed char)        \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, signed short)       \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, signed int)         \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, signed long)        \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, signed long long)   \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, unsigned char)      \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, unsigned short)     \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, unsigned int)       \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, unsigned long)      \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, unsigned long long) \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(T, bool)

KERNEL_FLOAT_DEFINE_PROMOTED_FLOAT(float)
KERNEL_FLOAT_DEFINE_PROMOTED_FLOAT(double)
KERNEL_FLOAT_DEFINE_PROMOTED_FLOAT(long double)

#define KERNEL_FLOAT_DEFINE_PROMOTED_INTEGRAL(T, U)       \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(signed T, signed U) \
    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(unsigned T, unsigned U)

KERNEL_FLOAT_DEFINE_PROMOTED_INTEGRAL(short, char)
KERNEL_FLOAT_DEFINE_PROMOTED_INTEGRAL(int, char)
KERNEL_FLOAT_DEFINE_PROMOTED_INTEGRAL(int, short)
KERNEL_FLOAT_DEFINE_PROMOTED_INTEGRAL(long, char)
KERNEL_FLOAT_DEFINE_PROMOTED_INTEGRAL(long, short)
KERNEL_FLOAT_DEFINE_PROMOTED_INTEGRAL(long, int)
KERNEL_FLOAT_DEFINE_PROMOTED_INTEGRAL(long long, char)
KERNEL_FLOAT_DEFINE_PROMOTED_INTEGRAL(long long, short)
KERNEL_FLOAT_DEFINE_PROMOTED_INTEGRAL(long long, int)
KERNEL_FLOAT_DEFINE_PROMOTED_INTEGRAL(long long, long)

template<typename T>
struct promote_type<T*, T*> {
    using type = T*;
};

#define KERNEL_FLOAT_DEFINE_PROMOTED_POINTER(I) \
    template<typename T>                        \
    struct promote_type<T*, I> {                \
        using type = T*;                        \
    };                                          \
    template<typename T>                        \
    struct promote_type<I, T*> {                \
        using type = T*;                        \
    };

KERNEL_FLOAT_DEFINE_PROMOTED_POINTER(char)
KERNEL_FLOAT_DEFINE_PROMOTED_POINTER(signed char)
KERNEL_FLOAT_DEFINE_PROMOTED_POINTER(signed short)
KERNEL_FLOAT_DEFINE_PROMOTED_POINTER(signed int)
KERNEL_FLOAT_DEFINE_PROMOTED_POINTER(signed long)
KERNEL_FLOAT_DEFINE_PROMOTED_POINTER(signed long long)
KERNEL_FLOAT_DEFINE_PROMOTED_POINTER(unsigned char)
KERNEL_FLOAT_DEFINE_PROMOTED_POINTER(unsigned short)
KERNEL_FLOAT_DEFINE_PROMOTED_POINTER(unsigned int)
KERNEL_FLOAT_DEFINE_PROMOTED_POINTER(unsigned long)
KERNEL_FLOAT_DEFINE_PROMOTED_POINTER(unsigned long long)

// half precision
//    KERNEL_FLOAT_DEFINE_PROMOTED_FLOAT(half)
//    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(half, bool)
//    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(float, half)
//    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(double, half)
//    KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(long double, half)

namespace detail {
template<typename... Ts>
struct multi_promote_type;

template<typename T>
struct multi_promote_type<T> {
    using type = T;
};

template<typename A, typename B>
struct multi_promote_type<A, B>: promote_type<A, B> {};

template<typename A, typename B, typename C, typename... Rest>
struct multi_promote_type<A, B, C, Rest...>:
    multi_promote_type<typename promote_type<A, B>::type, C, Rest...> {};

}  // namespace detail

template<typename... Ts>
using promote_t = typename detail::multi_promote_type<decay_t<Ts>...>::type;

namespace detail {

template<typename A, typename B>
struct is_same_helper {
    static constexpr bool value = false;
};

template<typename A>
struct is_same_helper<A, A> {
    static constexpr bool value = true;
};
}  // namespace detail

template<typename A, typename B>
static constexpr bool is_same = detail::is_same_helper<A, B>::value;

namespace detail {
template<typename From, typename To, typename Common = To>
struct is_implicit_convertible_helper {
    static constexpr bool value = false;
};

template<typename From, typename To>
struct is_implicit_convertible_helper<From, To, typename promote_type<From, To>::type> {
    static constexpr bool value = true;
};
}  // namespace detail

template<typename From, typename To>
static constexpr bool is_implicit_convertible =
    detail::is_implicit_convertible_helper<decay_t<From>, decay_t<To>>::value;

namespace detail {
template<typename T>
KERNEL_FLOAT_INLINE T& declval() {
    while (1)
        ;
}
}  // namespace detail

template<typename F, typename... Args>
using result_t = decltype((detail::declval<F>())(detail::declval<Args>()...));

namespace detail {
template<bool, typename T>
struct enabled_helper {};

template<typename T>
struct enabled_helper<true, T> {
    using type = T;
};
}  // namespace detail

template<bool C, typename T = void>
using enabled_t = typename detail::enabled_helper<C, T>::type;

}  // namespace kernel_float

#endif
#ifndef KERNEL_FLOAT_BASE_H
#define KERNEL_FLOAT_BASE_H




namespace kernel_float {

template<typename T, size_t N, size_t Alignment = alignof(T)>
struct alignas(Alignment) aligned_array {
    KERNEL_FLOAT_INLINE
    T* data() {
        return items_;
    }

    KERNEL_FLOAT_INLINE
    const T* data() const {
        return items_;
    }

    T items_[N] = {};
};

template<typename T, size_t Alignment>
struct aligned_array<T, 0, Alignment> {
    KERNEL_FLOAT_INLINE
    T* data() {
        while (true)
            ;
    }

    KERNEL_FLOAT_INLINE
    const T* data() const {
        while (true)
            ;
    }
};

template<typename T, size_t Alignment>
struct alignas(Alignment) aligned_array<T, 1, Alignment> {
    KERNEL_FLOAT_INLINE
    aligned_array(T value = {}) : x(value) {}

    KERNEL_FLOAT_INLINE
    operator T() const {
        return x;
    }

    KERNEL_FLOAT_INLINE
    T* data() {
        return &x;
    }

    KERNEL_FLOAT_INLINE
    const T* data() const {
        return &x;
    }

    T x;
};

template<typename T, size_t Alignment>
struct alignas(Alignment) aligned_array<T, 2, Alignment> {
    KERNEL_FLOAT_INLINE
    aligned_array(T x, T y) : x(x), y(y) {}

    KERNEL_FLOAT_INLINE
    aligned_array() : aligned_array(T {}, T {}) {}

    KERNEL_FLOAT_INLINE
    T* data() {
        return items;
    }

    KERNEL_FLOAT_INLINE
    const T* data() const {
        return items;
    }

    union {
        T items[2];
        struct {
            T x;
            T y;
        };
    };
};

template<typename T, size_t Alignment>
struct alignas(Alignment) aligned_array<T, 3, Alignment> {
    KERNEL_FLOAT_INLINE
    aligned_array(T x, T y, T z) : x(x), y(y), z(z) {}

    KERNEL_FLOAT_INLINE
    aligned_array() : aligned_array(T {}, T {}, T {}) {}

    KERNEL_FLOAT_INLINE
    T* data() {
        return items;
    }

    KERNEL_FLOAT_INLINE
    const T* data() const {
        return items;
    }

    union {
        T items[3];
        struct {
            T x;
            T y;
            T z;
        };
    };
};

template<typename T, size_t Alignment>
struct alignas(Alignment) aligned_array<T, 4, Alignment> {
    KERNEL_FLOAT_INLINE
    aligned_array(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

    KERNEL_FLOAT_INLINE
    aligned_array() : aligned_array(T {}, T {}, T {}, T {}) {}

    KERNEL_FLOAT_INLINE
    T* data() {
        return items;
    }

    KERNEL_FLOAT_INLINE
    const T* data() const {
        return items;
    }

    union {
        T items[4];
        struct {
            T x;
            T y;
            T z;
            T w;
        };
    };
};

KERNEL_FLOAT_INLINE
static constexpr size_t compute_max_alignment(size_t total_size, size_t min_align) {
    if (total_size % 32 == 0 || min_align >= 32) {
        return 32;
    } else if (total_size % 16 == 0 || min_align == 16) {
        return 16;
    } else if (total_size % 8 == 0 || min_align == 8) {
        return 8;
    } else if (total_size % 4 == 0 || min_align == 4) {
        return 4;
    } else if (total_size % 2 == 0 || min_align == 2) {
        return 2;
    } else {
        return 1;
    }
}

template<typename T, size_t N>
using vector_storage = aligned_array<T, N, compute_max_alignment(sizeof(T) * N, alignof(T))>;

template<size_t N>
struct extent {
    static constexpr size_t value = N;
    static constexpr size_t size = N;
};

template<typename T>
struct into_vector_traits {
    using value_type = T;
    using extent_type = extent<1>;

    KERNEL_FLOAT_INLINE
    static vector_storage<T, 1> call(const T& input) {
        return vector_storage<T, 1> {input};
    }
};

template<typename V>
struct into_vector_traits<const V>: into_vector_traits<V> {};

template<typename V>
struct into_vector_traits<V&>: into_vector_traits<V> {};

template<typename V>
struct into_vector_traits<const V&>: into_vector_traits<V> {};

template<typename V>
struct into_vector_traits<V&&>: into_vector_traits<V> {};

template<typename T, size_t N, size_t A>
struct into_vector_traits<aligned_array<T, N, A>> {
    using value_type = T;
    using extent_type = extent<N>;

    KERNEL_FLOAT_INLINE
    static vector_storage<T, N> call(const aligned_array<T, N, A>& input) {
        return input;
    }
};

template<typename V>
struct vector_traits;

template<typename T, typename E, typename S = vector_storage<T, E::size>>
struct vector;

template<typename T, typename E, typename S>
struct into_vector_traits<vector<T, E, S>> {
    using value_type = T;
    using extent_type = E;

    KERNEL_FLOAT_INLINE
    static vector_storage<T, E::value> call(const vector<T, E, S>& input) {
        return input.storage();
    }
};

template<typename T, typename E, typename S>
struct vector_traits<vector<T, E, S>> {
    using value_type = T;
    using extent_type = E;
    using storage_type = S;
    using vector_type = vector<T, E, S>;
};

template<typename V>
using vector_value_type = typename into_vector_traits<V>::value_type;

template<typename V>
using vector_extent_type = typename into_vector_traits<V>::extent_type;

template<typename V>
static constexpr size_t vector_extent = vector_extent_type<V>::value;

template<typename V>
using into_vector_type = vector<vector_value_type<V>, vector_extent_type<V>>;

template<typename V>
using vector_storage_type = vector_storage<vector_value_type<V>, vector_extent<V>>;

template<typename... Vs>
using promoted_vector_value_type = promote_t<vector_value_type<Vs>...>;

template<typename V>
KERNEL_FLOAT_INLINE vector_storage_type<V> into_vector_storage(V&& input) {
    return into_vector_traits<V>::call(std::forward<V>(input));
}

}  // namespace kernel_float

#endif
#ifndef KERNEL_FLOAT_COMPLEX_TYPE_H
#define KERNEL_FLOAT_COMPLEX_TYPE_H




namespace kernel_float {

template<typename T>
struct alignas(2 * alignof(T)) complex_type_storage {
    T re;
    T im;
};

template<typename T>
struct complex_type: complex_type_storage<T> {
    using base_type = complex_type_storage<T>;

    template<typename T2>
    KERNEL_FLOAT_INLINE complex_type(complex_type<T2> that) : base_type(that.real(), that.imag()) {}

    KERNEL_FLOAT_INLINE
    complex_type(T real = {}, T imag = {}) : base_type(real, im) {}

    KERNEL_FLOAT_INLINE
    T real() const {
        return re;
    }

    KERNEL_FLOAT_INLINE
    T imag() const {
        return im;
    }

    KERNEL_FLOAT_INLINE
    T norm() const {
        return re * re + im * im;
    }

    KERNEL_FLOAT_INLINE
    complex_type conj() const {
        return {re, -im};
    }
};

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator+(complex_type<T> v) {
    return v;
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator+(complex_type<T> a, complex_type<T> b) {
    return {a.real() + b.real(), a.imag() + b.imag()};
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator+(T a, complex_type<T> b) {
    return {a + b.real(), b.imag()};
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator+(complex_type<T> a, T b) {
    return {a.real() + b, a.imag()};
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T>& operator+=(complex_type<T>& a, complex_type<T> b) {
    return (a = a + b);
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T>& operator+=(complex_type<T>& a, T b) {
    return (a = a + b);
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator-(complex_type<T> v) {
    return {-v.real(), -v.imag()};
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator-(complex_type<T> a, complex_type<T> b) {
    return {
        a.real() - b.real(), a.imag() - b.imag()
    }
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator-(T a, complex_type<T> b) {
    return {
        a - b.real(), -b.imag()
    }
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator-(complex_type<T> a, T b) {
    return {
        a.real() - b, a.imag()
    }
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T>& operator-=(complex_type<T>& a, complex_type<T> b) {
    return (a = a - b);
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T>& operator-=(complex_type<T>& a, T b) {
    return (a = a - b);
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator*(complex_type<T> a, complex_type<T> b) {
    return {
        a.real() * b.real() - a.imag() * b.imag(), a.real() * b.imag() + a.imag() * b.real()
    }
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator*(complex_type<T> a, T b) {
    return {a.real() * b, a.imag() * b};
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T>* operator*=(complex_type<T>& a, complex_type<T> b) {
    return (a = a * b);
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T>& operator*=(complex_type<T>& a, T b) {
    return (a = a * b);
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator*(T a, complex_type<T> b) {
    return {
        a * b.real(),
        a * b.imag(),
    };
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator/(complex_type<T> a, complex_type<T> b) {
    T normi = 1 / b.norm();

    return {
        (a.real() * b.real() + a.imag() * b.imag()) * normi,
        (a.imag() * b.real() - a.real() * b.imag()) * normi};
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator/(complex_type<T> a, T b) {
    return {a.real() * (1 / b), a.imag() * (1 / b)};
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> operator/(T a, complex_type<T> b) {
    T normi = 1 / b.norm();

    return {a * b.real() * normi, -a * b.imag() * normi};
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T>* operator/=(complex_type<T>& a, complex_type<T> b) {
    return (a = a / b);
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T>& operator/=(complex_type<T>& a, T b) {
    return (a = a / b);
}

template<typename T>
KERNEL_FLOAT_INLINE T real(complex_type<T> v) {
    return v.real();
}

template<typename T>
KERNEL_FLOAT_INLINE T imag(complex_type<T> v) {
    return v.imag();
}

template<typename T>
KERNEL_FLOAT_INLINE T abs(complex_type<T> v) {
    return hypot(v.real(), v.imag());
}

template<typename T>
KERNEL_FLOAT_INLINE T arg(complex_type<T> v) {
    return atan2(v.imag(), v.real());
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> sqrt(complex_type<T> v) {
    T radius = abs(v);
    T cosA = v.real() / radius;

    complex_type<T> out = {
        sqrt(radius * (cosA + T(1)) * T(.5)),
        sqrt(radius * (T(1) - cosA) * T(.5))};

    // signbit should be false if x.y is negative
    if (v.imag() < 0) {
        out = complex_type<T> {out.real, -out.im};
    }

    return out;
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> norm(complex_type<T> v) {
    return v.real() * v.real() + v.imag() * v.imag();
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> conj(complex_type<T> v) {
    return {v.real(), -v.imag()};
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> exp(complex_type<T> v) {
    // TODO: Handle nan and inf correctly
    T e = exp(v.real());
    T a = v.imag();
    return complex_type<T>(e * cos(a), e * sin(a));
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> log(complex_type<T> v) {
    return {log(abs(v)), arg(v)};
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> pow(complex_type<T> a, T b) {
    return exp(a * log(b));
}

template<typename T>
KERNEL_FLOAT_INLINE complex_type<T> pow(complex_type<T> a, complex_type<T> b) {
    return exp(a * log(b));
}

template<typename L, typename R>
struct promote_type<complex_type<L>, complex_type<R>> {
    using type = complex_type<promote_t<L, R>>;
};

template<typename L, typename R>
struct promote_type<complex_type<L>, R> {
    using type = complex_type<promote_t<L, R>>;
};

template<typename L, typename R>
struct promote_type<L, complex_type<R>> {
    using type = complex_type<promote_t<L, R>>;
};

}  // namespace kernel_float

#endif
#ifndef KERNEL_FLOAT_UNOPS_H
#define KERNEL_FLOAT_UNOPS_H



namespace kernel_float {
namespace detail {

template<typename F, size_t N, typename Output, typename... Args>
struct apply_impl {
    KERNEL_FLOAT_INLINE static vector_storage<Output, N>
    call(F fun, const vector_storage<Args, N>&... inputs) {
        vector_storage<Output, N> result;

#pragma unroll
        for (size_t i = 0; i < N; i++) {
            result.data()[i] = fun(inputs.data()[i]...);
        }

        return result;
    }
};
}  // namespace detail

template<typename F, typename V>
using map_type = vector<result_t<F, vector_value_type<V>>, vector_extent_type<V>>;

template<typename F, typename V>
KERNEL_FLOAT_INLINE map_type<F, V> map(F fun, const V& input) {
    using Input = vector_value_type<V>;
    using Output = result_t<F, Input>;
    return detail::apply_impl<F, vector_extent<V>, Output, Input>::call(
        fun,
        into_vector_storage(input));
}

#define KERNEL_FLOAT_DEFINE_UNARY(NAME, EXPR)                      \
    namespace ops {                                                \
    template<typename T>                                           \
    struct NAME {                                                  \
        KERNEL_FLOAT_INLINE T operator()(T input) {                \
            return T(EXPR);                                        \
        }                                                          \
    };                                                             \
    }                                                              \
    template<typename V>                                           \
    KERNEL_FLOAT_INLINE into_vector_type<V> NAME(const V& input) { \
        using F = ops::NAME<vector_value_type<V>>;                 \
        return map(F {}, input);                                   \
    }

#define KERNEL_FLOAT_DEFINE_UNARY_OP(NAME, OP, EXPR)                        \
    KERNEL_FLOAT_DEFINE_UNARY(NAME, EXPR)                                   \
    template<typename T, typename D>                                        \
    KERNEL_FLOAT_INLINE vector<T, D> operator OP(const vector<T, D>& vec) { \
        return NAME(vec);                                                   \
    }

KERNEL_FLOAT_DEFINE_UNARY_OP(negate, -, -input)
KERNEL_FLOAT_DEFINE_UNARY_OP(bit_not, ~, ~input)
KERNEL_FLOAT_DEFINE_UNARY_OP(logical_not, !, !bool(input))

#define KERNEL_FLOAT_DEFINE_UNARY_FUN(NAME) KERNEL_FLOAT_DEFINE_UNARY(NAME, ::NAME(input))

KERNEL_FLOAT_DEFINE_UNARY_FUN(acos)
KERNEL_FLOAT_DEFINE_UNARY_FUN(abs)
KERNEL_FLOAT_DEFINE_UNARY_FUN(acosh)
KERNEL_FLOAT_DEFINE_UNARY_FUN(asin)
KERNEL_FLOAT_DEFINE_UNARY_FUN(asinh)
KERNEL_FLOAT_DEFINE_UNARY_FUN(atan)
KERNEL_FLOAT_DEFINE_UNARY_FUN(atanh)
KERNEL_FLOAT_DEFINE_UNARY_FUN(cbrt)
KERNEL_FLOAT_DEFINE_UNARY_FUN(ceil)
KERNEL_FLOAT_DEFINE_UNARY_FUN(cos)
KERNEL_FLOAT_DEFINE_UNARY_FUN(cosh)
KERNEL_FLOAT_DEFINE_UNARY_FUN(cospi)
KERNEL_FLOAT_DEFINE_UNARY_FUN(erf)
KERNEL_FLOAT_DEFINE_UNARY_FUN(erfc)
KERNEL_FLOAT_DEFINE_UNARY_FUN(erfcinv)
KERNEL_FLOAT_DEFINE_UNARY_FUN(erfcx)
KERNEL_FLOAT_DEFINE_UNARY_FUN(erfinv)
KERNEL_FLOAT_DEFINE_UNARY_FUN(exp)
KERNEL_FLOAT_DEFINE_UNARY_FUN(exp10)
KERNEL_FLOAT_DEFINE_UNARY_FUN(exp2)
KERNEL_FLOAT_DEFINE_UNARY_FUN(expm1)
KERNEL_FLOAT_DEFINE_UNARY_FUN(fabs)
KERNEL_FLOAT_DEFINE_UNARY_FUN(floor)
KERNEL_FLOAT_DEFINE_UNARY_FUN(ilogb)
KERNEL_FLOAT_DEFINE_UNARY_FUN(lgamma)
KERNEL_FLOAT_DEFINE_UNARY_FUN(log)
KERNEL_FLOAT_DEFINE_UNARY_FUN(log10)
KERNEL_FLOAT_DEFINE_UNARY_FUN(logb)
KERNEL_FLOAT_DEFINE_UNARY_FUN(nearbyint)
KERNEL_FLOAT_DEFINE_UNARY_FUN(normcdf)
KERNEL_FLOAT_DEFINE_UNARY_FUN(rcbrt)
KERNEL_FLOAT_DEFINE_UNARY_FUN(sin)
KERNEL_FLOAT_DEFINE_UNARY_FUN(sinh)
KERNEL_FLOAT_DEFINE_UNARY_FUN(sqrt)
KERNEL_FLOAT_DEFINE_UNARY_FUN(tan)
KERNEL_FLOAT_DEFINE_UNARY_FUN(tanh)
KERNEL_FLOAT_DEFINE_UNARY_FUN(tgamma)
KERNEL_FLOAT_DEFINE_UNARY_FUN(trunc)
KERNEL_FLOAT_DEFINE_UNARY_FUN(y0)
KERNEL_FLOAT_DEFINE_UNARY_FUN(y1)
KERNEL_FLOAT_DEFINE_UNARY_FUN(yn)
KERNEL_FLOAT_DEFINE_UNARY_FUN(rint)
KERNEL_FLOAT_DEFINE_UNARY_FUN(rsqrt)
KERNEL_FLOAT_DEFINE_UNARY_FUN(round)
KERNEL_FLOAT_DEFINE_UNARY_FUN(signbit)
KERNEL_FLOAT_DEFINE_UNARY_FUN(isinf)
KERNEL_FLOAT_DEFINE_UNARY_FUN(isnan)

#if KERNEL_FLOAT_IS_DEVICE
#define KERNEL_FLOAT_DEFINE_UNARY_FAST(FUN_NAME, OP_NAME, FLOAT_FUN) \
    KERNEL_FLOAT_DEFINE_UNARY(FUN_NAME, ops::OP_NAME<T> {}(input))   \
    namespace ops {                                                  \
    template<>                                                       \
    struct OP_NAME<float> {                                          \
        KERNEL_FLOAT_INLINE float operator()(float input) {          \
            return FLOAT_FUN(input);                                 \
        }                                                            \
    };                                                               \
    }
#else
#define KERNEL_FLOAT_DEFINE_UNARY_FAST(FUN_NAME, OP_NAME, FLOAT_FUN) \
    KERNEL_FLOAT_DEFINE_UNARY(FUN_NAME, ops::OP_NAME<T> {}(input))
#endif

KERNEL_FLOAT_DEFINE_UNARY_FAST(fast_exp, exp, __expf)
KERNEL_FLOAT_DEFINE_UNARY_FAST(fast_log, log, __logf)
KERNEL_FLOAT_DEFINE_UNARY_FAST(fast_cos, cos, __cosf)
KERNEL_FLOAT_DEFINE_UNARY_FAST(fast_sin, sin, __sinf)
KERNEL_FLOAT_DEFINE_UNARY_FAST(fast_tan, tan, __tanf)

enum struct RoundingMode { ANY, DOWN, UP, NEAREST, TOWARD_ZERO };

namespace ops {
template<typename T, typename R, RoundingMode m = RoundingMode::ANY, typename = void>
struct cast;

template<typename T, typename R>
struct cast<T, R, RoundingMode::ANY> {
    KERNEL_FLOAT_INLINE R operator()(T input) noexcept {
        return R(input);
    }
};

template<typename T, RoundingMode m>
struct cast<T, T, m> {
    KERNEL_FLOAT_INLINE T operator()(T input) noexcept {
        return input;
    }
};

template<typename T>
struct cast<T, T, RoundingMode::ANY> {
    KERNEL_FLOAT_INLINE T operator()(T input) noexcept {
        return input;
    }
};
}  // namespace ops

template<typename R, RoundingMode Mode = RoundingMode::ANY, typename V>
KERNEL_FLOAT_INLINE vector<R, vector_extent_type<V>> cast(const V& input) {
    using F = ops::cast<vector_value_type<V>, R, Mode>;
    return map(F {}, input);
}
}  // namespace kernel_float

#endif  //KERNEL_FLOAT_UNOPS_H
#ifndef KERNEL_FLOAT_CAST_H
#define KERNEL_FLOAT_CAST_H




namespace kernel_float {
namespace detail {

template<typename A, typename B>
struct broadcast_extent_helper;

template<size_t N>
struct broadcast_extent_helper<extent<N>, extent<N>> {
    using type = extent<N>;
};

template<size_t N>
struct broadcast_extent_helper<extent<1>, extent<N>> {
    using type = extent<N>;
};

template<size_t N>
struct broadcast_extent_helper<extent<N>, extent<1>> {
    using type = extent<N>;
};

template<>
struct broadcast_extent_helper<extent<1>, extent<1>> {
    using type = extent<1>;
};

}  // namespace detail

template<typename A, typename B>
using broadcast_extent = typename detail::broadcast_extent_helper<A, B>::type;

template<typename A, typename B>
using broadcast_vector_extent_type = broadcast_extent<vector_extent_type<A>, vector_extent_type<B>>;

template<typename From, typename To>
static constexpr bool is_broadcastable = is_same<broadcast_extent<From, To>, To>;

template<typename V, typename To>
static constexpr bool is_vector_broadcastable = is_broadcastable<vector_extent_type<V>, To>;

namespace detail {

template<typename T, typename From, typename To>
struct broadcast_impl;

template<typename T, size_t N>
struct broadcast_impl<T, extent<1>, extent<N>> {
    KERNEL_FLOAT_INLINE static vector_storage<T, N> call(const vector_storage<T, 1>& input) {
        vector_storage<T, N> output;
        for (size_t i = 0; i < N; i++) {
            output.data()[i] = input.data()[0];
        }
        return output;
    }
};

template<typename T, size_t N>
struct broadcast_impl<T, extent<N>, extent<N>> {
    KERNEL_FLOAT_INLINE static vector_storage<T, N> call(vector_storage<T, N> input) {
        return input;
    }
};

}  // namespace detail

template<size_t N, typename V>
KERNEL_FLOAT_INLINE vector<vector_value_type<V>, extent<N>>
broadcast(const V& input, extent<N> new_size = {}) {
    using T = vector_value_type<V>;
    return detail::broadcast_impl<T, vector_extent_type<V>, extent<N>>::call(
        into_vector_storage(input));
}

template<typename V, typename R>
KERNEL_FLOAT_INLINE vector<vector_value_type<V>, vector_extent_type<R>>
broadcast_like(const V& input, const R&) {
    using T = vector_value_type<V>;
    return detail::broadcast_impl<T, vector_extent_type<V>, vector_extent_type<R>>::call(
        into_vector_storage(input));
}

template<size_t N, typename T>
KERNEL_FLOAT_INLINE vector<T, extent<N>> fill(T value = {}, extent<N> = {}) {
    vector_storage<T, 1> input = {value};
    return detail::broadcast_impl<T, extent<1>, extent<N>>::call(input);
}

template<typename T, size_t N>
KERNEL_FLOAT_INLINE vector<T, extent<N>> zeros(extent<N> = {}) {
    vector_storage<T, 1> input = {T {}};
    return detail::broadcast_impl<T, extent<1>, extent<N>>::call(input);
}

template<typename T, size_t N>
KERNEL_FLOAT_INLINE vector<T, extent<N>> ones(extent<N> = {}) {
    vector_storage<T, 1> input = {T {1}};
    return detail::broadcast_impl<T, extent<1>, extent<N>>::call(input);
}

template<typename V, typename T = vector_value_type<V>, typename E = vector_extent_type<V>>
KERNEL_FLOAT_INLINE vector<T, E> zeros_like(const V&) {
    return zeros<T>(E {});
}

template<typename V, typename T = vector_value_type<V>, typename E = vector_extent_type<V>>
KERNEL_FLOAT_INLINE vector<T, E> ones_like(const V&) {
    return ones<T>(E {});
}

namespace detail {
template<typename T, typename E, typename T2, typename E2, RoundingMode M = RoundingMode::ANY>
struct convert_helper {
    KERNEL_FLOAT_INLINE
    static vector_storage<T2, E2::value> call(vector_storage<T, E::value> input) {
        using F = ops::cast<T, T2, M>;
        vector_storage<T2, E::value> intermediate =
            detail::apply_impl<F, E::value, T2, T>::call(F {}, input);
        return detail::broadcast_impl<T2, E, E2>::call(intermediate);
    }
};

template<typename T, typename E, RoundingMode M>
struct convert_helper<T, E, T, E, M> {
    KERNEL_FLOAT_INLINE
    static vector_storage<T, E::value> call(vector_storage<T, E::value> input) {
        return input;
    }
};

template<typename T, typename E, typename E2, RoundingMode M>
struct convert_helper<T, E, T, E2, M> {
    KERNEL_FLOAT_INLINE
    static vector_storage<T, E2::value> call(vector_storage<T, E::value> input) {
        return detail::broadcast_impl<T, E, E2>::call(input);
    }
};

template<typename T, typename E, typename T2, RoundingMode M>
struct convert_helper<T, E, T2, E, M> {
    KERNEL_FLOAT_INLINE
    static vector_storage<T2, E::value> call(vector_storage<T, E::value> input) {
        using F = ops::cast<T, T2, M>;
        return detail::apply_impl<F, E::value, T2, T>::call(F {}, input);
    }
};
}  // namespace detail

template<typename R, size_t N, RoundingMode M = RoundingMode::ANY, typename V>
KERNEL_FLOAT_INLINE vector_storage<R, N> convert_storage(const V& input, extent<N> new_size = {}) {
    return detail::convert_helper<vector_value_type<V>, vector_extent_type<V>, R, extent<N>, M>::
        call(into_vector_storage(input));
}

/**
 * Cast the values of the given input vector to type `R` and then broadcast the result to the given size `N`.
 */
template<typename R, size_t N, RoundingMode M = RoundingMode::ANY, typename V>
KERNEL_FLOAT_INLINE vector<R, extent<N>> convert(const V& input, extent<N> new_size = {}) {
    return convert_storage(input);
}

}  // namespace kernel_float

#endif
#ifndef KERNEL_FLOAT_BINOPS_H
#define KERNEL_FLOAT_BINOPS_H




namespace kernel_float {

template<typename F, typename L, typename R>
using zip_type = vector<
    result_t<F, vector_value_type<L>, vector_value_type<R>>,
    broadcast_vector_extent_type<L, R>>;

template<typename F, typename L, typename R>
KERNEL_FLOAT_INLINE zip_type<F, L, R> zip(F fun, const L& left, const R& right) {
    using A = vector_value_type<L>;
    using B = vector_value_type<R>;
    using O = result_t<F, A, B>;
    using E = broadcast_vector_extent_type<L, R>;

    return detail::apply_impl<F, E::value, O, A, B>::call(
        fun,
        broadcast<E>(left).storage(),
        broadcast<E>(right).storage());
}

template<typename F, typename L, typename R>
using zip_common_type = vector<
    result_t<F, promoted_vector_value_type<L, R>, promoted_vector_value_type<L, R>>,
    broadcast_vector_extent_type<L, R>>;

template<typename F, typename L, typename R>
KERNEL_FLOAT_INLINE zip_common_type<F, L, R> zip_common(F fun, const L& left, const R& right) {
    using T = promoted_vector_value_type<L, R>;
    using O = result_t<F, T, T>;
    using E = broadcast_vector_extent_type<L, R>;

    return detail::apply_impl<F, E::value, O, T, T>::call(
        fun,
        detail::convert_helper<vector_value_type<L>, vector_extent_type<L>, T, E>::call(
            into_vector_storage(left)),
        detail::convert_helper<vector_value_type<R>, vector_extent_type<R>, T, E>::call(
            into_vector_storage(right)));
}

#define KERNEL_FLOAT_DEFINE_BINARY(NAME, EXPR)                                             \
    namespace ops {                                                                        \
    template<typename T>                                                                   \
    struct NAME {                                                                          \
        KERNEL_FLOAT_INLINE T operator()(T left, T right) {                                \
            return T(EXPR);                                                                \
        }                                                                                  \
    };                                                                                     \
    }                                                                                      \
    template<typename L, typename R, typename C = promoted_vector_value_type<L, R>>        \
    KERNEL_FLOAT_INLINE zip_common_type<ops::NAME<C>, L, R> NAME(L&& left, R&& right) {    \
        return zip_common(ops::NAME<C> {}, std::forward<L>(left), std::forward<R>(right)); \
    }

#define KERNEL_FLOAT_DEFINE_BINARY_OP(NAME, OP)                                                   \
    KERNEL_FLOAT_DEFINE_BINARY(NAME, left OP right)                                               \
    template<typename L, typename R, typename C = promote_t<L, R>, typename E1, typename E2>      \
    KERNEL_FLOAT_INLINE zip_common_type<ops::NAME<C>, vector<L, E1>, vector<R, E2>> operator OP(  \
        const vector<L, E1>& left,                                                                \
        const vector<R, E2>& right) {                                                             \
        return zip_common(ops::NAME<C> {}, left, right);                                          \
    }                                                                                             \
    template<typename L, typename R, typename C = promote_t<L, vector_value_type<R>>, typename E> \
    KERNEL_FLOAT_INLINE zip_common_type<ops::NAME<C>, vector<L, E>, R> operator OP(               \
        const vector<L, E>& left,                                                                 \
        const R& right) {                                                                         \
        return zip_common(ops::NAME<C> {}, left, right);                                          \
    }                                                                                             \
    template<typename L, typename R, typename C = promote_t<vector_value_type<L>, R>, typename E> \
    KERNEL_FLOAT_INLINE zip_common_type<ops::NAME<C>, L, vector<R, E>> operator OP(               \
        const L& left,                                                                            \
        const vector<R, E>& right) {                                                              \
        return zip_common(ops::NAME<C> {}, left, right);                                          \
    }

KERNEL_FLOAT_DEFINE_BINARY_OP(add, +)
KERNEL_FLOAT_DEFINE_BINARY_OP(subtract, -)
KERNEL_FLOAT_DEFINE_BINARY_OP(divide, /)
KERNEL_FLOAT_DEFINE_BINARY_OP(multiply, *)
KERNEL_FLOAT_DEFINE_BINARY_OP(modulo, %)

KERNEL_FLOAT_DEFINE_BINARY_OP(equal_to, ==)
KERNEL_FLOAT_DEFINE_BINARY_OP(not_equal_to, !=)
KERNEL_FLOAT_DEFINE_BINARY_OP(less, <)
KERNEL_FLOAT_DEFINE_BINARY_OP(less_equal, <=)
KERNEL_FLOAT_DEFINE_BINARY_OP(greater, >)
KERNEL_FLOAT_DEFINE_BINARY_OP(greater_equal, >=)

KERNEL_FLOAT_DEFINE_BINARY_OP(bit_and, &)
KERNEL_FLOAT_DEFINE_BINARY_OP(bit_or, |)
KERNEL_FLOAT_DEFINE_BINARY_OP(bit_xor, ^)

// clang-format off
template<template<typename> typename F, typename T, typename E, typename R>
static constexpr bool is_vector_assign_allowed =
        is_vector_broadcastable<R, E> &&
        is_implicit_convertible<
            result_t<
                F<promote_t<T, vector_value_type<R>>>,
                    T,
                    vector_value_type<R>
                >,
            T
        >;
// clang-format on

#define KERNEL_FLOAT_DEFINE_BINARY_ASSIGN_OP(NAME, OP)                               \
    template<                                                                        \
        typename T,                                                                  \
        typename E,                                                                  \
        typename R,                                                                  \
        typename = enabled_t<is_vector_assign_allowed<ops::NAME, T, E, R>>>          \
    KERNEL_FLOAT_INLINE vector<T, E>& operator OP(vector<T, E>& lhs, const R& rhs) { \
        using F = ops::NAME<T>;                                                      \
        lhs = zip_common(F {}, lhs, rhs);                                            \
        return lhs;                                                                  \
    }

KERNEL_FLOAT_DEFINE_BINARY_ASSIGN_OP(add, +=)
KERNEL_FLOAT_DEFINE_BINARY_ASSIGN_OP(subtract, -=)
KERNEL_FLOAT_DEFINE_BINARY_ASSIGN_OP(divide, /=)
KERNEL_FLOAT_DEFINE_BINARY_ASSIGN_OP(multiply, *=)
KERNEL_FLOAT_DEFINE_BINARY_ASSIGN_OP(modulo, %=)
KERNEL_FLOAT_DEFINE_BINARY_ASSIGN_OP(bit_and, &=)
KERNEL_FLOAT_DEFINE_BINARY_ASSIGN_OP(bit_or, |=)
KERNEL_FLOAT_DEFINE_BINARY_ASSIGN_OP(bit_xor, ^=)

#define KERNEL_FLOAT_DEFINE_BINARY_FUN(NAME) KERNEL_FLOAT_DEFINE_BINARY(NAME, ::NAME(left, right))

KERNEL_FLOAT_DEFINE_BINARY_FUN(min)
KERNEL_FLOAT_DEFINE_BINARY_FUN(max)
KERNEL_FLOAT_DEFINE_BINARY_FUN(copysign)
KERNEL_FLOAT_DEFINE_BINARY_FUN(hypot)
KERNEL_FLOAT_DEFINE_BINARY_FUN(modf)
KERNEL_FLOAT_DEFINE_BINARY_FUN(nextafter)
KERNEL_FLOAT_DEFINE_BINARY_FUN(pow)
KERNEL_FLOAT_DEFINE_BINARY_FUN(remainder)

#if KERNEL_FLOAT_CUDA_DEVICE
KERNEL_FLOAT_DEFINE_BINARY_FUN(rhypot)
#endif

#if KERNEL_FLOAT_IS_DEVICE
#define KERNEL_FLOAT_DEFINE_BINARY_FAST(FUN_NAME, OP_NAME, FLOAT_FUN)     \
    KERNEL_FLOAT_DEFINE_BINARY(FUN_NAME, ops::OP_NAME<T> {}(left, right)) \
    namespace ops {                                                       \
    template<>                                                            \
    struct OP_NAME<float> {                                               \
        KERNEL_FLOAT_INLINE float operator()(float left, float right) {   \
            return FLOAT_FUN(left, right);                                \
        }                                                                 \
    };                                                                    \
    }
#else
#define KERNEL_FLOAT_DEFINE_BINARY_FAST(FUN_NAME, OP_NAME, FLOAT_FUN) \
    KERNEL_FLOAT_DEFINE_BINARY(FUN_NAME, ops::OP_NAME<T> {}(left, right))
#endif

KERNEL_FLOAT_DEFINE_BINARY_FAST(fast_div, divide, __fdividef)
KERNEL_FLOAT_DEFINE_BINARY_FAST(fast_pow, pow, __powf)

namespace ops {
template<>
struct add<bool> {
    KERNEL_FLOAT_INLINE bool operator()(bool left, bool right) {
        return left || right;
    }
};

template<>
struct multiply<bool> {
    KERNEL_FLOAT_INLINE bool operator()(bool left, bool right) {
        return left && right;
    }
};

template<>
struct bit_and<float> {
    KERNEL_FLOAT_INLINE float operator()(float left, float right) {
        return float(bool(left) && bool(right));
    }
};

template<>
struct bit_or<float> {
    KERNEL_FLOAT_INLINE float operator()(float left, float right) {
        return float(bool(left) || bool(right));
    }
};

template<>
struct bit_xor<float> {
    KERNEL_FLOAT_INLINE float operator()(float left, float right) {
        return float(bool(left) ^ bool(right));
    }
};

template<>
struct bit_and<double> {
    KERNEL_FLOAT_INLINE double operator()(double left, double right) {
        return double(bool(left) && bool(right));
    }
};

template<>
struct bit_or<double> {
    KERNEL_FLOAT_INLINE double operator()(double left, double right) {
        return double(bool(left) || bool(right));
    }
};

template<>
struct bit_xor<double> {
    KERNEL_FLOAT_INLINE double operator()(double left, double right) {
        return double(bool(left) ^ bool(right));
    }
};
};  // namespace ops

}  // namespace kernel_float

#endif
#ifndef KERNEL_FLOAT_CONSTANT
#define KERNEL_FLOAT_CONSTANT



namespace kernel_float {

template<typename T = double>
struct constant {
    KERNEL_FLOAT_INLINE
    constexpr constant(T value = {}) : value_(value) {}

    KERNEL_FLOAT_INLINE
    constexpr T get() const {
        return value_;
    }

    KERNEL_FLOAT_INLINE
    constexpr operator T() const {
        return value_;
    }

  private:
    T value_;
};

template<typename T = double>
KERNEL_FLOAT_INLINE constexpr constant<T> make_constant(T value) {
    return value;
}

template<typename L, typename R>
struct promote_type<constant<L>, constant<R>> {
    using type = typename promote_type<L, R>::type;
};

template<typename L, typename R>
struct promote_type<constant<L>, R> {
    using type = typename promote_type<L, R>::type;
};

template<typename L, typename R>
struct promote_type<L, constant<R>> {
    using type = typename promote_type<L, R>::type;
};

namespace ops {
template<typename T, typename R, RoundingMode m>
struct cast<constant<T>, R, m> {
    KERNEL_FLOAT_INLINE R operator()(const T& input) noexcept {
        return cast<T, R, m> {}(input);
    }
};
}  // namespace ops

}  // namespace kernel_float

#endif
#ifndef KERNEL_FLOAT_REDUCE_H
#define KERNEL_FLOAT_REDUCE_H



namespace kernel_float {
namespace detail {
template<typename F, size_t N, typename T, typename = void>
struct reduce_helper {
    KERNEL_FLOAT_INLINE static T call(F fun, const vector_storage<T, N>& input) {
        return call(fun, input, make_index_sequence<N> {});
    }

  private:
    template<size_t... Is>
    KERNEL_FLOAT_INLINE static T
    call(F fun, const vector_storage<T, N>& input, index_sequence<0, Is...>) {
        T result = input.data()[0];
#pragma unroll
        for (size_t i = 1; i < N; i++) {
            result = fun(result, input.data()[i]);
        }
        return result;
    }
};
}  // namespace detail

/**
 * Reduce the elements of the given vector ``input`` into a single value using
 * the function ``fun``. This function should be a binary function that takes
 * two elements and returns one element. The order in which the elements
 * are reduced is not specified and depends on the reduction function and
 * the vector type.
 *
 * Example
 * =======
 * ```
 * vec<int, 3> x = {5, 2, 1};
 * int y = reduce(x, [](int a, int b) { return a + b; }); // returns 5+2+1=8
 * ```
 */
template<typename F, typename V>
KERNEL_FLOAT_INLINE vector_value_type<V> reduce(F fun, const V& input) {
    return detail::reduce_helper<F, vector_extent<V>, vector_value_type<V>>::call(
        fun,
        into_vector_storage(input));
}

/**
 * Find the minimum element in the given vector ``input``.
 *
 * Example
 * =======
 * ```
 * vec<int, 5> x = {5, 0, 2, 1, 0};
 * int y = min(x);  // Returns 0
 * ```
 */
template<typename V, typename T = vector_value_type<V>>
KERNEL_FLOAT_INLINE T min(const V& input) {
    return reduce(ops::min<T> {}, input);
}

/**
 * Find the maximum element in the given vector ``input``.
 *
 * Example
 * =======
 * ```
 * vec<int, 5> x = {5, 0, 2, 1, 0};
 * int y = max(x);  // Returns 5
 * ```
 */
template<typename V, typename T = vector_value_type<V>>
KERNEL_FLOAT_INLINE T max(const V& input) {
    return reduce(ops::max<T> {}, input);
}

/**
 * Sum the items in the given vector ``input``.
 *
 * Example
 * =======
 * ```
 * vec<int, 5> x = {5, 0, 2, 1, 0};
 * int y = sum(x);  // Returns 8
 * ```
 */
template<typename V, typename T = vector_value_type<V>>
KERNEL_FLOAT_INLINE T sum(const V& input) {
    return reduce(ops::add<T> {}, input);
}

/**
 * Compute the dot product of the given vectors ``left`` and ``right``
 *
 * Example
 * =======
 * ```
 * vec<int, 3> x = {1, 2, 3};
 * vec<int, 3> y = {4, 5, 6};
 * int y = dot(x, y);  // Returns 1*4+2*5+3*6 = 32
 * ```
 */
template<typename L, typename R, typename T = promoted_vector_value_type<L, R>>
KERNEL_FLOAT_INLINE T dot(const L& left, const R& right) {
    return reduce(ops::add<T> {}, zip_common(ops::multiply<T> {}, left, right));
}

/**
 * Multiply the items in the given vector ``input``.
 *
 * Example
 * =======
 * ```
 * vec<int, 5> x = {5, 0, 2, 1, 0};
 * int y = sum(x);  // Returns 5*0*2*1*0 = 0
 * ```
 */
template<typename V, typename T = vector_value_type<V>>
KERNEL_FLOAT_INLINE T product(const V& input) {
    return reduce(ops::multiply<T> {}, input);
}

/**
 * Check if all elements in the given vector ``input`` are non-zero. An element ``v`` is considered
 * non-zero if ``bool(v)==true``.
 */
template<typename V>
KERNEL_FLOAT_INLINE bool all(const V& input) {
    return reduce(ops::bit_and<bool> {}, cast<bool>(input));
}

/**
 * Check if any element in the given vector ``input`` is non-zero. An element ``v`` is considered
 * non-zero if ``bool(v)==true``.
 */
template<typename V>
KERNEL_FLOAT_INLINE bool any(const V& input) {
    return reduce(ops::bit_or<bool> {}, cast<bool>(input));
}

/**
 * Count the number of non-zero items in the given vector ``input``. An element ``v`` is considered
 * non-zero if ``bool(v)==true``.
 *
 * Example
 * =======
 * ```
 * vec<int, 5> x = {5, 0, 2, 1, 0};
 * int y = count(x);  // Returns 3 (5, 2, 1 are non-zero)
 * ```
 */
template<typename V>
KERNEL_FLOAT_INLINE int count(const V& input) {
    return sum(cast<int>(cast<bool>(input)));
}
}  // namespace kernel_float

#endif  //KERNEL_FLOAT_REDUCE_H
#ifndef KERNEL_FLOAT_TRIOPS_H
#define KERNEL_FLOAT_TRIOPS_H




namespace kernel_float {

namespace ops {
template<typename T>
struct conditional {
    KERNEL_FLOAT_INLINE T operator()(bool cond, T true_value, T false_value) {
        if (cond) {
            return true_value;
        } else {
            return false_value;
        }
    }
};
}  // namespace ops

/**
 * Return elements chosen from `true_values` and `false_values` depending on `cond`.
 *
 * This function broadcasts all arguments to the same size and it promotes the values of `true_values` and
 * `false_values` into the same type. Next, it casts the values of `cond` to booleans and returns a vector where
 * the values are taken from `true_values` if the condition is true and `false_values` otherwise.
 *
 * @param cond The condition used for selection.
 * @param true_values The vector of values to choose from when the condition is true.
 * @param false_values The vector of values to choose from when the condition is false.
 * @return A vector containing selected elements as per the condition.
 */
template<
    typename C,
    typename L,
    typename R,
    typename T = promoted_vector_value_type<L, R>,
    typename E = broadcast_extent<vector_extent_type<C>, broadcast_vector_extent_type<L, R>>>
KERNEL_FLOAT_INLINE vector<T, E> where(const C& cond, const L& true_values, const R& false_values) {
    using F = ops::conditional<T>;

    return detail::apply_impl<F, E::value, T, bool, T, T>::call(
        F {},
        detail::convert_helper<vector_value_type<C>, vector_extent_type<C>, bool, E>::call(
            into_vector_storage(cond)),
        detail::convert_helper<vector_value_type<L>, vector_extent_type<L>, T, E>::call(
            into_vector_storage(true_values)),
        detail::convert_helper<vector_value_type<R>, vector_extent_type<R>, T, E>::call(
            into_vector_storage(false_values)));
}

/**
 * Selects elements from `true_values` depending on `cond`.
 *
 * This function returns a vector where the values are taken from `true_values` where `cond` is `true` and `0` where
 * `cond is `false`.
 *
 * @param cond The condition used for selection.
 * @param true_values The vector of values to choose from when the condition is true.
 * @return A vector containing selected elements as per the condition.
 */
template<
    typename C,
    typename L,
    typename T = vector_value_type<L>,
    typename E = broadcast_extent<vector_extent_type<C>, vector_extent_type<L>>>
KERNEL_FLOAT_INLINE vector<T, E> where(const C& cond, const L& true_values) {
    vector<T, extent<1>> false_values = T {};
    return where(cond, true_values, false_values);
}

/**
 * Returns a vector where the values are `T(1)` where `cond` is `true` and `T(0)` where `cond` is `false`.
 *
 * @param cond The condition used for selection.
 * @return A vector containing elements as per the condition.
 */
template<typename T = bool, typename C, typename E = vector_extent_type<C>>
KERNEL_FLOAT_INLINE vector<T, E> where(const C& cond) {
    vector<T, extent<1>> true_values = T {true};
    vector<T, extent<1>> false_values = T {false};
    return where(cond, true_values, false_values);
}

namespace ops {
template<typename T>
struct fma {
    KERNEL_FLOAT_INLINE T operator()(T a, T b, T c) {
        return a + b * c;
    }
};

#if KERNEL_FLOAT_IS_DEVICE
template<>
struct fma<float> {
    KERNEL_FLOAT_INLINE float operator()(float a, float b, float c) {
        return __fmaf_rn(a, b, c);
    }
};

template<>
struct fma<double> {
    KERNEL_FLOAT_INLINE double operator()(double a, double b, double c) {
        return __fma_rn(a, b, c);
    }
};
#endif
}  // namespace ops

/**
 * Computes the result of `a * b + c`. This is done in a single operation if possible.
 */
template<
    typename A,
    typename B,
    typename C,
    typename T = promoted_vector_value_type<A, B, C>,
    typename E = broadcast_extent<vector_extent_type<A>, broadcast_vector_extent_type<B, C>>>
KERNEL_FLOAT_INLINE vector<T, E> fma(const A& a, const B& b, const C& c) {
    using F = ops::fma<T>;

    return detail::apply_impl<F, E::value, T, T, T, T>::call(
        F {},
        detail::convert_helper<vector_value_type<A>, vector_extent_type<A>, T, E>::call(
            into_vector_storage(a)),
        detail::convert_helper<vector_value_type<B>, vector_extent_type<B>, T, E>::call(
            into_vector_storage(b)),
        detail::convert_helper<vector_value_type<C>, vector_extent_type<C>, T, E>::call(
            into_vector_storage(c)));
}

}  // namespace kernel_float

#endif  //KERNEL_FLOAT_TRIOPS_H
#ifndef KERNEL_FLOAT_VECTOR_H
#define KERNEL_FLOAT_VECTOR_H







namespace kernel_float {

template<typename T, typename E, class S>
struct vector: S {
    using value_type = T;
    using extent_type = E;
    using storage_type = S;

    // Copy another `vector<T, E>`
    vector(const vector&) = default;

    // Copy anything of type `storage_type`
    KERNEL_FLOAT_INLINE
    vector(const storage_type& storage) : storage_type(storage) {}

    // Copy anything of type `storage_type`
    KERNEL_FLOAT_INLINE
    vector(const value_type& input = {}) :
        storage_type(detail::broadcast_impl<T, extent<1>, E>::call(input)) {}

    // For all other arguments, we convert it using `convert_storage` according to broadcast rules
    template<typename U, enabled_t<is_implicit_convertible<vector_value_type<U>, T>, int> = 0>
    KERNEL_FLOAT_INLINE vector(U&& input) : storage_type(convert_storage<T, E::size>(input)) {}

    template<typename U, enabled_t<!is_implicit_convertible<vector_value_type<U>, T>, int> = 0>
    KERNEL_FLOAT_INLINE explicit vector(U&& input) :
        storage_type(convert_storage<T, E::size>(input)) {}

    // List of `N` (where N >= 2), simply pass forward to the storage
    template<
        typename A,
        typename B,
        typename... Rest,
        typename = enabled_t<sizeof...(Rest) + 2 == E::size>>
    KERNEL_FLOAT_INLINE vector(const A& a, const B& b, const Rest&... rest) :
        storage_type {a, b, rest...} {}

    KERNEL_FLOAT_INLINE
    static constexpr size_t size() {
        return E::size;
    }

    KERNEL_FLOAT_INLINE
    storage_type& storage() {
        return *this;
    }

    KERNEL_FLOAT_INLINE
    const storage_type& storage() const {
        return *this;
    }

    KERNEL_FLOAT_INLINE
    const T* cdata() const {
        return this->data();
    }

    KERNEL_FLOAT_INLINE
    T* begin() {
        return this->data();
    }

    KERNEL_FLOAT_INLINE
    const T* begin() const {
        return this->data();
    }

    KERNEL_FLOAT_INLINE
    const T* cbegin() const {
        return this->data();
    }

    KERNEL_FLOAT_INLINE
    T* end() {
        return this->data() + size();
    }

    KERNEL_FLOAT_INLINE
    const T* end() const {
        return this->data() + size();
    }

    KERNEL_FLOAT_INLINE
    const T* cend() const {
        return this->data() + size();
    }

    KERNEL_FLOAT_INLINE
    T& at(size_t x) {
        return *(this->data() + x);
    }

    KERNEL_FLOAT_INLINE
    const T& at(size_t x) const {
        return *(this->data() + x);
    }

    KERNEL_FLOAT_INLINE
    T get(size_t x) const {
        return at(x);
    }

    KERNEL_FLOAT_INLINE
    void set(size_t x, T value) {
        at(x) = std::move(value);
    }

    KERNEL_FLOAT_INLINE
    T& operator[](size_t x) {
        return at(x);
    }

    KERNEL_FLOAT_INLINE
    const T& operator[](size_t x) const {
        return at(x);
    }

    KERNEL_FLOAT_INLINE
    T& operator()(size_t x) {
        return at(x);
    }

    KERNEL_FLOAT_INLINE
    const T& operator()(size_t x) const {
        return at(x);
    }

    template<typename R, RoundingMode Mode = RoundingMode::ANY>
    KERNEL_FLOAT_INLINE vector<T, E2> cast() const {
        return kernel_float::cast<R, Mode>(*this);
    }

    template<size_t N>
    KERNEL_FLOAT_INLINE vector<T, extent<N>> broadcast(extent<N> new_size = {}) const {
        return kernel_float::broadcast(*this, new_size);
    }

    template<typename F>
    KERNEL_FLOAT_INLINE vector<result_t<F, T>, E> map(F fun = {}) const {
        return kernel_float::map(fun, *this);
    }

    template<typename F>
    KERNEL_FLOAT_INLINE T reduce(F fun = {}) const {
        return kernel_float::reduce(fun, *this);
    }

  private:
    storage_type storage_;
};

#define KERNEL_FLOAT_DEFINE_VECTOR_TYPE(T, T1, T2, T3, T4) \
    template<>                                             \
    struct into_vector_traits<::T2> {                      \
        using value_type = T;                              \
        using extent_type = extent<2>;                     \
                                                           \
        KERNEL_FLOAT_INLINE                                \
        static vector_storage<T, 2> call(::T2 v) {         \
            return {v.x, v.y};                             \
        }                                                  \
    };                                                     \
                                                           \
    template<>                                             \
    struct into_vector_traits<::T3> {                      \
        using value_type = T;                              \
        using extent_type = extent<3>;                     \
                                                           \
        KERNEL_FLOAT_INLINE                                \
        static vector_storage<T, 3> call(::T3 v) {         \
            return {v.x, v.y, v.z};                        \
        }                                                  \
    };                                                     \
                                                           \
    template<>                                             \
    struct into_vector_traits<::T4> {                      \
        using value_type = T;                              \
        using extent_type = extent<4>;                     \
                                                           \
        KERNEL_FLOAT_INLINE                                \
        static vector_storage<T, 4> call(::T4 v) {         \
            return {v.x, v.y, v.z, v.w};                   \
        }                                                  \
    };

template<typename V>
KERNEL_FLOAT_INLINE into_vector_type<V> into_vector(V&& input) {
    return into_vector_traits<V>::call(std::forward<V>(input));
}

KERNEL_FLOAT_DEFINE_VECTOR_TYPE(char, char1, char2, char3, char4)
KERNEL_FLOAT_DEFINE_VECTOR_TYPE(short, short1, short2, short3, short4)
KERNEL_FLOAT_DEFINE_VECTOR_TYPE(int, int1, int2, int3, int4)
KERNEL_FLOAT_DEFINE_VECTOR_TYPE(long, long1, long2, long3, long4)
KERNEL_FLOAT_DEFINE_VECTOR_TYPE(long long, longlong1, longlong2, longlong3, longlong4)

KERNEL_FLOAT_DEFINE_VECTOR_TYPE(unsigned char, uchar1, uchar2, uchar3, uchar4)
KERNEL_FLOAT_DEFINE_VECTOR_TYPE(unsigned short, ushort1, ushort2, ushort3, ushort4)
KERNEL_FLOAT_DEFINE_VECTOR_TYPE(unsigned int, uint1, uint2, uint3, uint4)
KERNEL_FLOAT_DEFINE_VECTOR_TYPE(unsigned long, ulong1, ulong2, ulong3, ulong4)
KERNEL_FLOAT_DEFINE_VECTOR_TYPE(unsigned long long, ulonglong1, ulonglong2, ulonglong3, ulonglong4)

KERNEL_FLOAT_DEFINE_VECTOR_TYPE(float, float1, float2, float3, float4)
KERNEL_FLOAT_DEFINE_VECTOR_TYPE(double, double1, double2, double3, double4)

template<typename T>
using scalar = vector<T, extent<1>>;

template<typename T, size_t N>
using vec = vector<T, extent<N>>;

template<typename... Args>
KERNEL_FLOAT_INLINE vec<promote_t<Args...>, sizeof...(Args)> make_vec(Args&&... args) {
    using T = promote_t<Args...>;
    return vector_storage<T, sizeof...(Args)> {T {args}...};
};

}  // namespace kernel_float

#endif
#ifndef KERNEL_FLOAT_FP16_H
#define KERNEL_FLOAT_FP16_H



#if KERNEL_FLOAT_FP16_AVAILABLE
#include <cuda_fp16.h>



namespace kernel_float {
KERNEL_FLOAT_DEFINE_PROMOTED_FLOAT(__half)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(float, __half)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(double, __half)

template<>
struct into_vector_traits<__half2> {
    using value_type = __half;
    using extent_type = extent<2>;

    KERNEL_FLOAT_INLINE
    static vector_storage<__half, 2> call(__half2 input) {
        return {input.x, input.y};
    }
};

namespace detail {
template<typename F>
struct map_halfx2 {
    KERNEL_FLOAT_INLINE
    static __half2 call(F fun, __half2 input) {
        __half a = fun(input.x);
        __half b = fun(input.y);
        return {a, b};
    }
};

template<typename F>
struct zip_halfx2 {
    KERNEL_FLOAT_INLINE
    static __half2 call(F fun, __half2 left, __half2 right) {
        __half a = fun(left.x, left.y);
        __half b = fun(right.y, right.y);
        return {a, b};
    }
};

template<typename F, size_t N>
struct apply_impl<F, N, __half, __half> {
    KERNEL_FLOAT_INLINE static vector_storage<__half, N>
    call(F fun, const vector_storage<__half, N>& input) {
        vector_storage<__half, N> result;

#pragma unroll
        for (size_t i = 0; i < N; i += 2) {
            __half2 a = {input.data()[i], input.data()[i + 1]};
            __half2 b = map_halfx2<F>::call(fun, a);
            result.data()[i + 0] = b.x;
            result.data()[i + 1] = b.y;
        }

        if (N % 2 != 0) {
            result.data()[N - 1] = fun(input.data()[N - 1]);
        }

        return result;
    }
};

template<typename F, size_t N>
struct apply_impl<F, N, __half, __half, __half> {
    KERNEL_FLOAT_INLINE static vector_storage<__half, N>
    call(F fun, const vector_storage<__half, N>& left, const vector_storage<__half, N>& right) {
        vector_storage<__half, N> result;
#pragma unroll
        for (size_t i = 0; i < N; i += 2) {
            __half2 a = {left.data()[i], left.data()[i + 1]};
            __half2 b = {right.data()[i], right.data()[i + 1]};
            __half2 c = zip_halfx2<F>::call(fun, a, b);
            result.data()[i + 0] = c.x;
            result.data()[i + 1] = c.y;
        }

        if (N % 2 != 0) {
            result.data()[N - 1] = fun(left.data()[N - 1], right.data()[N - 1]);
        }

        return result;
    }
};

template<typename F, size_t N>
struct reduce_helper<F, N, __half, enabled_t<(N >= 2)>> {
    KERNEL_FLOAT_INLINE static __half call(F fun, const vector_storage<__half, N>& input) {
        __half2 accum = {input.data()[0], input.data()[1]};

#pragma unroll
        for (size_t i = 2; i < N; i += 2) {
            __half2 a = {input.data()[i], input.data()[i + 1]};
            accum = zip_halfx2<F>::call(fun, accum, a);
        }

        __half result = fun(accum.x, accum.y);

        if (N % 2 != 0) {
            result = fun(result, input.data()[N - 1]);
        }

        return result;
    }
};

};  // namespace detail

#if KERNEL_FLOAT_IS_DEVICE
#define KERNEL_FLOAT_FP16_UNARY_FUN(NAME, FUN1, FUN2)                               \
    namespace ops {                                                                 \
    template<>                                                                      \
    struct NAME<__half> {                                                           \
        KERNEL_FLOAT_INLINE __half operator()(__half input) {                       \
            return FUN1(input);                                                     \
        }                                                                           \
    };                                                                              \
    }                                                                               \
    namespace detail {                                                              \
    template<>                                                                      \
    struct map_halfx2<ops::NAME<__half>> {                                          \
        KERNEL_FLOAT_INLINE static __half2 call(ops::NAME<__half>, __half2 input) { \
            return FUN2(input);                                                     \
        }                                                                           \
    };                                                                              \
    }

KERNEL_FLOAT_FP16_UNARY_FUN(abs, ::__habs, ::__habs2)
KERNEL_FLOAT_FP16_UNARY_FUN(negate, ::__hneg, ::__hneg2)
KERNEL_FLOAT_FP16_UNARY_FUN(ceil, ::hceil, ::h2ceil)
KERNEL_FLOAT_FP16_UNARY_FUN(cos, ::hcos, ::h2cos)
KERNEL_FLOAT_FP16_UNARY_FUN(exp, ::hexp, ::h2exp)
KERNEL_FLOAT_FP16_UNARY_FUN(exp10, ::hexp10, ::h2exp10)
KERNEL_FLOAT_FP16_UNARY_FUN(floor, ::hfloor, ::h2floor)
KERNEL_FLOAT_FP16_UNARY_FUN(log, ::hlog, ::h2log)
KERNEL_FLOAT_FP16_UNARY_FUN(log10, ::hlog10, ::h2log2)
KERNEL_FLOAT_FP16_UNARY_FUN(rint, ::hrint, ::h2rint)
KERNEL_FLOAT_FP16_UNARY_FUN(rsqrt, ::hrsqrt, ::h2rsqrt)
KERNEL_FLOAT_FP16_UNARY_FUN(sin, ::hsin, ::h2sin)
KERNEL_FLOAT_FP16_UNARY_FUN(sqrt, ::hsqrt, ::h2sqrt)
KERNEL_FLOAT_FP16_UNARY_FUN(trunc, ::htrunc, ::h2trunc)

KERNEL_FLOAT_FP16_UNARY_FUN(fast_exp, ::hexp, ::h2exp)
KERNEL_FLOAT_FP16_UNARY_FUN(fast_log, ::hlog, ::h2log)
KERNEL_FLOAT_FP16_UNARY_FUN(fast_cos, ::hcos, ::h2cos)
KERNEL_FLOAT_FP16_UNARY_FUN(fast_sin, ::hsin, ::h2sin)

#define KERNEL_FLOAT_FP16_BINARY_FUN(NAME, FUN1, FUN2)                                            \
    namespace ops {                                                                               \
    template<>                                                                                    \
    struct NAME<__half> {                                                                         \
        KERNEL_FLOAT_INLINE __half operator()(__half left, __half right) const {                  \
            return FUN1(left, right);                                                             \
        }                                                                                         \
    };                                                                                            \
    }                                                                                             \
    namespace detail {                                                                            \
    template<>                                                                                    \
    struct zip_halfx2<ops::NAME<__half>> {                                                        \
        KERNEL_FLOAT_INLINE static __half2 call(ops::NAME<__half>, __half2 left, __half2 right) { \
            return FUN2(left, right);                                                             \
        }                                                                                         \
    };                                                                                            \
    }

KERNEL_FLOAT_FP16_BINARY_FUN(add, __hadd, __hadd2)
KERNEL_FLOAT_FP16_BINARY_FUN(subtract, __hsub, __hsub2)
KERNEL_FLOAT_FP16_BINARY_FUN(multiply, __hmul, __hmul2)
KERNEL_FLOAT_FP16_BINARY_FUN(divide, __hdiv, __h2div)
KERNEL_FLOAT_FP16_BINARY_FUN(min, __hmin, __hmin2)
KERNEL_FLOAT_FP16_BINARY_FUN(max, __hmax, __hmax2)

KERNEL_FLOAT_FP16_BINARY_FUN(fast_div, __hdiv, __h2div)

KERNEL_FLOAT_FP16_BINARY_FUN(equal_to, __heq, __heq2)
KERNEL_FLOAT_FP16_BINARY_FUN(not_equal_to, __heq, __heq2)
KERNEL_FLOAT_FP16_BINARY_FUN(less, __hlt, __hlt2)
KERNEL_FLOAT_FP16_BINARY_FUN(less_equal, __hle, __hle2)
KERNEL_FLOAT_FP16_BINARY_FUN(greater, __hgt, __hgt2)
KERNEL_FLOAT_FP16_BINARY_FUN(greater_equal, __hge, __hgt2)

#endif

#define KERNEL_FLOAT_FP16_CAST(T, TO_HALF, FROM_HALF)    \
    namespace ops {                                      \
    template<>                                           \
    struct cast<T, __half> {                             \
        KERNEL_FLOAT_INLINE __half operator()(T input) { \
            return TO_HALF;                              \
        }                                                \
    };                                                   \
    template<>                                           \
    struct cast<__half, T> {                             \
        KERNEL_FLOAT_INLINE T operator()(__half input) { \
            return FROM_HALF;                            \
        }                                                \
    };                                                   \
    }

KERNEL_FLOAT_FP16_CAST(double, __double2half(input), double(__half2float(input)));
KERNEL_FLOAT_FP16_CAST(float, __float2half(input), __half2float(input));

// there are no official char casts. Instead, cast to int and then to char
KERNEL_FLOAT_FP16_CAST(char, __int2half_rn(input), (char)__half2int_rz(input));
KERNEL_FLOAT_FP16_CAST(signed char, __int2half_rn(input), (signed char)__half2int_rz(input));
KERNEL_FLOAT_FP16_CAST(unsigned char, __int2half_rn(input), (unsigned char)__half2int_rz(input));

KERNEL_FLOAT_FP16_CAST(signed short, __half2short_rz(input), __short2half_rn(input));
KERNEL_FLOAT_FP16_CAST(signed int, __half2int_rz(input), __int2half_rn(input));
KERNEL_FLOAT_FP16_CAST(signed long, __ll2half_rn(input), (signed long)(__half2ll_rz(input)));
KERNEL_FLOAT_FP16_CAST(signed long long, __ll2half_rn(input), __half2ll_rz(input));

KERNEL_FLOAT_FP16_CAST(unsigned short, __half2ushort_rz(input), __ushort2half_rn(input));
KERNEL_FLOAT_FP16_CAST(unsigned int, __half2uint_rz(input), __uint2half_rn(input));
KERNEL_FLOAT_FP16_CAST(unsigned long, __ull2half_rn(input), (unsigned long)(__half2ull_rz(input)));
KERNEL_FLOAT_FP16_CAST(unsigned long long, __ull2half_rn(input), __half2ull_rz(input));

using half = __half;
//KERNEL_FLOAT_TYPE_ALIAS(float16x, __half)
//KERNEL_FLOAT_TYPE_ALIAS(f16x, __half)

}  // namespace kernel_float

#endif

#endif  //KERNEL_FLOAT_FP16_H
#ifndef KERNEL_FLOAT_BF16_H
#define KERNEL_FLOAT_BF16_H



#if KERNEL_FLOAT_BF16_AVAILABLE
#include <cuda_bf16.h>





namespace kernel_float {
KERNEL_FLOAT_DEFINE_PROMOTED_FLOAT(__nv_bfloat16)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(float, __nv_bfloat16)
KERNEL_FLOAT_DEFINE_PROMOTED_TYPE(double, __nv_bfloat16)

template<>
struct into_vector_traits<__nv_bfloat162> {
    using value_type = __nv_bfloat16;
    using extent_type = extent<2>;

    KERNEL_FLOAT_INLINE
    static vector_storage<__nv_bfloat16, 2> call(__nv_bfloat162 input) {
        return {input.x, input.y};
    }
};

namespace detail {
template<typename F>
struct map_bfloat16x2 {
    KERNEL_FLOAT_INLINE
    static __nv_bfloat162 call(F fun, __nv_bfloat162 input) {
        __nv_bfloat16 a = fun(input.x);
        __nv_bfloat16 b = fun(input.y);
        return {a, b};
    }
};

template<typename F>
struct zip_bfloat16x2 {
    KERNEL_FLOAT_INLINE
    static __nv_bfloat162 call(F fun, __nv_bfloat162 left, __nv_bfloat162 right) {
        __nv_bfloat16 a = fun(left.x, left.y);
        __nv_bfloat16 b = fun(right.y, right.y);
        return {a, b};
    }
};

template<typename F, size_t N>
struct apply_impl<F, N, __nv_bfloat16, __nv_bfloat16> {
    KERNEL_FLOAT_INLINE static vector_storage<__nv_bfloat16, N>
    call(F fun, const vector_storage<__nv_bfloat16, N>& input) {
        vector_storage<__nv_bfloat16, N> result;

#pragma unroll
        for (size_t i = 0; i < N; i += 2) {
            __nv_bfloat162 a = {input.data()[i], input.data()[i + 1]};
            __nv_bfloat162 b = map_bfloat16x2<F>::call(fun, a);
            result.data()[i + 0] = b.x;
            result.data()[i + 1] = b.y;
        }

        if (N % 2 != 0) {
            result.data()[N - 1] = fun(input.data()[N - 1]);
        }

        return result;
    }
};

template<typename F, size_t N>
struct apply_impl<F, N, __nv_bfloat16, __nv_bfloat16, __nv_bfloat16> {
    KERNEL_FLOAT_INLINE static vector_storage<__nv_bfloat16, N> call(
        F fun,
        const vector_storage<__nv_bfloat16, N>& left,
        const vector_storage<__nv_bfloat16, N>& right) {
        vector_storage<__nv_bfloat16, N> result;
#pragma unroll
        for (size_t i = 0; i < N; i += 2) {
            __nv_bfloat162 a = {left.data()[i], left.data()[i + 1]};
            __nv_bfloat162 b = {right.data()[i], right.data()[i + 1]};
            __nv_bfloat162 c = zip_bfloat16x2<F>::call(fun, a, b);
            result.data()[i + 0] = c.x;
            result.data()[i + 1] = c.y;
        }

        if (N % 2 != 0) {
            result.data()[N - 1] = fun(left.data()[N - 1], right.data()[N - 1]);
        }

        return result;
    }
};

template<typename F, size_t N>
struct reduce_helper<F, N, __nv_bfloat16, enabled_t<(N >= 2)>> {
    KERNEL_FLOAT_INLINE static __nv_bfloat16
    call(F fun, const vector_storage<__nv_bfloat16, N>& input) {
        __nv_bfloat162 accum = {input.data()[0], input.data()[1]};

#pragma unroll
        for (size_t i = 2; i < N; i += 2) {
            __nv_bfloat162 a = {input.data()[i], input.data()[i + 1]};
            accum = zip_bfloat16x2<F>::call(fun, accum, a);
        }

        __nv_bfloat16 result = fun(accum.x, accum.y);

        if (N % 2 != 0) {
            result = fun(result, input.data()[N - 1]);
        }

        return result;
    }
};
}  // namespace detail

#if KERNEL_FLOAT_IS_DEVICE
#define KERNEL_FLOAT_BF16_UNARY_FUN(NAME, FUN1, FUN2)                       \
    namespace ops {                                                         \
    template<>                                                              \
    struct NAME<__nv_bfloat16> {                                            \
        KERNEL_FLOAT_INLINE __nv_bfloat16 operator()(__nv_bfloat16 input) { \
            return FUN1(input);                                             \
        }                                                                   \
    };                                                                      \
    }                                                                       \
    namespace detail {                                                      \
    template<>                                                              \
    struct map_bfloat16x2<ops::NAME<__nv_bfloat16>> {                       \
        KERNEL_FLOAT_INLINE static __nv_bfloat162                           \
        call(ops::NAME<__nv_bfloat16>, __nv_bfloat162 input) {              \
            return FUN2(input);                                             \
        }                                                                   \
    };                                                                      \
    }

KERNEL_FLOAT_BF16_UNARY_FUN(abs, ::__habs, ::__habs2)
KERNEL_FLOAT_BF16_UNARY_FUN(negate, ::__hneg, ::__hneg2)
KERNEL_FLOAT_BF16_UNARY_FUN(ceil, ::hceil, ::h2ceil)
KERNEL_FLOAT_BF16_UNARY_FUN(cos, ::hcos, ::h2cos)
KERNEL_FLOAT_BF16_UNARY_FUN(exp, ::hexp, ::h2exp)
KERNEL_FLOAT_BF16_UNARY_FUN(exp10, ::hexp10, ::h2exp10)
KERNEL_FLOAT_BF16_UNARY_FUN(floor, ::hfloor, ::h2floor)
KERNEL_FLOAT_BF16_UNARY_FUN(log, ::hlog, ::h2log)
KERNEL_FLOAT_BF16_UNARY_FUN(log10, ::hlog10, ::h2log2)
KERNEL_FLOAT_BF16_UNARY_FUN(rint, ::hrint, ::h2rint)
KERNEL_FLOAT_BF16_UNARY_FUN(rsqrt, ::hrsqrt, ::h2rsqrt)
KERNEL_FLOAT_BF16_UNARY_FUN(sin, ::hsin, ::h2sin)
KERNEL_FLOAT_BF16_UNARY_FUN(sqrt, ::hsqrt, ::h2sqrt)
KERNEL_FLOAT_BF16_UNARY_FUN(trunc, ::htrunc, ::h2trunc)

KERNEL_FLOAT_BF16_UNARY_FUN(fast_exp, ::hexp, ::h2exp)
KERNEL_FLOAT_BF16_UNARY_FUN(fast_log, ::hlog, ::h2log)
KERNEL_FLOAT_BF16_UNARY_FUN(fast_cos, ::hcos, ::h2cos)
KERNEL_FLOAT_BF16_UNARY_FUN(fast_sin, ::hsin, ::h2sin)

#define KERNEL_FLOAT_BF16_BINARY_FUN(NAME, FUN1, FUN2)                              \
    namespace ops {                                                                 \
    template<>                                                                      \
    struct NAME<__nv_bfloat16> {                                                    \
        KERNEL_FLOAT_INLINE __nv_bfloat16                                           \
        operator()(__nv_bfloat16 left, __nv_bfloat16 right) const {                 \
            return FUN1(left, right);                                               \
        }                                                                           \
    };                                                                              \
    }                                                                               \
    namespace detail {                                                              \
    template<>                                                                      \
    struct zip_bfloat16x2<ops::NAME<__nv_bfloat16>> {                               \
        KERNEL_FLOAT_INLINE static __nv_bfloat162                                   \
        call(ops::NAME<__nv_bfloat16>, __nv_bfloat162 left, __nv_bfloat162 right) { \
            return FUN2(left, right);                                               \
        }                                                                           \
    };                                                                              \
    }

KERNEL_FLOAT_BF16_BINARY_FUN(add, __hadd, __hadd2)
KERNEL_FLOAT_BF16_BINARY_FUN(subtract, __hsub, __hsub2)
KERNEL_FLOAT_BF16_BINARY_FUN(multiply, __hmul, __hmul2)
KERNEL_FLOAT_BF16_BINARY_FUN(divide, __hdiv, __h2div)
KERNEL_FLOAT_BF16_BINARY_FUN(min, __hmin, __hmin2)
KERNEL_FLOAT_BF16_BINARY_FUN(max, __hmax, __hmax2)

KERNEL_FLOAT_BF16_BINARY_FUN(fast_div, __hdiv, __h2div)

KERNEL_FLOAT_BF16_BINARY_FUN(equal_to, __heq, __heq2)
KERNEL_FLOAT_BF16_BINARY_FUN(not_equal_to, __heq, __heq2)
KERNEL_FLOAT_BF16_BINARY_FUN(less, __hlt, __hlt2)
KERNEL_FLOAT_BF16_BINARY_FUN(less_equal, __hle, __hle2)
KERNEL_FLOAT_BF16_BINARY_FUN(greater, __hgt, __hgt2)
KERNEL_FLOAT_BF16_BINARY_FUN(greater_equal, __hge, __hgt2)

#endif

#define KERNEL_FLOAT_BF16_CAST(T, TO_HALF, FROM_HALF)           \
    namespace ops {                                             \
    template<>                                                  \
    struct cast<T, __nv_bfloat16> {                             \
        KERNEL_FLOAT_INLINE __nv_bfloat16 operator()(T input) { \
            return TO_HALF;                                     \
        }                                                       \
    };                                                          \
    template<>                                                  \
    struct cast<__nv_bfloat16, T> {                             \
        KERNEL_FLOAT_INLINE T operator()(__nv_bfloat16 input) { \
            return FROM_HALF;                                   \
        }                                                       \
    };                                                          \
    }

KERNEL_FLOAT_BF16_CAST(double, __double2bfloat16(input), double(__bfloat162float(input)));
KERNEL_FLOAT_BF16_CAST(float, __float2bfloat16(input), __bfloat162float(input));

// there are no official char casts. Instead, cast to int and then to char
KERNEL_FLOAT_BF16_CAST(char, __int2bfloat16_rn(input), (char)__bfloat162int_rz(input));
KERNEL_FLOAT_BF16_CAST(
    signed char,
    __int2bfloat16_rn(input),
    (signed char)__bfloat162int_rz(input));
KERNEL_FLOAT_BF16_CAST(
    unsigned char,
    __int2bfloat16_rn(input),
    (unsigned char)__bfloat162int_rz(input));

KERNEL_FLOAT_BF16_CAST(signed short, __bfloat162short_rz(input), __short2bfloat16_rn(input));
KERNEL_FLOAT_BF16_CAST(signed int, __bfloat162int_rz(input), __int2bfloat16_rn(input));
KERNEL_FLOAT_BF16_CAST(
    signed long,
    __ll2bfloat16_rn(input),
    (signed long)(__bfloat162ll_rz(input)));
KERNEL_FLOAT_BF16_CAST(signed long long, __ll2bfloat16_rn(input), __bfloat162ll_rz(input));

KERNEL_FLOAT_BF16_CAST(unsigned short, __bfloat162ushort_rz(input), __ushort2bfloat16_rn(input));
KERNEL_FLOAT_BF16_CAST(unsigned int, __bfloat162uint_rz(input), __uint2bfloat16_rn(input));
KERNEL_FLOAT_BF16_CAST(
    unsigned long,
    __ull2bfloat16_rn(input),
    (unsigned long)(__bfloat162ull_rz(input)));
KERNEL_FLOAT_BF16_CAST(unsigned long long, __ull2bfloat16_rn(input), __bfloat162ull_rz(input));

using bfloat16 = __nv_bfloat16;
//KERNEL_FLOAT_TYPE_ALIAS(float16x, __nv_bfloat16)
//KERNEL_FLOAT_TYPE_ALIAS(f16x, __nv_bfloat16)

}  // namespace kernel_float

#if KERNEL_FLOAT_FP16_AVAILABLE


namespace kernel_float {
KERNEL_FLOAT_BF16_CAST(__half, __float2bfloat16(input), __bfloat162float(input));
}

#endif  // KERNEL_FLOAT_FP16_AVAILABLE
#endif

#endif  //KERNEL_FLOAT_BF16_H
#ifndef KERNEL_FLOAT_PRELUDE_H
#define KERNEL_FLOAT_PRELUDE_H




namespace kernel_float {
namespace prelude {
namespace kf = ::kernel_float;

template<typename T>
using kscalar = vector<T, extent<1>>;

template<typename T, size_t N>
using kvec = vector<T, extent<N>>;

template<typename T, size_t N>
using kvector = vector<T, extent<N>>;

// clang-format off
template<typename T> using kvec1 = kvec<T, 1>;
template<typename T> using kvec2 = kvec<T, 2>;
template<typename T> using kvec3 = kvec<T, 3>;
template<typename T> using kvec4 = kvec<T, 4>;
template<typename T> using kvec5 = kvec<T, 5>;
template<typename T> using kvec6 = kvec<T, 6>;
template<typename T> using kvec7 = kvec<T, 7>;
template<typename T> using kvec8 = kvec<T, 8>;
// clang-format on

#define KERNEL_FLOAT_TYPE_ALIAS(NAME, T)  \
    template<size_t N>                    \
    using k##NAME = vector<T, extent<N>>; \
    using k##NAME##1 = vec<T, 1>;         \
    using k##NAME##2 = vec<T, 2>;         \
    using k##NAME##3 = vec<T, 3>;         \
    using k##NAME##4 = vec<T, 4>;         \
    using k##NAME##5 = vec<T, 5>;         \
    using k##NAME##6 = vec<T, 6>;         \
    using k##NAME##7 = vec<T, 7>;         \
    using k##NAME##8 = vec<T, 8>;

KERNEL_FLOAT_TYPE_ALIAS(char, char)
KERNEL_FLOAT_TYPE_ALIAS(short, short)
KERNEL_FLOAT_TYPE_ALIAS(int, int)
KERNEL_FLOAT_TYPE_ALIAS(long, long)
KERNEL_FLOAT_TYPE_ALIAS(longlong, long long)

KERNEL_FLOAT_TYPE_ALIAS(uchar, unsigned char)
KERNEL_FLOAT_TYPE_ALIAS(ushort, unsigned short)
KERNEL_FLOAT_TYPE_ALIAS(uint, unsigned int)
KERNEL_FLOAT_TYPE_ALIAS(ulong, unsigned long)
KERNEL_FLOAT_TYPE_ALIAS(ulonglong, unsigned long long)

KERNEL_FLOAT_TYPE_ALIAS(float, float)
KERNEL_FLOAT_TYPE_ALIAS(f32x, float)
KERNEL_FLOAT_TYPE_ALIAS(float32x, float)

KERNEL_FLOAT_TYPE_ALIAS(double, double)
KERNEL_FLOAT_TYPE_ALIAS(f64x, double)
KERNEL_FLOAT_TYPE_ALIAS(float64x, double)

#if KERNEL_FLOAT_FP16_AVAILABLE
KERNEL_FLOAT_TYPE_ALIAS(half, __half)
KERNEL_FLOAT_TYPE_ALIAS(f16x, __half)
KERNEL_FLOAT_TYPE_ALIAS(float16x, __half)
#endif

#if KERNEL_FLOAT_BF16_AVAILABLE
KERNEL_FLOAT_TYPE_ALIAS(bfloat16, __nv_bfloat16)
KERNEL_FLOAT_TYPE_ALIAS(bf16, __nv_bfloat16)
#endif

template<size_t N>
static constexpr extent<N> kextent = {};

template<typename... Args>
KERNEL_FLOAT_INLINE kvec<promote_t<Args...>, sizeof...(Args)> make_kvec(Args&&... args) {
    return make_vec(std::forward<Args>(args)...);
};

template<typename T = double>
using kconstant = constant<T>;

template<typename T = double>
KERNEL_FLOAT_INLINE constexpr kconstant<T> kconst(T value) {
    return value;
}

}  // namespace prelude
}  // namespace kernel_float

#endif
