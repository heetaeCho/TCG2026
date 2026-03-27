#include <gtest/gtest.h>
#include <limits>

// Assuming the definition of checkedAssign() is available in the codebase
template <typename T>
inline bool checkedAssign(long long value, T *z) {
    if (value > std::numeric_limits<T>::max() || value < std::numeric_limits<T>::min()) {
        return false;  // Overflow/Underflow
    }
    *z = static_cast<T>(value);
    return true;
}

// Mock version of checkedMultiply based on the provided partial code
template <typename T>
inline bool checkedMultiply(T x, T y, T *z) {
#if __has_builtin(__builtin_mul_overflow)
    return __builtin_mul_overflow(x, y, z);
#else
    const auto lz = static_cast<long long>(x) * static_cast<long long>(y);
    return checkedAssign(lz, z);
#endif
}

TEST_F(CheckedMultiplyTest_1843, NormalOperation_1843) {
    int result;
    ASSERT_TRUE(checkedMultiply(2, 3, &result));
    ASSERT_EQ(result, 6);
}

TEST_F(CheckedMultiplyTest_1843, Overflow_1843) {
    int result;
    ASSERT_FALSE(checkedMultiply(std::numeric_limits<int>::max(), 2, &result));
}

TEST_F(CheckedMultiplyTest_1843, Underflow_1843) {
    int result;
    ASSERT_FALSE(checkedMultiply(std::numeric_limits<int>::min(), 2, &result));
}

TEST_F(CheckedMultiplyTest_1843, NegativeMultiplication_1843) {
    int result;
    ASSERT_TRUE(checkedMultiply(-2, 3, &result));
    ASSERT_EQ(result, -6);
}

TEST_F(CheckedMultiplyTest_1843, ZeroMultiplication_1843) {
    int result;
    ASSERT_TRUE(checkedMultiply(0, 3, &result));
    ASSERT_EQ(result, 0);
}

TEST_F(CheckedMultiplyTest_1843, LargeValues_1843) {
    long long result;
    ASSERT_TRUE(checkedMultiply(1000000000LL, 1000000000LL, &result));
    ASSERT_EQ(result, 1000000000000000000LL);
}