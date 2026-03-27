#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_console.cpp"

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch;

using ::testing::InSequence;



class TablePrinterTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    std::vector<ColumnInfo> columnInfos = {{10, Justification::Centre}, {15, Justification::Left}};

    TablePrinter tablePrinter{oss, columnInfos};

};



TEST_F(TablePrinterTest_756, OpenInitializesTableHeader_756) {

    tablePrinter.open();

    std::string expectedOutput = "        Column 0     |               Column 1          \n----------------------------------\n";

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(TablePrinterTest_756, OpenOnlyPrintsOnce_756) {

    tablePrinter.open();

    tablePrinter.open(); // Should not print again

    std::string expectedOutput = "        Column 0     |               Column 1          \n----------------------------------\n";

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(TablePrinterTest_756, OpenWithEmptyColumnsDoesNotCrash_756) {

    TablePrinter emptyTablePrinter{oss, {}};

    emptyTablePrinter.open();

    std::string expectedOutput = "\n-\n"; // Only the separator line is printed

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(TablePrinterTest_756, ColumnInfosReturnsCorrectData_756) {

    auto result = tablePrinter.columnInfos();

    ASSERT_EQ(result.size(), 2);

    EXPECT_EQ(result[0].width, 10);

    EXPECT_EQ(result[1].width, 15);

}



TEST_F(TablePrinterTest_756, CloseDoesNothingWithoutOpen_756) {

    tablePrinter.close();

    std::string expectedOutput = ""; // No output should be generated

    EXPECT_EQ(oss.str(), expectedOutput);

}
