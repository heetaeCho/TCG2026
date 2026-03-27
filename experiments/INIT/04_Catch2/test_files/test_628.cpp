// File: columns_plus_move_operator_tests_628.cpp
#include <gtest/gtest.h>
#include <sstream>

// Assume the production headers are available on include path
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;
using Catch::TextFlow::Columns;

namespace {

// Helper: count elements in a container via its const begin()/end()
template <typename Container>
size_t Count(const Container& c) {
    using std::begin;
    using std::end;
    return static_cast<size_t>(std::distance(c.begin(), c.end()));
}

} // namespace

// --- Normal operation: rvalue Columns + rvalue Column appends one Column
TEST(TextFlow_ColumnsPlusMove_628, RvaluePlusRvalue_AppendsOne_628) {
    // Start from two Columns created via Column + Column (yields Columns)
    Columns base = Column("A") + Column("B");
    ASSERT_EQ(Count(base), 2u) << "Precondition: base should contain 2 columns";

    // Target under test: Columns&& + Column&&
    Columns result = std::move(base) + Column("C");

    // Observable effect: result now contains 3 columns
    EXPECT_EQ(Count(result), 3u);
    // (We do not read/use 'base' after move.)
}

// --- Boundary: empty text column appended via rvalue API is still a column
TEST(TextFlow_ColumnsPlusMove_628, AppendingEmptyTextStillCountsAsColumn_628) {
    Columns base = Column("X") + Column("Y");
    ASSERT_EQ(Count(base), 2u);

    Columns result = std::move(base) + Column(""); // empty text column
    EXPECT_EQ(Count(result), 3u);
}

// --- Chaining: multiple successive rvalue additions work as expected
TEST(TextFlow_ColumnsPlusMove_628, ChainedRvalueAppendsIncreaseCount_628) {
    Columns result = std::move( Column("one") + Column("two") ) + Column("three");
    EXPECT_EQ(Count(result), 3u);

    // Add one more through the same rvalue path
    Columns result2 = std::move(result) + Column("four");
    EXPECT_EQ(Count(result2), 4u);
}

// --- Observable formatting: stream output contains all added column texts
// (We do not depend on exact layout/spacing/line wrapping.)
TEST(TextFlow_ColumnsPlusMove_628, OstreamOutputContainsAllColumnTexts_628) {
    Columns cols = std::move( Column("Hello") + Column("World") ) + Column("Catch2");

    std::ostringstream os;
    os << cols; // uses public operator<<(ostream&, const Columns&)

    const std::string s = os.str();
    // We only assert presence of substrings, not formatting specifics.
    EXPECT_NE(s.find("Hello"), std::string::npos);
    EXPECT_NE(s.find("World"), std::string::npos);
    EXPECT_NE(s.find("Catch2"), std::string::npos);
}

// --- Idempotence with respect to counts: starting from 1, add once via rvalue
TEST(TextFlow_ColumnsPlusMove_628, SingleBaseColumnThenAppendOnce_628) {
    // Build Columns from two Columns created out of one Column repeated scenario:
    Columns base = Column("only") + Column(""); // 2 columns (text content irrelevant)
    ASSERT_EQ(Count(base), 2u);

    Columns r = std::move(base) + Column("extra");
    EXPECT_EQ(Count(r), 3u);
}

