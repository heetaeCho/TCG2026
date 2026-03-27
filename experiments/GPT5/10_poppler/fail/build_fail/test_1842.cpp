#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock external dependencies if necessary (none in this case based on the provided code)
using ::testing::_;
using ::testing::Invoke;

template <typename T>
bool checkedAssign(long long result, T *z) {
    if (result > std::numeric_limits<T>::max() || result < std::numeric_limits<T>::min()) {
        return false;
    }
    *z = static_cast<T>(result);
    return true;
}

template <typename T>
inline bool checkedAdd(T x, T y, T *z) {
#if __has_builtin(__builtin_add_overflow)
    return __builtin_add_overflow(x, y, z);
#else
    const auto lz = static_cast<long long>(x) + static_cast<long long>(y);
    return checkedAssign(lz, z);
#endif
}

// Test fixture class
class GooCheckedOpsTest_1842 : public ::testing::Test {
protected:
    // You can add any test setup or teardown code here
};

// Test cases

TEST_F(GooCheckedOpsTest_1842, checkedAdd_NormalOperation_1842) {
    int x = 5, y = 10, result;
    EXPECT_TRUE(checkedAdd(x, y, &result));
    EXPECT_EQ(result, 15);
}

TEST_F(GooCheckedOpsTest_1842, checkedAdd_Overflow_1842) {
    int x = std::numeric_limits<int>::max(), y = 1, result;
    EXPECT_FALSE(checkedAdd(x, y, &result));  // Overflow expected
}

TEST_F(GooCheckedOpsTest_1842, checkedAdd_Underflow_1842) {
    int x = std::numeric_limits<int>::min(), y = -1, result;
    EXPECT_FALSE(checkedAdd(x, y, &result));  // Underflow expected
}

TEST_F(GooCheckedOpsTest_1842, checkedAdd_Zero_1842) {
    int x = 0, y = 0, result;
    EXPECT_TRUE(checkedAdd(x, y, &result));
    EXPECT_EQ(result, 0);
}

TEST_F(GooCheckedOpsTest_1842, checkedAdd_LargeValues_1842) {
    long long x = 1e18, y = 1e18, result;
    EXPECT_TRUE(checkedAdd(x, y, &result));  // Large numbers within range
    EXPECT_EQ(result, 2e18);
}

TEST_F(GooCheckedOpsTest_1842, checkedAdd_NegativeValues_1842) {
    int x = -50, y = -25, result;
    EXPECT_TRUE(checkedAdd(x, y, &result));
    EXPECT_EQ(result, -75);
}

TEST_F(GooCheckedOpsTest_1842, checkedAdd_SignedOverflow_1842) {
    short x = std::numeric_limits<short>::max(), y = 1, result;
    EXPECT_FALSE(checkedAdd(x, y, &result));  // Signed overflow expected
}

TEST_F(GooCheckedOpsTest_1842, checkedAdd_NullPointer_1842) {
    int x = 5, y = 10;
    EXPECT_DEATH(checkedAdd(x, y, nullptr), ".*");  // Expect crash or handle the null pointer
}