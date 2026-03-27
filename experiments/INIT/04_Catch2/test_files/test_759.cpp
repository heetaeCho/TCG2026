// File: tests/table_printer_columnbreak_759.cpp

#include <gtest/gtest.h>
#include <sstream>

// Use the public Catch2 reporter console header that declares TablePrinter, ColumnInfo, ColumnBreak, Justification.
#include <catch2/reporters/catch_reporter_console.hpp>

using namespace Catch;

namespace {
// Small helper to assert suffixes without caring about any table
// prologue that TablePrinter::open() might emit.
::testing::AssertionResult EndsWith(const std::string& whole, const std::string& suffix) {
    if (whole.size() < suffix.size()) {
        return ::testing::AssertionFailure()
               << "String too short. whole.size()=" << whole.size()
               << " < suffix.size()=" << suffix.size();
    }
    if (whole.compare(whole.size() - suffix.size(), suffix.size(), suffix) == 0) {
        return ::testing::AssertionSuccess();
    }
    return ::testing::AssertionFailure()
           << "Suffix mismatch.\nExpected suffix: [" << suffix << "]\nActual tail:   ["
           << whole.substr(whole.size() - suffix.size()) << "]";
}
}

// ------------------------
// Fixture
// ------------------------
class TablePrinterOperatorTest_759 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Convenience builders for columns.
    static ColumnInfo LeftCol(int width, std::string name = "L") {
        ColumnInfo c;
        c.name = std::move(name);
        c.width = width;
        c.justification = Justification::Left;
        return c;
    }
    static ColumnInfo RightCol(int width, std::string name = "R") {
        ColumnInfo c;
        c.name = std::move(name);
        c.width = width;
        c.justification = Justification::Right;
        return c;
    }
};

// Left justification: padding appears *after* the cell content, then a single space.
// Padding is computed as (width - (len + 1)) when positive.
TEST_F(TablePrinterOperatorTest_759, LeftJustificationPads_759) {
    // width = 10, content "abc" (len=3) -> (3+1)=4 -> padding=6 -> "abc" + 6*' ' + ' '
    TablePrinter tp{ os, { LeftCol(10) } };

    tp << "abc" << ColumnBreak{};

    const std::string expected_tail = std::string("abc") + std::string(6, ' ') + ' ';
    EXPECT_TRUE(EndsWith(os.str(), expected_tail));
}

// Right justification: padding appears *before* the cell content, then a single space.
TEST_F(TablePrinterOperatorTest_759, RightJustificationPads_759) {
    // width = 8, content "xy" (len=2) -> (2+1)=3 -> padding=5 -> 5*' ' + "xy" + ' '
    TablePrinter tp{ os, { RightCol(8) } };

    tp << "xy" << ColumnBreak{};

    const std::string expected_tail = std::string(5, ' ') + "xy" + ' ';
    EXPECT_TRUE(EndsWith(os.str(), expected_tail));
}

// No padding when (len + 1) >= width — only the trailing single space is emitted.
TEST_F(TablePrinterOperatorTest_759, NoPaddingWhenContentTooLong_759) {
    // width = 3, content "abcd" (len=4) -> (4+1)=5 !< 3 -> no padding -> "abcd" + ' '
    TablePrinter tp{ os, { LeftCol(3) } };

    tp << "abcd" << ColumnBreak{};

    const std::string expected_tail = std::string("abcd") + ' ';
    EXPECT_TRUE(EndsWith(os.str(), expected_tail));
}

// When the last column is broken, a newline is emitted, and the next cell starts a new row.
TEST_F(TablePrinterOperatorTest_759, NewlineAtEndOfRowAndContinue_759) {
    // Two columns: [Left width 6][Right width 5]
    TablePrinter tp{ os, { LeftCol(6, "A"), RightCol(5, "B") } };

    // Fill first row completely -> expect newline at the end.
    tp << "foo" << ColumnBreak{};   // col 0
    tp << "bar" << ColumnBreak{};   // col 1 -> should end row with '\n'

    std::string out = os.str();
    ASSERT_FALSE(out.empty());

    // The very last character after finishing the row should be '\n'.
    EXPECT_EQ(out.back(), '\n');

    // Now continue with the next row: first column again — should NOT append a newline (not last column).
    tp << "next" << ColumnBreak{};
    out = os.str();
    ASSERT_FALSE(out.empty());
    EXPECT_NE(out.back(), '\n'); // we should be mid-row now

    // And finishing the second row should end with newline again.
    tp << "row2" << ColumnBreak{};
    out = os.str();
    ASSERT_FALSE(out.empty());
    EXPECT_EQ(out.back(), '\n');
}
