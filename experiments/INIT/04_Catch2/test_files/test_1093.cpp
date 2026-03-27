// File: tests/test_textflow_column_iterator_1093.cpp

#include <gtest/gtest.h>
#include <string>

// Adjust include path to match your project structure.
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

namespace {

// Safety helper: iterate up to a sane cap so tests cannot hang if a bug
// created a non-terminating iterator sequence.
constexpr int kMaxLinesSafetyCap = 10'000;

} // namespace

// 1) Boundary: empty string should produce no lines.
TEST(TextFlow_ColumnIterator_1093, EmptyString_YieldsBeginEqEnd_1093) {
    Column col{std::string{""}};
    auto b = col.begin();
    auto e = col.end();
    EXPECT_EQ(b, e);
}

// 2) Normal: single short line -> one element, then end.
TEST(TextFlow_ColumnIterator_1093, SingleShortLine_OneElementThenEnd_1093) {
    Column col{std::string{"hi"}};
    auto it = col.begin();
    auto e  = col.end();

    ASSERT_NE(it, e) << "Non-empty input should yield at least one line";

    // Dereference should yield a non-empty, printable line
    const std::string first = *it;
    EXPECT_FALSE(first.empty());

    // Increment once should finish the sequence for a short single line
    ++it;
    EXPECT_EQ(it, e);
}

// 3) Normal: begin on non-empty must be dereferenceable and stable before increment.
TEST(TextFlow_ColumnIterator_1093, BeginIsDereferenceable_1093) {
    Column col{std::string{"some text"}};
    auto it = col.begin();
    auto e  = col.end();

    ASSERT_NE(it, e);
    const std::string line = *it;
    EXPECT_FALSE(line.empty());
}

// 4) Wrapping/width stress (observable): with a narrow width, iteration should terminate
// and yield >= 2 chunks for a longer text. We do NOT assert specific wrapping logic.
TEST(TextFlow_ColumnIterator_1093, NarrowWidth_IteratesMultipleLinesAndTerminates_1093) {
    Column col{std::string{"abcdef"}};
    // Use the fluent API exposed on Column to adjust width.
    // We do not assume how width affects content — only that iteration remains valid.
    col.width(3);

    auto it = col.begin();
    auto e  = col.end();

    int lineCount = 0;
    for (; it != e && lineCount < kMaxLinesSafetyCap; ++it) {
        const std::string line = *it;
        // Each produced line must be dereferenceable and not empty
        EXPECT_FALSE(line.empty());
        ++lineCount;
    }
    EXPECT_LT(lineCount, kMaxLinesSafetyCap) << "Iterator did not terminate";
    EXPECT_GE(lineCount, 2) << "Narrow width over longer text should likely yield multiple lines";
    EXPECT_EQ(it, e);
}

// 5) Indentation knobs should not cause crashes or invalid iteration.
// We do not assert on exact spaces or formatting — only that iteration is valid and terminates.
TEST(TextFlow_ColumnIterator_1093, IndentAndInitialIndent_DoNotCrashAndIterate_1093) {
    Column col{std::string{"line one\nline two"}};

    // Exercise the public configuration surface. We do not assume exact behavior.
    col.width(20).indent(2).initialIndent(4);

    auto it = col.begin();
    auto e  = col.end();

    int lineCount = 0;
    for (; it != e && lineCount < kMaxLinesSafetyCap; ++it) {
        const std::string line = *it;
        EXPECT_FALSE(line.empty());
        ++lineCount;
    }
    EXPECT_LT(lineCount, kMaxLinesSafetyCap);
    EXPECT_GT(lineCount, 0);
    EXPECT_EQ(it, e);
}

// 6) Large indent relative to width is still a valid (public) configuration path.
// We only assert that construction+iteration does not UB/crash and terminates.
TEST(TextFlow_ColumnIterator_1093, LargeIndentConfiguration_RemainsIterable_1093) {
    Column col{std::string{"x y z"}};
    col.width(10).indent(9).initialIndent(9);

    auto it = col.begin();
    auto e  = col.end();

    int lineCount = 0;
    for (; it != e && lineCount < kMaxLinesSafetyCap; ++it) {
        const std::string line = *it;
        EXPECT_FALSE(line.empty());
        ++lineCount;
    }
    EXPECT_LT(lineCount, kMaxLinesSafetyCap);
    EXPECT_GE(lineCount, 1);
    EXPECT_EQ(it, e);
}

// 7) Iterator post-increment returns previous position (basic iterator law).
// We avoid asserting on string content details; we only check observable iterator semantics.
TEST(TextFlow_ColumnIterator_1093, PostIncrement_SemanticsHold_1093) {
    Column col{std::string{"abc def ghi"}};
    col.width(5);

    auto it = col.begin();
    auto e  = col.end();
    ASSERT_NE(it, e);

    auto before = it;
    auto post   = it++; // post-increment returns old iterator

    // The returned iterator should compare equal to the pre-increment position.
    EXPECT_TRUE(post == before);

    // The incremented iterator should move forward (unless there was only one line).
    // We only assert that after consuming the whole range we reach end.
    int steps = 1; // we already advanced once above
    for (; it != e && steps < kMaxLinesSafetyCap; ++it, ++steps) {
        (void)*it; // ensure dereferenceable
    }
    EXPECT_LT(steps, kMaxLinesSafetyCap);
    EXPECT_EQ(it, e);
}

