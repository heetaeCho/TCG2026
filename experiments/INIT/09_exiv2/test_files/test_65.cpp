#include <gtest/gtest.h>
#include <type_traits>

// Assume the given partial code and namespaces are properly included
namespace Safe { namespace Internal {

template <typename T>
bool builtin_add_overflow(T summand_1, T summand_2, T& result) {
    // Function implementation
}

}} // namespace Safe::Internal

// Test suite for the Safe::Internal::builtin_add_overflow function
namespace SafeInternalTest {

    // TEST_ID 65
    TEST_F(SafeInternalTest, TestIntOverflow_65) {
        int summand_1 = INT_MAX;
        int summand_2 = 1;
        int result;

        bool overflow = Safe::Internal::builtin_add_overflow(summand_1, summand_2, result);

        // Test case where adding INT_MAX + 1 should overflow
        EXPECT_TRUE(overflow);
        EXPECT_EQ(result, INT_MIN);  // wrap-around value for signed int overflow
    }

    // TEST_ID 66
    TEST_F(SafeInternalTest, TestIntNoOverflow_66) {
        int summand_1 = 10;
        int summand_2 = 20;
        int result;

        bool overflow = Safe::Internal::builtin_add_overflow(summand_1, summand_2, result);

        // Test case where adding 10 + 20 should not overflow
        EXPECT_FALSE(overflow);
        EXPECT_EQ(result, 30);
    }

    // TEST_ID 67
    TEST_F(SafeInternalTest, TestUnsignedIntOverflow_67) {
        unsigned int summand_1 = UINT_MAX;
        unsigned int summand_2 = 1;
        unsigned int result;

        bool overflow = Safe::Internal::builtin_add_overflow(summand_1, summand_2, result);

        // Test case where adding UINT_MAX + 1 should overflow for unsigned int
        EXPECT_TRUE(overflow);
        EXPECT_EQ(result, 0);  // wrap-around value for unsigned int overflow
    }

    // TEST_ID 68
    TEST_F(SafeInternalTest, TestUnsignedIntNoOverflow_68) {
        unsigned int summand_1 = 100;
        unsigned int summand_2 = 200;
        unsigned int result;

        bool overflow = Safe::Internal::builtin_add_overflow(summand_1, summand_2, result);

        // Test case where adding 100 + 200 should not overflow
        EXPECT_FALSE(overflow);
        EXPECT_EQ(result, 300);
    }

    // TEST_ID 69
    TEST_F(SafeInternalTest, TestLongLongOverflow_69) {
        long long summand_1 = LLONG_MAX;
        long long summand_2 = 1;
        long long result;

        bool overflow = Safe::Internal::builtin_add_overflow(summand_1, summand_2, result);

        // Test case where adding LLONG_MAX + 1 should overflow
        EXPECT_TRUE(overflow);
        EXPECT_EQ(result, LLONG_MIN);  // wrap-around value for signed long long overflow
    }

    // TEST_ID 70
    TEST_F(SafeInternalTest, TestLongLongNoOverflow_70) {
        long long summand_1 = 1000;
        long long summand_2 = 2000;
        long long result;

        bool overflow = Safe::Internal::builtin_add_overflow(summand_1, summand_2, result);

        // Test case where adding 1000 + 2000 should not overflow
        EXPECT_FALSE(overflow);
        EXPECT_EQ(result, 3000);
    }

    // TEST_ID 71
    TEST_F(SafeInternalTest, TestFallback_71) {
        // Test the fallback behavior when builtin __overflow functions are unavailable
        int summand_1 = INT_MAX;
        int summand_2 = 1;
        int result;

        // Since we are not using the actual compiler intrinsics in this test, assume fallback
        bool overflow = Safe::Internal::builtin_add_overflow(summand_1, summand_2, result);

        // Simulate fallback function result
        EXPECT_TRUE(overflow);
    }

} // namespace SafeInternalTest