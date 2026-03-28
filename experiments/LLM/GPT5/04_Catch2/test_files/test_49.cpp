// File: column_initial_indent_tests_49.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include "catch2/internal/catch_textflow.hpp"

namespace {

using Catch::TextFlow::Column;

// Minimal detection idiom that works pre-C++17
template <typename...>
using void_t = void;

template <typename T, typename = void>
struct has_initialIndent : std::false_type {};

template <typename T>
struct has_initialIndent<T, void_t<decltype(std::declval<T>().initialIndent(std::declval<size_t>()))>>
    : std::true_type {};

// Convenience alias for deducing the expression type
template <typename T>
using initialIndent_expr_t = decltype(std::declval<T>().initialIndent(std::declval<size_t>()));

class ColumnInitialIndentTest_49 : public ::testing::Test {};
} // namespace

// Verifies that calling initialIndent on an lvalue returns an lvalue reference to Column
TEST_F(ColumnInitialIndentTest_49, ReturnsLvalueRef_49) {
    Column c("text");
    Column& ref = c.initialIndent(3);
    EXPECT_EQ(&ref, &c) << "initialIndent should return *this as an lvalue reference for chaining";
}

// Verifies fluent chaining works (since the function returns Column&)
TEST_F(ColumnInitialIndentTest_49, FluentChainingReturnsSelf_49) {
    Column c("text");
    Column* p = &c.initialIndent(2).initialIndent(5);
    EXPECT_EQ(p, &c) << "Chained calls should keep returning the same object";
}

// Compile-time: initialIndent is callable on non-const lvalues…
TEST_F(ColumnInitialIndentTest_49, IsCallableOnNonConstLvalue_49) {
    static_assert(has_initialIndent<Column&>::value,
                  "initialIndent(size_t) should be callable on non-const lvalues");
    // And its exact return type is Column&
    static_assert(std::is_same<initialIndent_expr_t<Column&>, Column&>::value,
                  "initialIndent(size_t) should return Column& on lvalues");
    SUCCEED();
}

// Compile-time: …but NOT on rvalues due to the '&' ref-qualifier
TEST_F(ColumnInitialIndentTest_49, NotCallableOnRvalue_49) {
    static_assert(!has_initialIndent<Column&&>::value,
                  "initialIndent(size_t) should NOT be callable on rvalues");
    SUCCEED();
}

// Compile-time: …and NOT on const lvalues (non-const '&' ref-qualifier)
TEST_F(ColumnInitialIndentTest_49, NotCallableOnConstLvalue_49) {
    static_assert(!has_initialIndent<const Column&>::value,
                  "initialIndent(size_t) should NOT be callable on const lvalues");
    SUCCEED();
}

// Boundary input: extremely large indent value should be accepted by the interface
// (We only verify callability & chaining; no assumptions about formatting/output.)
TEST_F(ColumnInitialIndentTest_49, AcceptsLargeIndentValue_49) {
    Column c("text");
    // Using a large value (e.g., npos) to ensure boundary input is accepted by the API
    size_t big = std::string::npos;
    Column& ref = c.initialIndent(big);
    EXPECT_EQ(&ref, &c) << "API should accept large size_t values and remain chainable";
}
