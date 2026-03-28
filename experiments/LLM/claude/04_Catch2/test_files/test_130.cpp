#include <catch2/internal/catch_decomposer.hpp>
#include <catch2/internal/catch_test_macro_impl.hpp>
#include <catch2/catch_tostring.hpp>

#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Test fixture
class DecomposerTest_130 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Decomposer with an integer value produces an ExprLhs<int>
TEST_F(DecomposerTest_130, DecomposerWithIntProducesExprLhs_130) {
    auto result = Catch::Decomposer{} <= 42;
    // ExprLhs should be constructible - verifying it compiles and runs
    static_assert(std::is_same<decltype(result), Catch::ExprLhs<int>>::value,
                  "Expected ExprLhs<int>");
}

// Test that Decomposer with a boolean value produces ExprLhs<bool>
TEST_F(DecomposerTest_130, DecomposerWithBoolProducesExprLhs_130) {
    auto result = Catch::Decomposer{} <= true;
    static_assert(std::is_same<decltype(result), Catch::ExprLhs<bool>>::value,
                  "Expected ExprLhs<bool>");
}

// Test with false boolean
TEST_F(DecomposerTest_130, DecomposerWithFalseProducesExprLhs_130) {
    auto result = Catch::Decomposer{} <= false;
    static_assert(std::is_same<decltype(result), Catch::ExprLhs<bool>>::value,
                  "Expected ExprLhs<bool>");
}

// Test that Decomposer with a float produces ExprLhs<float>
TEST_F(DecomposerTest_130, DecomposerWithFloatProducesExprLhs_130) {
    auto result = Catch::Decomposer{} <= 3.14f;
    static_assert(std::is_same<decltype(result), Catch::ExprLhs<float>>::value,
                  "Expected ExprLhs<float>");
}

// Test that Decomposer with a double produces ExprLhs<double>
TEST_F(DecomposerTest_130, DecomposerWithDoubleProducesExprLhs_130) {
    auto result = Catch::Decomposer{} <= 2.718;
    static_assert(std::is_same<decltype(result), Catch::ExprLhs<double>>::value,
                  "Expected ExprLhs<double>");
}

// Test with zero integer
TEST_F(DecomposerTest_130, DecomposerWithZeroInt_130) {
    auto result = Catch::Decomposer{} <= 0;
    static_assert(std::is_same<decltype(result), Catch::ExprLhs<int>>::value,
                  "Expected ExprLhs<int>");
}

// Test with negative integer
TEST_F(DecomposerTest_130, DecomposerWithNegativeInt_130) {
    auto result = Catch::Decomposer{} <= -1;
    static_assert(std::is_same<decltype(result), Catch::ExprLhs<int>>::value,
                  "Expected ExprLhs<int>");
}

// Test with unsigned int
TEST_F(DecomposerTest_130, DecomposerWithUnsignedInt_130) {
    auto result = Catch::Decomposer{} <= 42u;
    static_assert(std::is_same<decltype(result), Catch::ExprLhs<unsigned int>>::value,
                  "Expected ExprLhs<unsigned int>");
}

// Test with char value
TEST_F(DecomposerTest_130, DecomposerWithChar_130) {
    auto result = Catch::Decomposer{} <= 'A';
    static_assert(std::is_same<decltype(result), Catch::ExprLhs<char>>::value,
                  "Expected ExprLhs<char>");
}

// Test with long long
TEST_F(DecomposerTest_130, DecomposerWithLongLong_130) {
    auto result = Catch::Decomposer{} <= 123456789LL;
    static_assert(std::is_same<decltype(result), Catch::ExprLhs<long long>>::value,
                  "Expected ExprLhs<long long>");
}

// Test boundary: max int
TEST_F(DecomposerTest_130, DecomposerWithMaxInt_130) {
    auto result = Catch::Decomposer{} <= std::numeric_limits<int>::max();
    static_assert(std::is_same<decltype(result), Catch::ExprLhs<int>>::value,
                  "Expected ExprLhs<int>");
}

// Test boundary: min int
TEST_F(DecomposerTest_130, DecomposerWithMinInt_130) {
    auto result = Catch::Decomposer{} <= std::numeric_limits<int>::min();
    static_assert(std::is_same<decltype(result), Catch::ExprLhs<int>>::value,
                  "Expected ExprLhs<int>");
}

// Test with nullptr (pointer type)
TEST_F(DecomposerTest_130, DecomposerWithNullptr_130) {
    auto result = Catch::Decomposer{} <= nullptr;
    (void)result; // Just verifying it compiles and doesn't crash
}
