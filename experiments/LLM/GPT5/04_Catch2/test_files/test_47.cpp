// Column_width_tests_47.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <utility>
#include <string>

// Include the header under test
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

// ---------- Helper type traits (interface-level checks only) ----------
namespace {

// Checks that calling width on an rvalue is ill-formed (due to "&" ref-qualifier)
template <typename T, typename = void>
struct has_width_on_rvalue_47 : std::false_type {};

template <typename T>
struct has_width_on_rvalue_47<T,
    std::void_t<decltype(std::declval<T&&>().width(std::declval<std::size_t>()))>> : std::true_type {};

// Checks that calling width on an lvalue yields Column&
template <typename T>
using width_lvalue_return_t_47 =
    decltype(std::declval<T&>().width(std::declval<std::size_t>()));

} // namespace

// ---------- Tests ----------

class ColumnWidthTest_47 : public ::testing::Test {
protected:
    Column makeCol(const std::string& s = "abc") { return Column{s}; }
};

// Normal operation: setting then reading back via accessor
TEST_F(ColumnWidthTest_47, WidthSetsAndGets_47) {
    Column col = makeCol();
    col.width(10);
    EXPECT_EQ(col.width(), static_cast<std::size_t>(10));
}

// Boundary condition: minimal valid width (1)
TEST_F(ColumnWidthTest_47, WidthMinBoundary_47) {
    Column col = makeCol();
    col.width(1);
    EXPECT_EQ(col.width(), static_cast<std::size_t>(1));
}

// Normal operation: chaining width calls (and ensuring final value sticks)
TEST_F(ColumnWidthTest_47, WidthChaining_47) {
    Column col = makeCol();
    col.width(12).width(34);
    EXPECT_EQ(col.width(), static_cast<std::size_t>(34));
}

// Interface property: lvalue ref-qualified & return type is Column&
TEST_F(ColumnWidthTest_47, RefQualifierAndReturnType_47) {
    static_assert(std::is_same<width_lvalue_return_t_47<Column>, Column&>::value,
                  "Column::width(size_t) must return Column& for lvalues");
    SUCCEED(); // Keeps gtest happy at runtime; the check is compile-time.
}

// Interface property: calling width on an rvalue should be ill-formed
// (i.e., trait reports 'false' because the expression does not participate).
TEST_F(ColumnWidthTest_47, RvalueCallIsNotAllowed_47) {
    static_assert(!has_width_on_rvalue_47<Column>::value,
                  "Column::width(size_t) should NOT be invocable on rvalues");
    SUCCEED();
}

// Exceptional/error case (observable via debug assertion):
// In debug builds (no NDEBUG), width(0) should hit an assert.
TEST_F(ColumnWidthTest_47, WidthZeroTriggersAssertInDebug_47) {
#ifndef NDEBUG
    // Death tests must run in their own process; pattern can be anything.
    Column col = makeCol();
    ASSERT_DEATH({ col.width(0); }, ".*");
#else
    GTEST_SKIP() << "Skipping assert-based test in release builds (NDEBUG defined).";
#endif
}
