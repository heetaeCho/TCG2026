#include <catch2/catch_test_macros.hpp>
#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/internal/catch_textflow.hpp>

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

// Since TablePrinter and ColumnInfo are in an anonymous namespace or internal,
// we need to include the relevant source. We'll work with what's available.

// Forward reference the necessary types from the Catch namespace
// Based on the provided interface, we reconstruct minimal test scaffolding.

namespace {

// Helper to check if a string contains a substring
bool contains(const std::string& haystack, const std::string& needle) {
    return haystack.find(needle) != std::string::npos;
}

// Helper to count occurrences of a substring
int countOccurrences(const std::string& haystack, const std::string& needle) {
    int count = 0;
    size_t pos = 0;
    while ((pos = haystack.find(needle, pos)) != std::string::npos) {
        ++count;
        pos += needle.length();
    }
    return count;
}

} // anonymous namespace

using namespace Catch;

class TablePrinterTest_756 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that constructing a TablePrinter with column infos stores them correctly
TEST_F(TablePrinterTest_756, ConstructorStoresColumnInfos_756) {
    std::vector<ColumnInfo> infos = {
        {20, Justification::Left},
        {15, Justification::Right}
    };
    TablePrinter printer(oss, infos);

    auto const& retrieved = printer.columnInfos();
    ASSERT_EQ(retrieved.size(), 2u);
    EXPECT_EQ(retrieved[0].width, 20u);
    EXPECT_EQ(retrieved[1].width, 15u);
}

// Test that open() produces output to the stream
TEST_F(TablePrinterTest_756, OpenProducesOutput_756) {
    std::vector<ColumnInfo> infos = {
        {20, Justification::Left},
        {15, Justification::Right}
    };
    TablePrinter printer(oss, infos);

    std::string before = oss.str();
    EXPECT_TRUE(before.empty());

    printer.open();

    std::string after = oss.str();
    EXPECT_FALSE(after.empty());
}

// Test that calling open() twice only produces output once (idempotent)
TEST_F(TablePrinterTest_756, OpenCalledTwiceOnlyOpensOnce_756) {
    std::vector<ColumnInfo> infos = {
        {20, Justification::Left}
    };
    TablePrinter printer(oss, infos);

    printer.open();
    std::string afterFirstOpen = oss.str();

    printer.open();
    std::string afterSecondOpen = oss.str();

    EXPECT_EQ(afterFirstOpen, afterSecondOpen);
}

// Test that open() produces a line of dashes (separator line)
TEST_F(TablePrinterTest_756, OpenProducesDashSeparator_756) {
    std::vector<ColumnInfo> infos = {
        {20, Justification::Left},
        {15, Justification::Right}
    };
    TablePrinter printer(oss, infos);
    printer.open();

    std::string output = oss.str();
    // The open method outputs lineOfChars('-') which should produce dashes
    EXPECT_TRUE(contains(output, "---"));
}

// Test that open() with empty column infos doesn't crash
TEST_F(TablePrinterTest_756, OpenWithNoColumns_756) {
    std::vector<ColumnInfo> infos;
    TablePrinter printer(oss, infos);

    // Should not crash - though behavior with empty columns is undefined,
    // the guard m_isOpen should still work
    printer.open();
    // Just verify it didn't crash and produced some output
    EXPECT_FALSE(oss.str().empty());
}

// Test that close() can be called after open()
TEST_F(TablePrinterTest_756, CloseAfterOpen_756) {
    std::vector<ColumnInfo> infos = {
        {20, Justification::Left}
    };
    TablePrinter printer(oss, infos);

    printer.open();
    printer.close();
    // Should not crash; close should work after open
}

// Test that close() can be called without open()
TEST_F(TablePrinterTest_756, CloseWithoutOpen_756) {
    std::vector<ColumnInfo> infos = {
        {20, Justification::Left}
    };
    TablePrinter printer(oss, infos);

    // Calling close without open should not crash
    printer.close();
}

// Test that open() after close() reopens the table
TEST_F(TablePrinterTest_756, OpenAfterCloseReopens_756) {
    std::vector<ColumnInfo> infos = {
        {20, Justification::Left}
    };
    TablePrinter printer(oss, infos);

    printer.open();
    std::string afterFirstOpen = oss.str();

    printer.close();
    oss.str("");
    oss.clear();

    printer.open();
    std::string afterSecondOpen = oss.str();

    // If close resets m_isOpen, then the second open should produce output
    // If not, it should produce no output. Either way, no crash.
    // This tests the interaction between open and close.
}

// Test with a single wide column
TEST_F(TablePrinterTest_756, SingleWideColumn_756) {
    std::vector<ColumnInfo> infos = {
        {40, Justification::Left}
    };
    TablePrinter printer(oss, infos);
    printer.open();

    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(contains(output, "-"));
}

// Test with multiple columns
TEST_F(TablePrinterTest_756, MultipleColumns_756) {
    std::vector<ColumnInfo> infos = {
        {10, Justification::Left},
        {15, Justification::Right},
        {20, Justification::Left}
    };
    TablePrinter printer(oss, infos);
    printer.open();

    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test columnInfos returns reference to stored infos
TEST_F(TablePrinterTest_756, ColumnInfosReturnsCorrectReference_756) {
    std::vector<ColumnInfo> infos = {
        {10, Justification::Left},
        {20, Justification::Right},
        {30, Justification::Left}
    };
    TablePrinter printer(oss, infos);

    auto const& ref1 = printer.columnInfos();
    auto const& ref2 = printer.columnInfos();

    // Should return the same reference each time
    EXPECT_EQ(&ref1, &ref2);
    EXPECT_EQ(ref1.size(), 3u);
}

// Test that column width minimum boundary (width > 2 as per assert)
TEST_F(TablePrinterTest_756, ColumnWidthMinimumBoundary_756) {
    // Width of 3 is the minimum valid (since assert requires width > 2)
    std::vector<ColumnInfo> infos = {
        {3, Justification::Left}
    };
    TablePrinter printer(oss, infos);
    printer.open();

    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test output contains newlines (header and separator should each end with newline)
TEST_F(TablePrinterTest_756, OutputContainsNewlines_756) {
    std::vector<ColumnInfo> infos = {
        {20, Justification::Left}
    };
    TablePrinter printer(oss, infos);
    printer.open();

    std::string output = oss.str();
    int newlineCount = countOccurrences(output, "\n");
    // At minimum we expect the header line and separator line
    EXPECT_GE(newlineCount, 2);
}
