// ColumnIndentTest_48.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

#include "Catch2/src/catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

class ColumnIndentTest_48 : public ::testing::Test {};

// [Behavior] Returns self reference for fluent chaining on lvalues
TEST_F(ColumnIndentTest_48, ReturnsSelfReference_48) {
    Column col{"hello"};
    Column& ret = col.indent(5);
    EXPECT_EQ(&ret, &col) << "indent(newIndent) should return *this by reference";
}

// [Behavior] Multiple indent() calls remain on the same object (fluent API)
TEST_F(ColumnIndentTest_48, ChainedCallsReturnSelf_48) {
    Column col{"x"};
    Column& ret = col.indent(2).indent(10).indent(0);
    EXPECT_EQ(&ret, &col) << "Chained indent() calls should continue returning *this";
}

// [Constraint] Method is lvalue-qualified: invocable with lvalue, not with rvalue
TEST_F(ColumnIndentTest_48, LvalueQualifiedOnly_48) {
    // Pointer-to-member helps us check invocability without calling the function.
    auto mem = &Column::indent;

    // Should be invocable with lvalue Column&, size_t
    static_assert(std::is_invocable_v<decltype(mem), Column&, size_t>,
                  "indent should be invocable on lvalues");

    // Should NOT be invocable with rvalue Column&&, size_t
    static_assert(!std::is_invocable_v<decltype(mem), Column&&, size_t>,
                  "indent should not be invocable on rvalues");

    SUCCEED(); // Compile-time checks above are the essence of this test.
}

// [Constraint] Non-const member: not invocable on const lvalues
TEST_F(ColumnIndentTest_48, NotCallableOnConst_48) {
    auto mem = &Column::indent;

    // Should NOT be invocable with const Column&, size_t
    static_assert(!std::is_invocable_v<decltype(mem), const Column&, size_t>,
                  "indent should not be invocable on const lvalues");

    SUCCEED();
}

// [Boundary] Accepts large indent values and still returns self-reference (no UB/throwing assumed)
TEST_F(ColumnIndentTest_48, LargeIndentStillReturnsSelf_48) {
    Column col{"boundary"};
    const size_t veryLarge = static_cast<size_t>(-1); // maximum size_t
    Column& ret = col.indent(veryLarge);
    EXPECT_EQ(&ret, &col) << "Even with large values, indent should return *this";
}
