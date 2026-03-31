#include <sstream>
#include <vector>
#include <string>

#include "catch2/reporters/catch_reporter_console.cpp"
#include "catch2/catch_all.hpp"

#include <gtest/gtest.h>

using namespace Catch;

class TablePrinterTest_757 : public ::testing::Test {
protected:
    std::ostringstream oss;
    
    std::vector<ColumnInfo> makeDefaultColumns() {
        std::vector<ColumnInfo> cols;
        ColumnInfo col;
        col.name = "Column1";
        col.width = 10;
        col.justification = ColumnInfo::Left;
        cols.push_back(col);
        return cols;
    }
};

// Test that close() on a not-yet-opened TablePrinter does not write anything
TEST_F(TablePrinterTest_757, CloseWithoutOpenDoesNothing_757) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    // close without opening - should not write anything
    printer.close();
    
    EXPECT_TRUE(oss.str().empty());
}

// Test that close() after open() writes output to the stream
TEST_F(TablePrinterTest_757, CloseAfterOpenWritesToStream_757) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    printer.open();
    std::string afterOpen = oss.str();
    
    printer.close();
    std::string afterClose = oss.str();
    
    // After close, there should be additional content written (at least a newline)
    EXPECT_GT(afterClose.size(), afterOpen.size());
    // The close should end with a newline
    EXPECT_FALSE(afterClose.empty());
    EXPECT_EQ(afterClose.back(), '\n');
}

// Test that calling close() twice does not write extra output
TEST_F(TablePrinterTest_757, DoubleCloseDoesNotWriteExtraOutput_757) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    printer.open();
    printer.close();
    std::string afterFirstClose = oss.str();
    
    printer.close();
    std::string afterSecondClose = oss.str();
    
    // Second close should be a no-op since m_isOpen is already false
    EXPECT_EQ(afterFirstClose, afterSecondClose);
}

// Test that columnInfos returns the correct columns after close
TEST_F(TablePrinterTest_757, ColumnInfosPreservedAfterClose_757) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    printer.open();
    printer.close();
    
    auto const& returnedCols = printer.columnInfos();
    ASSERT_EQ(returnedCols.size(), cols.size());
    EXPECT_EQ(returnedCols[0].name, cols[0].name);
}

// Test close with multiple columns
TEST_F(TablePrinterTest_757, CloseWithMultipleColumns_757) {
    std::vector<ColumnInfo> cols;
    ColumnInfo col1;
    col1.name = "Col1";
    col1.width = 10;
    col1.justification = ColumnInfo::Left;
    cols.push_back(col1);
    
    ColumnInfo col2;
    col2.name = "Col2";
    col2.width = 15;
    col2.justification = ColumnInfo::Right;
    cols.push_back(col2);
    
    TablePrinter printer(oss, cols);
    
    printer.open();
    printer.close();
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

// Test open-close-open-close cycle
TEST_F(TablePrinterTest_757, OpenCloseOpenCloseCycle_757) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    printer.open();
    printer.close();
    std::string afterFirstCycle = oss.str();
    
    printer.open();
    printer.close();
    std::string afterSecondCycle = oss.str();
    
    // Second cycle should produce additional output
    EXPECT_GT(afterSecondCycle.size(), afterFirstCycle.size());
}

// Test close on printer with empty column vector
TEST_F(TablePrinterTest_757, CloseWithEmptyColumns_757) {
    std::vector<ColumnInfo> emptyCols;
    TablePrinter printer(oss, emptyCols);
    
    // Should not crash even with empty columns
    printer.close();
    EXPECT_TRUE(oss.str().empty());
}
