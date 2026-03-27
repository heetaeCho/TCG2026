#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_console.cpp"



using namespace Catch;



class TablePrinterTest_755 : public ::testing::Test {

protected:

    std::vector<ColumnInfo> columnInfos;

    std::ostringstream os;

    std::unique_ptr<TablePrinter> tablePrinter;



    void SetUp() override {

        columnInfos = { ColumnInfo("Column1"), ColumnInfo("Column2") };

        tablePrinter = std::make_unique<TablePrinter>(os, columnInfos);

    }

};



TEST_F(TablePrinterTest_755, ColumnInfosReturnsCorrectReference_755) {

    const auto& returnedColumnInfos = tablePrinter->columnInfos();

    EXPECT_EQ(&returnedColumnInfos, &tablePrinter->columnInfos());

}



TEST_F(TablePrinterTest_755, ColumnInfosContainsInitialColumns_755) {

    const auto& returnedColumnInfos = tablePrinter->columnInfos();

    EXPECT_EQ(returnedColumnInfos.size(), 2);

    EXPECT_EQ(returnedColumnInfos[0].name, "Column1");

    EXPECT_EQ(returnedColumnInfos[1].name, "Column2");

}



TEST_F(TablePrinterTest_755, OpenAndCloseDoNotThrow_755) {

    EXPECT_NO_THROW(tablePrinter->open());

    EXPECT_NO_THROW(tablePrinter->close());

}
