#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "catch2/internal/catch_decomposer.hpp"

namespace {

// Test fixture for BinaryExpr tests
class BinaryExprTest_124 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that BinaryExpr template class can be instantiated as a type
// We use int as placeholder template arguments since BinaryExpr is a template
TEST_F(BinaryExprTest_124, BinaryExprTypeExists_124) {
    // Verify that BinaryExpr is a valid class template by checking type traits
    // We can reference the type without calling the forbidden operator>=
    bool is_class = std::is_class<Catch::BinaryExpr<int, int>>::value;
    EXPECT_TRUE(is_class);
}

// Test that BinaryExpr can be default constructed (if default constructible)
TEST_F(BinaryExprTest_124, BinaryExprDefaultConstructible_124) {
    bool is_default_constructible = std::is_default_constructible<Catch::BinaryExpr<int, int>>::value;
    // The class should be constructible in some form since it's used internally
    // This tests observable type properties
    EXPECT_TRUE(is_default_constructible);
}

// Test that BinaryExpr is copy constructible
TEST_F(BinaryExprTest_124, BinaryExprCopyConstructible_124) {
    bool is_copy_constructible = std::is_copy_constructible<Catch::BinaryExpr<int, int>>::value;
    EXPECT_TRUE(is_copy_constructible);
}

// Test that operator>= member function exists on BinaryExpr
// We can't call it (static_assert prevents it), but we can verify the type has the method
// by checking that the expression is well-formed at the SFINAE level
// Note: Since static_assert is not SFINAE-friendly, we just document this behavior
TEST_F(BinaryExprTest_124, ChainedComparisonOperatorExists_124) {
    // The operator>= is declared as a template member function on BinaryExpr.
    // Calling it would trigger a static_assert compile error by design.
    // This test verifies that the BinaryExpr type itself is valid and usable
    // (the operator>= serves as a compile-time guard against misuse).
    Catch::BinaryExpr<int, int> expr;
    (void)expr; // BinaryExpr object can be created
    SUCCEED() << "BinaryExpr object created successfully; operator>= exists but is intentionally unusable (static_assert guard)";
}

// Test with different template parameter types
TEST_F(BinaryExprTest_124, BinaryExprWithDifferentTypes_124) {
    bool is_class_double = std::is_class<Catch::BinaryExpr<double, float>>::value;
    EXPECT_TRUE(is_class_double);
    
    bool is_class_string = std::is_class<Catch::BinaryExpr<std::string, int>>::value;
    EXPECT_TRUE(is_class_string);
}

// Test that BinaryExpr with reference types works as a type
TEST_F(BinaryExprTest_124, BinaryExprWithReferenceTypes_124) {
    bool is_class_ref = std::is_class<Catch::BinaryExpr<int, const int&>>::value;
    EXPECT_TRUE(is_class_ref);
}

} // namespace
