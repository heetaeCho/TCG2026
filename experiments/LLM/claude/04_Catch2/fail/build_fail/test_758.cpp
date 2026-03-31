#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

// Include necessary Catch2 headers
#include "catch2/reporters/catch_reporter_console.cpp"
#include "catch2/catch_all.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"

// If ColumnInfo is not directly accessible, we may need to define or include it
// Based on Catch2 source, ColumnInfo typically has name, width, and justification

using namespace Catch;

class TablePrinterTest_758 : public ::testing::Test {
protected:
    std::ostringstream oss;
    
    std::vector<ColumnInfo> makeDefaultColumns() {
        std::vector<ColumnInfo> cols;
        cols.push_back({"Column1", 20, ColumnInfo::Left});
        cols.push_back({"Column2", 15, ColumnInfo::Right});
        return cols;
    }
    
    std::vector<ColumnInfo> makeSingleColumn() {
        std::vector<ColumnInfo> cols;
        cols.push_back({"Single", 10, ColumnInfo::Left});
        return cols;
    }
};

TEST_F(TablePrinterTest_758, ConstructorWithColumns_758) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    ASSERT_EQ(printer.columnInfos().size(), 2u);
}

TEST_F(TablePrinterTest_758, ConstructorWithEmptyColumns_758) {
    std::vector<ColumnInfo> emptyCols;
    TablePrinter printer(oss, emptyCols);
    
    EXPECT_TRUE(printer.columnInfos().empty());
}

TEST_F(TablePrinterTest_758, ColumnInfosReturnsCorrectData_758) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    auto const& returnedCols = printer.columnInfos();
    EXPECT_EQ(returnedCols.size(), 2u);
    EXPECT_EQ(returnedCols[0].name, "Column1");
    EXPECT_EQ(returnedCols[1].name, "Column2");
}

TEST_F(TablePrinterTest_758, ColumnInfosPreservesWidth_758) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    auto const& returnedCols = printer.columnInfos();
    EXPECT_EQ(returnedCols[0].width, 20);
    EXPECT_EQ(returnedCols[1].width, 15);
}

TEST_F(TablePrinterTest_758, OpenDoesNotThrow_758) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    EXPECT_NO_THROW(printer.open());
}

TEST_F(TablePrinterTest_758, CloseDoesNotThrow_758) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    printer.open();
    EXPECT_NO_THROW(printer.close());
}

TEST_F(TablePrinterTest_758, OpenThenCloseSequence_758) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    EXPECT_NO_THROW(printer.open());
    EXPECT_NO_THROW(printer.close());
}

TEST_F(TablePrinterTest_758, StreamInsertionStringValue_758) {
    auto cols = makeSingleColumn();
    TablePrinter printer(oss, cols);
    
    printer.open();
    EXPECT_NO_THROW(printer << "hello");
}

TEST_F(TablePrinterTest_758, StreamInsertionIntegerValue_758) {
    auto cols = makeSingleColumn();
    TablePrinter printer(oss, cols);
    
    printer.open();
    EXPECT_NO_THROW(printer << 42);
}

TEST_F(TablePrinterTest_758, StreamInsertionChaining_758) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    printer.open();
    EXPECT_NO_THROW(printer << "value1" << 123);
}

TEST_F(TablePrinterTest_758, StreamInsertionReturnsReference_758) {
    auto cols = makeSingleColumn();
    TablePrinter printer(oss, cols);
    
    printer.open();
    TablePrinter& ref = (printer << "test");
    EXPECT_EQ(&ref, &printer);
}

TEST_F(TablePrinterTest_758, SingleColumnConstruction_758) {
    auto cols = makeSingleColumn();
    TablePrinter printer(oss, cols);
    
    EXPECT_EQ(printer.columnInfos().size(), 1u);
    EXPECT_EQ(printer.columnInfos()[0].name, "Single");
}

TEST_F(TablePrinterTest_758, MultipleOpenCloseCycles_758) {
    auto cols = makeDefaultColumns();
    TablePrinter printer(oss, cols);
    
    printer.open();
    printer.close();
    printer.open();
    printer.close();
    
    // Should not crash or throw
    SUCCEED();
}

TEST_F(TablePrinterTest_758, StreamInsertionDoubleValue_758) {
    auto cols = makeSingleColumn();
    TablePrinter printer(oss, cols);
    
    printer.open();
    EXPECT_NO_THROW(printer << 3.14);
}

TEST_F(TablePrinterTest_758, StreamInsertionEmptyString_758) {
    auto cols = makeSingleColumn();
    TablePrinter printer(oss, cols);
    
    printer.open();
    EXPECT_NO_THROW(printer << "");
}

TEST_F(TablePrinterTest_758, ColumnInfosIsConst_758) {
    auto cols = makeDefaultColumns();
    const TablePrinter printer(oss, cols);
    
    auto const& returnedCols = printer.columnInfos();
    EXPECT_EQ(returnedCols.size(), 2u);
}
