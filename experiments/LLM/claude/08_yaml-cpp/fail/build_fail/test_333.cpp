#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Simple mock types to use as template arguments
struct MockSignedSignificandBits {
    int value;
};

struct MockUnsignedDecimalFp {
    int significand;
    int exponent;
    
    bool operator==(const MockUnsignedDecimalFp& other) const {
        return significand == other.significand && exponent == other.exponent;
    }
};

// Test fixture
class SignIgnoreTest_333 : public ::testing::Test {
protected:
    YAML::jkj::dragonbox::policy::sign::ignore policy_;
};

// Test that handle_sign returns the second argument unchanged
TEST_F(SignIgnoreTest_333, HandleSignReturnsSecondArgument_333) {
    MockSignedSignificandBits bits{42};
    MockUnsignedDecimalFp fp{123, 456};
    
    auto result = decltype(policy_)::handle_sign(bits, fp);
    
    EXPECT_EQ(result.significand, 123);
    EXPECT_EQ(result.exponent, 456);
}

// Test that handle_sign ignores the first argument (sign bits)
TEST_F(SignIgnoreTest_333, HandleSignIgnoresSignBits_333) {
    MockSignedSignificandBits bits_positive{1};
    MockSignedSignificandBits bits_negative{-1};
    MockUnsignedDecimalFp fp{999, -5};
    
    auto result_pos = decltype(policy_)::handle_sign(bits_positive, fp);
    auto result_neg = decltype(policy_)::handle_sign(bits_negative, fp);
    
    EXPECT_EQ(result_pos, result_neg);
}

// Test with zero values
TEST_F(SignIgnoreTest_333, HandleSignWithZeroValues_333) {
    MockSignedSignificandBits bits{0};
    MockUnsignedDecimalFp fp{0, 0};
    
    auto result = decltype(policy_)::handle_sign(bits, fp);
    
    EXPECT_EQ(result.significand, 0);
    EXPECT_EQ(result.exponent, 0);
}

// Test that handle_sign is constexpr
TEST_F(SignIgnoreTest_333, HandleSignIsConstexpr_333) {
    // This test verifies that handle_sign can be used in a constexpr context
    // We use simple integer types for constexpr evaluation
    constexpr int signed_bits = 42;
    constexpr int result = YAML::jkj::dragonbox::policy::sign::ignore::handle_sign(signed_bits, 100);
    
    EXPECT_EQ(result, 100);
}

// Test that handle_sign is noexcept
TEST_F(SignIgnoreTest_333, HandleSignIsNoexcept_333) {
    MockSignedSignificandBits bits{0};
    MockUnsignedDecimalFp fp{0, 0};
    
    EXPECT_TRUE(noexcept(decltype(policy_)::handle_sign(bits, fp)));
}

// Test with negative exponent values
TEST_F(SignIgnoreTest_333, HandleSignWithNegativeExponent_333) {
    MockSignedSignificandBits bits{-100};
    MockUnsignedDecimalFp fp{1, -308};
    
    auto result = decltype(policy_)::handle_sign(bits, fp);
    
    EXPECT_EQ(result.significand, 1);
    EXPECT_EQ(result.exponent, -308);
}

// Test with large values
TEST_F(SignIgnoreTest_333, HandleSignWithLargeValues_333) {
    MockSignedSignificandBits bits{2147483647};
    MockUnsignedDecimalFp fp{2147483647, 2147483647};
    
    auto result = decltype(policy_)::handle_sign(bits, fp);
    
    EXPECT_EQ(result.significand, 2147483647);
    EXPECT_EQ(result.exponent, 2147483647);
}

// Test with integer types directly
TEST_F(SignIgnoreTest_333, HandleSignWithIntegerTypes_333) {
    int signed_bits = -5;
    int unsigned_fp = 42;
    
    auto result = YAML::jkj::dragonbox::policy::sign::ignore::handle_sign(signed_bits, unsigned_fp);
    
    EXPECT_EQ(result, 42);
}

// Test that different signed significand bits values don't affect result
TEST_F(SignIgnoreTest_333, DifferentSignBitsProduceSameResult_333) {
    MockUnsignedDecimalFp fp{555, 10};
    
    MockSignedSignificandBits bits1{0};
    MockSignedSignificandBits bits2{100};
    MockSignedSignificandBits bits3{-100};
    
    auto r1 = decltype(policy_)::handle_sign(bits1, fp);
    auto r2 = decltype(policy_)::handle_sign(bits2, fp);
    auto r3 = decltype(policy_)::handle_sign(bits3, fp);
    
    EXPECT_EQ(r1, r2);
    EXPECT_EQ(r2, r3);
}

} // namespace
