// File: tableprinter_rowbreak_tests_760.cpp
#include <gtest/gtest.h>
#include <sstream>

// Include the implementation unit so we can test the internal helper types
// This path matches your repo layout from the prompt.
#include "Catch2/src/catch2/reporters/catch_reporter_console.cpp"

using namespace ::testing;

namespace {

// Simple helper to construct a TablePrinter with 2 columns.
// We only rely on the public, observable behavior on the output stream.
auto makeTablePrinter(std::ostream& os) {
    std::vector<ColumnInfo> cols = {
        { "c1", 8, ColumnInfo::Left },
        { "c2", 8, ColumnInfo::Left }
    };
    return TablePrinter(os, cols);
}

} // namespace

// [Normal] Calling RowBreak on a fresh TablePrinter does not write anything
// because no columns have been started yet (observable: stream unchanged).
TEST(TablePrinterRowBreakTest_760, RowBreakOnFreshPrinter_WritesNothing_760) { // TEST_ID = 760
    std::ostringstream oss;
    auto tp = makeTablePrinter(oss);

    const auto before = oss.str();
    tp << RowBreak();
    const auto after = oss.str();

    // Observable behavior: no extra newline (indeed, no output at all).
    EXPECT_EQ(after, before);
}

// [Boundary] After exactly one ColumnBreak (current column index == 0),
// RowBreak should NOT append a newline (observable: stream size unchanged
// by the RowBreak call).
TEST(TablePrinterRowBreakTest_760, RowBreakWhenCurrentColumnIsZero_NoNewline_760) { // TEST_ID = 760
    std::ostringstream oss;
    auto tp = makeTablePrinter(oss);

    tp << ColumnBreak();                  // advance to first column
    const auto sizeBeforeRB = oss.str().size();
    tp << RowBreak();                     // condition in impl is (> 0), so no newline
    const auto sizeAfterRB  = oss.str().size();

    EXPECT_EQ(sizeAfterRB, sizeBeforeRB) << "RowBreak should not add newline at column 0";
}

// [Normal] After advancing to second column (current column index > 0),
// RowBreak appends exactly one newline (observable: last char is '\n' and
// size increases by exactly 1 due to the RowBreak call).
TEST(TablePrinterRowBreakTest_760, RowBreakWhenCurrentColumnGreaterThanZero_AppendsNewline_760) { // TEST_ID = 760
    std::ostringstream oss;
    auto tp = makeTablePrinter(oss);

    tp << ColumnBreak() << ColumnBreak(); // now current column index > 0
    const auto sizeBeforeRB = oss.str().size();

    tp << RowBreak();

    const auto s = oss.str();
    ASSERT_EQ(s.size(), sizeBeforeRB + 1) << "RowBreak should add exactly one character";
    EXPECT_EQ(s.back(), '\n') << "RowBreak should append a newline";
}

// [Interaction] RowBreak resets the column so that a subsequent ColumnBreak
// starts a new row (observable: the very next character written by ColumnBreak
// is the row-leading '|' that prefixes a new row).
TEST(TablePrinterRowBreakTest_760, RowBreakResetsToNewRow_NextColumnBreakStartsWithBar_760) { // TEST_ID = 760
    std::ostringstream oss;
    auto tp = makeTablePrinter(oss);

    // Get into a row (write at least one column), then RowBreak.
    tp << ColumnBreak() << ColumnBreak();
    tp << RowBreak();
    const auto posBeforeNext = oss.str().size();

    // First write into the next row:
    tp << ColumnBreak();

    const auto s = oss.str();
    ASSERT_GT(s.size(), posBeforeNext) << "ColumnBreak should write something after RowBreak";
    EXPECT_EQ(s[posBeforeNext], '|') << "New row should be prefixed by '|' after RowBreak";
}
