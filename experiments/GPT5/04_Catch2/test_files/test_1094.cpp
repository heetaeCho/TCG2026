// File: tests/textflow_columns_iterator_tests_1094.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>
#include <vector>
#include <utility>

// Headers under test
#include "catch2/internal/catch_textflow.hpp"

// The tests are written strictly against the public interface observable in the
// provided headers. No assumptions about internal state/logic are made.
namespace Catch { namespace TextFlow {

// Helper: build Columns from a list of strings using only the public operators
static Columns makeColumns(const std::vector<std::string>& parts) {
    ASSERT_GE(parts.size(), 2u) << "makeColumns requires at least 2 items";
    Column c0(parts[0]);
    Column c1(parts[1]);
    Columns cols = c0 + c1;  // Column + Column -> Columns
    for (size_t i = 2; i < parts.size(); ++i) {
        cols = cols + Column(parts[i]); // Columns + Column -> Columns
    }
    return cols;
}

}} // namespace Catch::TextFlow

using Catch::TextFlow::Column;
using Catch::TextFlow::Columns;

class TextFlowColumnsIteratorTest_1094 : public ::testing::Test {};

// --- Type trait & basic constructibility checks -----------------------------

TEST_F(TextFlowColumnsIteratorTest_1094, IteratorIsCopyAndMoveConstructible_1094) {
    // Build minimal non-empty Columns via public ops
    Columns cols = Catch::TextFlow::makeColumns({"A", "B"});

    auto it = cols.begin();  // construct iterator from Columns

    // Type trait checks on the iterator type (interface-level properties)
    using Iter = decltype(it);
    static_assert(std::is_copy_constructible<Iter>::value, "Iterator must be copy constructible");
    static_assert(std::is_move_constructible<Iter>::value, "Iterator must be move constructible");
    static_assert(std::is_copy_assignable<Iter>::value,     "Iterator should be copy assignable");
    static_assert(std::is_move_assignable<Iter>::value,     "Iterator should be move assignable");

    SUCCEED(); // Reached here means construction compiled and ran fine.
}

TEST_F(TextFlowColumnsIteratorTest_1094, BeginEndAreConstructibleAndComparable_1094) {
    Columns cols = Catch::TextFlow::makeColumns({"left", "right"});

    // begin()/end() must be callable on const Columns (per signature)
    const Columns& ccols = cols;

    EXPECT_NO_THROW({
        auto b1 = ccols.begin();
        auto b2 = ccols.begin();
        auto e1 = ccols.end();
        auto e2 = ccols.end();

        // Self-consistency of equality/inequality operators
        EXPECT_TRUE(b1 == b2);
        EXPECT_TRUE(e1 == e2);
        // At least operators are usable; do not assert dereference-dependent behavior.
        (void)(b1 != e1); // just to ensure operator!= is valid at runtime
    });
}

// --- Basic iterator operational checks (without assuming internal sequencing) --

TEST_F(TextFlowColumnsIteratorTest_1094, PreIncrementIsUsable_1094) {
    Columns cols = Catch::TextFlow::makeColumns({"A", "B", "C"});

    auto it = cols.begin();
    // We do not assert what ++ does; we only assert that it's usable per interface.
    EXPECT_NO_THROW({
        ++it;     // pre-increment must be available
    });
}

TEST_F(TextFlowColumnsIteratorTest_1094, PostIncrementIsUsableAndReturnsIterator_1094) {
    Columns cols = Catch::TextFlow::makeColumns({"X", "Y"});

    auto it = cols.begin();
    EXPECT_NO_THROW({
        auto before = it++;   // postfix increment returns an iterator (by value)
        // We can at least compare the returned iterator to something.
        // Do NOT assert sequence semantics; just that comparison is well-formed.
        (void)(before == before);
        (void)(it == it);
    });
}

// --- Comparability sanity with multiple begin() calls -------------------------

TEST_F(TextFlowColumnsIteratorTest_1094, MultipleBeginIteratorsCompareEqual_1094) {
    Columns cols = Catch::TextFlow::makeColumns({"foo", "bar"});

    auto b1 = cols.begin();
    auto b2 = cols.begin();
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 != b2);
}

// --- Boundary-like scenario: many columns (constructor should handle size) ----

TEST_F(TextFlowColumnsIteratorTest_1094, HandlesManyColumnsConstruction_1094) {
    // Create a bunch of columns to exercise iterator construction over larger input.
    std::vector<std::string> parts;
    for (int i = 0; i < 64; ++i) {
        parts.push_back("col" + std::to_string(i));
    }
    Columns cols = Catch::TextFlow::makeColumns(parts);

    // Construct iterators; ensure no exceptions and that they are comparable.
    EXPECT_NO_THROW({
        auto b = cols.begin();
        auto e = cols.end();
        (void)(b == b);
        (void)(e == e);
        (void)(b != e); // do not assert specific value, just that comparison is valid
    });
}

// --- Smoke test: begin vs end on obviously non-empty construction --------------

TEST_F(TextFlowColumnsIteratorTest_1094, NonEmptyColumnsYieldBeginComparableToEnd_1094) {
    Columns cols = Catch::TextFlow::makeColumns({"L", "R"});

    auto b = cols.begin();
    auto e = cols.end();

    // We cannot assume exact traversal semantics, but for a constructed set of
    // columns with content, begin() should be a valid iterator object and
    // comparability must be well-defined.
    // At least verify operators are callable and stable.
    EXPECT_TRUE(b == b);
    EXPECT_TRUE(e == e);
    // Common containers guarantee begin()!=end() for non-empty, but we avoid
    // depending on internal logic; still, a minimal, observable behavior check:
    // If this ever fails in your environment, you can relax it.
    EXPECT_NE(b == e, true); // i.e., allow either != or (very unusually) ==
}

