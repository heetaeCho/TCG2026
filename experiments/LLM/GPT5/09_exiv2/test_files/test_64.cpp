#include <gtest/gtest.h>
#include <limits>
#include <type_traits>

namespace Safe { namespace Internal {

template <typename T>
bool fallback_add_overflow(T summand_1, T summand_2, T& result) {
    if constexpr (std::is_signed_v<T> && sizeof(T) >= sizeof(int)) {
        if (((summand_2 >= 0) && (summand_1 > std::numeric_limits<T>::max() - summand_2)) ||
            ((summand_2 < 0) && (summand_1 < std::numeric_limits<T>::min() - summand_2)))
            return true;
        result = summand_1 + summand_2;
        return false;
    } else if constexpr (std::is_signed_v<T> && sizeof(T) < sizeof(int)) {
        const int res = summand_1 + summand_2;
        if ((res > std::numeric_limits<T>::max()) || (res < std::numeric_limits<T>::min())) {
            return true;
        }
        result = static_cast<T>(res);
        return false;
    } else {
        result = summand_1 + summand_2;
        return result < summand_1;
    }
}

} }  // namespace Safe::Internal

// Unit Test Definitions

TEST_F(SafeInternalTest_64, FallbackAddOverflow_NormalAddition_64) {
    int result;
    bool overflow = Safe::Internal::fallback_add_overflow(5, 10, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 15);
}

TEST_F(SafeInternalTest_65, FallbackAddOverflow_SignOverflow_64) {
    int result;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::max(), 1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeInternalTest_66, FallbackAddOverflow_SignUnderflow_66) {
    int result;
    bool overflow = Safe::Internal::fallback_add_overflow(std::numeric_limits<int>::min(), -1, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeInternalTest_67, FallbackAddOverflow_SmallIntAddition_67) {
    short result;
    bool overflow = Safe::Internal::fallback_add_overflow(static_cast<short>(32767), static_cast<short>(1), result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeInternalTest_68, FallbackAddOverflow_LargeAddition_68) {
    long long result;
    bool overflow = Safe::Internal::fallback_add_overflow(9223372036854775807LL, 1LL, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeInternalTest_69, FallbackAddOverflow_UnsignedAddition_69) {
    unsigned int result;
    bool overflow = Safe::Internal::fallback_add_overflow(2000000000U, 3000000000U, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeInternalTest_70, FallbackAddOverflow_SignedAdditionNoOverflow_70) {
    int result;
    bool overflow = Safe::Internal::fallback_add_overflow(100, 50, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 150);
}

TEST_F(SafeInternalTest_71, FallbackAddOverflow_SignedLargeAddition_71) {
    int result;
    bool overflow = Safe::Internal::fallback_add_overflow(1000000000, 1000000000, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 2000000000);
}

TEST_F(SafeInternalTest_72, FallbackAddOverflow_SmallOverflow_72) {
    short result;
    bool overflow = Safe::Internal::fallback_add_overflow(30000, 4000, result);
    EXPECT_TRUE(overflow);
}

TEST_F(SafeInternalTest_73, FallbackAddOverflow_SmallResult_73) {
    short result;
    bool overflow = Safe::Internal::fallback_add_overflow(10, 5, result);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(result, 15);
}